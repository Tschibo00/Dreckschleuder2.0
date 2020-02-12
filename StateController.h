#include "KeyboardController.h"

class StateController {
  private:
    char currentState;

  public:
    static const char IDLE=0;
    static const char PLAY=0;
    static const char REC=0;
    static const char SET_BPM=0;
    static const char PATTERN=0;

    StateController();
    void setCurrentState(KeyboardController *kc);
    char getCurrentState();
};
