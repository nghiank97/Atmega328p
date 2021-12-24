
#ifndef EEPROM_H_
#define EEPROM_H_
#include "config.h"

extern void eeprom_interrput(void);
extern uint8_t eeprom_read(uint16_t address);
extern void eeprom_write(uint16_t address,uint8_t data);
extern void eeprom_print(uint16_t address,char* data);

#endif