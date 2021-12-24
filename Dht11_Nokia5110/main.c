
#include "Lib/Inc/config.h"
#include "Lib/Inc/nokia5110.h"
#include "Lib/Inc/font.h"
#include "Lib/Inc/welcome.h"
#include "Lib/Inc/dht11.h"

bool status_dht11 = False;
uint8_t humi,part_humi,temp,part_temp,check_sum;

static void nokia5110_start(void){
    nokia5110_init();
    nokia5110_full_image(welcome_img,NORMAL_BG);
    delay_ms(500);
    nokia5110_blank();

    nokia5110_5x8_puts(0,9,"TEMPERATURE",NORMAL_BG);
    nokia5110_5x8_puts(3,18,"HUMIDITY",NORMAL_BG);
}

static void dht11_uploading(void){
    char text[10];
	sprintf(text,"%02d.%02d'C",(int)temp,(int)part_temp);
    nokia5110_5x8_puts(1,21,text,NORMAL_BG);
	sprintf(text,"%02d.%02d %%",(int)humi,(int)part_humi);
    nokia5110_5x8_puts(4,21,text,NORMAL_BG);
}

int main(void){
    CONFIG_CLOCK();
    nokia5110_start();
    while(1){
        status_dht11 = dht11_get(&humi,&part_humi,&temp,&part_temp,&check_sum);
        if (status_dht11 ==  False){
            continue;
        }
        else{
            dht11_uploading();
        }
        delay_ms(300);
    }
}