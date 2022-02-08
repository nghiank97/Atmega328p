#ifndef PID_H
#define PID_H
#include "bee.h"

class PIDController
{
public:
    PIDController(float P, float I, float D, float limit);
    float operator()(float error);
    float P;
    float I;
    float D;
    float limit;

protected:
    float error_prev;
    float output_prev;
    float integral_prev;
    unsigned long timestamp_prev;
};

#endif

