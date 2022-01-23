
/*
 * main.c
 *
 * Created:
 * Author: Khac Nghia
 */

#include "bee.h"

long i = 0;

float32_t speed_motor = 0.0;
volatile int16_t count_encoder;
volatile DIRECTION dir_encoder;
char speed_txt[5];

int main(void)
{
    CONFIG_EXTERNAL_CLOCK();
    serial_init();
    bldc_init();
    encoder_init();
    delay_ms(1000);

    // for (long i = 0; i <= 500; i++)
    // {
    //     float angle = _3PI_2 + _2PI * i / 500.0f;
    //     bldc_move_sine_pwm(3, 0, angle);
    //     delay_ms(2);
    // }
    // // move one electrical revolution backwards
    // for (int i = 500; i >= 0; i--)
    // {
    //     float angle = _3PI_2 + _2PI * i / 500.0f;
    //     bldc_move_sine_pwm(3, 0, angle);
    //     delay_ms(2);
    // }
    while (1)
    {
        count_encoder = 0;
        for (uint8_t i = 0; i < 200; i++){
            float angle = _2PI * i / 200.0f;
            bldc_move_sine_pwm(5, 0, angle);
        }

        sprintf(speed_txt,"%5d",count_encoder);
        serial_println(speed_txt);

    }
}
