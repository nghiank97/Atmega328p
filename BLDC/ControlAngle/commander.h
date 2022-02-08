#ifndef COMMANDER_H
#define COMMANDER_H
#include "bee.h"

class Commander
{
private:
    char eol = '\n';
    HardwareSerial *monitor = nullptr;
    char received_chars[20] = {0};
    uint8_t rec_cnt = 0;

public:
    Commander(HardwareSerial *serial, char eol = '\n');
    void run(void);
    void handle(HardwareSerial *serial, char eol);
    void isSentinel(char);
};

#endif
