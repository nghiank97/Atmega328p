
#include "bee.h"

volatile level phase = LOW;

ISR(PCINT2_vect)
{
    if (phase == LOW)
    {
        if ((_read(PIND, 2) == HIGH) & (_read(PIND, 3) == LOW)) // CW
        {
            Sensor.reloadEncoder(1);
            phase = HIGH;
            return;
        }
        if ((_read(PIND, 2) == LOW) & (_read(PIND, 3) == LOW)) // CCW
        {
            Sensor.reloadEncoder(-1);
            phase = HIGH;
            return;
        }
    }
    else
    {
        if ((_read(PIND, 2) == LOW) & (_read(PIND, 3) == HIGH)) // CW
        {
            Sensor.reloadEncoder(1);
            phase = LOW;
            return;
        }
        if ((_read(PIND, 2) == HIGH) & (_read(PIND, 3) == HIGH)) // CCW
        {
            Sensor.reloadEncoder(-1);
            phase = LOW;
            return;
        }
    }
}

HardwareEncoder::HardwareEncoder(long _cpr)
{
    cpr = _cpr * 2;
}

void HardwareEncoder::init(void)
{
    PCICR = (1 << 2);
    PCMSK2 = (1 << 2) | (1 << 3);
    sei();
}

void HardwareEncoder::reloadEncoder(int _time)
{
    pulse_counter += _time;
}

float HardwareEncoder::getRadiansAngle(void)
{
    return _2PI * (pulse_counter) / ((float)cpr);
}

void HardwareEncoder::update(void)
{
    float val = getRadiansAngle();
    angle_prev_ts = micros();
    float d_angle = val - angle_prev;
    if (fabs(d_angle) > (0.8f * _2PI))
        full_rotations += (d_angle > 0) ? -1 : 1;
    angle_prev = val;
}

float HardwareEncoder::getVelocity()
{
    float Ts = (angle_prev_ts - vel_angle_prev_ts) * 1e-6;
    if (Ts <= 0)
        Ts = 1e-3f;
    float vel = ((float)(full_rotations - vel_full_rotations) * _2PI + (angle_prev - vel_angle_prev)) / Ts;
    vel_angle_prev = angle_prev;
    vel_full_rotations = full_rotations;
    vel_angle_prev_ts = angle_prev_ts;
    return vel;
}

float HardwareEncoder::getMechanicalAngle(void)
{
    return angle_prev;
}

int32_t HardwareEncoder::getFullRotations(void)
{
    return full_rotations;
}
