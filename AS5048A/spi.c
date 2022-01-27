
#include "elephant.h"

extern void spi_init(int intp){

    DIR_SPI |= (1<<SS_PIN)|(1<<MOSI_PIN)|(1<<SCLK_PIN);
    set_input(DIR_SPI,MISO_PIN);
    switch (intp){
        case 0:{
            SPCR = (1<<SPE)|(1<<MSTR)|SPI_CLOCK|SPI_MODE;
            return; 
        }
        case 1:{
            SREG |= (1<<SREG_I);
            SPCR = (1<<SPIE)|(1<<SPE)|(1<<MSTR)|SPI_CLOCK|SPI_MODE;
            return; 
        }
    }
}

extern void spi_byte(uint8_t data){
    SPDR = data;
    while(!(SPSR&(1<<SPIF)));
}

extern void spi_put(uint8_t data){
    CLR(PORT_SPI,SS_PIN);
    SPDR = data;
    while(!(SPSR&(1<<SPIF)));
    SET(PORT_SPI,SS_PIN);
}

extern void spi_puts(uint8_t *datas,int len){

    CLR(PORT_SPI,SS_PIN);
    for(int i=0;i<len;i++){
        SPDR = datas[i];
        while(!(SPSR&(1<<SPIF)));
    }
    SET(PORT_SPI,SS_PIN);
}

extern uint8_t spi_transfer(uint8_t data){
    SPDR = data;
    while(!(SPSR&(1<<SPIF)));
    return SPDR;
}

extern void spi_word(uint16_t data){
    uint8_t msb = (data>>8)&0xFF;
    uint8_t lsb = data&0xFF;
    CLR(PORT_SPI,SS_PIN);
    if (!(SPCR & BV(DORD))) {
      SPDR = msb;
      asm volatile("nop");
      while (!(SPSR & BV(SPIF)));
      SPDR = lsb;
      asm volatile("nop");
      while (!(SPSR & BV(SPIF)));
    }
    else 
    {
      SPDR = lsb;
      asm volatile("nop");
      while (!(SPSR & BV(SPIF)));
      SPDR = msb;
      asm volatile("nop");
      while (!(SPSR & BV(SPIF)));
    }
    SET(PORT_SPI,SS_PIN);
}