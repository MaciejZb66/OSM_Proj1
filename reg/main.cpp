#include "main.h"

int main(){
    double tp = 0.1;
    double start = 18;
    PID reg_one(10, 3, 0.9, tp, start);
    Inercja in1(1, tp, 7, start);
    Inercja in2(1, tp, 5, start);
    //Inercja in3(0.4, tp, 1, start);
    double expected = start;
    double output = start;
    std::fstream file("result_creg.csv");
    file << std::fixed << std::setprecision(2); // Set precision for floating-point numbers
    file <<"Wsp. x,Wsp. y1,Wsp. y2\n";
    for(double i = 0; i< 40; i+=tp){
        reg_one.expected = expected;
        reg_one.input = output;
        //output = reg_one.Reg_step();
        // in1.input = expected;
        // output = in1.inercja_step();

        in1.input = reg_one.Reg_step();
        in2.input = in1.inercja_step();
        output = in2.inercja_step();
        //std::cout << i << "\t" << in1.input << "\t" << output << "\n";
        
        file << std::setprecision(1) <<i << ",\t" << std::setprecision(2) << in1.input << ",\t" << std::setprecision(4) << output << "\n";
        // printf("Time: %.2f\tR: %.2f \t O: %.4f\n",i,in1.input,output);
        expected = 28;
    }
    do{

    }while(!file.good());    
    file.close();
    std::cout << "ok\n";
    return 0;
}