#include "myfunctions.h"

extern unsigned long *ekran;
extern unsigned char *textEkran;
extern const int Test2[];
extern const int Test3[];

void Draw_flower(Kwiatek wyb) //texas int (16 bit) board
{
    for(int y = 9; y < 128; y++){
        for(int x = 0; x < 15; x++){
            for(int b = 15; b >= 0; b--){
                switch (wyb){
                    case Spalony:
                        if((Test2[(y - 9) * 15 + x])&0x0001 << b){
                            SetPixel(ekran, 16 * x + 15 - b, y);
                        }
                        break;
                    case Przegrzany:
                        break;
                    case Normalny:
                        break;
                    case Letni:
                        break;
                    case Zimny:
                        break;
                    case Brak:
                        if((Test3[(y - 9) * 15 + x])&0x0001 << b){
                            SetPixel(ekran, 16 * x + 15 - b, y);
                        }
                        break;
                }

            }
        }
    }
}

void Draw_info(int real_temp, int exp_temp, bool window){
    unsigned char data[]= "Temp:  .  Set:  .  Okno: ";
    data[5] = real_temp / 100 + '0';
    data[6] = ((real_temp / 10) - (real_temp / 100 * 10)) + '0';
    data[8] = real_temp % 10 + '0';
    data[14] = exp_temp / 100 + '0';
    data[15] = ((exp_temp / 10) - (exp_temp / 100 * 10)) + '0';
    data[17] = exp_temp % 10 + '0';
    if(window){
        data[24] = '1';
    }else{
        data[24] = '0';
    }
    PrintText(textEkran, data, 25, 0, 0);
}

void Change_data(char key,int* exp_temp, bool* window, Ekran* ekr){

    switch (key){
    case 1:
        if((*exp_temp) <= 499){
            (*exp_temp)++;
        }
        break;
    case 2:
        if((*exp_temp) != 0){
            (*exp_temp)--;
        }
        break;
    case 3:
        *window = !(*window);
        break;
    case 4:
        if(*ekr == Obrazek){
            *ekr = Wykres;
        }else{
            *ekr = Obrazek;
        }
        break;
    }
}

void Draw(Ekran ekr, Kwiatek wyb){

    switch(ekr){
    case Wykres:
        Draw_flower(Brak);
        break;
    case Obrazek:
        Draw_flower(wyb);
        break;
    }
    for(int i = 0; i<240;i++){
        SetPixel(ekran, i, 8);
    }
}

void ClearScreen()
{
    for (int a = 0; a < (128 * 8); a++)
    ekran[a] = 0;
}

void Reg(int* real_temp, int* exp_temp, bool* window){

}
