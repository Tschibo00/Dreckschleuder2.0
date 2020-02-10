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

char col[24];

void setup() {
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(255);

  kc=new KeyboardController();
  for (char j=0;j<24;j++)col[j]=0;
}

void loop() {
  gHue++;  
  fill_rainbow( leds, NUM_LEDS, gHue, 15);

  kc->scanKeyboard();
 
  for (int j=0;j<24;j++) {
    if (kc->getKeyClick(j))
      col[j]=(col[j]+1)%4;
    switch(col[j]){
      case 0: leds[j]=CRGB(0,0,0); break;
      case 1: leds[j]=CRGB(255,0,0);break;
      case 2: leds[j]=CRGB(0,255,0);break;
      case 3: leds[j]=CRGB(0,0,255);break;
    }
  }

  FastLED.show();  
}
