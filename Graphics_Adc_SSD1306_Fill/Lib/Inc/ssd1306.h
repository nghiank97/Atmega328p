/*
 * ssd1306.h
 *
 * Created: 03-01-2018 17:33:51
 *  Author: osc
 */ 


#ifndef SSD1306_H_
#define SSD1306_H_
#include "config.h"
#include "i2c.h"

#define GLCD_128_64 						        0
#define GLCD_128_32						            1 
#define GLCD_96_16						            2
	
#define SSD1306_ADDRESS                             0x7A

#if (GLCD_SIZE == GLCD_128_64) 
	#define SSD1306_LCDWIDTH          			    128
	#define SSD1306_LCDHEIGHT         			    64
#elif (GLCD_SIZE == GLCD_128_32)
	#define SSD1306_LCDWIDTH         			    128
	#define SSD1306_LCDHEIGHT        			    32
#elif (GLCD_SIZE == GLCD_96_16)
	#define SSD1306_LCDWIDTH          			    96
	#define SSD1306_LCDHEIGHT         			    16
#endif

#define SSD1306_SETCONTRAST                         0x81
#define SSD1306_DISPLAYALLON_RESUME                 0xA4
#define SSD1306_DISPLAYALLON                        0xA5
#define SSD1306_NORMALDISPLAY                       0xA6
#define SSD1306_INVERTDISPLAY                       0xA7
#define SSD1306_DISPLAYOFF                          0xAE
#define SSD1306_DISPLAYON                           0xAF
#define SSD1306_SETDISPLAYOFFSET                    0xD3
#define SSD1306_SETCOMPINS                          0xDA
#define SSD1306_SETVCOMDETECT                       0xDB
#define SSD1306_SETDISPLAYCLOCKDIV                  0xD5
#define SSD1306_SETPRECHARGE                        0xD9
#define SSD1306_SETMULTIPLEX                        0xA8
#define SSD1306_SETLOWCOLUMN                        0x00
#define SSD1306_SETHIGHCOLUMN                       0x10
#define SSD1306_SETSTARTLINE                        0x40
#define SSD1306_MEMORYMODE                          0x20
#define SSD1306_COLUMNADDR                          0x21
#define SSD1306_PAGEADDR                            0x22
#define SSD1306_COMSCANINC                          0xC0
#define SSD1306_COMSCANDEC                          0xC8
#define SSD1306_SEGREMAP                            0xA0
#define SSD1306_CHARGEPUMP                          0x8D
#define SSD1306_EXTERNALVCC                         0x1
#define SSD1306_SWITCHCAPVCC                        0x2

#define SSD1306_SETSTARTPAGE                        0xB0


enum SIGNAL{
    OFF_PIXEL = 0,
    ON_PIXEL = 1
};

enum INVERT_PIXEL{
    INVERT = 0,
    NORMAL = 1
};

extern void ssd1306_command(uint8_t cmd);
extern void ssd1306_data(uint8_t data);

extern void ssd1306_print_string(char *string, enum INVERT_PIXEL color);
extern void ssd1306_print_stringXY(char *string, int X, int Y, enum INVERT_PIXEL color);

extern void ssd1306_cursor(uint8_t row,uint8_t col);
extern void ssd1306_gotoXY(uint8_t X,uint8_t Y);

extern void ssd1306_print_char(uint8_t data, enum INVERT_PIXEL color);
extern void ssd1306_print_charXY(uint8_t data, int X, int Y, enum INVERT_PIXEL color);
extern void ssd1306_big_number(char string, int X, int Y, enum INVERT_PIXEL color);

extern void ssd1306_print_char_4x6_XY(char data, int X, int Y, enum INVERT_PIXEL color);
extern void ssd1306_print_string_4x6_XY(char *string, int X, int Y, enum INVERT_PIXEL color);

extern void ssd1306_display_on(void);
extern void ssd1306_display_off(void);

extern void ssd1306_clear_display(void);
extern void ssd1306_reset_display(void);

extern void ssd1306_logo(const uint8_t *logo, enum INVERT_PIXEL color);

extern void ssd1306_invert_display(void);
extern void ssd1306_normal_display(void);

extern void ssd1306_init(void);

#define OLED_GRAHPICS

#ifdef OLED_GRAHPICS

enum TYPE_MAP_PIXEL{
    UNCHANGED = 0,
    CHANGED = 1
};

extern void ssd1306_pixel(int row,int col,enum SIGNAL signal);
extern void ssd1306_line(int y1, int x1, int y2, int x2,enum SIGNAL color);
extern void ssd1306_8_point(int xc, int yc, int x, int y, enum SIGNAL color);
extern void ssd1306_circle(int yc,int xc,int r,enum SIGNAL color);
extern void ssd1306_box(int y1, int x1, int y2, int x2,enum SIGNAL color);

extern void ssd1306_box_fill(int y1, int x1, int y2, int x2,enum SIGNAL color);
#endif

enum ARROW_TYPE{
    RIGHT_ARROW         = 0,
    LEFT_ARROW          = 1,
    DOWN_ARROW          = 2,
    UP_ARROW            = 3
};

/* user function */
extern void ssd1306_scrool(int row,int time);
extern void ssd1306_clear_row(int row);
extern void ssd1306_load_arrow(int row,int col,enum ARROW_TYPE type,enum SIGNAL color);

#endif /* SSD1306_H_ */