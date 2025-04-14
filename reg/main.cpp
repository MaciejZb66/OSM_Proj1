#include "main.h"

int main(){
    double tp = 0.1;
    double start = 18;
    int is_window_open = 0;
    PID reg_one(10, 3, 0.9, tp, start);
    Inercja in1(1, tp, 7, start);
    Inercja in2(1, tp, 5, start);
    //Inercja in3(0.4, tp, 0.2, start);
    PID in3(0.8, 0, 0, tp, start);
    double expected = start;
    double output = start;
    std::fstream file("result_creg.csv");
    file << std::fixed << std::setprecision(2); // Set precision for floating-point numbers
    file <<"Wsp. x,\tWsp. y1,\tWsp. y2,\tZak\n";
    for(double i = 0; i< 40; i+=tp){
        reg_one.expected = expected;
        reg_one.input = output;
        //output = reg_one.Reg_step();
        // in1.input = expected;
        // output = in1.inercja_step();
        in1.input = reg_one.Reg_step();
        if(is_window_open != 0){
            in2.input = in1.inercja_step() - in3.Reg_step();
        }else{
            in2.input = in1.inercja_step();
        }        
        output = in2.inercja_step();
        in3.input = output - start;
        //std::cout << i << "\t" << in1.input << "\t" << output << "\n";
        
        file << std::setprecision(1) <<i << ",\t" << std::setprecision(2) << reg_one.output << ",\t" << std::setprecision(4) << output << ",\t" << is_window_open<< "\n";
        // printf("Time: %.2f\tR: %.2f \t O: %.4f\n",i,in1.input,output);
        expected = 28;
        if (i > 20) is_window_open = 1;
    }
    do{

    }while(!file.good());    
    file.close();
    std::cout << "ok\n";
    return 0;
}