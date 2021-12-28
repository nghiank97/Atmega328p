
/*
 * main.c
 *
 * Created:
 * Author: Khac Nghia
 */

#include "bee.h"

int main(void)
{
    CONFIG_EXTERNAL_CLOCK();
    servo_init();
    while (1)
        {
            servo_put(180);
            delay_ms(1000);
            servo_put(0);
            delay_ms(1000);
        }
}
