
#include "elephant.h"

float32_t acs712_current = 0.0;
float32_t acs712_vout = 0.0;
char text_value[8];

int main(void)
{
    CONFIG_EXTERNAL_CLOCK();

    acs712_init();
    serial_init();
    #ifdef DEBUG_MAIN
        serial_println("ACS712 debug on");
    #endif

    while (1)
    {
        acs712_read(&acs712_vout,&acs712_current);
        sprintf(text_value,"%4.1f",acs712_vout);
        serial_print("Vout : ");serial_println(text_value);
        sprintf(text_value,"%2.3f",acs712_current);
        serial_print("Current : ");serial_println(text_value);
        delay_ms(100);
    }
    
    return 1;
}