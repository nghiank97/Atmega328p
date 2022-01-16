
#ifndef CPU_MAP_H_
#define CPU_MAP_H_

#if defined (__AVR_ATmega328P__)


typedef enum{
    PWM_PD3 = 0,
    PWM_PD5 = 1,
    PWM_PD6 = 2,

    PWM_PB1 = 3,
    PWM_PB2 = 4,
    PWM_PB3 = 5
} PWM_PIN;


#define BLDC_HA                     PWM_PB1
#define BLDC_HB                     PWM_PB2
#define BLDC_HC                     PWM_PB3

#define BLDC_H_DIR                  DDRB
#define BLDC_H_PORT                 PORTB

#else
    #error "MCU invaild"

#endif
#endif
