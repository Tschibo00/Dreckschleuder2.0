#include "PatternController.h"

uint8_t PatternController::getTriggers(uint8_t pos, bool accent){
  if (accent)
    return currentPattern[pos];
  else
    return currentPattern[pos+16];
}

void PatternController::setTrigger(uint8_t pos, bool accent, uint8_t instrument){
  uint8_t posArray=pos+(!accent)*16;
  currentPattern[posArray]|=1<<(6-instrument);
  posArray=pos+accent*16;
  currentPattern[posArray]&=255^1<<(6-instrument);
}

void PatternController::clearTrigger(uint8_t pos, uint8_t instrument){
  currentPattern[pos]&=255^(1<<(6-instrument));
  currentPattern[pos+16]&=255^(1<<(6-instrument));
}

void PatternController::setPattern(uint8_t pattern){
  selectedPattern=pattern;
}

uint8_t PatternController::getPattern(){
  return selectedPattern;
}

void PatternController::loadPrePattern(uint8_t pattern){
  
}
