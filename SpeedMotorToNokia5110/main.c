
#include "Lib/Inc/config.h"
#include "Lib/Inc/nokia5110.h"
#include "Lib/Inc/encoder.h"
#include "Lib/Inc/welcome.h"

float32_t speed_motor = 0.0;
volatile int16_t count_encoder;
int angle_fan = 0;
char speed_txt[5];

static void show_nokia5110(void){
    speed_motor = count_encoder*1.5;
    sprintf(speed_txt,"%4d",(int16_t)speed_motor);
    nokia5110_5x8_array(1,50,speed_txt,4,NORMAL_BG);

    if (count_encoder > 0){
        nokia5110_5x8_put(2,56,'R',NORMAL_BG);
    }
    else{
        nokia5110_5x8_put(2,56,'L',NORMAL_BG);
    }
}

static void nokia5110_start(void){
    nokia5110_init();

    nokia5110_full_image(welcome_img,NORMAL_BG);
    delay_ms(1000);
    nokia5110_blank();
    nokia5110_5x8_puts(1,0,"Speed  : ",NORMAL_BG);
    nokia5110_5x8_puts(2,0,"Dir    : ",NORMAL_BG);
}
  
int main(void){
    CONFIG_CLOCK();
    nokia5110_start();
    encoder_init();
    while(1){
        count_encoder = 0;
        delay_ms(200);
        show_nokia5110();
    }
}