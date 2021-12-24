
/*
 * main.c
 *
 * Created:
 * Author: Khac Nghia
 */

#include "Lib/Inc/config.h"
#include "Lib/Inc/servo.h"

int main(void)
{
    CONFIG_EXTER_CLOCK();
    servo_init();
    servo_put(20);
    while (1)
        {
        }
}
