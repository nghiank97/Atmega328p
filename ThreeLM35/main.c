
#include "Lib/Inc/config.h"
#include "Lib/Inc/lcd4.h"
#include "Lib/Inc/adc.h"

uint16_t register_temp_0 = 0;
uint16_t register_temp_1 = 0;
uint16_t register_temp_2 = 0;
char temp_txt[5];

static void show_lcd(void){

    float32_t buff = 0.0;
    buff = register_temp_0*0.489;
    sprintf(temp_txt,"%3.1f",buff);
    lcd4_printf(0,11,temp_txt);

    buff = register_temp_1*0.489;
    sprintf(temp_txt,"%3.1f",buff);
    lcd4_printf(1,11,temp_txt);

    buff = register_temp_2*0.489;
    sprintf(temp_txt,"%3.1f",buff);
    lcd4_printf(2,11,temp_txt);
}

int main(void){
    CONFIG_CLOCK();
    lcd4_init();
    lcd4_printf(0,0,"Channal 0: ");
    lcd4_printf(1,0,"Channal 1: ");
    lcd4_printf(2,0,"Channal 2: ");

    adc_init();
    delay_ms(500);
    while(1){
        register_temp_0 = adc_get(CHANNEL_0);
        delay_ms(5);
        register_temp_1 = adc_get(CHANNEL_1);
        delay_ms(5);
        register_temp_2 = adc_get(CHANNEL_2);
        delay_ms(5);

        show_lcd();

        delay_ms(200);
    }
}