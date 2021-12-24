
/*
 * main.c
 *
 * Created:
 * Author: Khac Nghia
 */

#include "Lib/Inc/config.h"
#include "Lib/Inc/e25lc256.h"
#include "Lib/Inc/serial.h"

uint8_t data;

int main(void)
{
    CONFIG_EXTER_CLOCK();
    serial_init(0);
    e25lc256_init();
    e25lc256_print(0x0001,"Nguyen Khac Nghia");

    while (1)
        {
            data = e25lc256_read(0x0001);
            serial_put(data);
            serial_puts("\r\n");
            
            data = e25lc256_read(0x0002);
            serial_put(data);
            serial_puts("\r\n");

            delay_ms(500);
        }
}
