#ifndef KEYBOARD_CONTROLLER
#define KEYBOARD_CONTROLLER

#include <Arduino.h>

class KeyboardController {
  private:
    int latchPin[4]={2,3,4,5};
    int matrixPin[6]={10,9,A7,A6,12,11};
    bool keyStatus[24];
    bool keyLocked[24];

    bool myDigitalRead(int pin);

  public:
    enum KEY{A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,RESERVED,TEMPO,COPY,FILLIN,PATTERN,INSTRUMENT,SHIFT,PLAY};
  
    KeyboardController();
    void scanKeyboard();
    bool getKeyStatus(int key);
    bool getKeyClick(int key);
};
#endif
