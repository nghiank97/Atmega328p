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

#define SSD1306_LCDWIDTH                            128
#define SSD1306_LCDHEIGHT                           64

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

#define SSD1306_ADDRESS                             0x7A    //display write address

extern void ssd1306_command(uint8_t cmd);
extern void ssd1306_data(uint8_t data);
extern void ssd1306_init(void);
extern void ssd1306_send_string(char *string);
extern void ssd1306_send_stringXY( char *string, int X, int Y);
extern void ssd1306_cursor(uint8_t row,uint8_t col);
extern void ssd1306_gotoXY(uint8_t X,uint8_t Y);
extern void ssd1306_send_char(uint8_t data);
extern void ssd1306_send_charXY(uint8_t data, int X, int Y);
extern void ssd1306_display_on(void);
extern void ssd1306_display_off(void);
extern void ssd1306_clear_display(void);
extern void ssd1306_reset_display(void);
extern void ssd1306_logo(const uint8_t *logo);
extern void ssd1306_big_number(char string, int X, int Y);
extern void ssd1306_invert_display(void);
extern void ssd1306_normal_display(void);

#endif /* SSD1306_H_ */