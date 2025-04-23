#pragma once
#include "setup.h"
#include "drawhex.h"
#include "bitmaps.h"
#include "reg.h"

#define start 180
#define tp 0.1
#define wykres_char 7

extern unsigned long *ekran; // Adres obszaru graficznego LCD [8*128*2]

extern unsigned char *textEkran; // Adres obszaru tekstowego [40*16/2]


typedef enum{
    Spalony, Przegrzany, Normalny, Letni, Zimny, Brak
}Kwiatek;

typedef enum{
    Wykres_e, Obrazek_e
}Ekran;

void Draw_flower(Kwiatek wyb);
void Draw_info(int real_temp, int exp_temp, bool window);
void Change_data(char key,int* exp_temp, bool* window, Ekran* ekr);
void Draw(Ekran ekr, Kwiatek wyb);
void Draw_wykres();
void ClearScreen();
void Reg(int* real_temp, int* exp_temp, bool* window);
Kwiatek Choose_state(int temp);

class Wykres{
private:
    int last_temps_insert;
    char os_y_name[wykres_char];
    int* source_data;
public:
    int last_temps[220];
    Wykres(char* name, int* source){
        for(int i = 0; i< wykres_char; i++){
            os_y_name[i] = name[i];
        }
        last_temps_insert = 0;
        source_data = source;
    }

    void Draw(){
        if(last_temps_insert <219){
            last_temps[last_temps_insert] = *source_data;
            last_temps_insert++;
        }else{
            for(int i = 0 ;i < 219;i++){
                last_temps[i] = last_temps[i+1];
            }
            last_temps[219] = *source_data;
        }
    }

    void Show(){
        for(int i = 0; i< 220; i++){
            SetPixel(ekran, i+10, ((500-last_temps[i])/5)+20);
            SetPixel(ekran, i+10, 120);
            if (i < 100){
                SetPixel(ekran, 10, i+20);
            }
        }
        for(int i = 0; i < wykres_char; i++){
            PrintText(textEkran, os_y_name, 1, 39*i, i+4); //rzeŸba ale dzia³a
        }
    }
};
