
#include "../Inc/adc.h"

extern void adc_init(void){
    ADCSRA |= (1<<ADEN)|(7<<ADPS0);
    ADMUX |= (0<<REFS1)|(0<<REFS0)|(0<<ADLAR);   

    RESET_TIMER_1();
    TCCR1A = 0x00;
    TCCR1B = (1<<CS21)|(1<<CS11)|(1<<CS10);
    TIMSK1 = (1<<TOIE1);
    SREG |= (1<<SREG_I);
}

extern uint16_t adc_get(uint8_t adc_channel){
    ADMUX =(ADMUX&0xF0)|(adc_channel&0x0F);   
    ADCSRA |= (1<<ADSC);   
    while((ADCSRA&(1<<ADIF)) == 0);
    return ADCW;
} 
