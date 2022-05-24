
/*
    Copyright : Khac Nghia
*/

#ifndef GLCD_128X64_MCP23017_H
#define GLCD_128X64_MCP23017_H
#include "style.h"
#include "mcp23017.h"

#ifndef GLCD_128X64_WIDTH
#define GLCD_128X64_WIDTH                   128
#endif

#ifndef GLCD_128X64_HIGH
#define GLCD_128X64_HIGH                    64
#endif

#define GLCD_128X64_CS1                     2       // GPIO A
#define GLCD_128X64_CS2                     3       // GPIO A
#define GLCD_128X64_RST                     4       // GPIO A

#define GLCD_128X64_RS                      5       // GPIO A
#define GLCD_128X64_RW                      6       // GPIO A
#define GLCD_128X64_EN                      7       // GPIO A

#ifndef MCP23017_H
    #error "don't inclue library"
#endif

#define GLCD_128X64_CONTROL                 OLATA
#define GLCD_128X64_DATA                    OLATB

typedef enum{
    PAGE_0 = 0,
    PAGE_1 = 1
}glcd128x64_page;

extern void glcd_128x64_mcp23017_init(void);
extern void glcd_128x64_mcp23017_cmd(uint8_t data);
extern void glcd_128x64_mcp23017_write(glcd128x64_page page,uint8_t data);

#endif
