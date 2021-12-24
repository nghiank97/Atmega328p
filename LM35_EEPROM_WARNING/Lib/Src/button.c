
#include "../Inc/adc.h"

extern void button_init(void){
    _clr(DIR_BUTTON,UP_BUTTON);
    _clr(DIR_BUTTON,DOWN_BUTTON);
}
