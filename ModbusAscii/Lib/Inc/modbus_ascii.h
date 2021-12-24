
#ifndef MODBUS_ASCII_H_
#define MODBUS_ASCII_H_

#include "config.h"
#include "serial.h"

#define MODBUS_ADDRESS				0x0B
#define MODBUS_FUNC_01				0x01
#define MODBUS_FUNC_02				0x02
#define MODBUS_FUNC_03				0x03
#define MODBUS_FUNC_05				0x05

extern void mma_init(void);
extern void mma_put(uint8_t frame[],int len);
extern uint8_t merge_to_hex(uint8_t h_nibble, uint8_t l_nibble);
extern bool check_lrc(uint8_t frame[],int len);
extern uint8_t mma_lrc(uint8_t frame[],int len);

#endif


