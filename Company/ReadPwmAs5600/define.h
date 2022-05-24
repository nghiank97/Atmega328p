
#ifndef DEFINE_H_
#define DEFINE_H_

#ifndef F_CPU
#define F_CPU                                       16000000
#endif

#define delay_ms(t)                                 _delay_ms(t)
#define delay_us(t)                                 _delay_us(t)

#define BAUD_RATE                                   9600

#define CLOCK_DIV_ENABLE                            BV(CLKPCE)
#define CLOCK_DIV_1                                 (0<<CLKPCE) | (0<<CLKPS3) | (0<<CLKPS2) | (0<<CLKPS1) | (0<<CLKPS0)
        
#define CONFIG_EXTERNAL_CLOCK()                     {CLKPR=CLOCK_DIV_ENABLE; CLKPR=CLOCK_DIV_1;}


#define DEBUG_MAIN
// #define AS5048A_DEBUG
#define SPI_MASTER

#endif