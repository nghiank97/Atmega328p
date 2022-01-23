
#ifndef SERIAL_H_
#define SERIAL_H_
#include "style.h"

extern void serial_init(void);
extern void serial_write(char data);
extern void serial_print(char* data);
extern void serial_println(char* data);

#endif