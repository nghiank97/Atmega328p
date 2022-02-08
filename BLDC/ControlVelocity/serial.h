
#ifndef HARDWARESERIAL_H
#define HARDWARESERIAL_H
#include <avr/pgmspace.h>

#define F PSTR
#ifndef RX_BUFFER_SIZE
#define RX_BUFFER_SIZE 128
#endif
#ifndef TX_BUFFER_SIZE
#define TX_BUFFER_SIZE 128
#endif
#define SERIAL_NO_DATA 0xff

#define DEC 10
#define HEX 16
#define OCT 8
#ifdef BIN
#undef BIN
#endif
#define BIN 2

class HardwareSerial
{
private:
    uint8_t printNumber(unsigned long n, uint8_t base);
    uint8_t printFloat(double number, uint8_t digits);

protected:
    volatile uint8_t *const _ubrrh;
    volatile uint8_t *const _ubrrl;
    volatile uint8_t *const _ucsra;
    volatile uint8_t *const _ucsrb;
    volatile uint8_t *const _ucsrc;
    volatile uint8_t *const _udr;

    bool _written;

    volatile uint8_t _rx_buffer_head;
    volatile uint8_t _rx_buffer_tail;
    volatile uint8_t _tx_buffer_head;
    volatile uint8_t _tx_buffer_tail;

    uint8_t _rx_buffer[RX_BUFFER_SIZE];
    uint8_t _tx_buffer[TX_BUFFER_SIZE];

public:
    HardwareSerial(
      volatile uint8_t *ubrrh, volatile uint8_t *ubrrl,
      volatile uint8_t *ucsra, volatile uint8_t *ucsrb,
      volatile uint8_t *ucsrc, volatile uint8_t *udr);
    void begin(unsigned long);
    void end(void);

    uint8_t available(void);
    uint8_t peek(void);
    uint8_t read(void);
    uint8_t availableForWrite(void);
    void flush(void);

    uint8_t write(uint8_t);

    uint8_t print(char);
    uint8_t print(uint8_t);
    uint8_t print(const char *);
    uint8_t print(const char *, unsigned int);

    uint8_t print(uint8_t, int = DEC);
    uint8_t print(int, int = DEC);
    uint8_t print(unsigned int, int = DEC);
    uint8_t print(long, int = DEC);
    uint8_t print(unsigned long, int = DEC);
    uint8_t print(double, int = 2);

    uint8_t println(const char *);
    uint8_t println(const char *, unsigned int);
    uint8_t println(uint8_t, int = DEC);
    uint8_t println(int, int = DEC);
    uint8_t println(unsigned int, int = DEC);
    uint8_t println(long, int = DEC);
    uint8_t println(unsigned long, int = DEC);
    uint8_t println(double, int = 2);

    uint8_t word(uint16_t);

    uint8_t printPgmString(const PROGMEM char *);

    void _rx_complete_irq(void);
    void _tx_udr_empty_irq(void);
};

extern HardwareSerial Serial;

#endif
