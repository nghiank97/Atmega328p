
#include "Lib/Inc/config.h"
#include "Lib/Inc/ssd1306.h"
#include "Lib/Inc/logo.h"
#include "Lib/Inc/adc.h"

static void ssd1306_main(void){
    ssd1306_clear_display();
    ssd1306_print_stringXY("BATTERY",0,43,NORMAL);
    ssd1306_line(10,0,10,127,ON_PIXEL);
    ssd1306_print_stringXY("1024",2,85,NORMAL);
    ssd1306_print_stringXY("768 ",3,85,NORMAL);
    ssd1306_print_stringXY("512 ",4,85,NORMAL);
    ssd1306_print_stringXY("256 ",5,85,NORMAL);
    ssd1306_print_stringXY("0   ",6,85,NORMAL);

    ssd1306_box(19,30,51,80,NORMAL);
    ssd1306_pixel(19,81,NORMAL);
    ssd1306_pixel(27,81,NORMAL);
    ssd1306_pixel(35,81,NORMAL);
    ssd1306_pixel(43,81,NORMAL);
    ssd1306_pixel(51,81,NORMAL);
}

static void ssd1306_begin(void){
    ssd1306_init();
	ssd1306_logo(mylogo,NORMAL);
    delay_ms(1000);
    ssd1306_main();
}

static void ssd1306_clear_battery(void){
    for(int i=20;i<51;i++){
        ssd1306_line(i,31,i,79,OFF_PIXEL);
    }
}

uint16_t adc_value = 0;
char text_adc_value[5];
int slide_value = 0;
int past_slide_value = 0;
int subtract_slide_value = 0;

int main(void){
    CONFIG_CLOCK();

    ssd1306_begin();
    adc_init();

    while(1){
        adc_value = adc_get(CHANNEL_0);
        slide_value = (int)adc_value/31.03;
        subtract_slide_value = slide_value - past_slide_value;
        if (subtract_slide_value == 0){
            continue;
        }
        else if (subtract_slide_value > 0){
            for(int i=past_slide_value;i<=slide_value;i++){
                ssd1306_line(51-i,31,51-i,79,ON_PIXEL);
            }
        }
        else{
            for(int i=slide_value;i<=past_slide_value;i++){
                ssd1306_line(51-i,31,51-i,79,OFF_PIXEL);
            }
        }
        ssd1306_line(51,31,51,79,ON_PIXEL);
        ssd1306_line(19,31,19,79,ON_PIXEL);
        delay_ms(300);
        past_slide_value = slide_value;
    }
    return 0;
}