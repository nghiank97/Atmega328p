
#include "Lib/Inc/config.h"
#include "Lib/Inc/pcf8574.h"
#include "Lib/Inc/serial.h"

int main(void){
    CONFIG_CLOCK();
    i2c_lcd4_init();
    i2c_lcd4_print(0,0,"Speed: ");
    i2c_lcd4_print(1,0,"DIr: ");
    i2c_lcd4_print(2,0,"Pluse: ");

    serial_init(0);

    while(1){
        serial_puts("nghia \r\n");
        delay_ms(500);
    }
}