
/*
 * main.c
 *
 * Created:
 * Author: Khac Nghia
 */

#include "Lib/Inc/config.h"
#include "Lib/Inc/eeprom.h"
#include "Lib/Inc/lcd4.h"
#include "Lib/Inc/adc.h"
#include "Lib/Inc/button.h"

uint8_t max_temp = 0x00;
uint16_t register_temp_0 = 0;
char temp_txt[5];

static void show_lcd(void){
    float32_t buff = 0.0;
    buff = register_temp_0*0.489;
    sprintf(temp_txt,"%3.1f",buff);
    lcd4_printf(1,8,temp_txt);
}

void timer1_init(void){
    TCNT1 = 0xFFFF-20000;
    TCCR1A = 0x00;
    TCCR1B = (1<<CS11)|(0<<CS10);  
    TIMSK1 |= (1 << TOIE1);
    SREG |= (1<<SREG_I);
}

ISR(TIMER1_OVF_vect){
    register_temp_0 = adc_get(CHANNEL_0);
    show_lcd();
    TIFR1 |= (1<<TOV1);
    TCNT1 = 0xFFFF-30000;
}

static void begin(void){
    CONFIG_EXTER_CLOCK();
    lcd4_init();

    lcd4_printf(0,0,"MAX  :       *C");
    lcd4_printf(1,0,"TEMP :       *C");

    max_temp = eeprom_read(0x00);
    sprintf(temp_txt,"%d",max_temp);
    lcd4_printf(0,8,temp_txt);
}

extern void reload_max_value_on_lcd(void){
    if ((TIFR1&(1<<TOV1)) != 0x00){
        while((TIFR1&(1<<TOV1)) != 0x00);
    }
    char text_max[4];
    sprintf(text_max,"%d",max_temp);
    lcd4_printf(0,8,text_max);
    eeprom_write(0x0000,max_temp);
}

int main(void)
{
    begin();
    button_init();
    timer1_init();
    adc_init();
    while(1){
        if ((_read(PIN_BUTTON,UP_BUTTON)==0) && (_read(PIN_BUTTON,DOWN_BUTTON)==1)){
            delay_ms(DELAY_BT);
            if ((_read(PIN_BUTTON,UP_BUTTON)==0) && (_read(PIN_BUTTON,DOWN_BUTTON)==1)){
                max_temp +=1; 
                reload_max_value_on_lcd();
            }
        }
        else if ((_read(PIN_BUTTON,UP_BUTTON)==1) && (_read(PIN_BUTTON,DOWN_BUTTON)==0)){
            delay_ms(DELAY_BT);
            if ((_read(PIN_BUTTON,UP_BUTTON)==1) && (_read(PIN_BUTTON,DOWN_BUTTON)==0)){
                max_temp-=1;  
                reload_max_value_on_lcd();         
            }
        }
    }
}
