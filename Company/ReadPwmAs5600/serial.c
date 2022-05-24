
#include "elephant.h"

extern void serial_init(void){
    #if BAUD_RATE < 57600
        uint16_t UBRR0_value = (F_CPU / (16L * BAUD_RATE)) - 1;
        UCSR0A &= ~(1 << U2X0);
    #else
        uint16_t UBRR0_value = (F_CPU / (8L * BAUD_RATE)) - 1;
        UCSR0A |= (1 << U2X0);
    #endif
    UBRR0H = UBRR0_value >> 8;
    UBRR0L = UBRR0_value;
    UCSR0B = (1<<RXEN0)|(1<<TXEN0);
    UCSR0C = (1<<UCSZ00)|(1<<UCSZ01);    
}

extern void serial_write(char data){
    while(!(UCSR0A&(1<<UDRE0)));
    UDR0 = data; 
}

extern void serial_print(const char* data, ...){
	char buff[20];
	
	va_list args;
	va_start(args, data);
	vsprintf(buff,data,args);
	va_end(args);
	
	for(int i=0;i<strlen(buff);i++){
		serial_write(buff[i]);
	}
}

extern void serial_println(const char *data,...)
{
	char buff[20];
	
	va_list args;
	va_start(args, data);
	vsprintf(buff,data,args);
	va_end(args);
	
	for(int i=0;i<strlen(buff);i++){
		serial_write(buff[i]);
	}
    serial_print("\r\n");
}
