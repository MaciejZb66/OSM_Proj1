#pragma once

#include <iostream>
#include "reg2.h"

class PID{
    private:
    double Kp, Ti, Td, Ts, output;
    double limit_h, limit_l;
    double last_i, last_input, last_expected;
    public:
    double input, expected;

    PID(double kp, double ti, double td, double t){
        Kp = kp;
        Ti = ti;
        Td = td;
        Ts = t;
        last_i = 0;
        last_input = 0;
        last_expected = 0;
        limit_h = 15;
        limit_l = 0;
    }

    double Reg_step() {
        // Obliczenie członów regulatora PID
        double P = Kp * (expected - input);  // Proporcjonalny
        double I = (Kp / Ti) * Ts * (expected - input) + last_i;  // Całkujący
        double D = Kp * ((expected - input) - (last_expected - last_input)) / (Ts * Td);  // Róniczkujący
        printf("P: %2.2f,\tI: %2.2f,\tD: %2.2f  \t",P, I, D);
        // Zaktualizowanie zmiennych stanu
        last_i = I;
        last_input = input;
        last_expected = expected;

        // Obliczenie całkowitego wyjścia
        output = P + I + D;
        if (output > limit_h){
            I = I - (output - limit_h);
            output = P + I + D;
        }
        if (output < limit_l){
            I = I - (output - limit_l);
            output = P + I + D;
        }
        if (output < 0.0001 && output > -0.0001) output = 0;
        return output;
    }

};

class Inercja{
    private:
    double last_output, kp, tin ,ts, output;
    public:
    double input;
    Inercja(double k, double t, double ti){
        last_output = 0;
        kp = k;
        ts = t;
        tin = ti;
    }

    double inercja_step(){
        //local out =  (Tp / (5 + Tp)) * enter + (5 / (5 + Tp)) * last          -- 1/(5s+1)
        //local out = ((Tp / (3 + Tp)) * enter + (3 / (3 + Tp)) * last/2)*2     -- 2/(3s+1)
        output = ((ts / (tin + ts)) * input + (tin / (tin + ts)) * last_output/kp)*kp;
        last_output = output;
        return output;
    }
};



