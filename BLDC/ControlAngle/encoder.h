#ifndef ENCODER_H_
#define ENCODER_H_
#include "bee.h"

class HardwareEncoder{
    private:
        unsigned long cpr = 0; 
        volatile long counter = 0; 
        volatile long pulse_counter = 0; 

        float angle_prev = 0;
        float vel_angle_prev = 0;

        unsigned long angle_prev_ts = 0;
        unsigned long vel_angle_prev_ts = 0;

        int32_t full_rotations = 0;
        int32_t vel_full_rotations = 0;

    public:
        HardwareEncoder(long);
        void init(void);
        void reloadEncoder(int);

        void update(void);
        float getVelocity(void);
        float getRadiansAngle(void);
        float getMechanicalAngle(void);
        int32_t getFullRotations(void);
};

extern HardwareEncoder Sensor;

#endif
