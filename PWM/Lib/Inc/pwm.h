
#ifndef PWM_H_
#define PWM_H_
#include "config.h"

typedef enum{
    PWM_PD3 = 0,
    PWM_PD5 = 1,
    PWM_PD6 = 2,

    PWM_PB1 = 3,
    PWM_PB2 = 4,
    PWM_PB3 = 5

} PWM_PIN;

extern void pwm_put(PWM_PIN pin,int value);

#endif