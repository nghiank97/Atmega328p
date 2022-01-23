#ifndef PCF8574_H_
#define PCF8574_H_
#include "config.h"
#include "i2c.h"

#if defined LCD16x2|| defined LCD16x4|| defined LCD20x4

#define PCF8574_a0      1
#define PCF8574_a1      1
#define PCF8574_a2      1

extern void i2c_lcd4_init(uint8_t address);
extern void i2c_lcd4_cmd(uint8_t Cmd);
extern void i2c_lcd4_put(char Data);
extern void i2c_lcd4_puts(char* Data);
extern void i2c_lcd4_print(int row, int col,char* Data);
extern void i2c_lcd4_cursor(int row, int col);

#else
    #error Khong dinh nghia lcd
#endif

#endif
