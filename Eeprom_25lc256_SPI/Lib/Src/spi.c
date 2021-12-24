
#include "../Inc/spi.h"

extern void spi_init(int intp){
    DIR_SPI = (1<<SCE)|(1<<MOSI)|(1<<SCK);
    PORT_SPI |= (1<<MISO);
    _set(PORT_SPI,SCE);
    switch (intp){
        case 0:{
            SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR1)|(1<<SPR0);
            return; 
        }
        case 1:{
            SREG |= (1<<SREG_I);
            SPCR = (1<<SPIE)|(1<<SPE)|(1<<MSTR)|(1<<SPR1)|(1<<SPR0);
            return; 
        }
    }
}

extern void spi_byte(uint8_t data){
    SPDR = data;
    while(!(SPSR&(1<<SPIF)));
}

extern void spi_put(uint8_t data){
    _clr(PORT_SPI,SCE);
    spi_byte(data);
    _set(PORT_SPI,SCE);
}

extern void spi_puts(uint8_t *data){
    _clr(PORT_SPI,SCE);
    while(*data){
        spi_byte(*data);
        data++;
    }
    _set(PORT_SPI,SCE);
}

extern void spi_array(uint8_t data[],int len){
    _clr(PORT_SPI,SCE);
    for(int i=0;i<len;i++){
        spi_byte(data[i]);
    }
    _set(PORT_SPI,SCE);
}

extern uint8_t spi_get(void){
    while(!(SPSR & (1 << SPIF)));
    return SPDR;
}