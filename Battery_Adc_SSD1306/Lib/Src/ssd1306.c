  
/*
 * ssd1306.c
 */ 

#include "../Inc/ssd1306.h"
#include "../Inc/font.h"

uint8_t screen[1024];
uint16_t index_screen = 0;

extern void ssd1306_command(uint8_t cmd){
	//uint8_t control = 0x80;
	i2c_start(SSD1306_ADDRESS);
	i2c_write(0x80);
	i2c_write(cmd);
	i2c_stop();
}

extern void ssd1306_data(uint8_t data){
	i2c_start(SSD1306_ADDRESS);
	i2c_write(0x40);
	i2c_write(data);
	i2c_stop();

	screen[index_screen] = data;
    index_screen+=1;
}

extern void ssd1306_cursor(uint8_t row,uint8_t col){
	ssd1306_command(SSD1306_SETSTARTPAGE+row);              //set page address
	ssd1306_command(0x00+(6*col&0x0f));       				//set low col address
	ssd1306_command(0x10+((6*col>>4)&0x0f));  				//set high col address

	index_screen = row*SSD1306_LCDWIDTH+col;
}

extern void ssd1306_gotoXY(uint8_t X,uint8_t Y){
	ssd1306_command(SSD1306_SETSTARTPAGE+X);              //set page address
	ssd1306_command(0x00+(Y&0x0f));       				//set low col address
	ssd1306_command(0x10+(((Y>>4))&0x0f));  				//set high col address

	index_screen = X*SSD1306_LCDWIDTH+Y;
}

extern void ssd1306_print_char(uint8_t data, enum INVERT_PIXEL color){
	switch (color){
		case NORMAL:{
			i2c_start(SSD1306_ADDRESS);
			i2c_write(0x40);
			for(int i=0;i<6;i++){
				uint8_t buff = pgm_read_byte(console_font_5x7[data]+i);
				i2c_write(buff);
				screen[index_screen] = buff;
				index_screen+=1;
			}
			i2c_stop();
			break;
		}
		case INVERT:{
			i2c_start(SSD1306_ADDRESS);
			i2c_write(0x40);
			for(int i=0;i<6;i++){
				uint8_t buff = 0xff-pgm_read_byte(console_font_5x7[data]+i);
				i2c_write(buff);
				screen[index_screen] = buff;
				index_screen+=1;
			}
			i2c_stop();
			break;
		}
		default:
			break;
	}
}

extern void ssd1306_print_charXY(uint8_t data, int X, int Y, enum INVERT_PIXEL color){
	ssd1306_gotoXY(X, Y);
	ssd1306_print_char(data,color);
}

extern void ssd1306_print_string(char *string, enum INVERT_PIXEL color){
	while(*string){
		ssd1306_print_char(*string,color);
		string++;
	}
}

extern void ssd1306_print_stringXY(char *string, int X, int Y, enum INVERT_PIXEL color){
	ssd1306_gotoXY(X,Y);
	while(*string){
		ssd1306_print_char(*string,color);
		string++;
	}
}

static void ssd1306_print_char_4x6(uint8_t data, enum INVERT_PIXEL color){
	switch (color){
		case NORMAL:{
			i2c_start(SSD1306_ADDRESS);
			i2c_write(0x40);
			for(int i=0;i<4;i++){
				uint8_t buff = pgm_read_byte(console_font_4x6[data]+i);
				i2c_write(buff);
				screen[index_screen] = buff;
				index_screen+=1;
			}
			i2c_stop();
			break;
		}
		case INVERT:{
			i2c_start(SSD1306_ADDRESS);
			i2c_write(0x40);
			for(int i=0;i<4;i++){
				uint8_t buff = 0xff-pgm_read_byte(console_font_4x6[data]+i);
				i2c_write(buff);
				screen[index_screen] = buff;
				index_screen+=1;
			}
			i2c_stop();
			break;
		}
		default:
			break;
	}
}

