
#include "elephant.h"

extern void mcp23017_write(MCP2301_REGISTER address,uint8_t data){
    i2c_start();
    i2c_put(MCP23017_ADDRESS_WRITE);
    i2c_put(address);
    i2c_put(data);
    i2c_stop();
}

extern void mcp23017_gpio_byte(uint8_t data_a,uint8_t data_b){
    mcp23017_write(OLATA,data_a);
    mcp23017_write(OLATB,data_b);
}

extern void mcp23017_gpio_word(uint16_t data){
    uint8_t data_a = (uint8_t)data>>8&0xFF;
    uint8_t data_b = (uint8_t)data&0xFF;
    mcp23017_write(OLATA,data_a);
    mcp23017_write(OLATB,data_b);
}

extern void mcp23017_init(void){
    i2c_init();

    #if BLANK_MODE == 0
        mcp23017_write(IOCONA,(0<<BLANK)|(1<<SEQOP));
        mcp23017_write(IOCONB,(0<<BLANK)|(1<<SEQOP));
    #else
        mcp23017_write(IOCONA,(1<<BLANK)|(1<<SEQOP));
        mcp23017_write(IOCONB,(1<<BLANK)|(1<<SEQOP));
    #endif
    mcp23017_write(IODIRA,0x00);
    mcp23017_write(IODIRB,0x00);

    mcp23017_gpio_word(0x0000);
}
