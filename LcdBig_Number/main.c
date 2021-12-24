
/*
 * main.c
 *
 * Created:
 * Author: Khac Nghia
 */

#include "Lib/Inc/config.h"
#include "Lib/Inc/lcd4.h"

int main(void)
{
    CONFIG_EXTER_CLOCK();
    lcd4_init();

    lcd4_put_big_numbers("123",2);
    while (1)
        {
        }
}
