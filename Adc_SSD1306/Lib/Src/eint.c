
#include "../Inc/config.h"
#include "../Inc/eint.h"

void eint_channel(int channel){
    switch(channel){
        case 0:{ 
            EICRA |= (0<<ISC00)|(1<<ISC01);
            EIMSK |= (1<<INT0);       
            break;
        }
        case 1:{ 
            EICRA |= (0<<ISC10)|(1<<ISC11);
            EIMSK |= (1<<INT1);       
            break;
        }
    }
    SREG |= (1<<SREG_I);
}

extern void eint_init(void){
    DIR_BT = (0<<UP_BT)|(0<<UP_BT)|(0<<MAIN_BT);
    eint_channel(CHANNEL_0);
    eint_channel(CHANNEL_1);
}
