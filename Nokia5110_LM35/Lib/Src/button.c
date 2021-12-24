
#include "../Inc/button.h"

extern void button_init(void){
    DIR_BT &=~ (1<<UP);
    DIR_BT &=~ (1<<DOWN);
    DIR_BT &=~ (1<<MAIN);
}

extern But button_get(void){
    
    if ((_read(PIN_BT,UP) == 0) && (_read(PIN_BT,DOWN) == 1) && (_read(PIN_BT,MAIN) == 1)){
        delay_ms(150);
        if ((_read(PIN_BT,UP) == 0) && (_read(PIN_BT,DOWN) == 1) && (_read(PIN_BT,MAIN) == 1)){
            return UP_bt;
        }
    }
    else if ((_read(PIN_BT,UP) == 1) && (_read(PIN_BT,DOWN) == 0) && (_read(PIN_BT,MAIN) == 1)){
        delay_ms(150);
        if ((_read(PIN_BT,UP) == 1) && (_read(PIN_BT,DOWN) == 0) && (_read(PIN_BT,MAIN) == 1)){
            return DOWN_bt;
        }
    }
    else if ((_read(PIN_BT,UP) == 1) && (_read(PIN_BT,DOWN) == 1) && (_read(PIN_BT,MAIN) == 0)){
        delay_ms(150);
        if ((_read(PIN_BT,UP) == 1) && (_read(PIN_BT,DOWN) == 1) && (_read(PIN_BT,MAIN) == 0)){
            return MAIN_bt;
        }
    }
    return NONE_bt;
}