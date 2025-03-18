#include "myfunctions.h"

extern unsigned long *ekran;
extern unsigned char *textEkran;

void Draw_flower(Kwiatek wyb)
{
    for(int y = 9; y < 128; y++){
        for(int x = 0; x < 240; x++){
            SetPixel(ekran, x, y);
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

void Change_data(char key,int* exp_temp, bool* window){

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
    }
}

void Reg(int* real_temp, int* exp_temp, bool* window){

}