extern void ssd1306_print_char_4x6_XY(char data, int X, int Y, enum INVERT_PIXEL color){
	ssd1306_gotoXY(X,Y);
	ssd1306_print_char_4x6(data,color);
}

extern void ssd1306_print_string_4x6_XY(char *string, int X, int Y, enum INVERT_PIXEL color){
	ssd1306_gotoXY(X,Y);
	while(*string){
		ssd1306_print_char_4x6(*string,color);
		string++;
	}
}

extern void ssd1306_big_number(char string, int X, int Y, enum INVERT_PIXEL color){
	int salto=0;
	ssd1306_gotoXY(X,Y);
	for(int i=0;i<96;i++){
		if(string == ' ') {
			ssd1306_print_char(0,color);
		}
		else{
			ssd1306_print_char(pgm_read_byte(bigNumbers[string-0x30]+i),color);
		}
		if(salto == 23){
			salto = 0;
			X++;
			ssd1306_gotoXY(X,Y);
			} else {
			salto++;
		}
	}
}

extern void ssd1306_logo(const uint8_t *logo, enum INVERT_PIXEL color){
	int k = 0;
	switch (color){
		case NORMAL:{
			for(int i=0;i<8;i++){
				ssd1306_cursor(i,0);
				for(int j=0; j<SSD1306_LCDWIDTH; j++){
					uint8_t buff = pgm_read_byte(&logo[k]);
					ssd1306_data(buff);
					k++;
				}
			}
			break;
		}
		case INVERT:{
			for(int i=0;i<8;i++){
				ssd1306_cursor(i,0);
				for(int j=0; j<SSD1306_LCDWIDTH; j++){
					uint8_t buff = 0xff-pgm_read_byte(&logo[k]);
					ssd1306_data(buff);
					k++;
				}
			}
			break;
		}
		default:
			break;
	}
}

extern void ssd1306_reset_display(void){
	ssd1306_display_off();
	ssd1306_clear_display();
	ssd1306_display_on();
}

extern void ssd1306_display_on(void){
	ssd1306_command(SSD1306_DISPLAYON);
}

extern void ssd1306_display_off(void){
	ssd1306_command(SSD1306_DISPLAYOFF);
}

extern void ssd1306_clear_display(void){
	for(int k=0;k<8;k++){
		ssd1306_cursor(k,0);
        for(int i=0;i<SSD1306_LCDWIDTH;i++){
            ssd1306_data(0);
        }
    }
	index_screen = 0;
}

extern void ssd1306_init(void){
	#ifndef RESET_PIN
		#error "Don't define reset pin in ssd1306"
	#endif
	
	DIR_OLED|=(1<<RESET_PIN);
	PORT_OLED|=(1<<RESET_PIN);
	delay_ms(100);
	
	// Init sequence for 128x64 OLED module
	ssd1306_command(SSD1306_DISPLAYOFF);                    // 0xAE
	ssd1306_command(SSD1306_SETDISPLAYCLOCKDIV);            // 0xD5
	ssd1306_command(0x80);                 					// the suggested ratio 0x80
	ssd1306_command(SSD1306_SETMULTIPLEX);                  // 0xA8
	ssd1306_command(0x3F);
	ssd1306_command(SSD1306_SETDISPLAYOFFSET);              // 0xD3
	ssd1306_command(0x0);                                   // no offset
	ssd1306_command(SSD1306_SETSTARTLINE);// | 0x0);        // line #0
	ssd1306_command(SSD1306_CHARGEPUMP);                    // 0x8D
	ssd1306_command(0x14);  // using internal VCC
	//ssd1306_command(SSD1306_MEMORYMODE);                  // 0x20
	//ssd1306_command(0x00);          						// 0x00 horizontal addressing
	ssd1306_command(SSD1306_SEGREMAP | 0x1); 				// rotate screen 180
	ssd1306_command(SSD1306_COMSCANDEC); 					// rotate screen 180
	ssd1306_command(SSD1306_SETCOMPINS);                    // 0xDA

	#ifndef GLCD_SIZE
		#error "Don't define a GLCD Size"
	#endif
	#if (GLCD_SIZE == GLCD_128_64)
		ssd1306_command(0x12);						//Sequential COM pin configuration
	#elif (GLCD_Size == GLCD_128_32)
		ssd1306_command(0x02);						//Alternative COM pin configuration
	#elif (GLCD_Size == GLCD_96_16)
		ssd1306_command(0x02);						//Alternative COM pin configuration
	#endif

	ssd1306_command(SSD1306_SETCONTRAST);                   // 0x81
	ssd1306_command(0xCF);
	ssd1306_command(SSD1306_SETPRECHARGE);                  // 0xd9
	ssd1306_command(0xF1);
	ssd1306_command(SSD1306_SETVCOMDETECT);                 // 0xDB
	ssd1306_command(0x40);
	ssd1306_command(SSD1306_DISPLAYALLON_RESUME);           // 0xA4
	ssd1306_command(SSD1306_NORMALDISPLAY);                 // 0xA6
	ssd1306_command(SSD1306_DISPLAYON);                     //switch on OLED

	ssd1306_reset_display(); 
}

