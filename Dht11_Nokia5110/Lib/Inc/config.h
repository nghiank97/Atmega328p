
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

/* DHT11 */

#define DP_DHT11                                    3

#define DP_DIR                                      DDRD
#define DP_PORT                                     PORTD
#define DP_PIN                                      PIND

#endif
