#pragma once

#include <iostream>
#include "reg2.h"

class PID{
    private:
    float Kp, Ti, Td, Ts, output;
    float limit_h, limit_l;
    float last_i, last_input, last_expected;
    public:
    float input, expected;

    PID(float kp, float ti, float td, float t){
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

    float Reg_step() {
        // Obliczenie członów regulatora PID
        float P = Kp * (expected - input);  // Proporcjonalny
        float I = (Kp / Ti) * Ts * (expected - input) + last_i;  // Całkujący
        float D = Kp * ((expected - input) - (last_expected - last_input)) / (Ts * Td);  // Róniczkujący
        printf("P: %2.2f,\tI: %2.2f,\tD: %2.2f\t\t",P, I, D);
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

//kod z wykładu
/*
class UAR
{
    float m_out;
    float m_in;
    public:
    void setInput(float input){
        m_in=input;
    }

    void Calculate(){
        m_out=m_in;
    }

    float getOutput() {
        return m_out;
    }
};

class PID:public UAR {
    float m_Tp, m_Kp, m_Ki, m_Kd;
    float m_sum, m_Smin, m_Smax;
    float m_prevIn;
    public:
    PID(float Kp, float Ti, float Td,float Tp,float Smin,float Smax); 
    
    PID::PID(float Kp, float Ti, float Td,float Tp,float Smin,float Smax){
        m_Tp = Tp; m_Kp = Kp;
        m_Ki = Kp * Tp / Ti;
        m_Kd = Kp * Td / Tp;
        m_in = 0;
        m_prevIn = 0; m_out = 0;
        m_sum = 0;
        m_Smin=Smin; m_Smax=Smax;
    }
    PID::Calculate() {
        float deltaIn = m_in - m_prevIn;
        m_sum += m_in * m_Ki;
        if(m_sum>m_Smax) m_sum=m_Smax;
        if(m_sum<m_Smin) m_sum=m_Smin;
        m_out = m_sum + m_in * m_Kp + deltaIn * m_Kd; 
    }
};

class InercModel : public UAR {
    float m_pole;
    public:
    InercModel(float pole);
    InercModel::InercModel(float pole) {
        m_pole = pole;
        m_in = 0;
        m_out = 0; 
    }
    InercModel::Calculate( ) {
        m_out = m_out * m_pole + (1 - m_pole) * m_in; 
    }
};

*/

