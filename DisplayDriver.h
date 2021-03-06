#ifndef DISPLAY_DRIVER
#define DISPLAY_DRIVER

#include <FastLED.h>

#define NUM_LEDS 24

class DisplayDriver {
  private:
    CRGB leds[NUM_LEDS];
    
    void drawDigit(char i, char pos, CRGB color);

  public:
    DisplayDriver();
    void clear();
    void show();
    void drawNumber(int i, char pos, CRGB color);
    void drawNumber(float f, char pos, CRGB color);
    void drawShuffle(uint8_t shuffle, uint8_t sync);
    void fill(char first, char last, CRGB color);
    void set(char pos, CRGB color);
    void add(char pos, CRGB color);
};

#endif
