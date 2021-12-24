
#include "../Inc/pwm.h"

#ifdef PWM_1

extern void pwm_init(void){
    DDRB |= (1 << DDB1);
    ICR1L = 0; 
    ICR1H = 0; 
    OCR1AL = 0;
    OCR1AH = 0;
    TCCR1B |= (1<<CS11);
    TCCR1A |= (1 << COM1A1)|(0 << COM1A0);
    TCCR1A |= (1<<WGM10)|(1 << WGM11);
    TCCR1B |= (1<<WGM12);
}

extern void pwm_put(int duty){
    OCR1AH = (duty>>8)&0xFF;  
    OCR1AL = duty&0xFF; 
}

#elif defined(PWM_0)
extern void pwm_init(void){
    DDRD |= (1 << 6);
    OCR0A = 0;
    TCCR0A |= (1 << COM0A1);
    TCCR0A |= (1 << WGM01) | (1 << WGM00);
    TCCR0B |= (1 << CS01);
}

extern void pwm_put(uint8_t duty){
    OCR0A = duty;  
}

#elif defined(PWM_2)
extern void pwm_init(void){
    DDRB |= (1 << 3);
    OCR2A = 0;
    TCCR2A |= (1 << COM2A1);
    TCCR2A |= (1 << WGM21) | (1 << WGM20);
    TCCR2B |= (1 << CS22)|(1 << CS20);
}

extern void pwm_put(uint8_t duty){
    OCR2A = duty;  
}
#endif

