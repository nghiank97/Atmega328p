
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
    servo_put(20);
    while (1)
        {
        }
}
