#include "KeyboardController.h"

class BPMController {
  private:
    float bpm;

    void clampBPM();

  public:
    void handleKeyboard(KeyboardController *kc);
    float getBPM();
};
