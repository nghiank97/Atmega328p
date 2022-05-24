
#include "elephant.h"

uint16_t value = 0;

int main(void)
{
    system_init();
    adc_init();
    while (1)
    {
        value = adc_read(0);
        OCR1A = value;
        delay_ms(500);

    }
    return 1;
}