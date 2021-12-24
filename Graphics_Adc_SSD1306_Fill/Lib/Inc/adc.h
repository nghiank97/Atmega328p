
#ifndef ADC_H_
#define ADC_H_

#include "../Inc/config.h"

extern void adc_init(void);
extern uint16_t adc_get(uint8_t adc_channel);

#endif
