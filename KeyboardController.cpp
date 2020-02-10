#include "KeyboardController.h"

KeyboardController::KeyboardController() {
  char i;
  for (i=0;i<4;i++)pinMode(latchPin[i],OUTPUT);
  for (i=0;i<6;i++)pinMode(matrixPin[i],INPUT_PULLUP);
  for (i=0; i<24; i++)
    keyLocked[i]=false;
}

bool KeyboardController::myDigitalRead(int pin) {
  if ((pin==A6)||(pin==A7))
    return analogRead(pin)>500?true:false;
  else
    return digitalRead(pin);
}

void KeyboardController::scanKeyboard() {
  for (char j=0;j<4;j++) {
    for(char k=0;k<4;k++)
      digitalWrite(latchPin[k], j!=k);
    for (char l=0;l<6;l++)
      keyStatus[l*4+j]=!myDigitalRead(matrixPin[l]);
  }
}

bool KeyboardController::getKeyStatus(int key) {
  return keyStatus[key];
}

bool KeyboardController::getKeyClick(int key) {
  if (getKeyStatus(key)) {
    if (keyLocked[key])
      return false;
    else {
      keyLocked[key]=true;
      return true;
    }
  } else {
    keyLocked[key]=false;
    return false;
  }
}
