
#ifndef NOKIA5110_H_
#define NOKIA5110_H_
#include "config.h"
#include "spi.h"

enum COMMAND{
    INVERSE_BACKGROUND = 0x0D
};

enum SIGNAL{
    OFF_PIXEL = 0,
    ON_PIXEL = 1
};

enum BACKGROUND{
    INVERSE_BG = 0,
    NORMAL_BG = 1
};

enum SIZE_SCREEN{
    COL_SCREEN = 0x0054,
    ROW_SCREEN = 0x0030,
    PIXEL_SCREEN = 504
};

extern void nokia5110_cmd(uint8_t cmd);
extern void nokia5110_put(uint8_t data);
extern void nokia5110_puts(uint8_t *data,int len);
extern void nokia5110_blank(void);
extern void nokia5110_image(int row, int col,const uint8_t *image,enum BACKGROUND bg);
extern void nokia5110_full_image(const uint8_t *image,enum BACKGROUND bg);
extern void nokia5110_cursor(uint8_t row,uint8_t col);
extern void nokia5110_init(void);

extern void nokia5110_5x8_put(int row,int col,char Data, enum BACKGROUND bg);
extern void nokia5110_5x8_puts(int row,int col,char *Data, enum BACKGROUND bg);
extern void nokia5110_5x8_array(int row,int col,char *Data,int len, enum BACKGROUND bg);


#endif
