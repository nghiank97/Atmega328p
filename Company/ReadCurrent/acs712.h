

#ifndef ACS712_H_
#define ACS712_H_
#include "style.h"
#include "adc.h"

#define ACS712_SCALE                0.185 // 5A
//#define ACS712_SCALE              0.1 // 20A
//#define ACS712_SCALE              0.066 // 30A

#define ACS712_ZeroPoint            Vref/2

extern void acs712_init(void);
extern void acs712_read(float32_t *vout,float32_t *current);

#endif