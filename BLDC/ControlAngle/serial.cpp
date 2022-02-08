
#include "bee.h"

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

  *_ucsrc = (1 << UCSZ00) | (1 << UCSZ01);

  sbi(*_ucsrb, RXEN0);
  sbi(*_ucsrb, TXEN0);
  sbi(*_ucsrb, RXCIE0);
  cbi(*_ucsrb, UDRIE0);
  sei();
}

void HardwareSerial::end(void)
{
  cli();
  cbi(*_ucsrb, RXEN0);
  cbi(*_ucsrb, TXEN0);
  cbi(*_ucsrb, RXCIE0);
  cbi(*_ucsrb, UDRIE0);
}

ISR(USART0_RX_vect)
{
  Serial._rx_complete_irq();
}
void HardwareSerial::_rx_complete_irq(void)
{
  uint8_t data = UDR0;
  uint8_t next_head;

  next_head = _rx_buffer_head + 1;
  if (next_head == RX_BUFFER_SIZE)
  {
    next_head = 0;
  }
  if (next_head != _rx_buffer_tail)
  {
    _rx_buffer[_rx_buffer_head] = data;
    _rx_buffer_head = next_head;
  }
}

ISR(USART_UDRE_vect)
{
  Serial._tx_udr_empty_irq();
}
void HardwareSerial::_tx_udr_empty_irq(void)
{
  uint8_t tail = _tx_buffer_tail;
  *_udr = _tx_buffer[tail];
  tail++;
  if (tail == TX_BUFFER_SIZE)
  {
    tail = 0;
  }
  _tx_buffer_tail = tail;
  if (tail == _tx_buffer_head)
  {
    cbi(*_ucsrb, UDRIE0);
  }
}

uint8_t HardwareSerial::write(uint8_t data)
{
  uint8_t next_head = _tx_buffer_head + 1;
  if (next_head == TX_BUFFER_SIZE)
  {
    next_head = 0;
  }
  while (next_head == _tx_buffer_tail){
  }
  _tx_buffer[_tx_buffer_head] = data;
  _tx_buffer_head = next_head;
  sbi(*_ucsrb, UDRIE0);
  return 1;
}

uint8_t HardwareSerial::available(void){

  uint8_t head = _rx_buffer_head;
  uint8_t tail = _rx_buffer_tail;
  if (head >= tail){
    return (head - tail);
  }
  else{
    return (RX_BUFFER_SIZE - tail + head);
  }
}

uint8_t HardwareSerial::read(void)
{
    uint8_t tail = _rx_buffer_tail;
    if (_rx_buffer_head == tail)
    {
        return SERIAL_NO_DATA;
    }
    else
    {
        uint8_t data = _rx_buffer[tail];
        tail++;
        if (tail == RX_BUFFER_SIZE)
        {
            tail = 0;
        }
        _rx_buffer_tail = tail;
        return data;
    }
}

void HardwareSerial::_reset_read_buffer(void) 
{
  _rx_buffer_tail = _rx_buffer_head;
}

uint8_t HardwareSerial::print(const char *str)
{
  uint8_t n = 0;
  while(*str){
      write(*str++);
      n+=1;
  }
  return n;
}

uint8_t HardwareSerial::print(const char *str, unsigned int len)
{
  uint8_t n = 0;
  for(unsigned int i=0;i<len;i++){
      write(str[i]);
      n+=1;
  }
  return n;
}

uint8_t HardwareSerial::print(unsigned char b, int base)
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

uint8_t HardwareSerial::print(char d)
{
  return write((uint8_t)d);
}

uint8_t HardwareSerial::print(uint8_t d)
{
  return write((uint8_t)d);
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
  return print(str)+print("\r\n");
}

uint8_t HardwareSerial::println(const char *str, unsigned int len)
{
  return print(str, len)+print("\r\n");
}

uint8_t HardwareSerial::println(unsigned char b, int base)
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

uint8_t HardwareSerial::printPgmString(const PROGMEM char* str){
  char c;
  uint8_t n = 0;
  while ((c = pgm_read_byte_near(str++))){
    write(c);
    n+=1;
  }
  return n;
}

HardwareSerial::HardwareSerial(void) : _ubrrh(&UBRR0H), _ubrrl(&UBRR0L),
                                       _ucsra(&UCSR0A), _ucsrb(&UCSR0B), _ucsrc(&UCSR0C),
                                       _udr(&UDR0)
{
}
HardwareSerial Serial;