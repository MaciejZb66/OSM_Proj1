#include "main.h"
unsigned long *ekran;
int last_x;
int last_y;

extern const bool Test1[]; 

int main(){
    last_x = 0;
    last_y = 0;
    printf("(  0)");
    Draw_flower(Spalony);
    printf("\n");
    return 0;
}

void Draw_flower(Kwiatek wyb)
{
    for(int y = 9; y < 128; y++){
        for(int x = 0; x < 240; x++){            
            if((Test1[(y - 9) * 240 + x])){
                SetPixel(ekran, x, y);
            }            
        }
    }
}

void SetPixel(unsigned long* aekran, int x, int y){
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