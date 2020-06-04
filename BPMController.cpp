#include "BPMController.h"

void BPMController::clampBPM() {
  if (bpm<.1f) bpm=.1f;
  if (bpm>999.9f) bpm=999.9f;
  incPerStep=bpm/3750.f;  // increase per 1/1000th sec for 1/64 steps
}

void BPMController::handleKeyboard(KeyboardController *kc) {
  if (kc->getKeyStatus(kc->SHIFT)){
    if (kc->getKeyClick(0)) shuffle=-4;
    if (kc->getKeyClick(1)) shuffle=-3;
    if (kc->getKeyClick(2)) shuffle=-2;
    if (kc->getKeyClick(3)) shuffle=-1;
    if (kc->getKeyClick(4)) shuffle=0;
    if (kc->getKeyClick(5)) shuffle=1;
    if (kc->getKeyClick(6)) shuffle=2;
    if (kc->getKeyClick(7)) shuffle=3;
    if (kc->getKeyClick(8)) shuffle=4;
    if (kc->getKeyClick(9)) shuffle=5;
    if (kc->getKeyClick(10)) sync=S8;
    if (kc->getKeyClick(11)) sync=S16;
    if (kc->getKeyClick(12)) sync=S24;
    if (kc->getKeyClick(13)) sync=S48;
    if (kc->getKeyClick(14)) sync=NO;
    if (kc->getKeyClick(15)) sync=NO;
  }else{
    if (kc->getKeyClick(0)) bpm-=.1f;
    if (kc->getKeyClick(1)) bpm+=.1f;
    if (kc->getKeyClick(2)) bpm-=1.f;
    if (kc->getKeyClick(3)) bpm+=1.f;
    if (kc->getKeyClick(4)) bpm-=5.f;
    if (kc->getKeyClick(5)) bpm+=5.f;
    if (kc->getKeyClick(6)) bpm-=10.f;
    if (kc->getKeyClick(7)) bpm+=10.f;
    if (kc->getKeyClick(8)) bpm=90.f;
    if (kc->getKeyClick(9)) bpm=120.f;
    if (kc->getKeyClick(10)) bpm=140.f;
    if (kc->getKeyClick(11)) bpm=200.f;
    this->clampBPM();
  
    if (kc->getKeyClick(12)||kc->getKeyClick(13)) repeatStart=getPos();
    if (kc->getKeyStatus(13)) repeatPattern=1; else {if (kc->getKeyStatus(12)) repeatPattern=2; else {repeatPattern=16;repeatStart=0;}}
    if (kc->getKeyStatus(15)) repeatStep=1; else {if (kc->getKeyStatus(14)) repeatStep=2; else repeatStep=4;}
    repeatPressed=kc->getKeyStatus(12)|kc->getKeyStatus(13)|kc->getKeyStatus(14)|kc->getKeyStatus(15);
  }
}

float BPMController::getBPM() {
  clampBPM();
  return bpm;
}

uint8_t BPMController::getMicron() {
  return (uint8_t)currentMicron;
}

uint8_t BPMController::getPos(){
  return (((uint8_t)(currentMicron/4.f))%repeatPattern+repeatStart)%16;
}

uint8_t BPMController::getOriginalPos(){
  return ((uint8_t)(currentMicron/4.f));
}

void BPMController::advance(){
  lastMicron=getMicron();

  if (sync!=NO){
    if (digitalRead(13)&&!blockSync){
      blockSync=true;
      currentMicron+=4.f;
    }
    if (!digitalRead(13)) blockSync=false;
  } else {
  currentMicron+=incPerStep;
  }
  
  if (currentMicron>=64.f)
    currentMicron-=64.f;
  triggerState--;
  if (triggerState<0) triggerState=0;
  if (lastMicron!=getMicron()&&(getMicron()%repeatStep==0)) triggerState=2;
}

int8_t BPMController::getShuffle(){
  return 0;
}

uint8_t BPMController::getSync(){
  return sync;
}

void BPMController::reset(){
  currentMicron=0.f;
  lastMicron=255;
}

void BPMController::resetRepeat(){
  repeatPattern=16;
  repeatStep=4;
}

bool BPMController::getTrigger(){
  return triggerState>0;
}

void BPMController::setState(uint8_t state){
  runningState=state;
}

uint8_t BPMController::getState(){
  return runningState;
}