#ifdef OLED_GRAHPICS

extern void ssd1306_pixel(int row,int col,enum SIGNAL signal){
    uint8_t result = 0x00;
    uint8_t buff;
    uint16_t i;

	i = ((row >> 3) * 128) + col;
	if (i < 0 || i > 1025)
        return;

    buff = screen[i];

    switch (signal){
        case OFF_PIXEL:
            result = ~(1<<(row%8)) & buff;
            break;
        case ON_PIXEL:
            result = (1<<(row%8)) | buff;
            break;
        default:
            break;
    }
    ssd1306_gotoXY(row/8,col);
    ssd1306_data(result); 
}


extern void ssd1306_line(int y1, int x1, int y2, int x2,enum SIGNAL color){
	int Dx = x2 - x1;
	int Dy = y2 - y1;
    if((Dx==0)&(Dy==0)){
        ssd1306_pixel(y1,x1,color);
        return;
    } 
    else if((Dx==0)&(Dy>0)){
        int x;
        for(x=y1;x<=y2;x++)
            ssd1306_pixel(x, x1, color);
        return;
    }
    else if((Dx==0)&(Dy<0)){
        int x;
        for(x=y2;x<=y1;x++)
            ssd1306_pixel(x, x1, color); 
        return;
    }
    else if((Dx>0)&(Dy==0)){
        int x;
        for(x=x1;x<=x2;x++)
            ssd1306_pixel(y1, x, color);
        return;
    }
    else if((Dx<0)&(Dy==0)){
        int x;
        for(x=x2;x<=x1;x++)
            ssd1306_pixel(y1, x, color);
        return;
    }
    else if((Dx>0)&(Dy>0)){
        if(Dx>Dy){
            int x;
            int P = 2*Dy-Dx;
            for(x=x1;x<=x2;x++){
                ssd1306_pixel(y1, x, color);
                if(P < 0 ){
                    P = P + 2*Dy;
                }
                else{
                    P = P + 2*(Dy - Dx);
                    y1+=1;
                }
            }
            ssd1306_pixel(y2, x2, color);
            return;
        }
        else if(Dx==Dy){
            int x;
            for(x=x1;x<=x2;x++){
                ssd1306_pixel(y1, x, color);
                y1+=1;
            }
            return;
        }
        else{
            int y;
            int P = 2*Dx-Dy;
            for(y=y1;y<=y2;y++){
                ssd1306_pixel(y, x1, color);
                if(P < 0 ){
                    P = P + 2*Dx;
                }
                else{
                    P = P + 2*(Dx - Dy);
                    x1+=1;
                }
            }
            ssd1306_pixel(y2, x2, color);
            return;
        }
    }
    else if((Dx>0)&(Dy<0)){
        if(Dx>-Dy){
            int x;
            int P = 2*Dy+Dx;
            for(x=x1;x<x2;x++){
                ssd1306_pixel(y1, x, color);
                if (P > 0 ){
                    P = P + 2*Dy;
                }
                else {
                    P = P + 2*(Dy + Dx);
                    y1-=1;
                }
            }
            ssd1306_pixel(y2, x2, color); 
            return;
        }
        else if(Dx==-Dy){
            int x;
            for(x=x1;x<=x2;x++){
                ssd1306_pixel(y1, x, color);
                y1-=1;
            }
            return;
        }
        else{
            int y;
            int P = 2*Dx+Dy;
            for(y=y1;y>y2;y--){
                ssd1306_pixel(y, x1, color);
                if (P < 0 ){
                    P = P + 2*Dx;
                }
                else {
                    P = P + 2*(Dy + Dx);
                    x1+=1;
                }
            }
            ssd1306_pixel(y2, x2, color);
            return;  
        }
    }
    else if((Dx<0)&(Dy>0)){
        int x = x1;
        int y = y1;
        x1 = x2;
        x2 = x;
        y1 = y2;
        y2 = y;
        Dx = x2 - x1;
	    Dy = y2 - y1;
        if(Dx>-Dy){
            int x;
            int P = 2*Dy+Dx;
            for(x=x1;x<x2;x++){
                ssd1306_pixel(y1, x, color);
                if (P > 0 ){
                    P = P + 2*Dy;
                }
                else {
                    P = P + 2*(Dy + Dx);
                    y1-=1;
                }
            }
            ssd1306_pixel(y2, x2, color); 
            return;
        }
        else if(Dx==-Dy){
            int x;
            for(x=x1;x<=x2;x++){
                ssd1306_pixel(y1, x, color);
                y1-=1;
            }
            return;
        }
        else{
            int y;
            int P = 2*Dx+Dy;
            for(y=y1;y>y2;y--){
                ssd1306_pixel(y, x1, color);
                if (P < 0 ){
                    P = P + 2*Dx;
                }
                else {
                    P = P + 2*(Dy + Dx);
                    x1+=1;
                }
            }
            ssd1306_pixel(y2, x2, color);
            return;  
        }
    }
    else if((Dx<0)&(Dy<0)){
        int x = x1;
        int y = y1;
        x1 = x2;
        x2 = x;
        y1 = y2;
        y2 = y;
        Dx = x2 - x1;
	    Dy = y2 - y1;
        if(Dx>Dy){
            int x;
            int P = 2*Dy-Dx;
            for(x=x1;x<=x2;x++){
                ssd1306_pixel(y1, x, color);
                if(P < 0 ){
                    P = P + 2*Dy;
                }
                else{
                    P = P + 2*(Dy - Dx);
                    y1+=1;
                }
            }
            ssd1306_pixel(y2, x2, color);
            return;
        }
        else if(Dx==Dy){
            int x;
            for(x=x1;x<=x2;x++){
                ssd1306_pixel(y1, x, color);
                y1+=1;
            }
            return;
        }
        else{
            int y;
            int P = 2*Dx-Dy;
            for(y=y1;y<=y2;y++){
                ssd1306_pixel(y, x1, color);
                if(P < 0 ){
                    P = P + 2*Dx;
                }
                else{
                    P = P + 2*(Dx - Dy);
                    x1+=1;
                }
            }
            ssd1306_pixel(y2, x2, color);
            return;
        }
    }
}

