#include "elephant.h"

extern void adc_init(void){
    ADMUX = (0<<ADLAR)|(0<<REFS1)|(1<<REFS0);
    ADCSRA = (1<<ADPS2)|(1<<ADPS1)|(0<<ADPS0);
}

extern uint16_t adc_read(uint8_t channal){
    ADMUX|= channal;
    ADCSRA |= (1<<ADEN)|(1<<ADSC);
    while((ADCSRA&(1<<ADIF)) == 0x00);
    return ADC;
}