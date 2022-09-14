
#include "mcp2515_config.h"

extern void mcp2515_spi_init(void){
    DDRB |= (1<<2)|(1<<3)|(1<<5);
    DDRB &=~ (1<<4);
    SREG |= (1<<SREG_I);
    SPCR = (1<<SPIE)|(1<<SPE)|(1<<MSTR)|(0<<SPR1)|(1<<SPR0)|(0<<CPOL)|(1<<CPHA);
}
extern void mcp2515_spi_byte(uint8_t data){
    SPDR = data;
    while(!(SPSR & (1<<SPIF)));
}
extern uint8_t mcp2515_spi_read(void){
    while(!(SPSR&(1<<SPIF)));
    return SPDR;
}
extern void mcp2515_spi_enable(void){
    PORTD &=~ (1<<2);
}
extern void mcp2515_spi_disable(void){
    PORTD |= (1<<2);
}

extern uint8_t mcp2515_spi_transfer(uint8_t data){
    SPDR = data;
    while(!(SPSR&(1<<SPIF)));
    return SPDR;
}