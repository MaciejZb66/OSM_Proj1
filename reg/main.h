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
    double last_input, kp, tin ,ts, output;
    public:
    double input;
    Inercja(double k, double t, double ti){
        last_input = 0;
        kp = k;
        ts = t;
        tin = ti;
    }

    double inercja_step(){
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
    double m_out;
    double m_in;
    public:
    void setInput(double input){
        m_in=input;
    }

    void Calculate(){
        m_out=m_in;
    }

    double getOutput() {
        return m_out;
    }
};

class PID:public UAR {
    double m_Tp, m_Kp, m_Ki, m_Kd;
    double m_sum, m_Smin, m_Smax;
    double m_prevIn;
    public:
    PID(double Kp, double Ti, double Td,double Tp,double Smin,double Smax); 
    
    PID::PID(double Kp, double Ti, double Td,double Tp,double Smin,double Smax){
        m_Tp = Tp; m_Kp = Kp;
        m_Ki = Kp * Tp / Ti;
        m_Kd = Kp * Td / Tp;
        m_in = 0;
        m_prevIn = 0; m_out = 0;
        m_sum = 0;
        m_Smin=Smin; m_Smax=Smax;
    }
    PID::Calculate() {
        double deltaIn = m_in - m_prevIn;
        m_sum += m_in * m_Ki;
        if(m_sum>m_Smax) m_sum=m_Smax;
        if(m_sum<m_Smin) m_sum=m_Smin;
        m_out = m_sum + m_in * m_Kp + deltaIn * m_Kd; 
    }
};

class InercModel : public UAR {
    double m_pole;
    public:
    InercModel(double pole);
    InercModel::InercModel(double pole) {
        m_pole = pole;
        m_in = 0;
        m_out = 0; 
    }
    InercModel::Calculate( ) {
        m_out = m_out * m_pole + (1 - m_pole) * m_in; 
    }
};

*/

