
#include "../Inc/lcd4.h"

#ifdef LCD_BIG_NUMBER
#define ADD_CGRAM       0x40
#include "../Inc/lcd4_big_number.h"
#endif

#if defined(RW_LCD)
    void lcd4_byte(uint8_t Data){
        _write(PORT_DATA_LCD, FIR_LCD, ((Data>>4) & 0x01));
        _write(PORT_DATA_LCD, SEC_LCD, ((Data>>5) & 0x01));
        _write(PORT_DATA_LCD, THI_LCD, ((Data>>6) & 0x01));
        _write(PORT_DATA_LCD, FOR_LCD, ((Data>>7) & 0x01));
        
        _set(PORT_CONTROL_LCD,EN_LCD);
        _delay_us(100);
        _clr(PORT_CONTROL_LCD,EN_LCD);
        
        _write(PORT_DATA_LCD, FIR_LCD, ((Data>>0) & 0x01));
        _write(PORT_DATA_LCD, SEC_LCD, ((Data>>1) & 0x01));
        _write(PORT_DATA_LCD, THI_LCD, ((Data>>2) & 0x01));
        _write(PORT_DATA_LCD, FOR_LCD, ((Data>>3) & 0x01));
        
        _set(PORT_CONTROL_LCD,EN_LCD);
        _delay_us(100);
        _clr(PORT_CONTROL_LCD,EN_LCD);
    }

    void lcd4_high(uint8_t Data){
    
        _clr(PORT_CONTROL_LCD,RW_LCD);
        _clr(PORT_CONTROL_LCD,RS_LCD);
        
        _write(PORT_DATA_LCD, FIR_LCD, ((Data>>4) & 0x01));
        _write(PORT_DATA_LCD, SEC_LCD, ((Data>>5) & 0x01));
        _write(PORT_DATA_LCD, THI_LCD, ((Data>>6) & 0x01));
        _write(PORT_DATA_LCD, FOR_LCD, ((Data>>7) & 0x01));
        
        _set(PORT_CONTROL_LCD,EN_LCD);
        _delay_us(100);
        _clr(PORT_CONTROL_LCD,EN_LCD);
    }

    extern void lcd4_cmd(uint8_t cmd){
        
        _clr(PORT_CONTROL_LCD,RW_LCD);
        _clr(PORT_CONTROL_LCD,RS_LCD);

        lcd4_byte(cmd);
        if(cmd<0x03){
            delay_ms(2);
        }
        else{
            delay_ms(1);
        }
    }
    extern void lcd4_data(uint8_t byte){
        _clr(PORT_CONTROL_LCD,RW_LCD);
        _set(PORT_CONTROL_LCD,RS_LCD);
        
        lcd4_byte(byte);
        delay_ms(1);
    }

    extern void lcd4_put(char Data){
        _clr(PORT_CONTROL_LCD,RW_LCD);
        _set(PORT_CONTROL_LCD,RS_LCD);
        
        lcd4_byte(Data);
        delay_ms(1);
    } 
    
    extern void lcd4_puts(char *Data){
        int local = 0;
        while(Data[local]!= 0){
            lcd4_put(Data[local]);
            local+=1;
        }
    }

    extern void lcd4_printf(int row, int col,char *Data){
        int local = 0;
        lcd4_cursor(row,col);
        while(Data[local]!= 0){
            lcd4_put(Data[local]);
            local+=1;
        }
    }

    extern void lcd4_array(int row,int col, char Data[],int len){
        lcd4_cursor(row,col);
        for(int i=0;i<len;i++){
            lcd4_put(Data[i]);
        }
    }

