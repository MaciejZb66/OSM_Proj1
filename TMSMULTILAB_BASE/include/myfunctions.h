#pragma once
#include "setup.h"
#include "stdbool.h"

typedef enum{
    Spalony, Przegrzany, Normalny, Zimny, Brak
}Kwiatek;

void Draw_flower(Kwiatek wyb);
void Draw_info(int real_temp, int exp_temp, bool window);
void Change_data(char key,int* exp_temp, bool* window);
