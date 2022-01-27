
#ifndef DEFINE_H_
#define DEFINE_H_

#define F_CPU                                       16000000UL

#define CLOCK_DIV_ENABLE()                          {CLKPR=(1<<CLKPCE);}
#define CLOCK_DIV_1()                               {CLKPR=(0<<CLKPCE) | (0<<CLKPS3) | (0<<CLKPS2) | (0<<CLKPS1) | (0<<CLKPS0);}

#define CONFIG_EXTER_CLOCK()                        {CLOCK_DIV_ENABLE();CLOCK_DIV_1();}

#define delay_ms(t)                                 _delay_ms(t)
#define delay_us(t)                                 _delay_us(t)

#endif
