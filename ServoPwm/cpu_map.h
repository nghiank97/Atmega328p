
#ifndef CPU_MAP_H_
#define CPU_MAP_H_

#if defined (__AVR_ATmega328P__)

#define SERVO_PIN                                   1
#define DIR_SERVO                                   DDRB
#define PORT_SERVO                                  PORTB

#else
    #error "MCU invaild"

#endif
#endif