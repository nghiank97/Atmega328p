
#include "../Inc/pwm.h"

extern void pwm_put(PWM_PIN pin,int value){
    switch (pin){
        case PWM_PD3:{
            DDRD |= (1<<3);
            TCCR2A |= (1<<COM2B1)|(1<<WGM21)|(1<<WGM20);
            TCCR2B |= (0<<WGM22)|(CS21<<1)|(CS20<<1);
            OCR2B = value;
            break;
        }
        case PWM_PD5:{
            DDRD |= (1<<5);
            TCCR0A |= (1<<COM0B1)|(1<<WGM01)|(1<<WGM00);
            TCCR0B |= (0<<WGM02)|(CS01<<1)|(CS00<<1);
            OCR0B = value;
            break;
        }
        case PWM_PD6:{
            DDRD |= (1<<6);
            TCCR0A |= (1<<COM0A1)|(1<<WGM01)|(1<<WGM00);
            TCCR0B |= (0<<WGM02)|(CS01<<1)|(CS00<<1);
            OCR0A = value;
            break;
        }
        case PWM_PB1:{
            DDRB |= (1<<1);
            TCCR1A |= (1<<COM1A1)|(1<<WGM11)|(1<<WGM10);
            TCCR1B |= (0<<WGM13)|(1<<WGM12)|(CS11<<1)|(CS10<<1);
            OCR1AH = value/256;
            OCR1AL = value%256;
            break;
        }
        case PWM_PB2:{
            DDRB |= (1<<2);
            TCCR1A |= (1<<COM1B1)|(1<<WGM11)|(1<<WGM10);
            TCCR1B |= (0<<WGM13)|(1<<WGM12)|(CS11<<1)|(CS10<<1);
            OCR1BH = value/256;
            OCR1BL = value%256;
            break;
        }
        case PWM_PB3:{
            DDRB |= (1<<3);
            TCCR2A |= (1<<COM2A1)|(1<<WGM21)|(1<<WGM20);
            TCCR2B |= (0<<WGM22)|(CS21<<1)|(CS20<<1);
            OCR2A = value;
            break;
        }
        default:
            break;
    }
}