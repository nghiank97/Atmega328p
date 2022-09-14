
#include "serial.h"

extern void serial_init(long int bd){
    uint16_t UBRR0_value = 0;
    if (bd < 57600){
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
    SREG |= (1<<SREG_I);
}

extern void serial_write(char data){
    UDR0 = data; 
    while(!(UCSR0A&(1<<UDRE0)));
}

extern void serial_print(char* data,uint8_t len){
    for(int i=0;i<len;i++){
        serial_write(data[i]);
    }
}
