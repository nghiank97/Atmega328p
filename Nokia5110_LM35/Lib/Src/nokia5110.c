
#include "../Inc/font.h"
#include "../Inc/spi.h"
#include "../Inc/nokia5110.h"

extern void nokia5110_reset(void){
    _clr(PORT_NOKIA,RST);
    delay_us(500);
    _set(PORT_NOKIA,RST);
}

extern void nokia5110_cmd(uint8_t cmd){
    _clr(PORT_NOKIA,D_C);
    spi_put(cmd);
}

extern void nokia5110_put(uint8_t data){
    _set(PORT_NOKIA,D_C);
    spi_put(data); 
}

extern void nokia5110_puts(uint8_t *data,int len){
    _set(PORT_NOKIA,D_C);
    spi_puts(data,len);
}

extern void nokia5110_image(int row, int col,const uint8_t *image,enum BACKGROUND bg){
    int size_col = (int)pgm_read_word(&image[0]);
    int size_row = (int)pgm_read_word(&image[2]);
    uint16_t index = 3;
    size_row/=8;
    if (bg == NORMAL_BG){
        for(int i=0;i<size_row;i++){
            nokia5110_cursor(row+i,col);
            _set(PORT_NOKIA,D_C);
            _clr(PORT_SPI,SCE);
            for(int j=0;j<size_col;j++){
                spi_byte(pgm_read_byte(&image[index++]));
            }
            _set(PORT_SPI,SCE);
        }
    }
    else{
        for(int i=0;i<size_row;i++){
            nokia5110_cursor((uint8_t)row+i,(uint8_t)col);
            _set(PORT_NOKIA,D_C);
            _clr(PORT_SPI,SCE);
            for(int j=0;j<size_col;j++){
                spi_byte(0xff-pgm_read_byte(&image[index++]));
            }
            _set(PORT_SPI,SCE);
        }
    }
}

extern void nokia5110_full_image(const uint8_t *image,enum BACKGROUND bg){
    uint16_t col = pgm_read_word(&image[0]);
    uint16_t row = pgm_read_word(&image[2]);
    uint16_t j = 3;
    if ((col != COL_SCREEN) && (row != ROW_SCREEN)){
        return;
    }
    nokia5110_cursor(0,0);
    _set(PORT_NOKIA,D_C);
    _clr(PORT_SPI,SCE);
    if (bg == NORMAL_BG){
        for(int i=0;i<PIXEL_SCREEN;i++){
            spi_byte(pgm_read_byte(&image[j++]));
        }
    }
    else{
        for(int i=0;i<PIXEL_SCREEN;i++){
            spi_byte(0xff-pgm_read_byte(&image[j++]));
        }
    }
    _set(PORT_SPI,SCE);
}

extern void nokia5110_cursor(uint8_t row,uint8_t col){
    int i;
	i = row*84 + col;
	if (i < 0 || i > 503)
        return;
    nokia5110_cmd(0x80|col);  
    nokia5110_cmd(0x40|row);
}

extern void nokia5110_blank(void){
    nokia5110_cursor(0,0);
    _set(PORT_NOKIA,D_C);
    _clr(PORT_SPI,SCE);
    for(int i=0;i<504;i++){
        spi_byte(0x00);
    }
    _set(PORT_SPI,SCE);
}

extern void nokia5110_init(void){
    DIR_NOKIA |= (1<<RST)|(1<<D_C);
    DIR_LED |= (1<<LED);
    spi_init(0);
    nokia5110_reset();
    nokia5110_cmd(0x21);
    nokia5110_cmd(0x13);
    nokia5110_cmd(0x07);
    nokia5110_cmd(0xc0);
    nokia5110_cmd(0x20);   
    nokia5110_cmd(0x0c);        
}

extern void nokia5110_5x8_put(int row,int col,char Data, enum BACKGROUND bg){
    int j = 0;  
    uint8_t buff;
    nokia5110_cursor(row,col);
    _set(PORT_NOKIA,D_C);
    _clr(PORT_SPI,SCE);
    if (bg == NORMAL_BG){
        for(j=0;j<6;j++){
            buff = pgm_read_byte(&ASCII[Data-0x20][j]);
            spi_byte(buff);
        }       
    }
    else{
        for(j=0;j<6;j++){
            buff = pgm_read_byte(&ASCII[Data-0x20][j]);
            spi_byte(buff);
        }
    }
    _set(PORT_SPI,SCE);          
}

extern void nokia5110_5x8_puts(int row,int col,char *Data, enum BACKGROUND bg){
    int i = 0;
    int j = 0;  
    uint8_t buff;
    nokia5110_cursor(row,col);
    _set(PORT_NOKIA,D_C);
    _clr(PORT_SPI,SCE);
    if (bg == NORMAL_BG){
        while(Data[i] != 0){
            for(j=0;j<6;j++){
                buff = pgm_read_byte(&ASCII[Data[i]-0x20][j]);
                spi_byte(buff);
            }
            i +=1;
        }       
    }
    else{
        while(Data[i] != 0){
            for(j=0;j<6;j++){
                buff = 0xff-pgm_read_byte(&ASCII[Data[i]-0x20][j]);
                spi_byte(buff);
            }
            i +=1;
        }      
    }
    _set(PORT_SPI,SCE);          
}

extern void nokia5110_5x8_array(int row,int col,char *Data,int len, enum BACKGROUND bg){
    uint8_t buff;
    nokia5110_cursor(row,col);
    _set(PORT_NOKIA,D_C);
    _clr(PORT_SPI,SCE);
    if (bg == NORMAL_BG){
        for(int i=0;i<len;i++){
            for(int j=0;j<6;j++){
                buff = pgm_read_byte(&ASCII[Data[i]-0x20][j]);
                spi_byte(buff);
            }
        }       
    }
    else{
        for(int i=0;i<len;i++){
            for(int j=0;j<6;j++){
                buff = 0xff-pgm_read_byte(&ASCII[Data[i]-0x20][j]);
                spi_byte(buff);
            }
        }   
    }
    _set(PORT_SPI,SCE);          
}

extern void nokia5110_medium_number(int row,int col,char number, enum BACKGROUND bg){
    uint8_t buff;
    int num = ((int)number)-48;
    nokia5110_cursor(row,col);
    if (bg == NORMAL_BG){
        _set(PORT_NOKIA,D_C);
        _clr(PORT_SPI,SCE);
        for(int col= 0;col< 12;col++){
            buff = pgm_read_byte(&MediumNumbers[num][col]);
            spi_byte(buff);
        }
        _set(PORT_SPI,SCE);          

        nokia5110_cursor(row+1,col);
        _set(PORT_NOKIA,D_C);
        _clr(PORT_SPI,SCE);
        for(int col= 12;col< 24;col++){
            buff = pgm_read_byte(&MediumNumbers[num][col]);
            spi_byte(buff);
        }
        _set(PORT_SPI,SCE);       
    }
    else{
        _set(PORT_NOKIA,D_C);
        _clr(PORT_SPI,SCE);
        for(int col= 0;col< 12;col++){
            buff = pgm_read_byte(&MediumNumbers[num][col]);
            spi_byte(0xff-buff);
        }
        _set(PORT_SPI,SCE);          

        nokia5110_cursor(row+1,col);
        _set(PORT_NOKIA,D_C);
        _clr(PORT_SPI,SCE);
        for(int col= 12;col< 24;col++){
            buff = pgm_read_byte(&MediumNumbers[num][col]);
            spi_byte(0xff-buff);
        }
        _set(PORT_SPI,SCE);  
    }
}
