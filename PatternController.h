#ifndef PATTERN_CONTROLLER
#define PATTERN_CONTROLLER

#include <Arduino.h>

class PatternController {
  private:
    uint8_t currentPattern[16]={
      0b11100000,
      0b10001001,
      0b10000110,
      0b10000000,
      0b11111001,
      0b10001000,
      0b10000110,
      0b10000001,
      0b11101000,
      0b10001000,
      0b10000111,
      0b10000000,
      0b11111000,
      0b10001011,
      0b10000100,
      0b10000010
    };

  public:
    uint8_t getTriggers(uint8_t pos);
};
#endif
