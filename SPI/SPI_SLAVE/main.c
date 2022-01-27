
#include "elephant.h"

uint8_t data;

int main(void)
{
    CONFIG_EXTERNAL_CLOCK();

    spi_init();
    serial_init();
    serial_println("spi slave");
    while (1)
    {
        data = spi_read();
        serial_write(data);
    }
    return 1;
}