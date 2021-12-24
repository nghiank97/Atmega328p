
#include "Lib/Inc/config.h"
#include "Lib/Inc/glcd.h"
#include "Lib/Inc/adc.h"

int adc_value = 0;
char adc_value_text[5];


int main(void){
    CONFIG_CLOCK();
    adc_init(Enable);
    glcd_init();
    glcd_puts("adc value",0,0,0,1);
    while(1){
        adc_value = adc_get(CHANNEL_0);
        sprintf(adc_value_text,"%4d",adc_value);

        for(int i=0;i<4;i++){
            if (adc_value_text[i]==' '){
                glcd_big_number('0',0,3,12*i,1);
            }
            else{
                glcd_big_number(adc_value_text[i],0,3,12*i,12);
            }
        }
        delay_ms(100);
    }
}