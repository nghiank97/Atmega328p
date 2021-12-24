
/*
 * main.c
 *
 * Created:
 * Author: Khac Nghia
 */

#include "Lib/Inc/config.h"
#include "Lib/Inc/lcd4.h"
#include "Lib/Inc/pcint.h"

static void lcd4_begin(void){
    lcd4_init();
    lcd4_print(0,0,"Count : ");
    lcd4_print(1,0,"Speed : ");
}

volatile int count = 0;
char text_count[5];

static void show_to_lcd(void){
    int copy_count = count;
    int speed_motor = (int)copy_count*1.5;
    sprintf(text_count,"%4d",copy_count);
    lcd4_print(0,9,text_count);

    sprintf(text_count,"%4d",speed_motor);
    lcd4_print(1,9,text_count);
}

int main(void)
{
    CONFIG_EXTER_CLOCK();
    lcd4_begin();
    pcint_init();
    while (1)
        {
            count = 0;
            delay_ms(100);
            show_to_lcd();
        }
}
