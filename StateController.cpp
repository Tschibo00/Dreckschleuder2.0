#include "StateController.h"

StateController::StateController() {
  currentState = IDLE;
}

void StateController::setCurrentState(KeyboardController *kc, BPMController *bc) {
  if (kc->getKeyClick(kc->PLAY)) {
    if (kc->getKeyStatus(kc->SHIFT)) {
      switch(bc->getState()){
        case bc->STOP: bc->setState(bc->REC); break;
        case bc->PLAY: bc->setState(bc->REC); break;
        case bc->REC: bc->setState(bc->STOP); break;
      }
    }else{
      switch(bc->getState()){
        case bc->STOP: bc->setState(bc->PLAY); break;
        case bc->PLAY: bc->setState(bc->STOP); break;
        case bc->REC: bc->setState(bc->PLAY); break;
      }
    }
  }
  currentState=IDLE;
  if (kc->getKeyStatus(kc->INSTRUMENT)) {
    if (kc->getKeyStatus(kc->SHIFT)) currentState=RANDOMIZE; else currentState=INSTRUMENT;
  }
  if (kc->getKeyStatus(kc->PATTERN)) {
    if (kc->getKeyStatus(kc->SHIFT)) currentState=PREPATTERN; else currentState=PATTERN;
  }
  if (kc->getKeyStatus(kc->FILLIN)) {
    if (kc->getKeyStatus(kc->SHIFT)) currentState=FILLIN; else currentState=SONG;
  }
  if (kc->getKeyStatus(kc->COPY)) {
    if (kc->getKeyStatus(kc->SHIFT)) currentState=CLEAR; else currentState=COPY;
  }
  if (kc->getKeyStatus(kc->TEMPO)) {
    if (kc->getKeyStatus(kc->SHIFT)) currentState=REPEAT; else currentState=BPM;
  }
  if (kc->getKeyStatus(kc->RESERVED)) {
    if (kc->getKeyStatus(kc->SHIFT)) currentState=REPEAT; else currentState=REPEAT;
  }
}

uint8_t StateController::getCurrentState() {
  return currentState;
}

int8_t StateController::getSelectedInstrument(){
  return selectedInstrument;
}

void StateController::setSelectedInstrument(KeyboardController *kc){
  if (kc->getKeyClick(kc->INSTRUMENT)){
    selectedInstrument=-1;
  } else {
    if (kc->getKeyStatus(kc->INSTRUMENT)){
      for (char i=0;i<14;i++)
        if (kc->getKeyStatus(i))
          selectedInstrument=i/2;
    }
  }
}
