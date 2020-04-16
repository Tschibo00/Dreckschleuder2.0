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

int testStep=0;

void loop() {
  dd->clear();
  
  kc->scanKeyboard();

  sc->setCurrentState(kc);

  switch(sc->getCurrentState()){
    case sc->SET_BPM:
      bc->handleKeyboard(kc);
      dd->drawNumber(bc->getBPM(), 0, CRGB(0, 255, 0));
      if (bc->getRepeat()!=0) {
        dd->fill(12, 15, CRGB::Red);
        switch(bc->getRepeat()){
          case 8:
            if (bc->getStep()&1==1)
              dd->set(12, CRGB::Black);
            break;
          case 16:
            if (bc->getMicron()&7>3)
              dd->set(13, CRGB::Black);
            break;
          case 32:
            if (bc->getMicron()&3>1)
              dd->set(14, CRGB::Black);
            break;
          case 64:
            if (bc->getMicron()&1==1)
              dd->set(15, CRGB::Black);
            break;
        }
      }
      break;
  }

  dd->show();



  testStep++;
  bc->setMicron(testStep);
  delay(80);

  
}
