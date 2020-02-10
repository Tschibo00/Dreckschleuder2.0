#include <Arduino.h>

class KeyboardController {
  private:
    int latchPin[4]={2,3,4,5};
    int matrixPin[6]={10,9,A7,A6,12,11};
    bool keyStatus[24];

    bool myDigitalRead(int pin);

  public:
    KeyboardController();
    void scanKeyboard();
    bool getKeyStatus(int key);
};
