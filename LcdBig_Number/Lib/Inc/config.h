
#include "bee.h"
#ifndef CONFIG_H_
#define CONFIG_H_

#define CLOCK_DIV_ENABLE()                          {CLKPR=(1<<CLKPCE);}
#define CLOCK_DIV_1()                               {CLKPR=(0<<CLKPCE) | (0<<CLKPS3) | (0<<CLKPS2) | (0<<CLKPS1) | (0<<CLKPS0);}

#define CONFIG_EXTER_CLOCK()                        {CLOCK_DIV_ENABLE();CLOCK_DIV_1();}

//#define LCD16x2
#define LCD16x2
#define RS_LCD                                      0
//#define RW_LCD                                      1
#define EN_LCD                                      1
#define PORT_CONTROL_LCD                            PORTB
#define DIR_CONTROL_LCD                             DDRB

#define FIR_LCD                                     2
#define SEC_LCD                                     3
#define THI_LCD                                     4
#define FOR_LCD                                     5
#define PORT_DATA_LCD                               PORTB
#define DIR_DATA_LCD                                DDRB

#endif