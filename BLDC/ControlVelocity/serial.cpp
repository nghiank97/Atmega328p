#include "bee.h"

ISR(USART_UDRE_vect)
{
  Serial._tx_udr_empty_irq();
}

void HardwareSerial::_tx_udr_empty_irq(void)
{
  uint8_t c = _tx_buffer[_tx_buffer_tail];
  _tx_buffer_tail = (_tx_buffer_tail + 1) % TX_BUFFER_SIZE;
  *_udr = c;
  *_ucsra = ((*_ucsra) & ((1 << U2X0) | (1 << TXC0)));
  if (_tx_buffer_head == _tx_buffer_tail)
  {
    cbi(*_ucsrb, UDRIE0);
  }
}

ISR(USART_RX_vect)
{
  Serial._rx_complete_irq();
}

void HardwareSerial::_rx_complete_irq(void)
{
  if (bit_is_clear(*_ucsra, UPE0))
  {
    uint8_t c = *_udr;
    uint8_t i = (unsigned int)(_rx_buffer_head + 1) % RX_BUFFER_SIZE;
    if (i != _rx_buffer_tail)
    {
      _rx_buffer[_rx_buffer_head] = c;
      _rx_buffer_head = i;
    }
  }
  else
  {
    *_udr;
  };
}

void HardwareSerial::begin(unsigned long baud)
{
  unsigned long baud_setting = 0x00;
  if (baud < 57600)
  {
    baud_setting = (F_CPU / (16L * baud)) - 1;
    *_ucsra &= ~(1 << U2X0);
  }
  else
  {
    baud_setting = (F_CPU / (8L * baud)) - 1;
    *_ucsra |= (1 << U2X0);
  }
  *_ubrrh = baud_setting >> 8;
  *_ubrrl = baud_setting;

  _written = false;
  *_ucsrc = (1 << UCSZ00) | (1 << UCSZ01);

  sbi(*_ucsrb, RXEN0);
  sbi(*_ucsrb, TXEN0);
  sbi(*_ucsrb, RXCIE0);
  cbi(*_ucsrb, UDRIE0);
  sei();
}

void HardwareSerial::end(void)
{
  flush();
  cbi(*_ucsrb, RXEN0);
  cbi(*_ucsrb, TXEN0);
  cbi(*_ucsrb, RXCIE0);
  cbi(*_ucsrb, UDRIE0);
  _rx_buffer_head = _rx_buffer_tail;
}

uint8_t HardwareSerial::available(void)
{
  return ((unsigned int)(RX_BUFFER_SIZE + _rx_buffer_head - _rx_buffer_tail)) % RX_BUFFER_SIZE;
}

uint8_t HardwareSerial::peek(void)
{
  if (_rx_buffer_head == _rx_buffer_tail)
  {
    return SERIAL_NO_DATA;
  }
  else
  {
    return _rx_buffer[_rx_buffer_tail];
  }
}

uint8_t HardwareSerial::read(void)
{
  if (_rx_buffer_head == _rx_buffer_tail)
  {
    return SERIAL_NO_DATA;
  }
  else
  {
    uint8_t c = _rx_buffer[_rx_buffer_tail];
    _rx_buffer_tail = (uint8_t)(_rx_buffer_tail + 1) % RX_BUFFER_SIZE;
    return c;
  }
}

uint8_t HardwareSerial::availableForWrite(void)
{
  uint8_t head;
  uint8_t tail;

  ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
  {
    head = _tx_buffer_head;
    tail = _tx_buffer_tail;
  }
  if (head >= tail)
    return TX_BUFFER_SIZE - 1 - head + tail;
  return tail - head - 1;
}

void HardwareSerial::flush(void)
{
  if (!_written)
    return;

  while (bit_is_set(*_ucsrb, UDRIE0) || bit_is_clear(*_ucsra, TXC0))
  {
    if (bit_is_clear(SREG, SREG_I) && bit_is_set(*_ucsrb, UDRIE0))
      if (bit_is_set(*_ucsra, UDRE0))
        _tx_udr_empty_irq();
  }
}

uint8_t HardwareSerial::write(uint8_t c)
{
  _written = true;
  if ((_tx_buffer_head == _tx_buffer_tail) && bit_is_set(*_ucsra, UDRE0))
  {
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
      *_udr = c;
      *_ucsra = ((*_ucsra) & ((1 << U2X0) | (1 << TXC0)));
    }
    return 1;
  }
  uint8_t i = (_tx_buffer_head + 1) % TX_BUFFER_SIZE;
  while (i == _tx_buffer_tail)
  {
    if (bit_is_clear(SREG, SREG_I))
    {
      if (bit_is_set(*_ucsra, UDRE0))
        _tx_udr_empty_irq();
    }
    else
    {
    }
  }

  _tx_buffer[_tx_buffer_head] = c;
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
  {
    _tx_buffer_head = i;
    sbi(*_ucsrb, UDRIE0);
  }
  return 1;
}

uint8_t HardwareSerial::print(char data)
{
  write((uint8_t)data);
  return 1;
}

uint8_t HardwareSerial::print(uint8_t data)
{
  write((uint8_t)data);
  return 1;
}

