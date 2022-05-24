
#include "bee.h"

HardwareSerial Serial;

int main(){
    CONFIG_EXTERNAL_CLOCK();

    DDRB = 0xff;
    DDRC = 0xff;

    Serial.begin(9600);
    Serial.printPgmString(PSTR("khac"));
    while(1){

    }
    return 1;
}