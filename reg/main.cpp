#include "main.h"

#define struct

int main(){
    float tp = 0.01;
    #ifndef struct
        PID reg_one(10, 3, 0.9, tp);
        Inercja in1(1, tp, 5);
        Inercja in2(2, tp, 3);
    #endif
    #ifdef struct
        PID_s pid;
        Inercja_s in3;
        Inercja_s in4;
        PID_s_init(&pid, 10, 3, 0.9, tp);
        Inercja_s_init(&in3, 1, tp, 5);
        Inercja_s_init(&in4, 2, tp, 3);
    #endif
    float expected = 0;
    float output = 0;
    #ifndef struct
        for(int i = 0; i< 50; i++){
            reg_one.expected = expected;
            reg_one.input = output;
            output = reg_one.Reg_step();
            //in1.input = reg_one.Reg_step();
            //in2.input = in1.inercja_step();
            //output = in2.inercja_step();
            std::cout << i/10 << "." << i%10 << "\t" << output << "\n";
            output = 0;
            expected = 10;
        }
    #endif
    #ifdef struct
        for(int i = 0; i< 100; i++){
            pid.expected = expected;
            pid.input = output;
            Reg_s_step(&pid);
            //output = pid.output;
            in3.input = pid.output;
            Inercja_s_step(&in3);
            in4.input = in3.output;
            Inercja_s_step(&in4);
            output =  in4.output;
            std::cout << i/10 << "." << i%10 << "\t" << output << "\n";
            output = 0;
            expected = 1;
        }
    #endif
    return 0;
}