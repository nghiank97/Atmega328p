
#ifndef E25LC256_H_
#define E25LC256_H_
#include "config.h"
#include "spi.h"

enum EEPROM_25LC256_COMMAND{
    READ_25LC256    = 0b00000011,
    WRITE_25LC256   = 0b00000010,
    WRDI_25LC256    = 0b00000100,
    WREN_25LC256    = 0b00000110,
    RDSR_25LC256    = 0b00000101,
    WRSR_25LC256    = 0b00000001
};

extern void e25lc256_init(void);
extern void e25lc256_write_enable(void);
extern void e25lc256_write(uint16_t address,uint8_t data);
extern void e25lc256_print(uint16_t address,char *data);
extern uint8_t e25lc256_read(uint16_t address);

#endif