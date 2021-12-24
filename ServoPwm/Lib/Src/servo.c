

#include "../Inc/servo.h"

volatile int time = 0;
volatile int status = LOW;

extern void servo_init(void){
    DIR_SERVO |= (1<<SERVO_PIN);
    _clr(PORT_SERVO,SERVO_PIN);

    TCNT1 = 0xffff-20000+time;
    TCCR1B = (0<<CS12) | (1<<CS11) | (0<<CS10);
    TIMSK1 |= (1<<TOIE1);
    SREG |= (1<<SREG_I);
    status = LOW;
}

extern void servo_put(int angle){
    time = (int)angle*5.556;
}

ISR (TIMER1_OVF_vect)
{
    if (status == LOW){
        status = HIGH;
        _set(PORT_SERVO,SERVO_PIN);
	    TCNT1 = (0xffff-(1000+time));
    }
    else{
        status = LOW;
        _clr(PORT_SERVO,SERVO_PIN);
        TCNT1 = (0xffff-(20000-time));
    }
}