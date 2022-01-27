
#include "elephant.h"

int nghia = 11;

int main(void)
{
    CONFIG_EXTERNAL_CLOCK();
    DDRD = 0xff;
    PORTD = nghia;
    while (1)
    {
    }

    return 1;
}