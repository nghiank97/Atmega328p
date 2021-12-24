
#include "Lib/Inc/config.h"
#include "Lib/Inc/seg7.h"
#include "Lib/Inc/adc.h"

uint16_t adc_value;
uint16_t temp = 0;

int main(void){
    CONFIG_CLOCK_8RC();

    adc_init();
    seg7_init();

    while(1){
        adc_value = adc_get(CHANNEL_0);
        temp = (uint16_t)adc_value*0.488;
        delay_ms(200);
    }
}