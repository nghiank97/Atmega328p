
#include "../Inc/lcd4.h"

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
            _delay_ms(2);
        }
        else{
            _delay_ms(1);
        }
    }

    extern void lcd4_put(char Data){
        _clr(PORT_CONTROL_LCD,RW_LCD);
        _set(PORT_CONTROL_LCD,RS_LCD);
        
        lcd4_byte(Data);
        _delay_ms(1);
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

    extern void lcd4_init(void){
        _set(DIR_CONTROL_LCD,RS_LCD);
        _set(DIR_CONTROL_LCD,RW_LCD);
        _set(DIR_CONTROL_LCD,EN_LCD);
        
        _set(DIR_DATA_LCD,FIR_LCD);
        _set(DIR_DATA_LCD,SEC_LCD);
        _set(DIR_DATA_LCD,THI_LCD);
        _set(DIR_DATA_LCD,FOR_LCD);
        
        _delay_ms(60);
        lcd4_high(0x30);
        _delay_ms(5);
        lcd4_high(0x30);
        _delay_ms(1);
        lcd4_high(0x30);
        lcd4_high(0x20);
        
        lcd4_cmd(0x28);
        lcd4_cmd(0x0c);
        lcd4_cmd(0x06); 
        lcd4_cmd(0x01);  
        _delay_ms(10);
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
            _delay_ms(2);
        }
        else{
            _delay_ms(1);
        }
    }

    extern void lcd4_put(char Data){
        _set(PORT_CONTROL_LCD,RS_LCD);
        lcd4_byte(Data);
        _delay_ms(1);
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

    extern void lcd4_init(void){
        _set(DIR_CONTROL_LCD,RS_LCD);
        _set(DIR_CONTROL_LCD,EN_LCD);
        
        _set(DIR_DATA_LCD,FIR_LCD);
        _set(DIR_DATA_LCD,SEC_LCD);
        _set(DIR_DATA_LCD,THI_LCD);
        _set(DIR_DATA_LCD,FOR_LCD);
        
        _delay_ms(60);
        lcd4_high(0x30);
        _delay_ms(5);
        lcd4_high(0x30);
        _delay_ms(1);
        lcd4_high(0x30);
        lcd4_high(0x20);
        
        lcd4_cmd(0x28);
        lcd4_cmd(0x0c);
        lcd4_cmd(0x06); 
        lcd4_cmd(0x01);  
        _delay_ms(10);
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
