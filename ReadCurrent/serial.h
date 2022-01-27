
#ifndef SERIAL_H_
#define SERIAL_H_
#include "style.h"

#define LIBRARY_VERSION                     0.0.1

#ifndef RX_BUFFER_SIZE
#define RX_BUFFER_SIZE                      128
#endif
#ifndef TX_BUFFER_SIZE
#define TX_BUFFER_SIZE                      64
#endif

#define SERIAL_NO_DATA                      0xff

extern void serial_init(void);
extern void serial_write(uint8_t data);
extern void serial_print(char *data);
extern void serial_println(char *data);

#endif