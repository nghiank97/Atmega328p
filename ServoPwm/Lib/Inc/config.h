
#include "bee.h"
#ifndef CONFIG_H_
#define CONFIG_H_

#define CLOCK_DIV_ENABLE()                          {CLKPR=(1<<CLKPCE);}
#define CLOCK_DIV_1()                               {CLKPR=(0<<CLKPCE) | (0<<CLKPS3) | (0<<CLKPS2) | (0<<CLKPS1) | (0<<CLKPS0);}

#define CONFIG_EXTER_CLOCK()                        {CLOCK_DIV_ENABLE();CLOCK_DIV_1();}

/* servo */
#define SERVO_PIN               1
#define DIR_SERVO               DDRB
#define PORT_SERVO              PORTB

#endif