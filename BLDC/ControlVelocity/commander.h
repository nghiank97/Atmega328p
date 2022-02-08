#ifndef COMMANDER_H
#define COMMANDER_H
#include "bee.h"

#define MAX_COMMAND_LENGTH 30
typedef void (* CommandCallback)(uint8_t*,size_t);

class Commander{
private:
    HardwareSerial *com_port = nullptr;
    char received_chars[MAX_COMMAND_LENGTH] = {0};
    int rec_cnt = 0;

    CommandCallback call_list[1];
    char call_ids[20];
    int call_count = 0;

public:

    Commander(HardwareSerial &serial);
    void run(void);
    void run(uint8_t *user_input, size_t len);
    void run(HardwareSerial &serial);
    void add(CommandCallback onCommand);
    void motor(BLDCMotor* motor,uint8_t *user_command, size_t len);

    void print(const int number);
    void print(const float number);
    void print(const char *message);
    void print(const char message);
    void println(const int number);
    void println(const float number);
    void println(const char *message);
    void println(const char message);
    void printPgmString(const PROGMEM char *message);
    void printError(void);
};

#endif