#else
    void lcd4_byte(uint8_t Data){
        _write(PORT_DATA_LCD, FIR_LCD, ((Data>>4) & 0x01));
        _write(PORT_DATA_LCD, SEC_LCD, ((Data>>5) & 0x01));
        _write(PORT_DATA_LCD, THI_LCD, ((Data>>6) & 0x01));
        _write(PORT_DATA_LCD, FOR_LCD, ((Data>>7) & 0x01));
        
        _set(PORT_CONTROL_LCD,EN_LCD);
        _delay_us(100);
        _clr(PORT_CONTROL_LCD,EN_LCD);
        
        _write(PORT_DATA_LCD, FIR_LCD, ((Data>>0) & 0x01));
        _write(PORT_DATA_LCD, SEC_LCD, ((Data>>1) & 0x01));
        _write(PORT_DATA_LCD, THI_LCD, ((Data>>2) & 0x01));
        _write(PORT_DATA_LCD, FOR_LCD, ((Data>>3) & 0x01));
        
        _set(PORT_CONTROL_LCD,EN_LCD);
        _delay_us(100);
        _clr(PORT_CONTROL_LCD,EN_LCD);
    }

    void lcd4_high(uint8_t Data){
    
        _clr(PORT_CONTROL_LCD,RS_LCD);
        
        _write(PORT_DATA_LCD, FIR_LCD, ((Data>>4) & 0x01));
        _write(PORT_DATA_LCD, SEC_LCD, ((Data>>5) & 0x01));
        _write(PORT_DATA_LCD, THI_LCD, ((Data>>6) & 0x01));
        _write(PORT_DATA_LCD, FOR_LCD, ((Data>>7) & 0x01));
        
        _set(PORT_CONTROL_LCD,EN_LCD);
        _delay_us(100);
        _clr(PORT_CONTROL_LCD,EN_LCD);
    }

    extern void lcd4_cmd(uint8_t cmd){
        
        _clr(PORT_CONTROL_LCD,RS_LCD);

        lcd4_byte(cmd);
        if(cmd<0x03){
            delay_ms(2);
        }
        else{
            delay_ms(1);
        }
    }

    extern void lcd4_data(uint8_t byte){
        _set(PORT_CONTROL_LCD,RS_LCD);
        lcd4_byte(byte);
        delay_ms(1);
    }

    extern void lcd4_put(char Data){
        _set(PORT_CONTROL_LCD,RS_LCD);
        lcd4_byte(Data);
        delay_ms(1);
    } 
    
    extern void lcd4_puts(char *Data){
        int local = 0;
        while(Data[local]!= 0){
            lcd4_put(Data[local]);
            local+=1;
        }
    }

    extern void lcd4_printf(int row, int col,char *Data){
        int local = 0;
        lcd4_cursor(row,col);
        while(Data[local]!= 0){
            lcd4_put(Data[local]);
            local+=1;
        }
    }

    extern void lcd4_array(int row,int col, char Data[],int len){
        lcd4_cursor(row,col);
        for(int i=0;i<len;i++){
            lcd4_put(Data[i]);
        }
    }

#endif


#ifdef LCD16x2

extern void lcd4_cursor(int row,int col){
    if (row==0)
        lcd4_cmd(0x80+col);
    else
        lcd4_cmd(0x80+0x40+col);
}
#elif defined(LCD16x4)
extern void lcd4_cursor(int row,int col){
    switch (row){
        case 0:{
            lcd4_cmd(0x80+col);
            return;
            }
        case 1:{
            lcd4_cmd(0x80+0x40+col);
            return;
            }
        case 2:{
            lcd4_cmd(0x80+0x10+col);
            return;
            }
        case 3:{
            lcd4_cmd(0x80+0x50+col);
            return;
        }
    }
}

#elif defined(LCD20x4)
extern void lcd4_cursor(int row,int col){
    switch (row){
        case 0:{
            lcd4_cmd(0x80+col);
            return;
            }
        case 1:{
            lcd4_cmd(0x80+0x40+col);
            return;
            }
        case 2:{
            lcd4_cmd(0x80+0x14+col);
            return;
            }
        case 3:{
            lcd4_cmd(0x80+0x54+col);
            return;
        }
    }
}

#endif

#ifdef LCD_BIG_NUMBER

void lcd4_set_cgram(uint8_t add_cgram,const uint8_t new_txt[]){
    int i=0;
    lcd4_cmd(ADD_CGRAM+add_cgram*8);
    for(i=0;i<8;i++){
        lcd4_put(pgm_read_byte(&new_txt[i]));
    }
}

void lcd4_set_big_number(void){

    lcd4_set_cgram(0x00,leftSide);
    lcd4_set_cgram(0x01,upperBar);
    lcd4_set_cgram(0x02,rightSide);
    lcd4_set_cgram(0x03,leftEnd);

    lcd4_set_cgram(0x04,lowerBar);
    lcd4_set_cgram(0x05,rightEnd);
    lcd4_set_cgram(0x06,middleBar);
    lcd4_set_cgram(0x07,lowerEnd);
}
#endif

#if defined(RW_LCD)
    extern void lcd4_init(void){
        _set(DIR_CONTROL_LCD,RS_LCD);
        _set(DIR_CONTROL_LCD,RW_LCD);
        _set(DIR_CONTROL_LCD,EN_LCD);
        
        _set(DIR_DATA_LCD,FIR_LCD);
        _set(DIR_DATA_LCD,SEC_LCD);
        _set(DIR_DATA_LCD,THI_LCD);
        _set(DIR_DATA_LCD,FOR_LCD);
        
        delay_ms(60);
        lcd4_high(0x30);
        delay_ms(5);
        lcd4_high(0x30);
        delay_ms(1);
        lcd4_high(0x30);
        lcd4_high(0x20);
        
        lcd4_cmd(0x28);
        lcd4_cmd(0x0c);
        lcd4_cmd(0x06); 
        lcd4_cmd(0x01);  
        delay_ms(10);
        #ifdef LCD_BIG_NUMBER
            lcd4_set_big_number();
        #endif
    }
