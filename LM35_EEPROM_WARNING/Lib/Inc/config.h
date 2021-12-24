
#include "bee.h"
#ifndef CONFIG_H_
#define CONFIG_H_

#define CLOCK_DIV_ENABLE()                          {CLKPR=(1<<CLKPCE);}
#define CLOCK_DIV_1()                               {CLKPR=(0<<CLKPCE) | (0<<CLKPS3) | (0<<CLKPS2) | (0<<CLKPS1) | (0<<CLKPS0);}

#define CONFIG_EXTER_CLOCK()                        {CLOCK_DIV_ENABLE();CLOCK_DIV_1();}

#define BAUD_RATE                                   9600
#define BAUD_PRESCALE                               (uint16_t)((F_CPU/16/BAUD_RATE) - 1)

/* LCD */

//#define LCD16x2
// #define LCD20x4
#define LCD16x4
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

/* ADC Channel */

#define CHANNEL_0                                   0

#define RESOLUTION                                  1024
#define V_REF                                       5
#define SCALE_SENSOR                                100

/* Button */

#define UP_BUTTON                                   2
#define DOWN_BUTTON                                 3
#define DIR_BUTTON                                  DDRD
#define PIN_BUTTON                                  PIND

#endif