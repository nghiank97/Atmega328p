
#ifndef MCP2515_CONFIG_H
#define MCP2515_CONFIG_H
#include "elephant.h"

extern void mcp2515_spi_init(void);
extern void mcp2515_spi_byte(uint8_t data);
extern uint8_t mcp2515_spi_read(void);
extern void mcp2515_spi_enable(void);
extern void mcp2515_spi_disable(void);
extern uint8_t mcp2515_spi_transfer(uint8_t data);

#endif
