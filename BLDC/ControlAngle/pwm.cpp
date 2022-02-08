#include "pwm.h"

PWM3::PWM3(void)
{
    DDRB |= (1 << 1);
    DDRB |= (1 << 2);
    DDRB |= (1 << 3);

    TCCR1A = 0b10100001;
    TCCR1B = 0b00000000 | (0x01);

    TCCR2A = 0b10000001;
    TCCR2B = 0b00000000 | (0x01);

    voltage_power_supply = 24.0f;
    voltage_limit = 24.0f;
    Ua = 0.0f;
    Ub = 0.0f;
    Uc = 0.0f;
    dc_a = 0.0f;
    dc_b = 0.0f;
    dc_c = 0.0f;
}

void PWM3::writeDutyCycle3PWM(float _dc_a, float _dc_b, float _dc_c)
{
    OCR1AH = 0;
    OCR1AL = (uint8_t)255.0f * _dc_a;

    OCR1BH = 0;
    OCR1BL = (uint8_t)255.0f * _dc_b;

    OCR2A = (uint8_t)255.0f * _dc_c;
}

void PWM3::setPwm(float _Ua, float _Ub, float _Uc)
{
    Ua = _constrain(_Ua, 0.0f, voltage_limit);
    Ub = _constrain(_Ub, 0.0f, voltage_limit);
    Uc = _constrain(_Uc, 0.0f, voltage_limit);
    dc_a = _constrain(Ua / voltage_power_supply, 0.0f, 1.0f);
    dc_b = _constrain(Ub / voltage_power_supply, 0.0f, 1.0f);
    dc_c = _constrain(Uc / voltage_power_supply, 0.0f, 1.0f);
    writeDutyCycle3PWM(dc_a, dc_b, dc_c);
}
