
#include "../Inc/config.h"
#include "../Inc/encoder.h"

void encoder_channel(int channel){
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

extern void encoder_init(void){
    DIR_ENCODER = (0<<ENCODER_0)|(0<<ENCODER_1);
    //PORT_ENCODER = (1<<ENCODER_0)|(1<<ENCODER_1);
    encoder_channel(CHANNEL_0);
    encoder_channel(CHANNEL_1);
    count_encoder = 0;
}

ISR(INT0_vect){
    if(_read(PIN_ENCODER,ENCODER_1) == 1){
        count_encoder+=1;
    }
    else{
        count_encoder-=1;
    }
}

ISR(INT1_vect){
    if(_read(PIN_ENCODER,ENCODER_0) == 0){
        count_encoder+=1;
    }
    else{
        count_encoder-=1;
    }
}
