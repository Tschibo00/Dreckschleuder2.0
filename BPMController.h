#include "KeyboardController.h"

class BPMController {
  private:
    float bpm;
    int repeat;

    int micron;      // 1/128th

    void clampBPM();

  public:
    void handleKeyboard(KeyboardController *kc);
    float getBPM();
    int getRepeat();

    int getStep();
    int getMicron();   // 1/128th

    void setMicron(int step);
};
