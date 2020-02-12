#include "DisplayDriver.h"

#define FASTLED_ALLOW_INTERRUPTS 0
#define DATA_PIN 6
#define LED_TYPE WS2811
#define COLOR_ORDER GRB

DisplayDriver::DisplayDriver() {
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(15);
  for (char i=0; i<NUM_LEDS; i++)
    leds[i]=CRGB(0,0,0);
}

void DisplayDriver::show() {
  FastLED.show();  
}

void DisplayDriver::drawNumber(int i, char pos, CRGB color) {
  drawDigit(i/100,pos,color+CRGB(100));
  drawDigit((i/10)%10,pos+4,color+CRGB(50));
  drawDigit(i%10,pos+8,color);
}

void DisplayDriver::drawNumber(float f, char pos, CRGB color) {
  int i=(int)f;
  int fraction=((int)(f*10.f))%10;
  drawDigit(i/100,    pos,    color+CRGB(150));
  drawDigit((i/10)%10,pos+4,  color+CRGB(80));
  drawDigit(i%10,     pos+8,  color+CRGB(40));
  drawDigit(fraction, pos+12, color);
}

void DisplayDriver::drawDigit(char i, char pos, CRGB color) {
  if (i<0 || i>9) return;
  if (pos<0 || pos>NUM_LEDS-4) return;

  for (char j=3; j>=0; j--) {
    leds[pos+j]=(i&1==1)?color:CRGB(0,0,0);
    i=i>>1;
  }
}
