
#ifndef SPI_H_
#define SPI_H_
#include "config.h"

extern void spi_init(int intp);
extern void spi_byte(uint8_t data);
extern void spi_put(uint8_t data);
extern void spi_puts(uint8_t *datas,int len);
extern uint8_t mspi_get();

#endif