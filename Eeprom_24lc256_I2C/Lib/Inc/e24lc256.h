
#ifndef E24LC256_H_
#define E24LC256_H_
#include "config.h"
#include "i2c.h"

#define WP_PIN                              3
#define DIR_WP                              DDRC
#define PORT_WP                             PORTC

#define A2A1A0                              0b000
#define ADDRESS_EEPROM                      0xA0|(A2A1A0<<1)   
#define EEPROM_24LC256_WRITE                ADDRESS_EEPROM
#define EEPROM_24LC256_READ                 ADDRESS_EEPROM|(0x01)

extern void e24lc256_init(void);
extern void e24lc256_write(uint16_t address,uint8_t data);
extern void e24lc256_print(uint16_t address,char *data);
extern uint8_t e24lc256_read(uint16_t address);

#endif