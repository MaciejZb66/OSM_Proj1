#include "main.h"
unsigned long *ekran;
int last_x;
int last_y;

extern const bool Test1[]; 
//extern const int Test2[];
extern const int brak[];
extern const int czarny[];
extern const int kolejny[];
extern const int normalny[];
extern const int przegrzany[];
extern const int spalony[];

int buffer[1785];

int main(){
    
    for(int i = 0; i<6; i++){
        last_x = 0;
        last_y = 0;
        printf("(  0)");
        Draw_flower((Kwiatek)i);
        printf("\n\n");
    }
    
    return 0;
}

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
                        if((kolejny[(y - 9) * 15 + x])&0x0001 << b){
                            SetPixel(ekran, 16 * x + 15 - b, y);
                        }
                        break;
                    case Zimny:
                        if((czarny[(y - 9) * 15 + x])&0x0001 << b){
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

void Draw_flower2(Kwiatek wyb) //bool board
{
    for(int y = 9; y < 128; y++){
        for(int x = 0; x < 240; x++){            
            if((Test1[(y - 9) * 240 + x])){
                SetPixel(ekran, x, y);
            }            
        }
    }
}

void Draw_buffer()
{
    for(int y = 9; y < 128; y++){
        for(int x = 0; x < 15; x++){    
            for(int b = 15; b >= 0; b--){
                if((buffer[(y - 9) * 15 + x])&0x0001 << b){
                    SetPixel(ekran, 16 * x + 15 - b, y);
                } 
            }
        }
    }
}

void SetPixel(unsigned long* aekran, int x, int y){ //my simulation in terminal
    bool newline = false;
    do{
        if(y > last_y){
            printf("\n(%3d)", last_y + 1);
            last_y++;
            newline = true;
        }  
    }while(y > last_y);
    if(newline){
        for(int i = 0; i < x; i++){
            printf(" ");
        }
        printf("#");
    }else{
        for (int i = last_x; i < x - 1; i++)
        {
            printf(" ");
        }
        printf("#");
    }
    last_x = x;
    last_y = y;    
}