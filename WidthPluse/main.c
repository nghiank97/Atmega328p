
#include "Lib/Inc/config.h"
#include "Lib/Inc/capture.h"
#include "Lib/Inc/pcf8574.h"

volatile uint32_t period=0, duty=0;
uint32_t frequently = 0;
char time_text[6];

int main(void){

    CONFIG_CLOCK();

    capture_init();
    i2c_lcd4_init();
    i2c_lcd4_puts("period : ");
    i2c_lcd4_printf(1,0,"duty   :      %");
    while(1){
        frequently = (uint32_t)2000000/period;
        sprintf(time_text,"%5ld",frequently);
        i2c_lcd4_printf(0,9,time_text);

        sprintf(time_text,"%5ld",duty*100/period);
        i2c_lcd4_printf(1,9,time_text);
    }
}