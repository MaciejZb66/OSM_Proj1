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

class Inercja{
    private:
    float last_input, kp, tin ,ts, output;
    public:
    float input;
    Inercja(float k, float t, float ti){
        last_input = 0;
        kp = k;
        ts = t;
        tin = ti;
    }

    float inercja_step(){
        //local out =  (Tp / (5 + Tp)) * enter + (5 / (5 + Tp)) * last           -- 1/(5s+1)
        //local out = ((Tp / (3 + Tp)) * enter + (3 / (3 + Tp)) * last/2)*2     -- 2/(3s+1)
        output = ((ts / (tin + ts)) * input + (tin / (tin + ts)) * last_input/kp)*kp;
        last_input = input;
        return output;
    }
};