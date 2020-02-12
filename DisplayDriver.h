#include <FastLED.h>

#define NUM_LEDS 24

class DisplayDriver {
  private:
    CRGB leds[NUM_LEDS];
    
    void drawDigit(char i, char pos, CRGB color);

  public:
    DisplayDriver();
    void show();
    void drawNumber(int i, char pos, CRGB color);
    void drawNumber(float f, char pos, CRGB color);
};
