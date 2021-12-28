

#include "bee.h"

extern void servo_init(void){
    DIR_SERVO |= (1<<SERVO_PIN);

    TCCR1A = (1<<COM1A1)|(1<<COM1B1)|(1<<WGM11)|(0<<WGM10);
    TCCR1B = (1<<WGM13)|(1<<WGM12);
    TCCR1B |= (0<<CS12) | (1<<CS11) | (0<<CS10);
    
    OCR1A = 1000;
    ICR1 = 40000;
}

extern void servo_put(int angle){
    OCR1A = 1000+(uint16_t)angle*22.222;
}
