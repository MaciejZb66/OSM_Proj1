#pragma once
#include "setup.h"
#include "drawhex.h"
#include "bitmaps.h"
#include "reg.h"

#define start 180
#define tp 0.1
#define wykres_char 6

extern unsigned long *ekran; // Adres obszaru graficznego LCD [8*128*2]

extern unsigned char *textEkran; // Adres obszaru tekstowego [40*16/2]


typedef enum{
    Spalony, Przegrzany, Normalny, Letni, Zimny, Brak
}Kwiatek;

typedef enum{
    Wykres_err_e, Wykres_real_e, Wykres_reg_e, Obrazek_e
}Ekran;

void Draw_flower(Kwiatek wyb);
void Draw_info(int real_temp, int exp_temp, bool window);
void Change_data(char key,int* exp_temp, bool* window, Ekran* ekr);
void Draw(Ekran ekr, Kwiatek wyb);
void Draw_wykres();
void ClearScreen();
void Reg(int* real_temp, int* exp_temp, int* err_temp, bool* window);
Kwiatek Choose_state(int temp);

class Wykres{
private:
    int last_temps_insert;
    char os_y_name[wykres_char];
    char os_x_name[4];
    int* source_data;
public:
    int last_temps[220];
    Wykres(char* name, int* source){
        for(int i = 0; i< wykres_char; i++){
            os_y_name[i] = name[i];
            if(sizeof(name) + 1<i){
                os_y_name[i] = 0x20;
            }
        }
        os_x_name[0] = 0x74;
        os_x_name[1] = 0x69;
        os_x_name[2] = 0x6d;
        os_x_name[3] = 0x65;
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
        //data
        for(int i = 0; i< 220; i++){
            SetPixel(ekran, i+15, ((500-last_temps[i])/5)+20);
            SetPixel(ekran, i+15, 120);
            if (i < 100){
                SetPixel(ekran, 15, i+20);
            }
        }
        //value 50
        for(int i=13; i<18;i++){
            SetPixel(ekran,i,20);
        }
        textEkran[40*2]=0x35;
        textEkran[40*2+1]=0x30;
        //value 20
        for(int i=13; i<18;i++){
            SetPixel(ekran,i,80);
        }
        textEkran[40*10]=0x32;
        textEkran[40*10+1]=0x30;
        //value 10
        for(int i=13; i<18;i++){
            SetPixel(ekran,i,100);
        }
        textEkran[40*12]=0x31;
        textEkran[40*12+1]=0x30;
        //y name
        for(int i = 0; i < wykres_char; i++){
            textEkran[40*(i+4)]=os_y_name[i];
        }
        //x name
        PrintText(textEkran,os_x_name,4,20,15);

    }
};
