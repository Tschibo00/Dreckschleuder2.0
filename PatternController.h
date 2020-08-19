#ifndef PATTERN_CONTROLLER
#define PATTERN_CONTROLLER

#include <Arduino.h>

class PatternController {
  private:
    uint8_t currentPattern[32]={64,0,0,0,64,0,0,0,64,0,0,0,64,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};    // first 16 steps are the triggers with accent, step 16-31 are the trigger without accent
    uint8_t selectedPattern=0;

  public:
    uint8_t getTriggers(uint8_t pos, bool accent);
    void setTrigger(uint8_t pos, bool accent, uint8_t instrument); // 0=bdr,1=snr,2=clp,3=ch,4=oh,5=ride,6=crash
    void clearTrigger(uint8_t pos, uint8_t instrument);
    void setPattern(uint8_t pattern);
    uint8_t getPattern();
    void putPatternData(uint8_t **pattern);
    uint8_t** getPatternData();
};
#endif
