#ifndef ENCODER_H_
#define ENCODER_H_
#include <stdint.h>

typedef enum DIRECTION_ENCODER{
    RIGHT= 1,
    LEFT=0
} DIRECTION;

extern volatile int16_t count_encoder;
extern volatile DIRECTION dir_encoder;

extern void encoder_init(void);

#endif