extern void ssd1306_8_point(int xc, int yc, int x, int y, enum SIGNAL color)
{
    ssd1306_pixel( y + xc, x + yc, color);
    ssd1306_pixel(-y + xc, x + yc, color);
    ssd1306_pixel(y + xc, -x + yc, color);
    ssd1306_pixel(-y + xc, -x + yc, color);
    
    ssd1306_pixel(x + xc, y + yc, color);
    ssd1306_pixel(-x + xc, y + yc, color);
    ssd1306_pixel(x + xc, -y + yc, color);
    ssd1306_pixel(-x + xc, -y + yc, color);
}

extern void ssd1306_circle(int yc,int xc,int r,enum SIGNAL color){
    int x = 0; int y = r;
    int f = 1 - r;
    ssd1306_8_point(yc, xc, y, x, color);
    while (x < y){
        if (f < 0){
            f += 2*x + 3;
        }
        else{
            y--;
            f += 2*(x-y) + 5;
        }
        x++;
        ssd1306_8_point(yc, xc, y, x, color);
    }
}

extern void ssd1306_box(int y1, int x1, int y2, int x2,enum SIGNAL color){
    ssd1306_line(y1, x1, y2, x1, color); 
    ssd1306_line(y2, x1, y2, x2, color); 
    ssd1306_line(y1, x1, y1, x2, color); 
    ssd1306_line(y1, x2, y2, x2, color); 
}

