
#include "bee.h"
#ifndef CONFIG_H_
#define CONFIG_H_

#define CLOCK_DIV_ENABLE                            (1<<CLKPCE)
#define CLOCK_DIV_1                                 (0<<CLKPCE) | (0<<CLKPS3) | (0<<CLKPS2) | (0<<CLKPS1) | (0<<CLKPS0)
        
#define CONFIG_CLOCK()                              {CLKPR=CLOCK_DIV_ENABLE; CLKPR=CLOCK_DIV_1;}

/* NOKIA 5110 */   

#define RST                                         0
#define D_C                                         1

#define DIR_NOKIA                                   DDRB
#define PORT_NOKIA                                  PORTB

#define SCE                                         2 
#define DIN                                         3
#define SCLK                                        5

#define DIR_SPI                                     DDRB
#define PORT_SPI                                    PORTB

/* Button */

#define UP                                          0
#define DOWN                                        2
#define MAIN                                        1

#define DIR_BT                                      DDRD
#define PIN_BT                                      PIND

/* ADC Channel */

#define CHANNEL_0                                   0

#define RESOLUTION                                  1024
#define V_REF                                       5
#define SCALE_SENSOR                                100

/* Led */

#define LED                                         4

#define DIR_LED                                     DDRD
#define PORT_LED                                    PORTD

#endif
