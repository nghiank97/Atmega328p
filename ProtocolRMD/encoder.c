
#include "elephant.h"

int16_t count_encoder = 0;

extern void encoder_init(void){
    set_input(DIR_ENCODER,ENCODER_0);
    set_input(DIR_ENCODER,ENCODER_1);
    EICRA =  (1<<ISC11)|(0<<ISC10)|(1<<ISC01)|(0<<ISC00);
    EIMSK |= (1<<INT1)|(1<<INT0);
    SREG |= (1<<SREG_I);
}

ISR(INT0_vect)
{
    if(READ(PIN_ENCODER,ENCODER_1) == HIGH){
        count_encoder+=1;
    }
    else{
        count_encoder-=1;
    }
}

ISR(INT1_vect)
{
    if(READ(PIN_ENCODER,ENCODER_0) == LOW){
        count_encoder+=1;
    }
    else{
        count_encoder-=1;
    }
}


float i = 0.0;
float p = 0.0;
float d = 0.0;
float k = 0.0;

float kp = 10.0;
float ki = 1.0;
float kd = 5.0;

float expect_speed = 100.0;
float current_speed = 0.0;
float error_speed = 0.0;
float part_error = 0.0;

char text_encoder[5];

extern void encoder_excute(void){
    int16_t dummy = 0;
    count_encoder = 0;
    delay_ms(TIME_SAMPLE);
    dummy = count_encoder;
    current_speed = dummy*MOTOR_SCALE;

    error_speed = expect_speed - current_speed;
    p = kp*error_speed;
    i += ki*error_speed;

    if (i > 1000){
        i = 500;
    }
    if (i<-1000){
        i = -500;
    }

    d = kd*(error_speed-part_error);
    k = p+i+d;

    if (k > 1024){
        k = 1024;
    }
    if (k<0){
        k = 0;
    }
    motor_write(LEFT,(uint16_t)k);
    
    // sprintf(text_encoder,"%4d",(uint16_t)k);
    sprintf(text_encoder,"%3.1f",current_speed);
    serial_println(text_encoder);

    part_error = error_speed;
}