extern void ssd1306_box_fill(int y1, int x1, int y2, int x2,enum SIGNAL color){
	if (y1<=y2){
		for(int i=y1;i<=y2;i++){
			ssd1306_line(i, x1, i, x2, color);
		}
	}
	else{
		for(int i=y2;i<=y1;i++){
			ssd1306_line(i, x1, i, x2, color); 
		}
	}

	if (color == ON_PIXEL){
		color = OFF_PIXEL;
	}
	else{
		color = ON_PIXEL;
	}
	// ssd1306_pixel(y1, x1, color); 
	// ssd1306_pixel(y1+1, x1, color);
	// ssd1306_pixel(y1, x1+1, color);

	// ssd1306_pixel(y2, x1, color); 
	// ssd1306_pixel(y2-1, x1, color);
	// ssd1306_pixel(y2, x1+1, color);

	// ssd1306_pixel(y1, x2, color); 
	// ssd1306_pixel(y1+1, x2, color);
	// ssd1306_pixel(y1, x2-1, color);

	// ssd1306_pixel(y2, x2, color); 
	// ssd1306_pixel(y2-1, x2, color);
	// ssd1306_pixel(y2, x2-1, color);

	// ssd1306_pixel(y1, x1, color); 
	// ssd1306_pixel(y2, x1, color); 
	// ssd1306_pixel(y1, x2, color); 
	// ssd1306_pixel(y2, x2, color); 
}

extern void ssd1306_scrool(int row,int time){
    int index = row* 128;
    int about_index = (row+1)* 128;
    uint8_t save_bit = 0x00;

    while(time--){
        for(int i=0;i<128;i++){
            save_bit = screen[index+i]&0b10000000;
            save_bit = save_bit>>7;
            screen[index+i] = screen[index+i]<<1;

            screen[about_index+i]= screen[about_index+i]<<1;
            screen[about_index+i] |= save_bit;

            ssd1306_gotoXY(row,i);
            ssd1306_data(screen[index+i]);
            ssd1306_gotoXY(row+1,i);
            ssd1306_data(screen[about_index+i]);
        }
    }
}


extern void ssd1306_clear_row(int row){
    for(int i=0;i<128;i++){
        ssd1306_gotoXY(row,i);
        ssd1306_data(0x00);
    }
}

extern void ssd1306_load_arrow(int row,int col,enum ARROW_TYPE type,enum SIGNAL color){
    ssd1306_gotoXY(row,col);
    switch (color){
		case NORMAL:{
			i2c_start(SSD1306_ADDRESS);
			i2c_write(0x40);
			for(int i=0;i<5;i++){
				uint8_t buff = pgm_read_byte(customer_char[type]+i);
				i2c_write(buff);
				screen[index_screen] = buff;
				index_screen+=1;
			}
			i2c_stop();
			break;
		}
		case INVERT:{
			i2c_start(SSD1306_ADDRESS);
			i2c_write(0x40);
			for(int i=0;i<5;i++){
				uint8_t buff = 0xff-pgm_read_byte(customer_char[type]+i);
				i2c_write(buff);
				screen[index_screen] = buff;
				index_screen+=1;
			}
			i2c_stop();
			break;
		}
		default:
			break;
	}
}

#endif