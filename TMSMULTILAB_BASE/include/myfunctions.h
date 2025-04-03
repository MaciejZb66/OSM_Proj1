#pragma once
#include "setup.h"
#include "stdbool.h"
#include "drawhex.h"
#include "bitmaps.h"
#include "reg.h"

typedef enum{
    Spalony, Przegrzany, Normalny, Letni, Zimny, Brak
}Kwiatek;

typedef enum{
    Wykres, Obrazek
}Ekran;

void Draw_flower(Kwiatek wyb);
void Draw_info(int real_temp, int exp_temp, bool window);
void Change_data(char key,int* exp_temp, bool* window, Ekran* ekr);
void Draw(Ekran ekr, Kwiatek wyb);
void ClearScreen();
