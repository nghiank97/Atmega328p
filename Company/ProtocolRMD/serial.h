
#ifndef SERIAL_H_
#define SERIAL_H_
#include "style.h"

#ifndef RX_BUFFER_SIZE
#define RX_BUFFER_SIZE                      128
#endif
#ifndef TX_BUFFER_SIZE
#define TX_BUFFER_SIZE                      64
#endif

#define SERIAL_NO_DATA                      0xFF

extern uint8_t serial_get_rx_buffer_count(void);
extern uint8_t serial_get_tx_buffer_count(void);

extern void serial_init(void);
extern void serial_write(uint8_t data);
extern void serial_print(char *data);
extern void serial_println(char *data);
extern uint8_t serial_read(void);

// serial_print_pgm(PSTR("Expected command letter"));
extern void serial_print_pgm(const char *data);
extern void serial_reset_read_buffer(void);

#endif