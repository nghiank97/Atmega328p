
#include "bee.h"
#ifndef CONFIG_H_
#define CONFIG_H_

#define CLOCK_DIV_ENABLE                            _bv(CLKPCE)
#define CLOCK_DIV_1                                 (0<<CLKPCE) | (0<<CLKPS3) | (0<<CLKPS2) | (0<<CLKPS1) | (0<<CLKPS0)
        
#define CONFIG_CLOCK()                              {CLKPR=CLOCK_DIV_ENABLE; CLKPR=CLOCK_DIV_1;}

/* LCD */

#define LCD16x4

#define RS_LCD                                      2
//#define RW_LCD                                      1
#define EN_LCD                                      3
#define PORT_CONTROL_LCD                            PORTD
#define DIR_CONTROL_LCD                             DDRD

#define FIR_LCD                                     4
#define SEC_LCD                                     5
#define THI_LCD                                     6
#define FOR_LCD                                     7
#define PORT_DATA_LCD                               PORTD
#define DIR_DATA_LCD                                DDRD

/* ADC Channel */

#endif
