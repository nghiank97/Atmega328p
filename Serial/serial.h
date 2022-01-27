
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

extern uint8_t serial_get_rx_buffer_count(void);
extern uint8_t serial_get_tx_buffer_count(void);

extern void serial_init(void);
extern void serial_write(uint8_t data);
extern uint8_t seriale_available(void);
extern void serial_print(const char* data);
extern void serial_println(const char* data);
extern uint8_t serial_read(void);
extern void serial_reset_read_buffer(void);

#endif