#ifndef STATE_CONTROLLER
#define STATE_CONTROLLER

#include "KeyboardController.h"
#include "BPMController.h"

class StateController {
  private:
    uint8_t currentState;
    uint8_t playingState;
    int8_t selectedInstrument=-1;

  public:
    enum STATE{IDLE, BPM, REPEAT, PATTERN, PREPATTERN, SONG, FILLIN, COPY, CLEAR, INSTRUMENT, RANDOMIZE};

    StateController();
    void setCurrentState(KeyboardController *kc, BPMController *bc);
    uint8_t getCurrentState();
    uint8_t getPlayingState();
    int8_t getSelectedInstrument();
    void setSelectedInstrument(KeyboardController *kc);
};

#endif
