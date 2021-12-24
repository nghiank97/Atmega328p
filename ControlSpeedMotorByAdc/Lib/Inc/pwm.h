
#ifndef PWM_H_
#define PWM_H_
#include "config.h"

#if defined(PWM_1)

extern void pwm_init(void);
extern void pwm_put(int duty);

#elif defined(PWM_2)

extern void pwm_init(void);
extern void pwm_put(uint8_t duty);
#endif
#endif


