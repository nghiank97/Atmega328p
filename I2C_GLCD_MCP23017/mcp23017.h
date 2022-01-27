
/*
    Copyright : Khac Nghia
*/

#ifndef MCP23017_H
#define MCP23017_H
#include "style.h"

#ifndef I2C_H_
#error "Don't inclue i2c library"
#endif

#define BLANK_MODE          0

#if (BLANK_MODE == 1)

typedef enum{
IODIRA                      =0x00,
IODIRB                      =0x10,    
IPOLA                       =0x01,
IPOLB                       =0x11,
GPINTENA                    =0x02,
GPINTENB                    =0x12,
DEFVALA                     =0x03,
DEFVALB                     =0x13,
INTCONA                     =0x04,
INTCONB                     =0x14,
IOCONA                      =0x05,
IOCONB                      =0x15,
GPPUA                       =0x06,
GPPUB                       =0x16,
INTFA                       =0x07,
INTFB                       =0x17,
INTCAPA                     =0x08,
INTCAPB                     =0x18,
GPIOA                       =0x09,
GPIOB                       =0x19,
OLATA                       =0x0A,
OLATB                       =0x1A
}MCP2301_REGISTER;

#else

typedef enum{
IODIRA                      =0x00,
IODIRB                      =0x01,    
IPOLA                       =0x02,
IPOLB                       =0x03,
GPINTENA                    =0x04,
GPINTENB                    =0x05,
DEFVALA                     =0x06,
DEFVALB                     =0x07,
INTCONA                     =0x08,
INTCONB                     =0x09,
IOCONA                      =0x0A,
IOCONB                      =0x0B,
GPPUA                       =0x0C,
GPPUB                       =0x0D,
INTFA                       =0x0E,
INTFB                       =0x0F,
INTCAPA                     =0x10,
INTCAPB                     =0x11,
GPIOA                       =0x12,
GPIOB                       =0x13,
OLATA                       =0x14,
OLATB                       =0x15
}MCP2301_REGISTER;

#endif

typedef enum{
BLANK                       = bit_7,
MIRROR                      = bit_6,    
SEQOP                       = bit_5,
DISSLW                      = bit_4,
HAEN                        = bit_3,
ODR                         = bit_2,
INTPOL                      = bit_1,
}MCP2301_ICON_REGISTER;

#define MCP23017_A0                 0
#define MCP23017_A1                 0
#define MCP23017_A2                 0
#define MCP23017_ADDRESS            (0x40+8*MCP23017_A2+4*MCP23017_A1+2*MCP23017_A0)
#define MCP23017_ADDRESS_WRITE	    MCP23017_ADDRESS
#define MCP23017_ADDRESS_READ       (MCP23017_ADDRESS|0x01)

extern void mcp23017_write(MCP2301_REGISTER address,uint8_t data);
extern void mcp23017_gpio_byte(uint8_t data_a,uint8_t data_b);
extern void mcp23017_gpio_word(uint16_t data);
extern void mcp23017_init(void);

#endif
