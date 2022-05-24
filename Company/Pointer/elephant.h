
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

#define delay_ms(t)                                 _delay_ms(t)
#define delay_us(t)                                 _delay_us(t)

#endif