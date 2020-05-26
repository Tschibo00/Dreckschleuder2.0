#include "KeyboardController.h"

class StateController {
  private:
    char currentState;
    int8_t selectedInstrument=-1;

  public:
    enum STATE{IDLE, SET_BPM, SET_REPEAT, PATTERN};

    StateController();
    void setCurrentState(KeyboardController *kc);
    char getCurrentState();
    int8_t getSelectedInstrument();
    void setSelectedInstrument(KeyboardController *kc);
};
