
#ifndef AS5600_H
#define AS5600_H

#define AS5600_ADDRESS                      0x36    
#define AS5600_ADDRESS_WRITE                AS5600_ADDRESS 
#define AS5600_ADDRESS_READ                 (AS5600_ADDRESS|0x01)      

/* Configuration Registers */
#define AS5600_ZMCO                         0x00

#define AS5600_ZPOS_HI                      0x01
#define AS5600_ZPOS_LO                      0x02

#define AS5600_MPOS_HI                      0x03
#define AS5600_MPOS_LO                      0x04

#define AS5600_MANG_HI                      0x05
#define AS5600_MANG_LO                      0x06

#define AS5600_CONF_HI                      0x07
#define AS5600_CONF_LO                      0x08
/* Output Registers */
#define AS5600_RAW_ANGLE_HI                 0x0C
#define AS5600_RAW_ANGLE_LO                 0x0D

#define AS5600_ANGLE_HI                     0x0E
#define AS5600_ANGLE_LO                     0x0F

/* Status Register */
#define AS5600_STATUS                       0x0B
#define AS5600_AGC                          0x1A

#define AS5600_MAGNITUDE_HI                 0x1B
#define AS5600_MAGNITUDE_LO                 0x1C

/* Burn Commands */
#define AS5600_BURN                         0xFF

typedef enum{
    OUTPUT_STAGE_ANALOG_0 = 0x00,
    OUTPUT_STAGE_ANALOG_1 = 0x01,
    OUTPUT_STAGE_DIGITAL_PWM = 0x02
}OutputStageMode;


extern void AS5600_init(void);
/* Option A : angle programming throung the i2c interface*/

extern uint8_t AS5600_read_one(uint8_t address);
extern uint16_t AS5600_read_two(uint8_t address);
extern void AS5600_write_one(uint8_t address,uint8_t byte);
extern void AS5600_write_two(uint8_t address,uint16_t byte);

extern void AS5600_write_output_stage(OutputStageMode mode);

extern uint16_t AS5600_read_raw_angle(void);
extern uint16_t AS5600_write_zpos(uint16_t angle);
extern uint16_t AS5600_write_mpos(uint16_t angle);

#endif
