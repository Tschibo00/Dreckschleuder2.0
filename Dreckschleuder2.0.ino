#define FASTLED_ALLOW_INTERRUPTS 0
#include <FastLED.h>
#include "KeyboardController.h"

#define DATA_PIN    6
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS    32

KeyboardController *kc;

CRGB leds[NUM_LEDS];
uint8_t gHue = 0; 

void setup() {
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(255);

  kc=new KeyboardController();
}

void loop() {
  gHue++;  
  fill_rainbow( leds, NUM_LEDS, gHue, 15);

  kc->scanKeyboard();
 
  for (int j=0;j<24;j++)
    if (!kc->getKeyStatus(j)) leds[j]=CRGB(0,0,0);

  FastLED.show();  
}
