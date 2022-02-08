
#include "bldc_motor.h"

BLDCMotor::BLDCMotor(uint8_t pp)
{
    pole_pairs = pp;
    target = 5.0f;
    phase_resistance = 3.8f;
    monitor = nullptr;
    sensor = nullptr;
}

void BLDCMotor::init(void)
{
    set_output(DRV8302_CONTROL_DIR, DRV8302_ENABLE);
    set_output(DRV8302_HANDLE_DIR, DRV8302_OC_ADJ);
    set_output(DRV8302_HANDLE_DIR, DRV8302_M_PWM);
    set_output(DRV8302_HANDLE_DIR, DRV8302_M_OC);

    _write(DRV8302_HANDLE_PORT, DRV8302_OC_ADJ, 1);
    _write(DRV8302_HANDLE_PORT, DRV8302_M_PWM, 1);
    _write(DRV8302_HANDLE_PORT, DRV8302_M_OC, 0);

    velocity_limit = 24.0f;
    voltage_limit = 24.0f;
    enable();
    delay_ms(500);
}

void BLDCMotor::enable(void)
{
    _write(DRV8302_CONTROL_PORT, DRV8302_ENABLE, 1);
}

void BLDCMotor::disable(void)
{
    _write(DRV8302_CONTROL_PORT, DRV8302_ENABLE, 0);
}

void BLDCMotor::linkSensor(HardwareEncoder *_sensor)
{
    sensor = _sensor;
}

void BLDCMotor::linkSerial(HardwareSerial *_serial)
{
    monitor = _serial;
}

void BLDCMotor::calibration(void)
{
    alignSensor();
    sensor->update();
    shaft_angle = shaftAngle();
    delay_ms(500);
}

float BLDCMotor::electricalAngle(void)
{
    return _normalizeAngle((float)(sensor_direction * pole_pairs) * sensor->getMechanicalAngle() - zero_electric_angle);
}

void BLDCMotor::alignSensor(void)
{
    for (int i = 0; i <= 500; i++)
    {
        float angle = _3PI_2 + _2PI * i / 500.0f;
        setPhaseVoltage(3, 0, angle);
        delay_ms(2);
    }
    sensor->update();
    float mid_angle = sensor->getRadiansAngle();
    for (int i = 500; i >= 0; i--)
    {
        float angle = _3PI_2 + _2PI * i / 500.0f;
        setPhaseVoltage(3, 0, angle);
        delay_ms(2);
    }
    sensor->update();
    float end_angle = sensor->getRadiansAngle();
    setPhaseVoltage(0, 0, 0);
    delay_ms(200);

    if (mid_angle < end_angle)
    {
        sensor_direction = Direction_s::CCW;
    }
    else
    {
        sensor_direction = Direction_s::CW;
    }

    setPhaseVoltage(3, 0, _3PI_2);
    delay_ms(200);
    sensor->update();
    zero_electric_angle = 0.0f;
    zero_electric_angle = electricalAngle();

    delay_ms(200);
    setPhaseVoltage(0, 0, 0);
    delay_ms(200);
}

void BLDCMotor::setPhaseVoltage(float Uq, float Ud, float angle_el)
{
    float center;
    float _ca, _sa;

    angle_el = _normalizeAngle(angle_el);
    _ca = _cos(angle_el);
    _sa = _sin(angle_el);
    Ualpha = _ca * Ud - _sa * Uq;
    Ubeta = _sa * Ud + _ca * Uq;
    center = voltage_limit / 2;
    Ua = Ualpha + center;
    Ub = -0.5f * Ualpha + _SQRT3_2 * Ubeta + center;
    Uc = -0.5f * Ualpha - _SQRT3_2 * Ubeta + center;
    driver.setPwm(Ua, Ub, Uc);
}

float BLDCMotor::shaftAngle(void)
{
    return sensor_direction * LPF_velocity(sensor->getRadiansAngle());
}

float BLDCMotor::shaftVelocity(void)
{
    return sensor_direction * LPF_velocity(sensor->getVelocity());
}

void BLDCMotor::loop(void)
{
    sensor->update();
    electric_angle = electricalAngle();
    setPhaseVoltage(voltage.q, voltage.d, electric_angle);

    shaft_velocity = shaftVelocity();
    current_sp = PID_velocity(target - shaft_velocity);
    voltage.q = current_sp;
    voltage.d = 0;

    monitor->print(shaft_velocity);monitor->print('\t');monitor->print(voltage.q);monitor->print('\t');monitor->println(electric_angle);
}