#include "StateController.h"

StateController::StateController() {
  currentState = IDLE;
}

void StateController::setCurrentState(KeyboardController *kc) {
  currentState=IDLE;
  if (kc->getKeyStatus(kc->TEMPO)) currentState=SET_BPM;
  if (kc->getKeyStatus(kc->RESERVED)) currentState=SET_REPEAT;
  if (kc->getKeyStatus(kc->PATTERN)) currentState=PATTERN;
}

char StateController::getCurrentState() {
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
