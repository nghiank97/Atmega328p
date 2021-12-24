
#include "Lib/Inc/config.h"
#include "Lib/Inc/capture.h"
#include "Lib/Inc/lcd4.h"

volatile uint32_t period=0, duty=0, check=0;
float32_t speed_motor = 0.0;
uint32_t frequently = 0;
char time_text[5];

int main(void){

    CONFIG_CLOCK();

    capture_init();
    lcd4_init();
    lcd4_puts("period :     Hz");
    lcd4_printf(1,0,"duty   :     %");
    lcd4_printf(2,0,"speed  :     rpm");
    while(1){
        if (check == 1){
            if ((2*duty-5) <= period){
                frequently = (uint32_t)2000000/period;
                sprintf(time_text,"%4ld",frequently);
                lcd4_printf(0,8,time_text);

                sprintf(time_text,"%4ld",duty*100/period);
                lcd4_printf(1,8,time_text);

                speed_motor = 0.6*frequently;
                sprintf(time_text,"%4.0f",speed_motor);
                lcd4_printf(2,8,time_text);
            }
            else{
                lcd4_printf(0,8,"   0");
                lcd4_printf(1,8,"   0");
                lcd4_printf(2,8,"   0");
                duty = 0;
                period = 0;
            }
        }
        else{
            lcd4_printf(0,8,"   0");
            lcd4_printf(1,8,"   0");
            lcd4_printf(2,8,"   0");
            duty = 0;
            period = 0;
        }
        delay_ms(100);
    }
}