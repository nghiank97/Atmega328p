
#ifndef CPU_MAP_H_
#define CPU_MAP_H_

// #if defined (__AVR_ATmega328P__)

/* DRV8302 */

#define DRV8302_ENABLE                      0           // 8
#define DRV8302_INHA                        1           // 9
#define DRV8302_INHB                        2           // 10
#define DRV8302_INHC                        3           // 11

#define DRV8302_CONTROL_DIR                 DDRD
#define DRV8302_CONTROL_PORT                PIND

/* DRV8302 */

#define DRV8302_OC_ADJ                      7           // 8
#define DRV8302_M_PWM                       6           // 9
#define DRV8302_M_OC                        5           // 10

#define DRV8302_HANDLE_DIR                  DDRD
#define DRV8302_HANDLE_PORT                 PIND

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

// #else
//     #error "MCU invaild"
// #endif
#endif