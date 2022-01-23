
#ifndef CONFIG_H
#define CONFIG_H

#ifndef F_CPU                   
#define F_CPU                                       16000000
#endif

#define CLOCK_DIV_ENABLE                            (1<<CLKPCE)
#define CLOCK_DIV_1                                 (0<<CLKPCE) | (0<<CLKPS3) | (0<<CLKPS2) | (0<<CLKPS1) | (0<<CLKPS0)
#define CONFIG_EXTERNAL_CLOCK()                     {CLKPR=CLOCK_DIV_ENABLE; CLKPR=CLOCK_DIV_1;}

#define BAUD_RATE                                   9600
#define BAUD_PRESCALE                               (uint16_t)((F_CPU/16/BAUD_RATE) - 1)

/*I2C LCD */
#define LCD16x2

#endif
