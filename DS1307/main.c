
/*
 * main.c
 *
 * Created:
 * Author: Khac Nghia
 */

#include "Lib/Inc/config.h"
#include "Lib/Inc/lcd4.h"
#include "Lib/Inc/ds1307.h"

uint8_t hou,min,sec;
char text_time[3]; 

static void lcd4_time(){
	sprintf(text_time,"%2d",cvt_hou_r(hou)); 
    lcd4_printf(0,6,text_time);    
	lcd4_put('-');  
    
	sprintf(text_time,"%2d",cvt_num_r(min));  
    lcd4_puts(text_time);
	lcd4_put('-'); 
      
	sprintf(text_time,"%2d",cvt_num_r(sec)); 
    lcd4_puts(text_time);
}

int main(void)
{
    CONFIG_EXTER_CLOCK();
    lcd4_init();
    lcd4_puts("TIME: 00-00-00");
    ds1307_init();

    ds1307_sout_pluse(PLUSE_4096_Hz);

    while (1)
        {
            ds1307_getime(&hou,&min,&sec);
            lcd4_time();
            delay_ms(1000);
        }
}
