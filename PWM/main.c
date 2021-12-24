
/*
 * main.c
 *
 * Created:
 * Author: Khac Nghia
 */

#include "Lib/Inc/config.h"
#include "Lib/Inc/pwm.h"

int main(void)
{
    CONFIG_EXTER_CLOCK();
    pwm_put(PWM_PB1,102);
    pwm_put(PWM_PB2,102);
    pwm_put(PWM_PD3,102);
    pwm_put(PWM_PD5,102);

    while (1)
        {
        }
}
