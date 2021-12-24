
#ifndef DHT11_H_
#define DHT11_H_
#include "config.h"

extern void dht11_start(void);
extern uint8_t dht11_read(void);
extern bool dht11_get(uint8_t* humi,uint8_t* part_humi,uint8_t* temp,uint8_t* part_temp,uint8_t* check_sum);

#endif