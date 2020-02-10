#define FASTLED_ALLOW_INTERRUPTS 0
#include <FastLED.h>
//FASTLED_USING_NAMESPACE
#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define DATA_PIN    6
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS    32


CRGB leds[NUM_LEDS];
uint8_t gHue = 0; 

int latchPin[4]={2,3,4,5};
int matrixPin[6]={10,9,A7,A6,12,11};

void setup() {
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(255);

  for (int i=0;i<4;i++)pinMode(latchPin[i],OUTPUT);
  for (int i=0;i<6;i++)pinMode(matrixPin[i],INPUT_PULLUP);
}

bool myDigitalRead(int pin) {
  if ((pin==A6)||(pin==A7))
    return analogRead(pin)>500?true:false;
  else
    return digitalRead(pin);
}

void loop() {
gHue++;  
fill_rainbow( leds, NUM_LEDS, gHue, 15);
 
  for (int j=0;j<4;j++){
    for(int k=0;k<4;k++) if (j==k) digitalWrite(latchPin[k], false); else digitalWrite(latchPin[k], true);
    for (int l=0;l<6;l++){
    if(myDigitalRead(matrixPin[l])) leds[l*4+j]=CRGB(0,0,0);
    }
  }


/*
for (int i=0;i<24;i++)leds[i]=CRGB(0,0,0);


for(int i=2;i<6;i++)digitalWrite(i,true);
digitalWrite(2,false);
if(analogRead(A6)>500)leds[0]=CRGB(255,255,255);
*/





  FastLED.show();  
}
