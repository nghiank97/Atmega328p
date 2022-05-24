
#include "elephant.h"

// uint16_t value;
// char text_value[6];
// char text_degreep[8];

volatile uint32_t period=0, duty=0, check=0;
float32_t speed_motor = 0.0;
uint32_t frequently = 0;


int main(void)
{
    CONFIG_EXTERNAL_CLOCK();
    // AS5048A_init();
    // serial_init();
    // #ifdef DEBUG_MAIN
    //     serial_println("AS5048 debug on");
    // #endif

    // /* write zero position */
    // uint16_t responce = AS5048_set_zero_position(0);
    // sprintf(text_degreep,"%05X",responce);
    // serial_print("Responce : ");
    // serial_println(text_degreep);

    // while (1)
    // {
    //     #ifdef DEBUG_MAIN
    //         // float32_t degree  = AS5048A_get_rotation_in_degree();
            
    //         // if (AS5048A_error() == False){
    //         //     sprintf(text_degreep,"%3.2f",degree);
    //         //     serial_print("Degree : ");
    //         //     serial_println(text_degreep);
    //         // }

    //         uint16_t value  = AS5048A_get_raw_rotation();
    //         if (AS5048A_error() == False){
    //             sprintf(text_degreep,"%05X",value);
    //             serial_print("Degree : ");
    //             serial_println(text_degreep);
    //         }

    //         // uint16_t agc  = AS5048A_get_diag_agc();
    //         // if (AS5048A_error() == False){
    //         //     sprintf(text_degreep,"%05X",agc);
    //         //     serial_print("AGC : ");
    //         //     serial_println(text_degreep);
    //         // }
            
    //     #endif

    //     delay_ms(500);
    // }

    serial_init();
    capture_init();
    delay_ms(500);
    while(1){
        if (check == 1){
            frequently = (uint32_t)2000000/period;
            serial_println("Freq %4ld",frequently);
            serial_println("Duty %4ld",duty*100/period);
        }
        delay_ms(100);
    }
    return 1;
}