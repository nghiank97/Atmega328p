
#ifndef CAPTURE_H_
#define CAPTURE_H_
#include "style.h"

extern volatile uint32_t period, duty, check;

extern void capture_init(void);

#endif