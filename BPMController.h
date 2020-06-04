#ifndef BPM_CONTROLLER
#define BPM_CONTROLLER

#include "KeyboardController.h"

class BPMController {
  private:
    float bpm=130.f;
    float incPerStep=130.f/3750.f;
    float currentMicron=0.f;    // 1/64th notes
    uint8_t lastMicron=255;
    uint8_t repeatPattern=16;
    uint8_t repeatStep=4;
    uint8_t repeatStart=0;
    int8_t triggerState=0;     // 0=no trigger, 2=accent trigger, 1=no accent triggers
    int8_t shuffle=0;
    uint8_t sync=NO;
    bool blockSync=false;
    uint8_t runningState=STOP;

    void clampBPM();

  public:
    enum STATE{STOP, PLAY, REC};
    enum SYNC{NO,S8,S16,S24,S48};

    void setState(uint8_t state);
    uint8_t getState();

    bool repeatPressed;
    void handleKeyboard(KeyboardController *kc);
    float getBPM();

    bool getTrigger();
    uint8_t getMicron();
    uint8_t getPos();
    uint8_t getOriginalPos();

    int8_t getShuffle();
    uint8_t getSync();

    void reset();
    void resetRepeat();

    void advance();
};

#endif
