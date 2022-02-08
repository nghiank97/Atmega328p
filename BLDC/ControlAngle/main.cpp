
#include "bee.h"
#include "bldc_motor.h"
#include "encoder.h"
#include "pid.h"

BLDCMotor BldcMotor(14);
HardwareEncoder Sensor(600);

int main(void)
{
    system_init();
    Serial.begin(9600);
    BldcMotor.init();
    Sensor.init();

    BldcMotor.linkSerial(&Serial);
    BldcMotor.linkSensor(&Sensor); 
    BldcMotor.calibration();

    while (1)
    {
        BldcMotor.loop();
    }
}
