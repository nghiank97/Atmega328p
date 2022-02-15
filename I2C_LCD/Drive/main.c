
#include "bee.h"

int main(void){
    CONFIG_EXTERNAL_CLOCK();
    i2c_lcd4_init(64);
    i2c_lcd4_puts("hello");
    while(1){
    }
}