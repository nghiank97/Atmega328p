
#ifndef ADC_H_
#define ADC_H_

#include "../Inc/config.h"

#define RESET_TIMER_2()             {TCNT2 = 0xff-250;}

extern uint16_t adc_value;

extern void adc_init(void);
extern uint16_t adc_get(uint8_t adc_channel);

#endif
