#include "myfunctions.h"

//extern unsigned long *ekran;
//extern unsigned char *textEkran;
extern const int Test2[];
extern const int Test3[];
//extern int last_temps[];


int exp_temp = start;
int real_temp = start;

PID reg_one(10, 3, 0.9, tp, start);
Inercja in1(1, tp, 7, start);
Inercja in2(1, tp, 5, start);
PID in3(0.8, 0, 0, tp, start);
char buf[7] = "real";
Wykres real(&buf[0], &real_temp);

void Draw_flower(Kwiatek wyb) //texas int (16 bit) board
{
    for(int y = 9; y < 128; y++){
        for(int x = 0; x < 15; x++){
            for(int b = 15; b >= 0; b--){
                switch (wyb){
                    case Spalony:
                        if((spalony[(y - 9) * 15 + x])&0x0001 << b){
                            SetPixel(ekran, 16 * x + 15 - b, y);
                        }
                        break;
                    case Przegrzany:
                        if((przegrzany[(y - 9) * 15 + x])&0x0001 << b){
                            SetPixel(ekran, 16 * x + 15 - b, y);
                        }
                        break;
                    case Normalny:
                        if((normalny[(y - 9) * 15 + x])&0x0001 << b){
                            SetPixel(ekran, 16 * x + 15 - b, y);
                        }
                        break;

                    case Letni:
                        if((letni[(y - 9) * 15 + x])&0x0001 << b){
                            SetPixel(ekran, 16 * x + 15 - b, y);
                        }
                        break;
                    case Zimny:
                        if((zimny[(y - 9) * 15 + x])&0x0001 << b){
                            SetPixel(ekran, 16 * x + 15 - b, y);
                        }
                        break;
                    case Brak:
                        if((brak[(y - 9) * 15 + x])&0x0001 << b){
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
    if(real_temp > 500) real_temp = 500;
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
        if(*ekr == Obrazek_e){
            *ekr = Wykres_e;
        }else{
            *ekr = Obrazek_e;
        }
        break;
    }
}

void Draw(Ekran ekr, Kwiatek wyb){

    switch(ekr){
    case Wykres_e:
        real.Show();
        break;
    case Obrazek_e:
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
    reg_one.expected = (double)(*exp_temp);
    reg_one.input = (double)(*real_temp);
    in1.input = reg_one.Reg_step();
    if(*window){
        in2.input = in1.inercja_step() - in3.Reg_step();
    }else{
        in2.input = in1.inercja_step();
    }
    *real_temp = (int)in2.inercja_step();
    in3.input = (double)*real_temp - 180;
    real.Draw();

}

Kwiatek Choose_state(int temp){
    Kwiatek kw;
    if(temp < 83){
       kw = Brak;
    }else if(temp < 166){
       kw = Zimny;
    }else if(temp < 250){
       kw = Letni;
    }else if(temp < 333){
       kw = Normalny;
    }else if(temp < 416){
       kw = Przegrzany;
    }else{
       kw = Spalony;
    }
    return kw;
}




