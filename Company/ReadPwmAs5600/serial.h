
#ifndef SERIAL_H_
#define SERIAL_H_

extern void serial_init(void);
extern void serial_write(char data);
extern void serial_print(const char* data, ...);
extern void serial_println(const char *data,...);

#endif
