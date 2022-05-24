
#ifndef DEFINE_H_
#define DEFINE_H_

#ifndef F_CPU
#define F_CPU                                       16000000
#endif

#define delay_ms(t)                                 _delay_ms(t)
#define delay_us(t)                                 _delay_us(t)

#define CLOCK_DIV_ENABLE                            bv(CLKPCE)
#define CLOCK_DIV_1                                 (0<<CLKPCE) | (0<<CLKPS3) | (0<<CLKPS2) | (0<<CLKPS1) | (0<<CLKPS0)
        
#define CONFIG_EXTERNAL_CLOCK()                     {CLKPR=CLOCK_DIV_ENABLE; CLKPR=CLOCK_DIV_1;}

#endif