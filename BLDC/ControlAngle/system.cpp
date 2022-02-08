#include "system.h"

volatile unsigned long timer0_overflow_count = 0;

ISR(TIMER0_OVF_vect)
{
	timer0_overflow_count++;
}

void tim_init(void){
	TCNT0 = 0x00;
    TCCR0B = (0<<CS02)|(1<<CS01)|(1<<CS00);
    sbi(TIMSK0, TOIE0);
    sei();
}

void system_init(void){
    CONFIG_EXTERNAL_CLOCK();
    tim_init();
}

unsigned long micros(void){
	unsigned long m;
	uint8_t oldSREG = SREG, t;
	cli();
	m = timer0_overflow_count;
    t = TCNT0;
	if ((TIFR0 & bv(TOV0)) && (t < 255))
		m++;
	SREG = oldSREG;
	return (((m<<8) + t)*4);
}
