  
/*
 * ssd1306.c
 */ 

#include "../Inc/ssd1306.h"
#include "../Inc/font.h"

extern void ssd1306_command(uint8_t cmd)
{
	uint8_t control = 0x80; // some use 0X00 other examples use 0X80. I tried both
	i2c_start(SSD1306_ADDRESS);
	i2c_write(control); // This is Command
	i2c_write(cmd);
	i2c_stop();
}

extern void ssd1306_data(uint8_t data)
{
	i2c_start(SSD1306_ADDRESS);
	i2c_write(0x40); // This byte is DATA
	i2c_write(data);
	i2c_stop();
}

// Used when doing Horizontal or Vertical Addressing
// void setColAddress()
// {
// 	ssd1306_command(SSD1306_COLUMNADDR); // 0x21 COMMAND
// 	ssd1306_command(0); // Column start address
// 	ssd1306_command(SSD1306_LCDWIDTH-1); // Column end address
// }

// Used when doing Horizontal or Vertical Addressing
// void setPageAddress()
// {
// 	ssd1306_command(SSD1306_PAGEADDR); // 0x22 COMMAND
// 	ssd1306_command(0); // Start Page address
// 	ssd1306_command((SSD1306_LCDHEIGHT/8)-1);// End Page address
// }

// init according to SSD1306 data sheet and many places on the web
extern void ssd1306_init(void)
{
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
	
	//ssd1306_command(SSD1306_MEMORYMODE);                    // 0x20
	//ssd1306_command(0x00);          // 0x00 horizontal addressing
	
	ssd1306_command(SSD1306_SEGREMAP | 0x1); // rotate screen 180
	
	ssd1306_command(SSD1306_COMSCANDEC); // rotate screen 180
	
	ssd1306_command(SSD1306_SETCOMPINS);                    // 0xDA
	ssd1306_command(0x12);									// set oled size 128x64
	
	ssd1306_command(SSD1306_SETCONTRAST);                   // 0x81
	ssd1306_command(0xCF);
	
	ssd1306_command(SSD1306_SETPRECHARGE);                  // 0xd9
	ssd1306_command(0xF1);
	
	ssd1306_command(SSD1306_SETVCOMDETECT);                 // 0xDB
	ssd1306_command(0x40);
	
	ssd1306_command(SSD1306_DISPLAYALLON_RESUME);           // 0xA4
	
	ssd1306_command(SSD1306_NORMALDISPLAY);                 // 0xA6
	
	ssd1306_command(SSD1306_DISPLAYON);                     //switch on OLED
}

extern void ssd1306_logo(const uint8_t *logo)
{
	int i,j,k = 0;
	for(i=0;i<8;i++)
	{
		ssd1306_cursor(i,0);
		for(j=0; j<128; j++)
		{
			ssd1306_data(pgm_read_byte(&logo[k]));
			k++;
		}
	}
}

extern void ssd1306_reset_display(void)
{
	ssd1306_display_off();
	ssd1306_clear_display();
	ssd1306_display_on();
}

// Turns display on.
extern void ssd1306_display_on(void)
{
	ssd1306_command(SSD1306_DISPLAYON);        //display on
}

// Turns display off.
extern void ssd1306_display_off(void)
{
	ssd1306_command(SSD1306_DISPLAYOFF);		//display off
}

// Clears the display by sending 0 to all the screen map.
extern void ssd1306_clear_display(void)
{
	int i,k;
	for(k=0;k<8;k++)
	{
		ssd1306_cursor(k,0);
		{
			for(i=0;i<128;i++)
			{
				ssd1306_send_char(0); 
			}
		}
	}
}

//==========================================================//
// Prints a display big number (96 bytes) in coordinates X Y,
// being multiples of 8. This means we have 16 COLS (0-15)
// and 8 ROWS (0-7).
extern void ssd1306_big_number(char string, int X, int Y)
{
	int salto=0;
	ssd1306_cursor(X,Y);
	for(int i=0;i<96;i++)
	{
		if(string == ' ') {
			ssd1306_send_char(0);
		}
		else{
			ssd1306_send_char(pgm_read_byte(bigNumbers[string-0x30]+i));
		}
		if(salto == 23) {
			salto = 0;
			X++;
			ssd1306_cursor(X,Y);
			} else {
			salto++;
		}
	}
}

// Actually this sends a byte, not a char to draw in the display.
// Display's chars uses 8 byte font the small ones and 96 bytes
// for the big number font.
extern void ssd1306_send_char(uint8_t data)
{
	i2c_start(SSD1306_ADDRESS); // begin transmitting
	i2c_write(0x40);//data mode
	for(int i=0;i<6;i++){
		i2c_write(pgm_read_byte(myFont[data-0x20]+i));
	}
	i2c_stop();    // stop transmitting
}

// Prints a display char (not just a byte) in coordinates X Y,
// being multiples of 8. This means we have 16 COLS (0-15)
// and 8 ROWS (0-7).
extern void ssd1306_send_charXY(uint8_t data, int X, int Y)
{
	ssd1306_cursor(X, Y);
	i2c_start(SSD1306_ADDRESS); // begin transmitting
	i2c_write(0x40);//data mode
	for(int i=0;i<6;i++){
		i2c_write(pgm_read_byte(myFont[data-0x20]+i));
	}
	i2c_stop();    // stop transmitting
}

// Set the cursor position in a 16 COL * 8 ROW map.
extern void ssd1306_cursor(uint8_t row,uint8_t col)
{
	ssd1306_command(SSD1306_SETSTARTPAGE+row);              //set page address
	ssd1306_command(0x00+(6*col&0x0f));       				//set low col address
	ssd1306_command(0x10+((6*col>>4)&0x0f));  				//set high col address
}

// Set the cursor position in map.
extern void ssd1306_gotoXY(uint8_t X,uint8_t Y)
{
	ssd1306_command(SSD1306_SETSTARTPAGE+X);              //set page address
	ssd1306_command(0x00+(Y&0x0f));       				//set low col address
	ssd1306_command(0x10+(((Y>>4))&0x0f));  				//set high col address
}

// Prints a string regardless the cursor position.
extern void ssd1306_send_string(char *string)
{
	int i=0;
	while(*string)
	{
		for(i=0;i<6;i++)
		{
			ssd1306_send_char(pgm_read_byte(myFont[*string-0x20]+i));
		}
		string++;
	}
}

// Prints a string in coordinates X Y, being multiples of 8.
// This means we have 16 COLS (0-15) and 8 ROWS (0-7).
extern void ssd1306_send_stringXY( char *string, int X, int Y)
{
	ssd1306_cursor(X,Y);
	unsigned char i=0;
	while(*string)
	{
		for(i=0;i<6;i++)
		{
			ssd1306_send_char(pgm_read_byte(myFont[*string-0x20]+i));
		}
		string++;
	}
}
// Invert display
extern void ssd1306_invert_display(void)
{
	ssd1306_command(SSD1306_INVERTDISPLAY);
}
// Normal display
extern void ssd1306_normal_display(void)
{
	ssd1306_command(SSD1306_NORMALDISPLAY);
}