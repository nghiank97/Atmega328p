
#ifndef CPU_MAP_H_
#define CPU_MAP_H_

#if defined (__AVR_ATmega328P__)

/* Encoder */

#define ENCODER_0                   2
#define ENCODER_1                   3

#define DIR_ENCODER                 DDRD
#define PIN_ENCODER                 PIND

/* L298 */

#define IN1_L298                    4
#define ENA_L298                    1       // pwm
#define IN2_L298                    5

#define DIR_L298                    DDRB
#define PORT_L298                   PORTB

#else
    #error "MCU invaild"

#endif
#endif