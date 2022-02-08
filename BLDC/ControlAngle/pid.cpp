#include "pid.h"

PIDController::PIDController(float P, float I, float D, float limit)
    : P(P), I(I), D(D), limit(limit), error_prev(0.0f), output_prev(0.0f), integral_prev(0.0f)
{
    timestamp_prev = micros();
}

float PIDController::operator()(float error)
{
    unsigned long timestamp_now = micros();
    float Ts = (timestamp_now - timestamp_prev) * 1e-6f;
    if (Ts <= 0 || Ts > 0.5f)
        Ts = 1e-3f;
    float proportional = P * error;
    float integral = integral_prev + I * Ts * error;
    integral = _constrain(integral, -limit, limit);
    float derivative = D * (error - error_prev) / Ts;
    float output = proportional + integral + derivative;
    output = _constrain(output, -limit, limit);
    integral_prev = integral;
    output_prev = output;
    error_prev = error;
    timestamp_prev = timestamp_now;
    return output;
}
