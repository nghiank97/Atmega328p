
#include "Lib/Inc/config.h"
#include "Lib/Inc/lcd4.h"
#include "Lib/Inc/adc.h"
#include "Lib/Inc/encoder.h"
#include "Lib/Inc/pwm.h"

uint16_t adc_value = 0;
uint16_t pwm_value = 0;

float32_t speed_motor = 0.0;
volatile int16_t count_encoder;
volatile DIRECTION dir_encoder;
char speed_txt[5];

static void show_lcd(void){
    speed_motor = count_encoder*0.6;
    sprintf(speed_txt,"%3.1f",speed_motor);
    lcd4_printf(0,10,speed_txt);

    sprintf(speed_txt,"%4d",count_encoder);
    lcd4_printf(1,10,speed_txt);

    if (dir_encoder == RIGHT){
        lcd4_printf(2,10,"R");
    }
    else{
        lcd4_printf(2,10,"L");
    }

    sprintf(speed_txt,"%4d",pwm_value);
    lcd4_printf(3,10,speed_txt);
}

static void timer_1_init(void){
    TCNT1 = (65536-31250);
    TCCR1B = (1<<CS12)|(0<<CS11)|(0<<CS10);
    SREG |= (1<<SREG_I);
    TIMSK1 = (1 << TOIE1);
}

ISR(TIMER1_OVF_vect){
    show_lcd();
    TCNT1 = (65536-31250);
    count_encoder = 0;
}

int main(void){
    CONFIG_CLOCK();
    lcd4_init();
    lcd4_printf(0,0,"Speed   : ");
    lcd4_printf(1,0,"Encoder : ");
    lcd4_printf(2,0,"Dir     : ");
    lcd4_printf(3,0,"PWM duty: ");

    adc_init();
    timer_1_init();
    pwm_init();
    encoder_init();
    while(1){
        adc_value = adc_get(CHANNEL_0);
        pwm_value = (uint16_t)adc_value/4;
        pwm_put((uint8_t)pwm_value);
    }
}