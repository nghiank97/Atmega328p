
#ifndef BLDC_H_
#define BLDC_H_

// sign function
#define _sign(a) ( ( (a) < 0 )  ?  -1   : ( (a) > 0 ) )
#define _round(x) ((x)>=0?(long)((x)+0.5f):(long)((x)-0.5f))
#define _constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))
#define _sqrt(a) (_sqrtApprox(a))
#define _isset(a) ( (a) != (NOT_SET) )
#define _UNUSED(v) (void) (v)

// utility defines

#define _2_SQRT3    1.15470053838f
#define _SQRT3      1.73205080757f
#define _1_SQRT3    0.57735026919f
#define _SQRT3_2    0.86602540378f
#define _SQRT2      1.41421356237f
#define _120_D2R    2.09439510239f
#define _PI         3.14159265359f
#define _PI_2       1.57079632679f
#define _PI_3       1.0471975512f
#define _2PI        6.28318530718f
#define _3PI_2      4.71238898038f
#define _PI_6       0.52359877559f

#include <stdint.h>

void pwm_init(PWM_PIN pin, uint16_t value);
void pwm_write(PWM_PIN pin, uint16_t value);
extern void bldc_init(void);
float _sin(float a);
float _cos(float a);
float normalizeAngle(float angle);
void writeDutyCycle3PWM(float dc_a,  float dc_b, float dc_c);
void setPwm(float Ua, float Ub, float Uc);
extern void bldc_move_sine_pwm(float Uq, float Ud, float angle_el);

#endif
