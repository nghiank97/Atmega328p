
#include "../Inc/spi.h"

extern void spi_init(int intp){

    DIR_SPI |= (1<<SCE)|(1<<DIN)|(1<<SCLK);
    _set(PORT_SPI,SCE);
    switch (intp){
        case 0:{
            SPCR = (1<<SPE)|(1<<MSTR)|(1 << SPR1)|(1<<SPR0);
            return; 
        }
        case 1:{
            SREG |= (1<<SREG_I);
            SPCR = (1<<SPIE)|(1<<SPE)|(1<<MSTR)|(1 << SPR1)|(1<<SPR0);
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
    SPDR = data;
    while(!(SPSR&(1<<SPIF)));
    _set(PORT_SPI,SCE);
}

extern void spi_puts(uint8_t *datas,int len){

    _clr(PORT_SPI,SCE);
    for(int i=0;i<len;i++){
        SPDR = datas[i];
        while(!(SPSR&(1<<SPIF)));
    }
    _set(PORT_SPI,SCE);
}

extern uint8_t spi_get(){
    while(!(SPSR&(1<<SPIF)));
    return SPDR;
}