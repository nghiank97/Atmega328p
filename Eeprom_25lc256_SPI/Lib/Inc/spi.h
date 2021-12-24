
#ifndef SPI_H_
#define SPI_H_
#include "config.h"

#define SCE                                 2
#define MOSI                                3
#define MISO                                4
#define SCK                                 5

#define DIR_SPI                             DDRB
#define PORT_SPI                            PORTB

extern void spi_init(int intp);
extern void spi_byte(uint8_t data);
extern void spi_put(uint8_t data);
extern void spi_puts(uint8_t *data);
extern void spi_array(uint8_t data[],int len);
extern uint8_t spi_get(void);

#endif