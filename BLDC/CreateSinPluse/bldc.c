
#include "bee.h"

/*
    F_CPU = 16MHz
    Prescaler : 64
    Pwm mode : center
    ->Fpwm = 16M*2/64
*/

void pwm_init(PWM_PIN pin, uint16_t value)
{
    switch (pin)
    {
    case PWM_PD3:
    {
        DDRD |= (1 << 3);
        TCCR2A |= (1 << COM2B1) | (0 << WGM21) | (1 << WGM20);
        TCCR2B |= (0 << WGM22) | (CS21 << 1) | (CS20 << 1);
        pwm_write(PWM_PD3, value);
        break;
    }
    case PWM_PD5:
    {
        DDRD |= (1 << 5);
        TCCR0A |= (1 << COM0B1) | (0 << WGM01) | (1 << WGM00);
        TCCR0B |= (0 << WGM02) | (CS01 << 1) | (CS00 << 1);
        pwm_write(PWM_PD5, value);
        break;
    }
    case PWM_PD6:
    {
        DDRD |= (1 << 6);
        TCCR0A |= (1 << COM0A1) | (0 << WGM01) | (1 << WGM00);
        TCCR0B |= (0 << WGM02) | (CS01 << 1) | (CS00 << 1);
        pwm_write(PWM_PD6, value);
        break;
    }
    case PWM_PB1:
    {
        DDRB |= (1 << 1);
        TCCR1A |= (1 << COM1A1) | (1 << WGM11) | (0 << WGM10);
        TCCR1B |= (1 << WGM13) | (0 << WGM12) | (CS12 << 0) | (CS11 << 1) | (CS10 << 1);
        ICR1H = 0x00;
        ICR1L = 0xff;
        pwm_write(PWM_PB1, value);
        break;
    }
    case PWM_PB2:
    {
        DDRB |= (1 << 2);
        TCCR1A |= (1 << COM1B1) | (1 << WGM11) | (0 << WGM10);
        TCCR1B |= (1 << WGM13) | (0 << WGM12) | (CS12 << 0) | (CS11 << 1) | (CS10 << 1);
        ICR1H = 0x00;
        ICR1L = 0xff;
        pwm_write(PWM_PB2, value);
        break;
    }
    case PWM_PB3:
    {
        DDRB |= (1 << 3);
        TCCR2A |= (1 << COM2A1) | (0 << WGM21) | (1 << WGM20);
        TCCR2B |= (0 << WGM22) | (CS21 << 1) | (CS20 << 1);
        pwm_write(PWM_PB3, value);
        break;
    }
    default:
        break;
    }
}

void pwm_write(PWM_PIN pin, uint16_t value)
{
    switch (pin)
    {
    case PWM_PD3:
    {
        OCR2B = value;
        break;
    }
    case PWM_PD5:
    {
        OCR0B = value;
        break;
    }
    case PWM_PD6:
    {
        OCR0A = value;
        break;
    }
    case PWM_PB1:
    {
        OCR1AH = 0;
        OCR1AL = value;
        break;
    }
    case PWM_PB2:
    {
        OCR1BH = 0;
        OCR1BL = value;
        break;
    }
    case PWM_PB3:
    {
        OCR2A = value;
        break;
    }
    default:
        break;
    }
}

extern void bldc_init(void)
{
    pwm_init(BLDC_HA, 0);
    pwm_init(BLDC_HB, 0);
    pwm_init(BLDC_HC, 0);
}
