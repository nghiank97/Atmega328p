
#include "bee.h"

BLDCMotor BldcMotor(14);
HardwareEncoder Sensor(600);
Commander command = Commander(Serial);
void onMotor(uint8_t* cmd,size_t len){
  command.motor(&BldcMotor,cmd,len);
}

int main(void)
{
    system_init();
    Serial.begin(9600);
    BldcMotor.init();
    Sensor.init();

    BldcMotor.linkSerial(&Serial);
    BldcMotor.linkSensor(&Sensor);
    BldcMotor.calibration();
    command.add(onMotor);
    delay_ms(1000);

    while (1)
    {
        BldcMotor.loop();
        command.run();
    }
}
