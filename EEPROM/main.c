
/*
 * main.c
 *
 * Created: 10/29/2020 11:09:25 PM
 * Author: Khac Nghia
 */

#include "Lib/Inc/config.h"
#include "Lib/Inc/eeprom.h"


int main(void)
{
    CONFIG_EXTER_CLOCK();

    eeprom_write(0x05,0x0f);
    eeprom_write(0x07,0xf0);

    eeprom_print(0x20,"hello world");
    while (1)
        {
        }
}
