
#include "elephant.h"

#define _PINB               (*(volatile unsigned char*)0x23)
#define _DDRB               (*(volatile unsigned char*)0x24)
#define _PORTB              (*(volatile unsigned char*)0x25)

int main(void)
{
    _DDRB |= 0x01;
    _PORTB |= 0x01;
    while (1)
    {
        _PORTB |= 0x01;
        delay_ms(50);
        _PORTB &=~ 0x01;
        delay_ms(50);
    }
    
    return 1;
}