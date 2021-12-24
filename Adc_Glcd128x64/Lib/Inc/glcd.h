
#ifndef GLCD_H_
#define GLCD_H_
#include "config.h"

enum GLCD_CONTROL{
    GLCD_ON = 0x3f,
    GLCD_OFF = 0x3e,
    GLCD_ADD = 0x40,
    GLCD_PAGE = 0xb8
};

#define LEN_FONT                    6

extern void glcd_part(int part);
extern void glcd_page(int page);
extern void glcd_write(uint8_t byte,int color);
extern void glcd_cmd(uint8_t byte);

extern void glcd_put(char Data,int part,int page,int str_col,int color);
extern void glcd_puts(char *Data,int part,int page,int str_col,int color);
extern void glcd_init(void);

extern void glcd_big_number(char number,int part,int page,int str_col,int color);

#endif