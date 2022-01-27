
#include "elephant.h"

/* 
 *   Parity : even
 *   Calculator parity for word 
*/

static uint16_t calculate_parity(uint16_t value)
{
    int count = 0;
    uint16_t dummy = 0x0000;
    for (int i = 0; i < 16; i++)
    {
        dummy = (value >> i) & 0x0001;
        if (dummy == 0x0001)
        {
            count += 1;
        }
    }
    if (count % 2 == 0)
    {
        return value;
    }
    else
    {
        value |= (1 << AS5048_PAR);
        return value;
    }
}

//#define AS5048A_DEBUG

volatile bool error_flag = False;

/*
 * ! Mean   : Initial AS5048A_status, Spi as master
 * @ para   : void
 * > return : void
 */

extern void AS5048A_init(void)
{
    error_flag = False;
    spi_init(0);
}

/*
 * ! Mean   : read data in a address register not parity
 * @ para   : address - address of a register
 * > return : void
 */

extern uint16_t AS5048A_read(uint16_t address)
{
    uint16_t command = address|0x4000;
    uint8_t low_byte, high_byte;
    command = calculate_parity(command);

#ifdef AS5048A_DEBUG
    char text_value[6];
    sprintf(text_value, "%04X", address);
    serial_print("Read (0x");
    serial_print(text_value);

    sprintf(text_value, "%04X", command);
    serial_print(") with command: 0b");
    serial_println(text_value);
#endif

    //Send the command
    SPI_ENABLE();
    spi_word(command);
    SPI_DISENABLE();

    //Now read the response
    SPI_ENABLE();
    high_byte = spi_transfer(0x00);
    low_byte = spi_transfer(0x00);
    SPI_DISENABLE();
    // check error flag

#ifdef AS5048A_DEBUG
    sprintf(text_value, "%02X %02X", high_byte, low_byte);
    serial_print("Read returned: ");
    serial_println(text_value);
#endif

    if (high_byte & 0x40)
    {
        #ifdef AS5048A_DEBUG
            serial_println("Error");
        #endif
        error_flag = True;
    }
    else
    {
        #ifdef AS5048A_DEBUG
            serial_println("Right");
        #endif
        error_flag = False;
    }
    return ((high_byte<<8)|low_byte) &~ 0xC000;
}
/*
 * ! Mean   : write data in a address register
 * @ para   : address - address of a register
 *            data
 * > return : responce
 */
extern uint16_t AS5048A_write(uint16_t address,uint16_t data){
    uint16_t command = 0x0000;
    uint16_t data_send = 0x0000;
    uint8_t low_byte, high_byte;
    command = calculate_parity(address);

    #ifdef AS5048A_DEBUG
        char text_value[6];
        sprintf(text_value, "%04X", command);
        serial_print("Command : ");
        serial_println(text_value);
    #endif

    SPI_ENABLE();
    spi_word(command);
    SPI_DISENABLE();

    data_send = calculate_parity(data);

    #ifdef AS5048A_DEBUG
        sprintf(text_value, "%04X", data_send);
        serial_print("Data : ");
        serial_println(text_value);
    #endif

    SPI_ENABLE();
    spi_word(data_send);
    SPI_DISENABLE();

    SPI_ENABLE();
    high_byte = spi_transfer(0x00);
    low_byte = spi_transfer(0x00);
    SPI_DISENABLE();

	return ((high_byte<<8)|low_byte) &~ 0xC000;
}

/*
 * Get current value error
 */
extern bool AS5048A_error(void)
{
    return error_flag;
}
/*
*  Get the value error from sensor
*/
extern uint16_t AS5048A_get_error(void)
{
    return AS5048A_read(AS5048A_CLEAR_ERROR_FLAG);
}
/*
*  Get the value raw rotation
*/
extern uint16_t AS5048A_get_raw_rotation(void)
{
    uint16_t angle = AS5048A_read(AS5048A_ANGLE);
    return angle;
}
/*
*  Rotation is between 0 and 360
*/
extern float32_t AS5048A_get_rotation_in_degree(void)
{
    int16_t rotation = AS5048A_get_raw_rotation();
    double degrees = 360.0*rotation/(AS5048A_MAX_VALUE);
    #ifdef LIMIT_DEGREE_0_360
        return degrees;
    #elif defined(LIMIT_DEGREE_180_180)
        return degrees-180;
    #endif
}
/*
*  Cvt degree to radians
*/
extern float32_t AS5048A_get_rotation_in_radians(void)
{
	float32_t rotation = AS5048A_get_rotation_in_degree();
	double radians = PI * rotation / 180;
	return radians;
}

/*
*   Get Diagnostics + Automation Gain Control (AGC)
*   Bit 11  - Comp High
*   Bit 10  - Comp Low
*   Bit 9   - COF
*   Bit 8   - OCF
*   Bit 7-0 - AGC
*/
extern uint16_t AS5048A_get_diag_agc(void)
{
	return AS5048A_read(AS5048A_DIAG_AGC);
}

/*
*   Read zero position 
*/
extern uint16_t AS5048_set_zero_position(uint16_t zero_position){
    uint8_t msb = (zero_position>>8)&0xFF;
    uint8_t lsb = zero_position&0xFF;
    uint16_t responce = 0x0000;
    responce = AS5048A_write(AS5048A_OTP_REGISTER_ZERO_POS_HIGH,msb);
    responce = AS5048A_write(AS5048A_OTP_REGISTER_ZERO_POS_HIGH,lsb);
    return responce;
}


