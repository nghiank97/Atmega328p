
#include "bee.h"

static volatile uint8_t ADD_WRITE = 0x00;
static volatile uint8_t ADD_READ = 0x00;

static void pcf8574_put(uint8_t byte){
    i2c_start();
    i2c_put(ADD_WRITE);
    i2c_put(byte);
    i2c_stop(); 
}
              
extern void i2c_lcd4_cmd(uint8_t Cmd){
    uint8_t data_u, data_l;
    data_u = (Cmd&0xf0)|0x04;
    data_l = (Cmd<<4)|0x04;
    
    pcf8574_put(data_u);delay_us(100);
    pcf8574_put(_clr(data_u,2));

    pcf8574_put(data_l);delay_us(100);
    pcf8574_put(_clr(data_l,2));
    delay_ms(2);
}

extern void i2c_lcd4_put(char Data){
    uint8_t data_u, data_l;
    data_u = (Data&0xF0)|0x05;
    data_l = (Data<<4)|0x05;

    pcf8574_put(data_u);delay_us(100);
    pcf8574_put(_clr(data_u,2));
    
    pcf8574_put(data_l);delay_us(100);
    pcf8574_put(_clr(data_l,2));
    delay_ms(1);
}

extern void i2c_lcd4_high(uint8_t byte){
    uint8_t data_u = (byte&0xf0)|0x04;
    pcf8574_put(data_u);delay_us(100);
    pcf8574_put(_clr(data_u,2));
}

extern void i2c_lcd4_puts(char *Data){
    while(*Data!= 0){
        i2c_lcd4_put(*Data);
        Data+= 1;
    }
}

extern void i2c_lcd4_print(int row,int col,char *Data){
    i2c_lcd4_cursor(row,col);
    i2c_lcd4_puts(Data);
}

#ifdef LCD16x2

extern void i2c_lcd4_cursor(int row,int col){
    if (row==0)
        i2c_lcd4_cmd(0x80+col);
    else
        i2c_lcd4_cmd(0x80+0x40+col);
}

#elif defined(LCD16x4)
void i2c_lcd4_cursor(int row,int col){
    switch (row){
		case 0:{
			i2c_lcd4_cmd(0x80+col);
			return;
			}
		case 1:{
			i2c_lcd4_cmd(0x80+0x40+col);
			return;
			}
		case 2:{
			i2c_lcd4_cmd(0x80+0x10+col);
			return;
			}
		case 3:{
			i2c_lcd4_cmd(0x80+0x50+col);
			return;
		}
	}
}

#elif defined(LCD20x4)
void i2c_lcd4_cursor(int row,int col){
    switch (row){
		case 0:{
			i2c_lcd4_cmd(0x80+col);
			return;
			}
		case 1:{
			i2c_lcd4_cmd(0x80+0x40+col);
			return;
			}
		case 2:{
			i2c_lcd4_cmd(0x80+0x14+col);
			return;
			}
		case 3:{
			i2c_lcd4_cmd(0x80+0x54+col);
			return;
		}
	}
}

#endif

extern void i2c_lcd4_init(uint8_t address){
    ADD_WRITE = (uint8_t)(address+PCF8574_a2*8+PCF8574_a1*4+PCF8574_a0*2);
    ADD_READ = (ADD_WRITE+1);

    i2c_init();
    delay_ms(60);
    i2c_lcd4_high(0x30); 
    
    delay_ms(5);
    i2c_lcd4_high(0x30);
    
    delay_ms(1);
    i2c_lcd4_high(0x30);
    i2c_lcd4_high(0x20);
    
    i2c_lcd4_cmd(0x01);
    i2c_lcd4_cmd(0x28);
    i2c_lcd4_cmd(0x0c);
    i2c_lcd4_cmd(0x06);   
    delay_ms(10);
}
