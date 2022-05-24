
#ifndef ADC_H_
#define ADC_H_
#include "style.h"

#define Vref                5.00
#define ADC_MAX             1024
#define Vscale              Vref/ADC_MAX

extern void adc_init(void);
extern uint16_t adc_read(uint8_t channal);

#endif