uint8_t HardwareSerial::print(const char *str)
{
  uint8_t n = 0;
  while (*str)
  {
    write(*str++);
    n += 1;
  }
  return n;
}

uint8_t HardwareSerial::print(const char *str, unsigned int len)
{
  uint8_t n = 0;
  for (unsigned int i = 0; i < len; i++)
  {
    write(str[i]);
    n += 1;
  }
  return n;
}

uint8_t HardwareSerial::print(uint8_t b, int base)
{
  return print((unsigned long)b, base);
}

uint8_t HardwareSerial::print(int n, int base)
{
  return print((long)n, base);
}

uint8_t HardwareSerial::print(unsigned int n, int base)
{
  return print((unsigned long)n, base);
}

uint8_t HardwareSerial::print(long n, int base)
{
  if (base == 0)
  {
    return write((uint8_t)n);
  }
  else if (base == 10)
  {
    if (n < 0)
    {
      int t = write((uint8_t)'-');
      n = -n;
      return printNumber(n, 10) + t;
    }
    return printNumber(n, 10);
  }
  else
  {
    return printNumber(n, base);
  }
}

uint8_t HardwareSerial::print(unsigned long n, int base)
{
  if (base == 0)
    return write((uint8_t)n);
  else
    return printNumber(n, base);
}

uint8_t HardwareSerial::print(double n, int digits)
{
  return printFloat(n, digits);
}

uint8_t HardwareSerial::println(const char *str)
{
  return print(str) + print("\r\n");
}

uint8_t HardwareSerial::println(const char *str, unsigned int len)
{
  return print(str, len) + print("\r\n");
}

uint8_t HardwareSerial::println(uint8_t b, int base)
{
  uint8_t i = 0;
  i = print(b, base);
  i += print("\r\n");
  return i;
}

uint8_t HardwareSerial::println(int n, int base)
{
  uint8_t i = 0;
  i = print(n, base);
  i += print("\r\n");
  return i;
}

uint8_t HardwareSerial::println(unsigned int n, int base)
{
  uint8_t i = 0;
  i = print(n, base);
  i += print("\r\n");
  return i;
}

uint8_t HardwareSerial::println(long n, int base)
{
  uint8_t i = 0;
  i = print(n, base);
  i += print("\r\n");
  return i;
}

uint8_t HardwareSerial::println(unsigned long n, int base)
{
  uint8_t i = 0;
  i = print(n, base);
  i += print("\r\n");
  return i;
}

uint8_t HardwareSerial::println(double n, int digits)
{
  uint8_t i = 0;
  i = print(n, digits);
  i += print("\r\n");
  return i;
}

uint8_t HardwareSerial::printPgmString(const PROGMEM char *str)
{
  char c;
  uint8_t n = 0;
  while ((c = pgm_read_byte_near(str++)))
  {
    write(c);
    n += 1;
  }
  return n;
}

uint8_t HardwareSerial::printNumber(unsigned long n, uint8_t base)
{
  char buf[8 * sizeof(long) + 1];
  char *str = &buf[sizeof(buf) - 1];

  *str = '\0';
  if (base < 2)
    base = 10;
  do
  {
    char c = n % base;
    n /= base;
    *--str = c < 10 ? c + '0' : c + 'A' - 10;
  } while (n);

  return print(str);
}

uint8_t HardwareSerial::printFloat(double number, uint8_t digits)
{
  uint8_t n = 0;

  if (isnan(number))
    return print("nan");
  if (isinf(number))
    return print("inf");
  if (number > 4294967040.0)
    return print("ovf");
  if (number < -4294967040.0)
    return print("ovf");
  if (number < 0.0)
  {
    n += write('-');
    number = -number;
  }
  double rounding = 0.5;
  for (uint8_t i = 0; i < digits; ++i)
    rounding /= 10.0;

  number += rounding;
  unsigned long int_part = (unsigned long)number;
  double remainder = number - (double)int_part;
  n += print(int_part);
  if (digits > 0)
  {
    n += write('.');
  }
  while (digits-- > 0)
  {
    remainder *= 10.0;
    unsigned int toPrint = (unsigned int)(remainder);
    n += print(toPrint);
    remainder -= toPrint;
  }

  return n;
}

uint8_t HardwareSerial::word(uint16_t data){
  write((uint8_t)data/256);
  write((uint8_t)data%256);
  return 2;
}

HardwareSerial::HardwareSerial(
  volatile uint8_t *ubrrh, volatile uint8_t *ubrrl,
  volatile uint8_t *ucsra, volatile uint8_t *ucsrb,
  volatile uint8_t *ucsrc, volatile uint8_t *udr) :
    _ubrrh(ubrrh), _ubrrl(ubrrl),
    _ucsra(ucsra), _ucsrb(ucsrb), _ucsrc(ucsrc),
    _udr(udr),
    _rx_buffer_head(0), _rx_buffer_tail(0),
    _tx_buffer_head(0), _tx_buffer_tail(0)
{
}

HardwareSerial Serial(&UBRR0H, &UBRR0L, &UCSR0A, &UCSR0B, &UCSR0C, &UDR0);