#else
    extern void lcd4_init(void){
        _set(DIR_CONTROL_LCD,RS_LCD);
        _set(DIR_CONTROL_LCD,EN_LCD);
        
        _set(DIR_DATA_LCD,FIR_LCD);
        _set(DIR_DATA_LCD,SEC_LCD);
        _set(DIR_DATA_LCD,THI_LCD);
        _set(DIR_DATA_LCD,FOR_LCD);
        
        delay_ms(60);
        lcd4_high(0x30);
        delay_ms(5);
        lcd4_high(0x30);
        delay_ms(1);
        lcd4_high(0x30);
        lcd4_high(0x20);
        
        lcd4_cmd(0x28);
        lcd4_cmd(0x0c);
        lcd4_cmd(0x06); 
        lcd4_cmd(0x01);  
        delay_ms(10);

        #ifdef LCD_BIG_NUMBER
            lcd4_set_big_number();
        #endif
    }
#endif

#ifdef LCD_BIG_NUMBER

extern void lcd4_put_big_number(char Number, int col){
    lcd4_printf(0,col,"   ");
    lcd4_printf(1,col,"   ");
    switch (Number){
        case '0':{
            lcd4_cursor(0, col);
            lcd4_data(0);
            lcd4_data(1);
            lcd4_data(2);
            lcd4_cursor(1, col);
            lcd4_data(0);
            lcd4_data(4);
            lcd4_data(2);
            break;
        }
        case '1':{
            lcd4_cursor(0, col);
            lcd4_data(254);
            lcd4_data(2);
            lcd4_data(254);
            lcd4_cursor(1, col);
            lcd4_data(254);
            lcd4_data(2);
            lcd4_data(254);
            break;
        }
        case '2':{
            lcd4_cursor(0, col);
            lcd4_data(3);
            lcd4_data(6);
            lcd4_data(2);
            lcd4_cursor(1, col);
            lcd4_data(0);
            lcd4_data(4);
            lcd4_data(4);
            break;
        }
        case '3':{
            lcd4_cursor(0, col);
            lcd4_data(3);
            lcd4_data(6);
            lcd4_data(2);
            lcd4_cursor(1, col);
            lcd4_data(7);
            lcd4_data(4);
            lcd4_data(2);
            break;
        }
        case '4':{
            lcd4_cursor(0, col);
            lcd4_data(0);
            lcd4_data(4);
            lcd4_data(2);
            lcd4_cursor(1, col);
            lcd4_data(254);
            lcd4_data(254);
            lcd4_data(2);
            break;
        }
        case '5':{
            lcd4_cursor(0, col);
            lcd4_data(0);
            lcd4_data(6);
            lcd4_data(5);
            lcd4_cursor(1, col);
            lcd4_data(7);
            lcd4_data(4);
            lcd4_data(2);
            break;
        }
        case '6':{
            lcd4_cursor(0, col);
            lcd4_data(0);
            lcd4_data(6);
            lcd4_data(5);
            lcd4_cursor(1, col);
            lcd4_data(0);
            lcd4_data(4);
            lcd4_data(2);
            break;
        }
        case '7':{
            lcd4_cursor(0, col);
            lcd4_data(1);
            lcd4_data(1);
            lcd4_data(2);
            lcd4_cursor(1, col);
            lcd4_data(254);
            lcd4_data(254);
            lcd4_data(2);
            break;
        }
        case '8':{
            lcd4_cursor(0, col);
            lcd4_data(0);
            lcd4_data(6);
            lcd4_data(2);
            lcd4_cursor(1, col);
            lcd4_data(0);
            lcd4_data(4);
            lcd4_data(2);
            break;
        }
        case '9':{
            lcd4_cursor(0, col);
            lcd4_data(0);
            lcd4_data(6);
            lcd4_data(2);
            lcd4_cursor(1, col);
            lcd4_data(7);
            lcd4_data(4);
            lcd4_data(2);
            break;
        }
    }
}

extern void lcd4_put_big_numbers(char* Number, int col){
    while (*Number)
    {
        lcd4_put_big_number(*Number,col);
        Number+=1;
        col+=3;
    }
}

#endif