
#include "bee.h"

uint8_t serial_rx_buffer[RX_BUFFER_SIZE];
uint8_t serial_rx_buffer_head = 0;
volatile uint8_t serial_rx_buffer_tail = 0;

uint8_t serial_tx_buffer[TX_BUFFER_SIZE];
uint8_t serial_tx_buffer_head = 0;
volatile uint8_t serial_tx_buffer_tail = 0;

// Returns the number of bytes used in the RX serial buffer.
extern uint8_t serial_get_rx_buffer_count(void)
{
  uint8_t rtail = serial_rx_buffer_tail; // Copy to limit multiple calls to volatile
  if (serial_rx_buffer_head >= rtail) { return(serial_rx_buffer_head-rtail); }
  return (RX_BUFFER_SIZE - (rtail-serial_rx_buffer_head));
}

// Returns the number of bytes used in the TX serial buffer.
// NOTE: Not used except for debugging and ensuring no TX bottlenecks.
extern uint8_t serial_get_tx_buffer_count(void)
{
  uint8_t ttail = serial_tx_buffer_tail; // Copy to limit multiple calls to volatile
  if (serial_tx_buffer_head >= ttail) { return(serial_tx_buffer_head-ttail); }
  return (TX_BUFFER_SIZE - (ttail-serial_tx_buffer_head));
}

extern void serial_init(void)
{
#if BAUD_RATE < 57600
    uint16_t UBRR0_value = (F_CPU / (16L * BAUD_RATE)) - 1;
    UCSR0A &= ~(1 << U2X0);
#else
    uint16_t UBRR0_value = (F_CPU / (8L * BAUD_RATE)) - 1;
    UCSR0A |= (1 << U2X0);
#endif
    UBRR0H = UBRR0_value >> 8;
    UBRR0L = UBRR0_value;

    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    UCSR0C = (1 << UCSZ00) | (1 << UCSZ01);
    UCSR0B |= (1<<RXCIE0);
    SREG |= (1<<SREG_I);
}

extern void serial_write(uint8_t data)
{
    uint8_t next_head = serial_tx_buffer_head + 1;
    if (next_head == TX_BUFFER_SIZE)
    {
        next_head = 0;
    }
    if (next_head == serial_tx_buffer_tail){
        return;
    }

    serial_tx_buffer[serial_tx_buffer_head] = data;
    serial_tx_buffer_head = next_head;
    UCSR0B |= (1 << UDRIE0);
}

// Data Register Empty Interrupt handler
ISR(USART_UDRE_vect)
{
    uint8_t tail = serial_tx_buffer_tail; // Temporary serial_tx_buffer_tail (to optimize for volatile)
    // Send a byte from the buffer	
    UDR0 = serial_tx_buffer[tail];
    // Update tail position
    tail++;
    if (tail == TX_BUFFER_SIZE) {
        tail = 0;
    }
    serial_tx_buffer_tail = tail;
    // Turn off Data Register Empty Interrupt to stop tx-streaming if this concludes the transfer
    if (tail == serial_tx_buffer_head) { UCSR0B &= ~(1 << UDRIE0); }
}

extern void serial_print(char* data){
	while(*data != 0){
		serial_write(*data);
        data+=1;
	}
}

extern void serial_println(char *data)
{
	while(*data != 0){
		serial_write(*data);
        data+=1;
	}
    serial_write(0x0d);serial_write(0x0a);
}

extern uint8_t seriale_available(void){

  uint8_t head = serial_rx_buffer_head;
  uint8_t tail = serial_rx_buffer_tail;
  if (head >= tail){
    return (head - tail);
  }
  else{
    return (RX_BUFFER_SIZE - tail + head);
  }
}

extern uint8_t serial_read(void)
{
    uint8_t tail = serial_rx_buffer_tail;
    if (serial_rx_buffer_head == tail)
    {
        return SERIAL_NO_DATA;
    }
    else
    {
        uint8_t data = serial_rx_buffer[tail];
        tail++;
        if (tail == RX_BUFFER_SIZE)
        {
            tail = 0;
        }
        serial_rx_buffer_tail = tail;
        return data;
    }
}

ISR(USART_RX_vect)
{
    uint8_t data = UDR0;
    uint8_t next_head;

    next_head = serial_rx_buffer_head + 1;
    if (next_head == RX_BUFFER_SIZE)
    {
        next_head = 0;
    }
    if (next_head != serial_rx_buffer_tail)
    {
        serial_rx_buffer[serial_rx_buffer_head] = data;
        serial_rx_buffer_head = next_head;
    }
}

extern void serial_reset_read_buffer(void) 
{
  serial_rx_buffer_tail = serial_rx_buffer_head;
}
