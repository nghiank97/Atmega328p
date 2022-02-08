
#ifndef BLDC_MOTOR_H
#define BLDC_MOTOR_H
#include "bee.h"

class BLDCMotor
{
private:
    uint8_t pole_pairs;

    float target;
    float shaft_angle = 0.0f;
    float shaft_angle_sp = 0.0f;
    float shaft_velocity = 0.0f;
    float shaft_velocity_sp = 0.0f;

    float electric_angle = 0.0f;
    float current_sp = 0.0f;
    float phase_resistance = 0.0f;
    float velocity_limit = 0.0f;
    float voltage_limit = 0.0f;
    float zero_electric_angle = 0.0f;

    DQVoltage_s voltage{0.0f, 0.0f};
    Direction_s sensor_direction = Direction_s::CW;

    PIDController PID_velocity{0.5f, 20.0f, 0.0f, 24.0f};
    LowPassFilter LPF_velocity{0.1};

    HardwareSerial *monitor;
    HardwareEncoder *sensor;
    PWM3 driver;

    float Ua, Ub, Uc;
    float Ualpha, Ubeta;

public:
    BLDCMotor(uint8_t pp);
    void init(void);
    void enable(void);
    void disable(void);
    void linkSensor(HardwareEncoder *);
    void linkSerial(HardwareSerial *);
    void setPhaseVoltage(float Uq, float Ud, float angle_el);

    void alignSensor(void);
    void calibration(void);

    float electricalAngle(void);
    float shaftAngle(void);
    float shaftVelocity(void);

    void loop(void);
};

#endif
