#pragma once
/* Idiot notes
generate bitmap on https://notisrac.github.io/FileToCArray/
copy (only values) to input.txt
run: lua correct.lua
copy res.txt to draw.h or other included header file
build: g++ main.cpp
run in terminal (max 9 font) ./a.out
*/
#include <iostream>
#include <stdbool.h>
#include "draw.h"
#include "drawhex.h"

typedef enum{
    Spalony, Przegrzany, Normalny, Zimny, Brak
}Kwiatek;

void Draw_flower(Kwiatek wyb);
void Draw_flower2(Kwiatek wyb);
void SetPixel(unsigned long* aekran, int x, int y);