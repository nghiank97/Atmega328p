
#ifndef LCD4_BIG_NUMBER
#define LCD4_BIG_NUMBER

#include <avr/pgmspace.h>

const uint8_t leftSide[8] PROGMEM= 
{
  0b00111,
  0b01111,
  0b01111,
  0b01111,
  0b01111,
  0b01111,
  0b00111,
  0b00000
};

const uint8_t upperBar[8] PROGMEM=
{
  0b11111,
  0b11111,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};
const uint8_t rightSide[8] PROGMEM=
{
  0b11100,
  0b11110,
  0b11110,
  0b11110,
  0b11110,
  0b11110,
  0b11100,
  0b00000
};
const uint8_t leftEnd[8] PROGMEM=
{
  0b01111,
  0b00111,
  0b00000,
  0b00000,
  0b00000,
  0b00011,
  0b00111,
  0b00000
};
const uint8_t lowerBar[8] PROGMEM=
{
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b11111,
  0b11111,
  0b00000
};
const uint8_t rightEnd[8] PROGMEM=
{
  0b11110,
  0b11100,
  0b00000,
  0b00000,
  0b00000,
  0b11000,
  0b11100,
  0b00000
};
const uint8_t middleBar[8] PROGMEM=
{
  0b11111,
  0b11111,
  0b00000,
  0b00000,
  0b00000,
  0b11111,
  0b11111,
  0b00000
};
const uint8_t lowerEnd[8] PROGMEM= 
{
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00111,
  0b01111,
  0b00000
};

#endif