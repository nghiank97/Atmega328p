
#ifndef MODBUS_H
#define MODBUS_H
#include <stdint.h>
#include "serial.h"
#define MODBUS_ADDRESS				0x01
#define MODBUS_FUNC_01				0x01
#define MODBUS_FUNC_02				0x02
#define MODBUS_FUNC_03				0x03
#define MODBUS_FUNC_05				0x05
#define MODBUS_FUNC_06				0x06

class Modbus{
    public:
        static uint8_t cvt_to_ascii(uint8_t b_hex);
        static uint16_t split_to_ascii(uint8_t b_hex);
        static void print(HardwareSerial *port, uint8_t *frame,size_t len);
        static void sent_responce(HardwareSerial *port, uint8_t *frame,size_t len);
        static uint8_t cvt_to_hex(uint8_t d_ascii);
        static uint8_t merge_to_hex(uint8_t h_nibble, uint8_t l_nibble);
        static bool check_lrc(uint8_t *frame,size_t len);
        static uint8_t get_lrc(uint8_t *frame,size_t len);
};

#endif


