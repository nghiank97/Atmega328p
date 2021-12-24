
#include "../Inc/e25lc256.h"

extern void e25lc256_init(void){
    spi_init(0);
}

extern void e25lc256_write_enable(void){
    _clr(PORT_SPI,SCE);
    spi_byte(WREN_25LC256);
    _set(PORT_SPI,SCE);
}

extern void e25lc256_write(uint16_t address,uint8_t data){
    e25lc256_write_enable();
    _clr(PORT_SPI,SCE);
    spi_byte(WRITE_25LC256);
    spi_byte((uint8_t)(address>>8));
    spi_byte((uint8_t)(address&0xFF));
    spi_byte(data);
    delay_ms(1);
    _set(PORT_SPI,SCE);
}

extern void e25lc256_print(uint16_t address,char *data){
    e25lc256_write_enable();
    _clr(PORT_SPI,SCE);
    spi_byte(WRITE_25LC256);
    spi_byte((uint8_t)(address>>8));
    spi_byte((uint8_t)(address&0xFF));
    while(*data){
        spi_byte(*data);
        data++;
    }
    delay_ms(1);
    _set(PORT_SPI,SCE);
}

extern uint8_t e25lc256_read(uint16_t address){
    _clr(PORT_SPI,SCE);
    spi_byte(READ_25LC256);
    spi_byte((uint8_t)(address>>8));
    spi_byte((uint8_t)(address&0xFF));
    spi_get();
    delay_ms(1);
    _set(PORT_SPI,SCE);
    return SPDR;
}