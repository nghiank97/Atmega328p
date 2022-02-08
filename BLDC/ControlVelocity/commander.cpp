
#include "bee.h"

Commander::Commander(HardwareSerial &serial)
{
  com_port = &serial;
}

void Commander::run(void)
{
  run(*com_port);
}

void Commander::run(uint8_t *user_input, size_t len)
{
  call_list[0](user_input,len);
}

void Commander::run(HardwareSerial &serial)
{
  HardwareSerial *tmp = com_port;
  com_port = &serial;

  while (serial.available())
  {
    uint8_t ch = serial.read();

    if ((ch == (uint8_t)':') && (rec_cnt == -1))
    {
      rec_cnt = 0;
      continue;
    }
    if ((ch != 13) && (rec_cnt >= 0))
    {
      received_chars[rec_cnt] = ch;
      rec_cnt += 1;
      continue;
    }
    if ((ch == 13) && (rec_cnt >= 0))
    {
      run(received_chars, rec_cnt);
      rec_cnt = -1;
      continue;
    }
    if (rec_cnt >= MAX_COMMAND_LENGTH)
    {
      received_chars[0] = 0;
      rec_cnt = -1;
      continue;
    }
  }
  com_port = tmp;
}

void Commander::add(CommandCallback onCommand)
{
  call_list[0] = onCommand;
  call_count++;
}

uint8_t mb_frame_1[4] = {MODBUS_ADDRESS, MODBUS_FUNC_01, 0x01, 0x00};
uint8_t mb_frame_2[4] = {MODBUS_ADDRESS, MODBUS_FUNC_02, 0x01, 0x00};
uint8_t mb_frame_3[11] = {MODBUS_ADDRESS, MODBUS_FUNC_03, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t mb_frame_5[6] = {MODBUS_ADDRESS, MODBUS_FUNC_05, 0x00, 0x00, 0x00, 0x00};
uint8_t mb_frame_6[6] = {MODBUS_ADDRESS, MODBUS_FUNC_06, 0x00, 0x00, 0x00, 0x00};

void Commander::motor(BLDCMotor* motor,uint8_t *user_command, size_t len)
{
  uint8_t address_device = Modbus::merge_to_hex(user_command[0], user_command[1]);
  uint8_t function = Modbus::merge_to_hex(user_command[2], user_command[3]);

  if (address_device != MODBUS_ADDRESS)
  {
    return;
  }
  switch (function)
  {
  case 0x01:
  {
    Modbus::print(com_port,mb_frame_1, 4);
    break;
  }
  case 0x02:
  {
    Modbus::print(com_port,mb_frame_2, 4);
    break;
  }
  case 0x03:
  {
    float angle = motor->shaftAngle()*100;
    uint8_t a = (uint8_t)angle;
    mb_frame_3[4] = a;
    Modbus::print(com_port,mb_frame_3, 11);
    break;
  }
  case 0x06:
  {
    uint16_t address = Modbus::merge_to_hex(user_command[4], user_command[5])*256;
    address += Modbus::merge_to_hex(user_command[6], user_command[7]);

    uint16_t value = Modbus::merge_to_hex(user_command[8], user_command[9])*256;
    value += Modbus::merge_to_hex(user_command[10], user_command[11]);

    mb_frame_6[3] = address/256;
    mb_frame_6[4] = address%256;

    mb_frame_6[5] = value/256;
    mb_frame_6[6] = value%256;
    Modbus::sent_responce(com_port,user_command, len);
    
    float angle = value/100;
    motor->setShaftAngle(angle);
    break;
  }
  default:
    break;
  }
}

void Commander::print(const int number)
{
  com_port->print(number);
}
void Commander::print(const float number)
{
  com_port->print((float)number, DEC);
}
void Commander::print(const char *message)
{
  com_port->print(message);
}
void Commander::print(const char message)
{
  com_port->print(message);
}
void Commander::println(const int number)
{
  com_port->println(number);
}
void Commander::println(const float number)
{
  com_port->println((float)number, DEC);
}
void Commander::println(const char *message)
{
  com_port->println(message);
}
void Commander::println(const char message)
{
  com_port->println(message);
}
void Commander::printPgmString(const PROGMEM char *message)
{
  com_port->printPgmString(message);
}
void Commander::printError(void)
{
  com_port->printPgmString(PSTR("err"));
}
