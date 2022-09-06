
#include "elephant.h"


void led_init(void){
    DDRD |= (1<<6);
    PORTD |= (1<<6);
}

uint8_t line[255];
uint8_t line_[255];

bool compare(uint8_t* data1, uint8_t* data2, uint8_t len){
    for(uint8_t i=0;i<len;i++){
        if(*(data1++) != *(data2++)){
            return false;
        }
    }
    return true;
}

void led_handle(uint8_t *data, uint8_t len){
    if (compare(data, "LED13=1;",8)){
        LED_13_ON();
        return;
    }
    if (compare(data, "LED13=0;",8)){
        LED_13_OFF();
        return;
    }
}

void protocol_execute(void){
    static uint8_t line[255];
    static uint8_t index = 0;

    uint8_t c = serial_read();
    if (c != SERIAL_NO_DATA){
        if ((c == '\n') || (c == '\r')){
            line[index++] = 0;
            led_handle(line,index);
            index = 0;
        }
        else{
            line[index++] = c;
        }
    }
}

int main(void) 
{
    CONFIG_EXTERNAL_CLOCK();
    led_init();
    serial_init(9600);
    
    while (1)
    {
        protocol_execute();
    }
    
    return 1;
}