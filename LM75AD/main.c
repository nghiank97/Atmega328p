
#include "Lib/Inc/config.h"
#include "Lib/Inc/lcd4.h"
#include "Lib/Inc/lm75ad.h"
#include "Lib/Inc/serial.h"

uint8_t ms_temp = 0;
uint8_t ls_temp = 0;
char temp_txt[5];
char temp_serial[7];


static void show_lcd(LM75_STATUS status){
    if (status == LM75_SUCCESS){
        sprintf(temp_txt,"%4d",ms_temp);
        lcd4_printf(0,8,temp_txt);
        serial_puts(temp_txt);
        serial_puts("\r\n");
    }
    else{
        lcd4_printf(0,8,"ERROR");
    }
}

int main(void){
    CONFIG_CLOCK();
    lcd4_init();
    lcd4_puts("temp : ");
    serial_init(0);
    lm75_init();
    delay_ms(500);
    while(1){
        LM75_STATUS status = lm75_read_temp_register(TEMP,&ms_temp,&ls_temp);
        show_lcd(status);
        sprintf(temp_serial,":%3d\r\n",ms_temp);
        serial_puts(temp_serial);
        delay_ms(500);
    }
}