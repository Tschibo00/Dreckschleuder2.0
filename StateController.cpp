#include "StateController.h"

StateController::StateController() {
  currentState = IDLE;
}

void StateController::setCurrentState(KeyboardController *kc) {
  if (kc->getKeyStatus(17)) currentState=SET_BPM;
  if (kc->getKeyStatus(20)) currentState=PATTERN;
}

char StateController::getCurrentState() {
  return currentState;
}
