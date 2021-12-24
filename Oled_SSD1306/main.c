
#include "Lib/Inc/config.h"
#include "Lib/Inc/ssd1306.h"
#include "Lib/Inc/logo.h"

int main(void){
    CONFIG_CLOCK();

    ssd1306_init();
	ssd1306_reset_display(); 
	ssd1306_logo(mylogo);
	ssd1306_invert_display();
    while(1){
    }
    return 0;
}