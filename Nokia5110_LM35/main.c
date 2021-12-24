
#include "Lib/Inc/config.h"
#include "Lib/Inc/nokia5110.h"
#include "Lib/Inc/font.h"
#include "Lib/Inc/welcome.h"
#include "Lib/Inc/button.h"
#include "Lib/Inc/adc.h"

But press = NONE_bt;
int load_home = 0;
int index_home = 0;
bool is_temp_form = False;
bool is_light = True;

uint16_t adc_value = 0;
char temp_txt[3];

char* menu[] = {
    "   MAIN MENU",
    " > Temperature",
    " > Light: On ",
    " > Reset",
};

static void nokia5110_home_form(void){
    nokia5110_5x8_puts(0,0,menu[0],NORMAL_BG);
    nokia5110_5x8_puts(1,0,"--------------",NORMAL_BG);
    nokia5110_5x8_puts(2,0,menu[1],INVERSE_BG);
    nokia5110_5x8_puts(3,0,menu[2],NORMAL_BG);
    nokia5110_5x8_puts(4,0,menu[3],NORMAL_BG);
}

static void load_temperature(void){
    int buff = (int)adc_value*0.488;
    sprintf(temp_txt,"%2d",buff);
    nokia5110_medium_number(3,10,temp_txt[0],NORMAL_BG);
    nokia5110_medium_number(3,22,temp_txt[1],NORMAL_BG);
}

static void nokia5110_temperature_form(void){
    nokia5110_5x8_puts(0,0," Temperature",NORMAL_BG);
    nokia5110_5x8_puts(1,0,"--------------",NORMAL_BG);
    nokia5110_5x8_puts(2,10,"Value",NORMAL_BG);
    load_temperature();
}

static void nokia5110_light_form(bool status){
    if (status==True){
        nokia5110_5x8_puts(3,0," > Light: On ",INVERSE_BG);
        _clr(PORT_LED,LED);
    }
    else{
        nokia5110_5x8_puts(3,0," > Light: Off",INVERSE_BG);
        _set(PORT_LED,LED);
    }

}

static void loading_up_form(void){
    switch(index_home){
        case 0:{
            nokia5110_5x8_puts(4,0,menu[3],NORMAL_BG);
            nokia5110_5x8_puts(2,0,menu[1],INVERSE_BG);
            return;
        }
        case 1:{
            nokia5110_5x8_puts(2,0,menu[1],NORMAL_BG);
            nokia5110_5x8_puts(3,0,menu[2],INVERSE_BG);
            return;
        }
        case 2:{
            nokia5110_5x8_puts(3,0,menu[2],NORMAL_BG);
            nokia5110_5x8_puts(4,0,menu[3],INVERSE_BG);
            return;
        }                   
    }
}

static void loading_down_form(void){
    switch(index_home){
        case 0:{
            nokia5110_5x8_puts(3,0,menu[2],NORMAL_BG);
            nokia5110_5x8_puts(2,0,menu[1],INVERSE_BG);
            return;
        }
        case 1:{
            nokia5110_5x8_puts(4,0,menu[3],NORMAL_BG);
            nokia5110_5x8_puts(3,0,menu[2],INVERSE_BG);
            return;
        }
        case 2:{
            nokia5110_5x8_puts(2,0,menu[1],NORMAL_BG);
            nokia5110_5x8_puts(4,0,menu[3],INVERSE_BG);
            return;
        }                
    }
}

static void nokia5110_start(void){
    nokia5110_init();
    nokia5110_full_image(welcome_img,NORMAL_BG);
    delay_ms(500);
    nokia5110_blank();
    nokia5110_home_form();
}

ISR(TIMER2_OVF_vect){
    adc_value = adc_get(CHANNEL_0);

    if (is_temp_form == True){
        load_temperature();
    }
    RESET_TIMER_2();
}

int main(void){
    CONFIG_CLOCK();
    nokia5110_start();
    button_init();
    adc_init();
    while(1){
        press = button_get();
        switch (press){
            case UP_bt:{
                index_home+=1;
                if (index_home == 3){
                    index_home = 0;
                }
                loading_up_form();
                break;
            }
            case DOWN_bt:{
                index_home-=1;
                if (index_home == -1){
                    index_home = 2;
                }
                loading_down_form();
                break;
            }
            case MAIN_bt:{
                if ((index_home == 0) && (is_temp_form == False)){
                    nokia5110_blank();
                    nokia5110_temperature_form();
                    is_temp_form = True;
                    continue;
                    
                }
                else if ((index_home == 0) && (is_temp_form == True)){
                    is_temp_form = False;
                    delay_ms(50);
                    nokia5110_blank();
                    nokia5110_home_form();
                    continue;
                }

                if ((index_home == 1) && (is_light == False)){
                    nokia5110_light_form(True);
                    is_light = True;
                    continue;
                    
                }
                else if ((index_home == 1) && (is_light == True)){
                    nokia5110_light_form(False);
                    is_light = False;
                    continue;
                }
                if (index_home == 2){
                    nokia5110_reset();
                    continue;
                }
                break;
            }
            case NONE_bt:{
                /* code */
                break;
            }
        }
    }
}