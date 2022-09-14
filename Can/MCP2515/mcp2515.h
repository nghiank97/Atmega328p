
#ifndef MCP2515_H
#define MCP2515_H
#include "elephant.h"

extern void mcp2515_init(void);
extern void mcp2515_write(uint8_t address, uint8_t data);
extern uint8_t mcp2515_read_status(uint8_t address);

#endif
