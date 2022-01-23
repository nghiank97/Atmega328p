
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


#define DRV8302_INHA                        PWM_PB1     // 9
#define DRV8302_INHB                        PWM_PB2     // 10
#define DRV8302_INHC                        PWM_PB3     // 11

#define BLDC_H_DIR                          DDRB
#define BLDC_H_PORT                         PORTB

#define DRV8302_ENABLE                      0           // 8

#define DRV8302_CONTROL_DIR                 DDRB
#define DRV8302_CONTROL_PORT                PORTB

/* DRV8302 */

#define DRV8302_OC_ADJ                      7           // 7
#define DRV8302_M_PWM                       6           // 6
#define DRV8302_M_OC                        5           // 5

#define DRV8302_HANDLE_DIR                  DDRD
#define DRV8302_HANDLE_PORT                 PORTD

/* ENCODER OF BLDC MOTOR */

#define ENCODER_A                           2           // 2
#define ENCODER_B                           3           // 3
#define INDEX_OPTIONAL_ENCODER              4           // ?

#define DRV8302_ENCODER_DIR                 DDRD        
#define DRV8302_ENCODER_PIN                 PIND        

/* ADC OF BLDC MOTOR */

#define DRV8302_nOCTW                       0           // 0
#define DRV8302_nFAULT                      1           // 1

#define DRV8302_ADC_DIR                     DDRC        
#define DRV8302_ADC_PIN                     PINC        

/* Interrupt external channel */

#define CHANNEL_0                                   0
#define CHANNEL_1                                   1

#define ENCODER_0                                   2
#define ENCODER_1                                   3

#define DIR_ENCODER                                 DDRD
#define PORT_ENCODER                                PORTD
#define PIN_ENCODER                                 PIND

#else
    #error "MCU invaild"

#endif
#endif
