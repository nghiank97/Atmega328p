
#ifndef SERIAL_H_
#define SERIAL_H_

#ifndef RX_BUFFER_SIZE
#define RX_BUFFER_SIZE                      128
#endif
#ifndef TX_BUFFER_SIZE
#define TX_BUFFER_SIZE                      64
#endif

#define SERIAL_NO_DATA                      0xff

extern void serial_init(long int bd);
extern uint8_t serial_read(void);

#endif