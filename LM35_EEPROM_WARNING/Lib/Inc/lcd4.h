
#ifndef LCD4_H_
#define LCD4_H_
#include "config.h"

#if defined LCD16x2|| defined LCD16x4|| defined LCD20x4

extern void lcd4_init(void);
extern void lcd4_cmd(uint8_t cmd);
extern void lcd4_put(char Data);
extern void lcd4_puts(char* Data);
extern void lcd4_printf(int row, int col, char* Data);
extern void lcd4_array(int row,int col, char Data[],int len);
extern void lcd4_cursor(int row, int col);

#else
    #error Khong dinh nghia lcd
#endif

#endif