  
/*
 * I2C.h
 *
 * Created: 22-12-2017 19:00:53
 *  Author: osc
 */ 

#ifndef I2C_H_
#define I2C_H_
#include "config.h"

extern void i2c_init(void);
extern uint8_t i2c_start(uint8_t write_address);/* I2C start function */
extern uint8_t i2c_repeated_start(uint8_t read_address); /* I2C repeated start function */
extern uint8_t i2c_write(uint8_t data);	/* I2C write function */
extern uint8_t i2c_read_ack(void);	/* I2C read ack function */
extern uint8_t i2c_read_Nack(void);		/* I2C read nack function */
extern void i2c_stop(void);		/* I2C stop function */
#endif /* I2C_H_ */