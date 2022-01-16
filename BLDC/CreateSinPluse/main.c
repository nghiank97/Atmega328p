
/*
 * main.c
 *
 * Created:
 * Author: Khac Nghia
 */

#include "bee.h"

volatile int pwmSin[] = {127, 110, 94, 78, 64, 50, 37, 26, 17, 10, 4, 1, 0, 1, 4, 10, 17, 26, 37, 50, 64, 78, 94, 110, 127, 144, 160, 176, 191, 204, 217, 228, 237, 244, 250, 253, 255, 253, 250, 244, 237, 228, 217, 204, 191, 176, 160, 144, 127}; // array of PWM duty values for 8-bit timer - sine function
volatile int currentStepA = 0;
volatile int currentStepB = 0;
volatile int currentStepC = 0;
char pwm_value_text[20];

int main(void)
{
    uint8_t i = 0;
    CONFIG_EXTERNAL_CLOCK();
    bldc_init();
    serial_init();
    bldc_init();
    while (1)
    {
        currentStepA = (i) % 48;
        currentStepB = (i + 16) % 48;
        currentStepC = (i + 32) % 48;

        // sprintf(pwm_value_text, "%03d %03d %03d %d", pwmSin[currentStepA], pwmSin[currentStepB], pwmSin[currentStepC],i);
        // serial_println(pwm_value_text);

        pwm_write(BLDC_HA, (uint16_t)pwmSin[currentStepA]);
        pwm_write(BLDC_HB, (uint16_t)pwmSin[currentStepB]);
        pwm_write(BLDC_HC, (uint16_t)pwmSin[currentStepC]);

        i +=1;
        if (i>48){
            i=0;
        }
        delay_ms(10);
    }
}
