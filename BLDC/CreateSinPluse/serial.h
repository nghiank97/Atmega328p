
#ifndef SERIAL_H_
#define SERIAL_H_

extern void serial_init(void);
extern void serial_write(uint8_t data);
extern void serial_print(char* data);
extern void serial_println(char *data);

#endif