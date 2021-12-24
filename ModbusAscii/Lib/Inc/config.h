
#include "bee.h"
#ifndef CONFIG_H_
#define CONFIG_H_

#define CLOCK_DIV_ENABLE                            _bv(CLKPCE)
#define CLOCK_DIV_1                                 (0<<CLKPCE) | (0<<CLKPS3) | (0<<CLKPS2) | (0<<CLKPS1) | (0<<CLKPS0)
        
#define CONFIG_CLOCK()                              {CLKPR=CLOCK_DIV_ENABLE; CLKPR=CLOCK_DIV_1;}

#define BAUD_RATE                                   9600
#define BAUD_PRESCALE                               (uint16_t)((F_CPU/16/BAUD_RATE) - 1)

/* LCD */

//#define LCD16x2
// #define LCD20x4
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

#define CHANNEL_0                                   0
#define CHANNEL_1                                   1
#define CHANNEL_2                                   2
#define CHANNEL_3                                   3

#define RESOLUTION                                  1024
#define V_REF                                       5

/* Coil */

#define COIL_0										0
#define COIL_1										1
#define COIL_2										2
#define COIL_3										3

#define DIR_COIL									DDRB
#define PORT_COIL									PORTB

/* Input */

#define BUTTON_0									4
#define BUTTON_1									5

#define DIR_BUTTON									DDRB
#define PIN_BUTTON									PINB

#endif
