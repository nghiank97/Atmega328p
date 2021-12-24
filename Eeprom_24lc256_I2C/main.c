
/*
 * main.c
 *
 * Created:
 * Author: Khac Nghia
 */

#include "Lib/Inc/config.h"
#include "Lib/Inc/e24lc256.h"

int main(void)
{
    CONFIG_EXTER_CLOCK();
    e24lc256_init();
    e24lc256_print(0x0001,"Nguyen Khac Nghia");
    while (1)
        {
        }
}
