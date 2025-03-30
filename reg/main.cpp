#include "main.h"

int main(){
    float tp = 0.1;
    PID reg_one(10, 3, 0.9, tp);
    Inercja in1(1, tp, 5);
    Inercja in2(2, tp, 3);
    float expected = 10;
    float output = 0;
    for(int i = 0; i< 50; i++){
        reg_one.expected = expected;
        reg_one.input = output;
        output = reg_one.Reg_step();
        //in1.input = reg_one.Reg_step();
        //in2.input = in1.inercja_step();
        //output = in2.inercja_step();
        std::cout << i/10 << "." << i%10 << "\t" << output << "\n";
    }
    return 0;
}