
#include "elephant.h"

/*
  Method: AS5600_init
  In: none
  Out: none
  Description: generate i2c for the as5600
*/

extern void AS5600_init(void){
    i2c_init();
}

/*
  Method: AS5600_one_read
  In: the register's address
  Out: content in the register's address
  Description: read the data in the register
*/

extern uint8_t AS5600_read_one(uint8_t address){
    uint8_t result;
    i2c_start();
    i2c_put(AS5600_ADDRESS_WRITE);
    i2c_put(address);
    i2c_start();
    i2c_put(AS5600_ADDRESS_READ);
    result = i2c_get(STOP);
    i2c_stop();
    return result;
}

/*
  Method: AS5600_one_read
  In: the register's address
  Out: content in the register's address & the next
  Description: read the data in the register & the next, then join them
*/

extern uint16_t AS5600_read_two(uint8_t address){
    uint8_t high_byte,low_byte;
    i2c_start();
    i2c_put(AS5600_ADDRESS_WRITE);
    i2c_put(address);
    i2c_start();
    i2c_put(AS5600_ADDRESS_READ);
    high_byte = i2c_get(CONTINUE);
	low_byte = i2c_get(STOP);
    i2c_stop();
    return (uint16_t)(high_byte<<8 + low_byte);
}

/*
  Method: AS5600_one_read
  In:
    + address : the register's address
    + byte : the data to write
  Out: None
  Description: write one "byte" to the register's address
*/

extern void AS5600_write_one(uint8_t address,uint8_t byte){
    i2c_start();
    i2c_put(AS5600_ADDRESS_WRITE);
    i2c_put(address);
    i2c_put(byte);
    i2c_stop();
}

/*
  Method: AS5600_tow_write
  In:
    + address : the register's address
    + byte : the data to write
  Out: None
  Description: writes tow "byte" to the register's address
*/

extern void AS5600_write_two(uint8_t address,uint16_t byte){
    uint8_t high_byte = ((uint8_t)byte>>8)&0x0f;
    uint8_t low_byte = (uint8_t)byte&0x00ff;
    i2c_start();
    i2c_put(AS5600_ADDRESS_WRITE);
    i2c_put(address);
    i2c_put(high_byte);
    i2c_put(low_byte);
    i2c_stop();
}

/*
  Method: AS5600_output_stage
  In: ModeOutputStage mode : 
    + the mode includes :
        - 00 : analog 0%- 100% ~ 0(GND) - VDD
        - 01 : analog 10%- 90% ~ 0(GND) - VDD
        - 10 : digital PWM
  Out: None
  Description: write the output stage mode
*/

extern void AS5600_write_output_stage(OutputStageMode mode){
    uint8_t pass_mode = AS5600_read_one(AS5600_CONF_LO);
    uint8_t new_mode = 0x00;
    switch (mode)
    {
    case OUTPUT_STAGE_ANALOG_0:
        new_mode = (pass_mode&0xCF);
        AS5600_write_one(AS5600_CONF_LO,new_mode);
        break;
    case OUTPUT_STAGE_ANALOG_1:
        new_mode = (pass_mode&0xCF)|(0x01<<4);
        AS5600_write_one(AS5600_CONF_LO,new_mode);
        break;
    case OUTPUT_STAGE_DIGITAL_PWM:
        new_mode = (pass_mode&0xCF)|(0x02<<4);
        AS5600_write_one(AS5600_CONF_LO,new_mode);
        break;
    default:
        break;
    }
}
/*
  Method: AS5600_read_raw_angle 
  In: None 
  Out: value of the raw angle
  Description: read the raw angle
*/

extern uint16_t AS5600_read_raw_angle(void){
    return AS5600_read_two(AS5600_RAW_ANGLE_LO);
}

/*
  Method: AS5600_write_zpos 
  In: value of the raw angle 
  Out: None
  Description: write the raw angle in to the ZPOS register 
*/

extern uint16_t AS5600_write_zpos(uint16_t angle){
    angle = angle&0x0FFF;
    return AS5600_write_two(AS5600_ZPOS_LO,angle);
}

/*
  Method: AS5600_write_mpos 
  In: value of the RAW ANGLE
  Out: None
  Description: write the RAW ANGLE in to the MPOS register 
*/

extern uint16_t AS5600_write_mpos(uint16_t angle){
    angle = angle&0x0FFF;
    return AS5600_write_two(AS5600_MPOS_LO,angle);
}