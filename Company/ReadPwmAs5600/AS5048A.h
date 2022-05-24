
/*
    Copyright : Khac Nghia
    Date : 4-11-21
*/

#ifndef AS5048A_H_
#define AS5048A_H_
#include "style.h"

/*
    Spi command package
    Bit 15: PAR             - Parity bit (EVEN) - handling
    Bit 14: PWM             - Indicates read(1) or write(0) command 
    Bit 13-0: 14 bit address code
    Note : 
        check EF         : 0100 0000 = 0x40
    
*/
#define AS5048A_SPI_MODE                        0
#define AS5048A_PWM_MODE                        1
#define AS5048A_MODE                            AS5048A_PWM_MODE


#if AS5048A_MODE == AS5048A_SPI_MODE
#define AS5048_PWM                              14 
#define AS5048_PAR                              15         

#define AS5048A_CLEAR_NONE                      0x0000
#define AS5048A_CLEAR_ERROR_FLAG                0x0001
#define AS5048A_PROGRAMMING_CONTROL             0x0003
#define AS5048A_OTP_REGISTER_ZERO_POS_HIGH      0x0016
#define AS5048A_OTP_REGISTER_ZERO_POS_LOW       0x0017
#define AS5048A_DIAG_AGC                        0x3FFD
#define AS5048A_MAGNITUDE                       0x3FFE
#define AS5048A_ANGLE                           0x3FFF
#define AS5048A_ANGLE_NONE                      0xFFFF
#define AS5048A_MAX_VALUE                       0x3FFF


#define LIMIT_DEGREE_0_360
//#define LIMIT_DEGREE_180_180

extern void AS5048A_init(void);
extern uint16_t AS5048A_read(uint16_t address);
extern uint16_t AS5048A_write(uint16_t address,uint16_t data);

extern bool AS5048A_error(void);
extern bool AS5048A_get_error(void);

extern uint16_t AS5048A_get_raw_rotation(void);
extern float32_t AS5048A_get_rotation_in_degree(void);

extern uint16_t AS5048_set_zero_position(uint16_t zero_position);

extern uint16_t AS5048A_get_diag_agc(void);

#elif AS5048A_MODE == AS5048A_PWM_MODE



#endif

#endif
