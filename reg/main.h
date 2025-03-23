#pragma once

#include <iostream>

class PID{
    private:
    float Kp, Ti, Td, Ts, output;
    float last_i, last_input;
    public:
    float input, expected;

    PID(float kp, float ti, float td, float t){
        Kp = kp;
        Ti = ti;
        Td = td;
        Ts = t;
        last_i = 0;
        last_input = 0;
    }

    float Reg_step(){
        float P = Kp * (expected - input);
        float I = (Kp /Ti * Ts * (expected - input)) + last_i;
        float D = Kp * ((expected - input) - (expected - last_input))/Ts * Td;
        last_i = I;
        last_input = input;
        output = P + I + D;
        return output;
    }
};