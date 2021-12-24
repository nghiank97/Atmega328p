
#include "../Inc/pcf8574.h"

static void pcf8574_put(uint8_t byte){
    i2c_start();
    i2c_put(ADD_WRITE);
    i2c_put(byte);
    i2c_stop(); 
}
              
extern void i2c_lcd4_cmd(uint8_t Cmd){

    uint8_t data_u, data_l;
    data_u = (Cmd&0xf0);
    data_l = ((Cmd<<4)&0xf0);
    
    pcf8574_put(data_u|0x08);
    pcf8574_put(data_u|0x00);
    pcf8574_put(data_l|0x08);
    pcf8574_put(data_l|0x00);
}

extern void i2c_lcd4_put(char Data)
{
    uint8_t data_u, data_l;
    data_u = (Data&0xf0);
    data_l = ((Data<<4)&0xf0);

    pcf8574_put(data_u|0x0A);
    pcf8574_put(data_u|0x02);
    pcf8574_put(data_l|0x0A);
    pcf8574_put(data_l|0x02);
}

static void i2c_lcd4_high(uint8_t Data)
{
    uint8_t data_u;
    data_u = (Data&0xf0);
      
    pcf8574_put(data_u|0x08);
    pcf8574_put(data_u|0x00);
}

extern void i2c_lcd4_puts(char *Data){
    int local = 0;
    while(Data[local]!= 0){
        uint8_t data_u, data_l;
        data_u = (Data[local]&0xf0);
        data_l = ((Data[local]<<4)&0xf0);
        
        pcf8574_put(data_u|0x0A);
        pcf8574_put(data_u|0x02);
        pcf8574_put(data_l|0x0A);
        pcf8574_put(data_l|0x02);
        local+= 1;
    }
}

extern void i2c_lcd4_printf(int row,int col,char *Data){
    int local = 0;
    i2c_lcd4_cursor(row,col);
    while(Data[local]!= 0){
        uint8_t data_u, data_l;
        data_u = (Data[local]&0xf0);
        data_l = ((Data[local]<<4)&0xf0);
        
        pcf8574_put(data_u|0x0A);
        pcf8574_put(data_u|0x02);
        pcf8574_put(data_l|0x0A);
        pcf8574_put(data_l|0x02);
        local+= 1;
    }
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


extern void i2c_lcd4_init(void){
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
