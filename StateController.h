#include "KeyboardController.h"

class StateController {
  private:
    char currentState;

  public:
    enum STATE{IDLE, PLAY, REC, SET_BPM, SET_REPEAT, PATTERN};

    StateController();
    void setCurrentState(KeyboardController *kc);
    char getCurrentState();
};
