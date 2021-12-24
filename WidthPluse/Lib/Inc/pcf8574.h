#ifndef PCF8574_H_
#define PCF8574_H_
#include "config.h"
#include "i2c.h"

#if defined LCD16x2|| defined LCD16x4|| defined LCD20x4

#define a0 0
#define a1 0
#define a2 0
#define ADD_WRITE (64+a2*8+a1*4+a0*2)
#define ADD_READ (ADD_WRITE+1)

extern void i2c_lcd4_init(void);
extern void i2c_lcd4_cmd(uint8_t Cmd);
extern void i2c_lcd4_put(char Data);
extern void i2c_lcd4_puts(char* Data);
extern void i2c_lcd4_printf(int row, int col,char* Data);
extern void i2c_lcd4_cursor(int row, int col);

#else
    #error Khong dinh nghia lcd
#endif

#endif
