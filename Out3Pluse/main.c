
#include "Lib/Inc/config.h"
#include "Lib/Inc/serial.h"

#define PLUSE_0                 3
#define PLUSE_1                 4
#define PLUSE_2                 5
#define DIR_PLUSE               DDRD
#define PORT_PLUSE              PORTD

static void gpio_init(void){
    DIR_PLUSE = (1<<PLUSE_0)|(1<<PLUSE_1)|(1<<PLUSE_2);
}

static void timer_init(void){
    /* timer 0 */
    TCNT0 = 0x00;
    TCCR0B = (0<<CS00) | (1<<CS01) | (0<<CS02);
    TIMSK0 |= (1<<TOIE0);

    TCNT1 = 0x0000;
    TCCR1B = (0<<CS10) | (1<<CS11) | (0<<CS12);
    TIMSK1 |= (1<<TOIE1);

    TCNT2 = 0x00;
    TCCR2B = (0<<CS20) | (1<<CS21) | (0<<CS22);
    TIMSK2 |= (1<<TOIE2);

    SREG |= (1<<SREG_I);
}

ISR (TIMER0_OVF_vect)
{
	_toggle(PORT_PLUSE,PLUSE_0);
	TCNT0 = 20;
}

ISR (TIMER1_OVF_vect)
{
	_toggle(PORT_PLUSE,PLUSE_1);
	TCNT1 = (0xffff-236);
}

ISR (TIMER2_OVF_vect)
{
	_toggle(PORT_PLUSE,PLUSE_2);
	TCNT2 = 20;
}

int main(void){
    CONFIG_CLOCK();
    gpio_init();
    timer_init();
    while(1){
    }
}