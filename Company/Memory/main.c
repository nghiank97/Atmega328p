
#include "elephant.h"

int nghia = 11;

int main(void)
{
    CONFIG_EXTERNAL_CLOCK();
    DDRB = 0xff;
    while (1)
    {
        PORTB = 0x00;
        delay_ms(500);
        PORTB = 0x80;
        delay_ms(500);
    }

    return 1;
}