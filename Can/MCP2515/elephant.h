
#ifndef ELEPHANT_H_
#define ELEPHANT_H_

#ifndef F_CPU
#define F_CPU                                       16000000
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define delay_ms(t)                                 _delay_ms(t)
#define delay_us(t)                                 _delay_us(t)

#define CLOCK_DIV_ENABLE                            (1<<CLKPCE)
#define CLOCK_DIV_1                                 (0<<CLKPCE) | (0<<CLKPS3) | (0<<CLKPS2) | (0<<CLKPS1) | (0<<CLKPS0)
        
#define CONFIG_EXTERNAL_CLOCK()                     {CLKPR=CLOCK_DIV_ENABLE; CLKPR=CLOCK_DIV_1;}

typedef enum                {OFF,ON}                flask;
typedef enum                {LOW,HIGH}              level;

#include "serial.h"
#include "mcp2515.h"
#include "mcp2515_map.h"
#include "mcp2515_config.h"

#endif
