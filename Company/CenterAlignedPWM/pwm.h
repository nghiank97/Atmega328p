
#ifndef PWM_H_
#define PWM_H_

typedef enum{
    PWM_PD3 = 0,
    PWM_PD5 = 1,
    PWM_PD6 = 2,

    PWM_PB1 = 3,
    PWM_PB2 = 4,
    PWM_PB3 = 5

} PWM_PIN;

extern void pwm_init(PWM_PIN pin,uint16_t value);
extern void pwm_write(PWM_PIN pin,uint16_t value);

#endif