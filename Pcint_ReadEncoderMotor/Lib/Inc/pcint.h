
#ifndef PCINT_H_
#define PCINT_H_
#include "config.h"

#define PCINT_PIN_0                                 0
#define PCINT_PIN_1                                 1
#define PCINT_PIN_2                                 2
#define PCINT_PIN_3                                 3
#define PCINT_PIN_4                                 4
#define PCINT_PIN_5                                 5
#define PCINT_PIN_6                                 6
#define PCINT_PIN_7                                 7


#define PCINT_CHANNAL_0                             0b001
#define PCINT_CHANNAL_1                             0b010
#define PCINT_CHANNAL_2                             0b100

#define PCINT_CHANNAL                               PCINT_CHANNAL_0


#if PCINT_CHANNAL == PCINT_CHANNAL_0                
#define PCINT_vect                                  PCINT0_vect                             

#elif PCINT_CHANNAL == PCINT_CHANNAL_1
#define PCINT_vect                                  PCINT1_vect                             

#elif PCINT_CHANNAL == PCINT_CHANNAL_2
#define PCINT_vect                                  PCINT2_vect    
#endif

extern volatile int count;
ISR(PCINT_vect){
    count +=1;
}

static void pcint_init(void){
    PCICR |= PCINT_CHANNAL;
    PCMSK0 |= (1<<PCINT_PIN_1)|(1<<PCINT_PIN_2);
    SREG |= (1<<SREG_I);
}

#endif