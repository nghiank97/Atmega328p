
#include "Lib/Inc/config.h"
#include "Lib/Inc/ssd1306.h"
#include "Lib/Inc/logo.h"
#include "Lib/Inc/adc.h"

static void ssd1306_main(void){
    ssd1306_clear_display();
    ssd1306_print_stringXY("1024",0,0,NORMAL);
    ssd1306_print_stringXY(" 512",3,0,NORMAL);
    ssd1306_print_stringXY("   0",6,0,NORMAL);
    ssd1306_print_stringXY("Value",7,45,NORMAL);

    ssd1306_line(48,30,48,127,ON_PIXEL);
    ssd1306_line(0,30,48,30,ON_PIXEL);

    ssd1306_pixel(0,29,ON_PIXEL);
    ssd1306_pixel(24,29,ON_PIXEL);
}

static void ssd1306_begin(void){
    ssd1306_init();
	ssd1306_logo(mylogo,NORMAL);
    delay_ms(1000);
    ssd1306_main();
}

static void ssd1306_clear_graphic(void){
    for(int i=0;i<6;i++){
        ssd1306_gotoXY(i,31);
        for(int j=31;j<128;j++){
            ssd1306_data(0x00);
        }
    }
}

uint16_t adc_value = 0;
char text_adc_value[5];
int slide_value = 0;

int local_adc_array = 1;
#define MAX_ARRAY 97
int adc_value_array[MAX_ARRAY] = {0};


int main(void){
    CONFIG_CLOCK();

    ssd1306_begin();
    adc_init();

    while(1){
        adc_value = adc_get(CHANNEL_0);
        slide_value = (int)adc_value/20.899;
        adc_value_array[local_adc_array] = slide_value;
        local_adc_array +=1;

        if (local_adc_array == MAX_ARRAY){
            ssd1306_clear_graphic();
            for(int i=0;i<MAX_ARRAY;i++){
                if (i+25 >= MAX_ARRAY){
                    adc_value_array[i] = 0;
                }
                else{
                    adc_value_array[i] = adc_value_array[i+25];
                }
            }
            local_adc_array = MAX_ARRAY-25;
        }
        sprintf(text_adc_value,"%4d",adc_value);
        ssd1306_print_stringXY(text_adc_value,7,80,NORMAL);

        for(int i=0;i<local_adc_array-1;i++){
            ssd1306_line(48-adc_value_array[i],i+31,48-adc_value_array[i+1],i+32,ON_PIXEL);
        }
        delay_ms(300);
    }
    return 0;
}