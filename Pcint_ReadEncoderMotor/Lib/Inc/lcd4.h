
#ifndef LCD4_H_
#define LCD4_H_
#include "config.h"

#if defined LCD16x2|| defined LCD16x4|| defined LCD20x4

void lcd4_init(void);
void lcd4_cmd(uint8_t cmd);
void lcd4_put(char Data);
void lcd4_puts(char* Data);
void lcd4_print(int row, int col, char* Data);
void lcd4_array(int row,int col, char Data[],int len);
void lcd4_cursor(int row, int col);

#else
    #error Khong dinh nghia lcd
#endif

#endif
