#include "MemoryController.h"
#incude <EEPROM.h>

void MemoryController::setBPM(float bpm){
	EEPROM.put(512,bpm);
}

float MemoryController::getBPM(){
	float bpm;
	EEPROM.get(512,bpm);
	return bpm;
}

void MemoryController::writePattern(uint8_t patternNumber, uint8_t **pattern){
	for (uint8_t i=0;i<32;i++)
		EEPROM.update(patternNumber*32+i, pattern[i]);
}

uint8_t** MemoryController::readPattern(uint8_t patternNumber){
	uint8_t pattern[32];
	for (uint8_t i=0;i<32;i++)
		EEPROM.read(patternNumber*32+i);
	return pattern;
}

void MemoryController::copyPattern(uint8_t sourcePattern, uint8_t targetPattern){
	for (uint8_t i=0;i<32;i++)
		EEPROM.update(targetPattern*32+i, EEPROM.read(sourcePattern*32+i));
}
