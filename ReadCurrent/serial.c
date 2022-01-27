
#include "elephant.h"

uint8_t serial_rx_buffer[RX_BUFFER_SIZE];
uint8_t serial_rx_buffer_head = 0;
volatile uint8_t serial_rx_buffer_tail = 0;

extern void serial_init(void)
{
#if BAUD_RATE < 57600
    uint16_t UBRR0_value = ((F_CPU / (8L * BAUD_RATE)) - 1) / 2;
    UCSR0A &= ~(1 << U2X0);
#else
    uint16_t UBRR0_value = ((F_CPU / (4L * BAUD_RATE)) - 1) / 2;
    UCSR0A |= (1 << U2X0);
#endif
    UBRR0H = UBRR0_value >> 8;
    UBRR0L = UBRR0_value;

    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    UCSR0C = (1 << UCSZ00) | (1 << UCSZ01);
}

void serial_write(uint8_t data)
{
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = data;
}

extern void serial_print(char *data)
{
    while (*data != 0)
    {
        serial_write(*data);
        data++;
    }
}

extern void serial_println(char *data)
{
    serial_print(data);
    serial_print("\r\n");
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
