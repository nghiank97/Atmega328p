
#include "../Inc/seg7.h"

uint8_t Code7Seg[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x98};
int seg7_num = 1;
extern uint16_t temp;
#define RESET_TIMER_1()         {TCNT1 = (0xffff-5000);}

static void timer1_init(void){
    RESET_TIMER_1();
    TCCR1A = 0x00;
    TCCR1B = (1<<CS11)|(0<<CS10);
    TIMSK1 = (1<<TOIE1);
    SREG |= (1<<SREG_I);
}

extern void seg7_init(void){
    DIR_DATA_7SEG = 0xff;
    DIR_SELECT_7SEG = (1<<SELECT_1)|(1<<SELECT_2)|(1<<SELECT_3)|(1<<SELECT_4);
    timer1_init();
}
extern void seg7_put(int select,int number){
    _write(PORT_SELECT_7SEG,select,1);
    PORT_DATA_7SEG = Code7Seg[number];
}

ISR (TIMER1_OVF_vect){
    switch (seg7_num){
        case 1:{
            seg7_num = 2;
            _clr(PORT_SELECT_7SEG,SELECT_4);
            PORT_DATA_7SEG = Code7Seg[temp/1000];
            _set(PORT_SELECT_7SEG,SELECT_1);
            RESET_TIMER_1();
            return;
        }
        case 2:{
            int buff = temp%1000;
            seg7_num = 3;
            _clr(PORT_SELECT_7SEG,SELECT_1);
            PORT_DATA_7SEG = Code7Seg[buff/100];
            _set(PORT_SELECT_7SEG,SELECT_2);
            RESET_TIMER_1();
            return;
        }
        case 3:{ 
            int buff = temp%1000;
            buff = buff%100;
            seg7_num = 4;
            _clr(PORT_SELECT_7SEG,SELECT_2);
            PORT_DATA_7SEG = Code7Seg[buff/10];
            _set(PORT_SELECT_7SEG,SELECT_3);
            RESET_TIMER_1();
            return;
        }
        case 4:{ 
            int buff = temp%1000;
            buff = buff%100;
            buff = buff%10;
            seg7_num = 1;
            _clr(PORT_SELECT_7SEG,SELECT_3);
            PORT_DATA_7SEG = Code7Seg[buff];
            _set(PORT_SELECT_7SEG,SELECT_4);
            RESET_TIMER_1();
            return;
        }
    }
}
