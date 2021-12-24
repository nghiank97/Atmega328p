
#ifndef SERVO_H_
#define SERVO_H_
#include "config.h"

// static void pwm_put(int angle){
//     float time = (float)angle/180;
//     _set(PORT_SERVO,SERVO_PIN);
//     delay_ms(1+time);
//     _clr(PORT_SERVO,SERVO_PIN);
//     delay_ms(20-time);
// }


extern void servo_init(void);
extern void servo_put(int angle);

#endif