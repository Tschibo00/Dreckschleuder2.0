#include "KeyboardController.h"
#include "DisplayDriver.h"
#include "StateController.h"
#include "BPMController.h"

KeyboardController *kc;
DisplayDriver *dd;
StateController *sc;
BPMController *bc;

void setup() {
  kc=new KeyboardController();
  dd=new DisplayDriver();
  sc=new StateController();
  bc=new BPMController();
}

void loop() {
  kc->scanKeyboard();

  sc->setCurrentState(kc);

  switch(sc->getCurrentState()){
    case sc->SET_BPM:
      bc->handleKeyboard(kc);
      dd->drawNumber(bc->getBPM(), 0, CRGB(0, 255, 0));
      break;
  }

  dd->show();
}
