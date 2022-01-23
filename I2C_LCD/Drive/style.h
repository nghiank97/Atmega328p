
#ifndef STYLE_H_
#define STYLE_H_

#define _set(PORT,PIN)                              (PORT |= (1<<PIN))
#define _clr(PORT,PIN)                              (PORT &= ~(1<<PIN))
#define _write(PORT,PIN,S)                          (S==1 ? _set(PORT,PIN): _clr(PORT,PIN))  
#define _read(PORT,PIN)                             ((PORT&(1<<PIN))==0x00 ? 0:1)
#define _toggle(PORT,PIN)                           ((PORT) ^=(1<<PIN))
#define _bv(PIN)                                    (1<<PIN)

typedef   signed            char    	            int8_t;
typedef   signed            int     	            int16_t;
typedef   signed long       int    		            int32_t;
typedef   unsigned          char    	            uint8_t;
typedef   unsigned 			int			            uint16_t;
typedef   unsigned long		int			            uint32_t;
typedef   float							            float32_t;

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>

#define delay_ms(t)                                 _delay_ms(t)
#define delay_us(t)                                 _delay_us(t)

#endif
