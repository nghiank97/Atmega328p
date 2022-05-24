
#ifndef ENCODER_H_
#define ENCODER_H_
#include "style.h"

#define TIME_SAMPLE             50         // ms
#define RESOLUTION_ENCODER      100         // 
#define MOTOR_SCALE             (float32_t)30000/TIME_SAMPLE/RESOLUTION_ENCODER 

extern void encoder_init(void);
extern void encoder_excute(void);
#endif