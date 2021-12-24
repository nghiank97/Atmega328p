
#include "../Inc/e24lc256.h"

extern void e24lc256_init(void){
    _set(DIR_WP,WP_PIN);
    _clr(PORT_WP,WP_PIN);
    i2c_init();
}

extern void e24lc256_write(uint16_t address,uint8_t data){
    i2c_start();
	i2c_put(EEPROM_24LC256_WRITE);
	i2c_put((uint8_t)(address>>8));
	i2c_put((uint8_t)(address&0xFF));
    i2c_put(data);
	i2c_stop();
}

extern void e24lc256_print(uint16_t address,char *data){
    i2c_start();
	i2c_put(EEPROM_24LC256_WRITE);
	i2c_put((uint8_t)(address>>8));
	i2c_put((uint8_t)(address&0xFF));
    while(*data){
        i2c_put(*data);
        data+=1;
    }
	i2c_stop();
}

extern uint8_t e24lc256_read(uint16_t address){
    uint8_t data;
    i2c_start();
    i2c_put(EEPROM_24LC256_WRITE);
	i2c_put((uint8_t)(address>>8));
	i2c_put((uint8_t)(address&0xFF));
    i2c_start();
	i2c_put(EEPROM_24LC256_READ);
	data = i2c_get(1);
	i2c_stop();
    return data;
}