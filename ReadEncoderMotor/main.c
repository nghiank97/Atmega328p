
#include "Lib/Inc/config.h"
#include "Lib/Inc/lcd4.h"
#include "Lib/Inc/encoder.h"

float32_t speed_motor = 0.0;
volatile int16_t count_encoder;
volatile DIRECTION dir_encoder;
char speed_txt[5];

static void show_lcd(void){
    int16_t buff = count_encoder;
    speed_motor = buff*0.6;
    sprintf(speed_txt,"%3.1f",speed_motor);
    lcd4_printf(0,10,speed_txt);

    sprintf(speed_txt,"%4d",buff);
    lcd4_printf(1,10,speed_txt);

    if (dir_encoder == RIGHT){
        lcd4_printf(2,10,"R");
    }
    else{
        lcd4_printf(2,10,"L");
    }
}

int main(void){
    CONFIG_CLOCK();
    lcd4_init();
    lcd4_printf(0,0,"Speed   : ");
    lcd4_printf(1,0,"Encoder : ");
    lcd4_printf(2,0,"Dir     : ");

    encoder_init();
    while(1){
        count_encoder = 0;
        delay_ms(500);
        show_lcd();
    }
}