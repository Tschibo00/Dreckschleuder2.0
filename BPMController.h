#include "KeyboardController.h"

class BPMController {
  private:
    float bpm=130.f;
    float incPerStep=0.f;
    float currentMicron=0.f;    // 1/64th notes
    uint8_t lastMicron=255;
    uint8_t repeatPattern=16;
    uint8_t repeatStep=4;
    uint8_t repeatStart=0;

    void clampBPM();

  public:
    bool isRunning=false;
    bool repeatPressed;
    void handleKeyboard(KeyboardController *kc);
    float getBPM();

    bool getTrigger(bool accent);
    uint8_t getMicron();
    uint8_t getPos();
    uint8_t getOriginalPos();

    void reset();
    void resetRepeat();

    void advance();
};
