
#include "../Inc/config.h"

extern void eeprom_interrput(void){
    EECR |= (1<<EERIE);
    SREG |= (1<<SREG_I);
}

extern uint8_t eeprom_read(uint16_t address){
    while ((EECR&(1<<EEPE)) != 0x00);
    EEAR = address; 
    EECR = (1<<EERE);
    return EEDR;
}

extern void eeprom_write(uint16_t address,uint8_t data){
    while ((EECR&(1<<EEPE)) != 0x00);
    EEAR = address;
    EEDR = data;
    EECR = (1<<EEMPE);
    EECR |= (1<<EEPE);
}

extern void eeprom_print(uint16_t address,char* data){
    while(*data){
        while ((EECR&(1<<EEPE)) != 0x00);
        EEAR = address;
        EEDR = *data;
        EECR = (1<<EEMPE);
        EECR |= (1<<EEPE);
        address++;
        data++;
    }
}