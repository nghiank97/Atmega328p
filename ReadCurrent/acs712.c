
#include "elephant.h"

extern void acs712_init(void)
{
    adc_init();
}

/*
    Mean : acs712 read a current and vout value
*/

extern void acs712_read(float32_t *vout,float32_t *current)
{
    *vout = 0.0;
    *current = 0.0;
    for(int i = 0; i < 100; i++) {
        *vout = (*vout + (Vscale * adc_read(ASC712_PIN)));   
        delay_ms(1);
    }
    // Get Vout in mv
    *vout = *vout / 100;
    *current = (*vout - ACS712_ZeroPoint)/ ACS712_SCALE;     
}