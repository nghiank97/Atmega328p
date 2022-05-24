#include "bee.h"

typedef void (*voidFunc)(void);


volatile voidFunc hangle_external;


void attachInterrupt(uint8_t interruptNum, void (*userFunc)(void), int mode){
    hangle_external = userFunc;
}

ISR(INT0_vect) {
    hangle_external();
}

void doA(void){
    Serial.println("handle external");
}

int main(){
    CONFIG_EXTERNAL_CLOCK();

    Serial.begin(9600);
    Serial.println("start");

    EICRA |= (0<<ISC10)|(1<<ISC11)|(0<<ISC00)|(1<<ISC01);
    EIMSK |= (1<<INT1)|(1<<INT0);

    attachInterrupt(1,doA,0);

    sei();

    while(1){


    }
    return 1;
}