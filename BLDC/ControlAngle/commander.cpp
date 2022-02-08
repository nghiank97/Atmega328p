
#include "Commander.h"

Commander::Commander(HardwareSerial *serial, char eol)
{
  monitor = serial;
  this->eol = eol;
}

void Commander::run(void)
{
  handle(monitor, eol);
}

void Commander::handle(HardwareSerial *serial, char eol)
{
  while (serial.available())
  {
    uint8_t ch = serial.read();
    received_chars[rec_cnt++] = (char)ch;
    isSentinel(ch);
  }
}

bool Commander::isSentinel(char ch)
{
  if (ch == eol)
    return true;
  else if (ch == '\r')
  {
    printVerbose(F("Warn: \\r detected! \n"));
  }
  return false;
}
