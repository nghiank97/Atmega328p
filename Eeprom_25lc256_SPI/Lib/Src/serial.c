
#include "../Inc/config.h"
#include "../Inc/serial.h"

extern void serial_init(int intp){
    UBRR0 = BAUD_PRESCALE;
    UCSR0B = (1<<RXEN0)|(1<<TXEN0);
    UCSR0C = (1<<UCSZ00)|(1<<UCSZ01); 
    if (intp == 1){
        SREG |= (1<<SREG_I);   
        UCSR0B |= (1<<RXCIE0);
    }            
}

extern void serial_put(char Data){
    while(!(UCSR0A&(1<<UDRE0)));
    UDR0 = Data; 
}

extern void serial_puts(char* Data){
    while(*Data != 0){
        serial_put(*Data++);
    }
}
