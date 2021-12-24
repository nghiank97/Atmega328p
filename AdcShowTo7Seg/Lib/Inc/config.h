
#include "bee.h"
#ifndef CONFIG_H_
#define CONFIG_H_

#define CLOCK_DIV_ENABLE                            (1<<CLKPCE)
#define CLOCK_DIV_1                                 (0<<CLKPCE) | (0<<CLKPS3) | (0<<CLKPS2) | (0<<CLKPS1) | (0<<CLKPS0)

#define CONFIG_CLOCK()                              {CLKPR=CLOCK_DIV_ENABLE; CLKPR=CLOCK_DIV_1;}
#define CONFIG_CLOCK_8RC()                          {CLKPR=CLOCK_DIV_ENABLE; CLKPR=(0<<CLKPS3) | (0<<CLKPS2) | (1<<CLKPS1) | (0<<CLKPS0);}

#define BAUD_RATE                                   9600
#define BAUD_PRESCALE                               (uint16_t)((F_CPU/16/BAUD_RATE) - 1)

/* 7 seg */
#define DIR_DATA_7SEG                               DDRB                                   
#define PORT_DATA_7SEG                              PORTB                                

#define SELECT_1                                    2
#define SELECT_2                                    3
#define SELECT_3                                    4
#define SELECT_4                                    5

#define DIR_SELECT_7SEG                             DDRD                  
#define PORT_SELECT_7SEG                            PORTD         

/* ADC Channel */

#define CHANNEL_0                                   0

#define RESOLUTION                                  1024
#define V_REF                                       5
#define SCALE_SENSOR                                100

#endif
