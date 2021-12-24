
#ifndef BEE_H_
#define BEE_H_

#define F_CPU                                       16000000UL

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
#include <avr/pgmspace.h>
#include <stdio.h>


#define delay_ms(t)                                 _delay_ms(t)
#define delay_us(t)                                 _delay_us(t)

enum Interrupt{
    Enable = 1,
    Disable = 0
};

#endif
