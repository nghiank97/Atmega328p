
#include "mcp2515.h"

extern void mcp2515_init(void){
    mcp2515_spi_init();
    mcp2515_spi_disable();
}

extern void mcp2515_write(uint8_t address, uint8_t data){
    mcp2515_spi_enable();
    mcp2515_spi_byte(0x02);
    mcp2515_spi_byte(address);
    mcp2515_spi_byte(data);
    mcp2515_spi_disable();
}

extern uint8_t mcp2515_read_status(uint8_t address){
    uint8_t data = 0;
    mcp2515_spi_enable();
    mcp2515_spi_byte(MCP_READ_STATUS);
    data = mcp2515_spi_transfer(address);
    mcp2515_spi_disable();
    return data;
}