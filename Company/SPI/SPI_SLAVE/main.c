
#include "elephant.h"

uint8_t data;

int main(void)
{
    CONFIG_EXTERNAL_CLOCK();

    spi_init();
    serial_init();
    while (1)
    {
        data = spi_read();
        serial_write(data);
    }
    return 1;
}