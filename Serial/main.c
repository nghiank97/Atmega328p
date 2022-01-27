
#include "elephant.h"

int main(void)
{
    CONFIG_EXTERNAL_CLOCK();
    serial_init();
    
    while (1)
    {
        serial_println("speed : %03d");

    }
    
    return 1;
}