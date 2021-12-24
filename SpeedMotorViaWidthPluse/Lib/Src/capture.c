
#include "../Inc/config.h"
#include "../Inc/capture.h"

volatile uint32_t temp_duty=0, pre_val=0, over_step=0, buff=0;

extern void capture_init(void){
    TCNT1 = 0x00;
    TCCR1A = 0x00;
    TIMSK1 = (1<<ICIE1)|(1<<TOIE1);
    TCCR1B = (1<<ICES1)|(1<<CS11)|(0<<CS10);
    SREG |= (1<<SREG_I);
}

ISR (TIMER1_OVF_vect ){
	over_step+=0xFFFF;
}

ISR (TIMER1_CAPT_vect){		
    check =1;
    buff = ICR1;
    TCCR1B ^= (1<<ICES1);               // doi canh
	temp_duty= over_step + buff -pre_val;
    if(_read(TCCR1B, ICES1)==0) 
		period=duty+temp_duty;          //tinh chu ky xung
	else
		duty=temp_duty;	                //cap nhat thoi gian phan ON

	pre_val = buff;
    over_step=0;	
}
