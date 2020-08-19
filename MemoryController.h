#ifndef MEMORY_CONTROLLER
#define MEMORY_CONTROLLER

#include <Arduino.h>

class MemoryController {
  private:

  public:
	void setBPM(float bpm);
	float getBPM();

	void writePattern(uint8_t patternNumber, uint8_t **pattern);
	uint8_t** readPattern(uint8_t patternNumber);
	void copyPattern(uint8_t sourcePattern, uint8_t targetPattern);
};

#endif
