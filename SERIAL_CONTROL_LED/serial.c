
#include "elephant.h"

extern void serial_init(long int bd)
{
    uint16_t UBRR0_value;
    if(bd < 57600){
        UBRR0_value = (F_CPU / (16L * bd)) - 1;
        UCSR0A &= ~(1 << U2X0);
    }
    else{
        UBRR0_value = (F_CPU / (8L * bd)) - 1;
        UCSR0A |= (1 << U2X0);
    }
    UBRR0H = UBRR0_value >> 8;
    UBRR0L = UBRR0_value;

    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    UCSR0C = (1 << UCSZ00) | (1 << UCSZ01);
    UCSR0B |= (1<<RXCIE0);
    SREG |= (1<<SREG_I);
}

ISR(USART_UDRE_vect)
{

}

#define LENGTH_MAX 255
uint8_t rx_data[LENGTH_MAX];
uint8_t rx_header = 0;
uint8_t rx_tail = 0;

ISR(USART_RX_vect)
{
    uint8_t data = UDR0;
    rx_data[rx_header] = data;
    rx_header = (rx_header+1)%LENGTH_MAX;
}

extern uint8_t serial_read(void){
    if (rx_tail == rx_header){
        return 0xFF;
    }
    uint8_t data = rx_data[rx_tail];
    rx_tail = (rx_tail+1)%LENGTH_MAX;
    return data;
}
