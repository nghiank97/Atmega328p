
#include "../Inc/glcd.h"
#include "../Inc/fonts.h"

extern void glcd_write(uint8_t byte,int color){
    _clr(PORT_CONTROL_GLCD,EN_GLCD);
    _set(PORT_CONTROL_GLCD,RS_GLCD);
	_clr(PORT_CONTROL_GLCD,RW_GLCD);
    
    if (color == 0){
        PORT_DATA_GLCD = byte;
    }
    else{
        PORT_DATA_GLCD = 0xff-byte;
    }
	delay_us(50);
    _set(PORT_CONTROL_GLCD,EN_GLCD);
    delay_us(50);
    _clr(PORT_CONTROL_GLCD,EN_GLCD);
}

extern void glcd_cmd(uint8_t byte){
    _clr(PORT_CONTROL_GLCD,EN_GLCD);
    _clr(PORT_CONTROL_GLCD,RS_GLCD);
	_clr(PORT_CONTROL_GLCD,RW_GLCD); 
    
    PORT_DATA_GLCD = byte;
    delay_us(50);
    _set(PORT_CONTROL_GLCD,EN_GLCD);
    delay_us(50);
    _clr(PORT_CONTROL_GLCD,EN_GLCD);
}

extern void glcd_part(int part){
    switch (part){
        case 0:{
            // select part  0
            _set(PORT_CONTROL_GLCD,CS2_GLCD);
            _clr(PORT_CONTROL_GLCD,CS1_GLCD);
            break;
        }
        case 1:{
            // select part 1
            _clr(PORT_CONTROL_GLCD,CS2_GLCD);
            _set(PORT_CONTROL_GLCD,CS1_GLCD);
            break;
        }
        case 2:{
            // select part 0,1
            _set(PORT_CONTROL_GLCD,CS2_GLCD);
            _set(PORT_CONTROL_GLCD,CS1_GLCD);
            break;
        }
        default:{
            break;
        }
    }
}

extern void glcd_page(int page){
    //page: 0 to 7
    glcd_cmd(GLCD_PAGE+page);
}

extern void glcd_put(char Data,int part,int page,int str_col,int color){
    int col;
    if (str_col>57)
        str_col = 57;
    if (str_col<0)
        str_col = 0;
    glcd_part(part);
    glcd_page(page);
    glcd_cmd(GLCD_ADD+str_col);
    for(col= 0;col< LEN_FONT;col++){
        glcd_write(pgm_read_byte(&Ascii[(int)Data][col]),color);
    }
}

extern void glcd_puts(char *Data,int part,int page,int str_col,int color){
    int local = 0;
    int col;
    if (str_col>57)
        str_col = 57;
    if (str_col<0)
        str_col = 0;
    glcd_part(part);
    glcd_page(page);
    glcd_cmd(GLCD_ADD+str_col);
    
    while(Data[local]!=0){
        int index = (int)Data[local];
        for(col= 0;col< LEN_FONT;col++){
            glcd_write(pgm_read_byte(&Ascii[index][col]),color);
        }
        local+=1;
    }
}

extern void glcd_big_number(char number,int part,int page,int str_col,int color){
    int num = ((int)number)-48;
    int col;
    if (str_col>57)
        str_col = 57;
    if (str_col<0)
        str_col = 0;
    glcd_part(part);
    glcd_page(page);
    glcd_cmd(GLCD_ADD+str_col);
    
    for(col= 0;col< 12;col++){
        glcd_write(pgm_read_byte(&MediumNumbers[num][col]),color);
    }

    glcd_part(part);
    glcd_page(page+1);
    glcd_cmd(GLCD_ADD+str_col);

    for(col= 12;col< 24;col++){
        glcd_write(pgm_read_byte(&MediumNumbers[num][col]),color);
    }
}

extern void glcd_init(void){
	DIR_CONTROL_GLCD = (1<<EN_GLCD)|(1<<RW_GLCD)|(1<<RS_GLCD)|(1<<CS2_GLCD)|(1<<CS1_GLCD);
    DIR_DATA_GLCD = 0xff; 
    
    glcd_cmd(GLCD_ON);
    glcd_cmd(GLCD_ADD);
}
