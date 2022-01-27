
#ifndef LCD4_H_
#define LCD4_H_
#include "style.h"

typedef enum{
    LCD4_RESET      = 0x01,
    LCD4_INLINE     = 0x02
}LCD4_COMMAND;

class LCD4{

private:
    int RS_pin;
    int RW_pin;
    int D4_pin;
    int D5_pin;
    int D6_pin;
    int D7_pin;
public:
    LCD4(int rs,int rw,int d4,int d5,int d6,int d7);
    extern void begin(void);
    extern void command(uint8_t cmd);
    extern void write(char data);
    extern void print(int row,int col,char *data);
};