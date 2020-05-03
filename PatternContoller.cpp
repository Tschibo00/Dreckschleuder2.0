#include "PatternController.h"

uint8_t PatternController::getTriggers(uint8_t pos){
  return currentPattern[pos];
}
