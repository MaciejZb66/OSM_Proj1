#include "bitmaps.h"

void Draw_last(double temp){
    Kwiatek kw;
    if(temp < 8.3){
        kw = Brak_k;
    }else if(temp < 16.6){
        kw = Zimny_k;
    }else if(temp < 25.0){
        kw = Letni_k;
    }else if(temp < 33.3){
        kw = Normalny_k;
    }else if(temp < 41.6){
        kw = Przegrzany_k;
    }else{
        kw = Spalony_k;
    }   
    
    switch(kw){
        case Brak_k:
            Draw_csv(brak);
            break;
        case Zimny_k:
            Draw_csv(zimny);
            break;
        case Letni_k:
            Draw_csv(letni);
            break;
        case Normalny_k:
            Draw_csv(normalny);
            break;
        case Przegrzany_k:
            Draw_csv(przegrzany);
            break;
        case Spalony_k:
            Draw_csv(spalony);
            break;
    }
}

void Draw_csv(const int* kw){
    std::fstream file("draw.csv");
    for(int y = 9; y < 128; y++){
        for(int x = 0; x < 15; x++){
            for(int b = 15; b >= 0; b--){         
                if(kw[(y - 9) * 15 + x]&(0x0001 << b)){
                    file << "1";
                }else{
                    file << "0";
                }
                if(x == 14 && b == 0){
                    file << "\n";
                }else{
                    file << ", ";
                }
            }      
        }
    }
    do{

    }while(!file.good());    
    file.close();
}