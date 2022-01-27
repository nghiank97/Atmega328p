
#include "elephant.h"

uint8_t data;

int main(void)
{
    CONFIG_EXTERNAL_CLOCK();

    spi_init(0);
    while (1)
    {
        spi_put('a');
        delay_ms(100);
    }
    return 1;
}