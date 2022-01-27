
#include "elephant.h"

extern void system_init(void){

    DDRB = (1<<1);
    TCCR1A |= (1<<COM1A1)|(1<<WGM11)|(1<<WGM10);
    TCCR1B |= (0<<WGM13)|(0<<WGM12)|(CS12<<0)|(CS11<<1)|(CS10<<0);
}