
#include "elephant.h"

extern void glcd_128x64_mcp23017_init(void){
    uint8_t data_a = 0x00, data_b = 0x00;
    mcp23017_init();

    data_a = (1<<GLCD_128X64_CS2)|(1<<GLCD_128X64_CS1)|(1<<GLCD_128X64_RST);
    mcp23017_gpio_byte(data_a,data_b);
    delay_ms(1);

    glcd_128x64_mcp23017_cmd(0x3E); /* Display OFF */
    glcd_128x64_mcp23017_cmd(0x40); /* Set Y address (column=0) */
    glcd_128x64_mcp23017_cmd(0xB8); /* Set x address (page=0) */
    glcd_128x64_mcp23017_cmd(0xC0); /* Set z address (start line=0) */
    glcd_128x64_mcp23017_cmd(0x3F); /* Display ON */
}

extern void glcd_128x64_mcp23017_cmd(uint8_t data)
{                  
    uint8_t cmd =(0<<GLCD_128X64_RW)|(0<<GLCD_128X64_RS);
    uint8_t control = (1<<GLCD_128X64_EN)|cmd;
    mcp23017_gpio_byte(control,data);
    delay_us(10);
    control = (0<<GLCD_128X64_EN)|cmd;
    mcp23017_gpio_byte(control,data);
}

extern void glcd_128x64_mcp23017_write(glcd128x64_page page,uint8_t data)
{                  
    uint8_t cmd =(0<<GLCD_128X64_RW)|(1<<GLCD_128X64_RS);
    uint8_t control = 0x00;
    switch (page)
    {
    case PAGE_0:

        control = (1<<GLCD_128X64_CS2)|(0<<GLCD_128X64_CS1)|(1<<GLCD_128X64_EN)|cmd;
        mcp23017_gpio_byte(control,data);
        delay_us(10);
        
        control = (1<<GLCD_128X64_CS2)|(0<<GLCD_128X64_CS1)|(0<<GLCD_128X64_EN)|cmd;
        mcp23017_gpio_byte(control,data);

        break;
    case PAGE_1:
        control = (0<<GLCD_128X64_CS2)|(1<<GLCD_128X64_CS1)|(1<<GLCD_128X64_EN)|cmd;
        mcp23017_gpio_byte(control,data);
        delay_us(10);
        
        control = (0<<GLCD_128X64_CS2)|(1<<GLCD_128X64_CS1)|(0<<GLCD_128X64_EN)|cmd;
        mcp23017_gpio_byte(control,data);
        break;
    default:
        break;
    }
}
