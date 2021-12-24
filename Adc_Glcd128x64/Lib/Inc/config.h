
#include "bee.h"
#ifndef CONFIG_H_
#define CONFIG_H_

#define CLOCK_DIV_ENABLE                            _bv(CLKPCE)
#define CLOCK_DIV_1                                 (0<<CLKPCE) | (0<<CLKPS3) | (0<<CLKPS2) | (0<<CLKPS1) | (0<<CLKPS0)
        
#define CONFIG_CLOCK()                              {CLKPR=CLOCK_DIV_ENABLE; CLKPR=CLOCK_DIV_1;}

//----------------------------------GLCD---------------------------------------------

#define EN_GLCD                                     2
#define RW_GLCD                                     1
#define RS_GLCD                                     0
#define CS2_GLCD                                    4
#define CS1_GLCD                                    3

#define DIR_CONTROL_GLCD                            DDRB
#define PORT_CONTROL_GLCD                           PORTB
#define PIN_CONTROL_GLCD                            PINB

#define DIR_DATA_GLCD                               DDRD
#define PORT_DATA_GLCD                              PORTD
#define PIN_DATA_GLCD                               PIND

/* ADC */

#define CHANNEL_0                                   0

#define RESOLUTION                                  1024
#define V_REF                                       5

#endif
