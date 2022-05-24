
#include "elephant.h"

extern void pwm_init(PWM_PIN pin,uint16_t value){
    switch (pin){
        case PWM_PD3:{
            DDRD |= (1<<3);
            TCCR2A |= (1<<COM2B1)|(1<<WGM21)|(1<<WGM20);
            TCCR2B |= (0<<WGM22)|(CS21<<1)|(CS20<<1);
            pwm_write(PWM_PD3,value);
            break;
        }
        case PWM_PD5:{
            DDRD |= (1<<5);
            TCCR0A |= (1<<COM0B1)|(1<<WGM01)|(1<<WGM00);
            TCCR0B |= (0<<WGM02)|(CS01<<1)|(CS00<<1);
            pwm_write(PWM_PD5,value);
            break;
        }
        case PWM_PD6:{
            DDRD |= (1<<6);
            TCCR0A |= (1<<COM0A1)|(1<<WGM01)|(1<<WGM00);
            TCCR0B |= (0<<WGM02)|(CS01<<1)|(CS00<<1);
            pwm_write(PWM_PD6,value);
            break;
        }
        case PWM_PB1:{
            DDRB |= (1<<1);
            TCCR1A |= (1<<COM1A1)|(1<<WGM11)|(1<<WGM10);
            TCCR1B |= (0<<WGM13)|(1<<WGM12)|(CS11<<1)|(CS10<<1);
            pwm_write(PWM_PB1,value);
            break;
        }
        case PWM_PB2:{
            DDRB |= (1<<2);
            TCCR1A |= (1<<COM1B1)|(1<<WGM11)|(1<<WGM10);
            TCCR1B |= (0<<WGM13)|(1<<WGM12)|(CS11<<1)|(CS10<<1);
            pwm_write(PWM_PB2,value);
            break;
        }
        case PWM_PB3:{
            DDRB |= (1<<3);
            TCCR2A |= (1<<COM2A1)|(1<<WGM21)|(1<<WGM20);
            TCCR2B |= (0<<WGM22)|(CS21<<1)|(CS20<<1);
            pwm_write(PWM_PB3,value);
            break;
        }
        default:
            break;
    }
}

static uint8_t map(uint16_t value,uint16_t min_a,uint16_t max_a, uint16_t min_b, uint16_t max_b){
    int16_t delta_x = -min_a+max_a;
    int16_t delta_y = -min_b+max_b;
    int16_t high_div = value-min_a;
    uint16_t result = (uint16_t)((float32_t)(high_div/delta_x)*delta_y+min_b);
    return result;
}

extern void pwm_write(PWM_PIN pin,uint16_t value){
    switch (pin){
        case PWM_PD3:{
            OCR2B = map(value,0,255,0,1023);
            break;
        }
        case PWM_PD5:{
            OCR0B = map(value,0,255,0,1023);
            break;
        }
        case PWM_PD6:{
            OCR0A = map(value,0,255,0,1023);
            break;
        }
        case PWM_PB1:{
            OCR1AH = value/256;
            OCR1AL = value%256;
            break;
        }
        case PWM_PB2:{
            OCR1BH = value/256;
            OCR1BL = value%256;
            break;
        }
        case PWM_PB3:{
            OCR2A = map(value,0,255,0,1023);
            break;
        }
        default:
            break;
    }
}
