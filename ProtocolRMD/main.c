
#include "elephant.h"

int main(void)
{
    CONFIG_EXTERNAL_CLOCK();
    serial_init();
    //serial_print_pgm(PSTR("Hello world"));

    while (1)
    {
        protocol_main_loop();
    }

    return 1;
}