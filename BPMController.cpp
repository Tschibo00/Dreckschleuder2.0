#include "BPMController.h"

void BPMController::clampBPM() {
  if (bpm<0.f) bpm=0.f;
  if (bpm>999.f) bpm=999.f;
}

void BPMController::handleKeyboard(KeyboardController *kc) {
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
}

float BPMController::getBPM() {
  clampBPM();
  return bpm;
}
