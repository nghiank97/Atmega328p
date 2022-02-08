
#ifndef DEFAULTS_H
#define DEFAULTS_H
#include "bee.h"

#ifndef F_CPU                           
#define F_CPU                                       16000000
#endif

#define delay_ms(t)                                 _delay_ms(t)
#define delay_us(t)                                 _delay_us(t)

#define CLOCK_DIV_ENABLE                            bv(CLKPCE)

#define CONFIG_EXTERNAL_CLOCK()                     {CLKPR=CLOCK_DIV_ENABLE; CLKPR=(0<<CLKPCE) | (0<<CLKPS3) | (0<<CLKPS2) | (0<<CLKPS1) | (0<<CLKPS0);}
#define CONFIG_8Mhz_CLOCK()                         {CLKPR=CLOCK_DIV_ENABLE; CLKPR=(0<<CLKPCE) | (0<<CLKPS3) | (0<<CLKPS2) | (1<<CLKPS1) | (0<<CLKPS0);}

#define sbi(port,pin)                               (port |= (1<<pin))
#define cbi(port,pin)                               (port &= ~(1<<pin))
#define bv(pin)                                     (1<<pin)
#define bit_is_clear(port,pin)                      (!(port&(1<<pin)))
#define bit_is_set(port,pin)                        (port&(1<<pin))
#define bit_clear(port,pin)                         cbi(port,pin)
#define bit_set(port,pin)                           sbi(port,pin)

#define _write(port,pin,S)                          (S==1 ? sbi(port,pin): cbi(port,pin))  
#define _read(port,pin)                             ((port&(1<<pin))==0x00 ? 0:1)
#define set_output(port,pin)                        sbi(port,pin)
#define set_input(port,pin)                         cbi(port,pin)
typedef enum level{
    LOW = 0,
    HIGH = 1
};

#define _sign(a)                                    ( ( (a) < 0 )  ?  -1   : ( (a) > 0 ) )
#define _round(x)                                   ((x)>=0?(long)((x)+0.5f):(long)((x)-0.5f))
#define _constrain(amt,low,high)                    ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))
#define _sqrt(a)                                    (_sqrtApprox(a))
#define _isset(a)                                   ( (a) != (NOT_SET) )
#define _UNUSED(v)                                  (void) (v)

#define _2_SQRT3                                    1.15470053838f
#define _SQRT3                                      1.73205080757f
#define _1_SQRT3                                    0.57735026919f
#define _SQRT3_2                                    0.86602540378f
#define _SQRT2                                      1.41421356237f
#define _120_D2R                                    2.09439510239f
#define _PI                                         3.14159265359f
#define _PI_2                                       1.57079632679f
#define _PI_3                                       1.0471975512f
#define _2PI                                        6.28318530718f
#define _3PI_2                                      4.71238898038f
#define _PI_6                                       0.52359877559f

struct DQVoltage_s
{
    float d;
    float q;
};

enum Direction_s{
    UNKNOWN = 0,
    CW      = 1,
    CCW     = -1,
};

float _sin(float a);
float _cos(float a);
float _normalizeAngle(float angle);
float _electricalAngle(float shaft_angle, int pole_pairs);
float _sqrtApprox(float value);

#endif