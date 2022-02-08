
#ifndef PWM_H
#define PWM_H

class PWM3
{
    private:
        float voltage_power_supply;
        float voltage_limit;
        float dc_a,dc_b,dc_c;
        float Ua,Ub,Uc;
    public:
        PWM3(void);
        void setPwm(float, float, float);
        void writeDutyCycle3PWM(float, float, float);
};

#endif
