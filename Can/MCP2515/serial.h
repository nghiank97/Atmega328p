
#ifndef SERIAL_H_
#define SERIAL_H_
#include "elephant.h"

extern void serial_init(long int bd);
extern void serial_write(char data);
extern void serial_print(char* data,uint8_t len);


#endif
