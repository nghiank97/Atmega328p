
#include "elephant.h"

#if defined(SPI_MASTER)

extern void SPI_ENABLE(void){
    CLR(PORT_SPI,SS_PIN);
}
extern void SPI_DISABLE(void){
    SET(PORT_SPI,SS_PIN);
}

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
    while(!(SPSR & (1<<SPIF)));
}

extern void spi_put(uint8_t data){
    SPI_ENABLE();
    spi_byte(data);
    SPI_DISABLE();
}

extern void spi_puts(uint8_t *data,int len){
    SPI_ENABLE();
    for(int i=0;i<len;i++){
        spi_byte(data[i]);
    }
    SPI_DISABLE();
}

extern void spi_print(char *data)
{
    SPI_ENABLE();
    while(*data != 0)
    {
        spi_byte(*data);
        data+=1;
    }
    SPI_DISABLE();
}

extern void spi_println(char *data)
{
    SPI_ENABLE();
    while(*data != 0)
    {
        spi_byte(*data);
        data+=1;
    }
    spi_byte('\r');spi_byte('\n');
    SPI_DISABLE();
}

extern void spi_word(uint16_t data){
    uint8_t msb = (data>>8)&0xFF;
    uint8_t lsb = data&0xFF;
    SPI_ENABLE();
    if (!(SPCR & BV(DORD))) {
        SPDR = msb;
        while(!(SPSR&(1<<SPIF)));
        SPDR = lsb;
        while(!(SPSR&(1<<SPIF)));
    }
    else 
    {
        SPDR = lsb;
        while(!(SPSR&(1<<SPIF)));
        SPDR = msb;
        while(!(SPSR&(1<<SPIF)));
    }
    SPI_DISABLE();
}

#elif defined(SPI_SLAVE)
extern void spi_init(void){
    set_input(DIR_SPI,SS_PIN);
    set_input(DIR_SPI,MOSI_PIN);
    set_input(DIR_SPI,SCLK_PIN);
    set_output(DIR_SPI,MISO_PIN);
    SPCR = (1<<SPE);
}

extern uint8_t spi_read(void){
    while(!(SPSR&(1<<SPIF)));
    return SPDR;
}
#endif
