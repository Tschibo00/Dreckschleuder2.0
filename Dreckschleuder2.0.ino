/*
 * D8 Bassdrum
 * A5 Snare
 * A4 Clap
 * A3 Closed Hi
 * A2 Open Hi
 * A1 Ride
 * A0 Crash
 * D7 Accent
 */

#include "KeyboardController.h"
#include "DisplayDriver.h"
#include "StateController.h"
#include "BPMController.h"
#include "PatternController.h"
#include "MemoryContoller.h"

KeyboardController *kc;
DisplayDriver *dd;
StateController *sc;
BPMController *bc;
PatternController *pc;
MemoryController *mc;

void setup() {
  kc=new KeyboardController();
  dd=new DisplayDriver();
  sc=new StateController();
  bc=new BPMController();
  pc=new PatternController();
  mc=new MemoryController();

  cli();//disable interrupts
  //set timer1 interrupt at 1000Hz
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1 = 0;//initialize counter value to 0
  OCR1A=249; // (16.000.000/64/1000)-1 = 250-1
  TCCR1B |= (1 << WGM12);  // turn on CTC mode
  TCCR1B |= (1 << CS11) | (1 << CS10);      // Set CS10 and CS11 bits for 64 prescaler
  TIMSK1 |= (1 << OCIE1A);      // enable timer compare interrupt
  sei();//enable interrupts

  DDRB=DDRB&0b11111110|0b00000001;  //set D8 to output
  DDRC=DDRC&0b11000000|0b00111111;  //set A0-A5 to output
  DDRD=DDRD&0b01111111|0b10000000;  //set D7 to output

//  Serial.begin(115200);
}

bool isAccentTrigger=true;
ISR(TIMER1_COMPA_vect){
  if (bc->getState()!=bc->STOP){
    bc->advance();
    if (bc->getTrigger()){
      uint8_t triggers=pc->getTriggers(bc->getPos(), isAccentTrigger);
      PORTB=PORTB&0b11111110|((triggers&64)>>6);
      PORTC=triggers;
      PORTD=PORTD&0b01111111|(isAccentTrigger<<7);
    }
  } else {
    bc->reset();
  }
  if (bc->getState()==bc->STOP||!bc->getTrigger()){
    uint8_t manualTriggers=0;
    if ((bc->getState()!=bc->REC)&&(sc->getSelectedInstrument()==-1))
      for (uint8_t k=0;k<7;k++)
        if (kc->getKeyClick(k*2+isAccentTrigger)) manualTriggers|=1<<(6-k);
    PORTB=PORTB&0b11111110|((manualTriggers&64)>>6);
    PORTC=manualTriggers;
    PORTD=PORTD&0b01111111|(isAccentTrigger<<7);
  }
  isAccentTrigger=!isAccentTrigger;
}

void loop() {
  dd->clear();
 
  kc->scanKeyboard();
  sc->setState(kc,bc);

  if (sc->getState()==sc->IDLE&&bc->getState()==bc->REC&&sc->getSelectedInstrument()==-1){
    for (uint8_t k=0;k<7;k++){
      if (kc->getKeyStatus(kc->SHIFT)){
        if (kc->getKeyStatus(k*2)||kc->getKeyStatus(k*2+1))
          pc->clearTrigger(bc->getPos(), k);
      } else {
        if (kc->getKeyClick(k*2)) pc->setTrigger(((bc->getMicron()+1)%64)/4, false, k);
        if (kc->getKeyClick(k*2+1)) pc->setTrigger(((bc->getMicron()+1)%64)/4, true, k);
      }
    }
  }

  if (bc->getPos()%4==0){
    if (bc->getState()==bc->PLAY) dd->set(kc->PLAY,CRGB::Green);
    if (bc->getState()==bc->REC) dd->set(kc->PLAY,CRGB::Red);
  }
  if (bc->getState()==bc->PLAY||bc->getState()==bc->REC)
    dd->set(bc->getOriginalPos(),CRGB::Green);

  sc->setSelectedInstrument(kc);
  if (sc->getSelectedInstrument()!=-1){
    dd->add(sc->getSelectedInstrument()*2,CRGB(0,0,24));
    dd->add(sc->getSelectedInstrument()*2+1,CRGB(0,0,24));
    dd->set(kc->INSTRUMENT,CRGB::Red);
    for (char i=0;i<16;i++){
      if (!kc->getKeyStatus(kc->INSTRUMENT)){
        if (kc->getKeyClick(i)){
          if (kc->getKeyStatus(kc->SHIFT))
            pc->clearTrigger(i,sc->getSelectedInstrument());
          else {
            if (pc->getTriggers(i,true)&(1<<(6-sc->getSelectedInstrument()))){
              pc->setTrigger(i,false,sc->getSelectedInstrument());
            } else
              if (pc->getTriggers(i,false)&(1<<(6-sc->getSelectedInstrument())))
                pc->clearTrigger(i,sc->getSelectedInstrument());
              else
                pc->setTrigger(i,true,sc->getSelectedInstrument());
          }
        }
      }
      if (pc->getTriggers(i,true)&(1<<(6-sc->getSelectedInstrument())))
        dd->add(i,CRGB::Orange);
      if (pc->getTriggers(i,false)&(1<<(6-sc->getSelectedInstrument())))
        dd->add(i,CRGB::Red);
    }
  } else {
    dd->set(kc->INSTRUMENT,CRGB::Black);
  }

  switch(sc->getState()){
    case sc->BPM:
      bc->handleKeyboard(kc);
      if (kc->getKeyStatus(kc->SHIFT)){
        dd->drawShuffle(bc->getShuffle(), bc->getSync());
      }else{
        if (!bc->repeatPressed)
          dd->drawNumber(bc->getBPM(), 0, CRGB(0, 255, 0));
        else
          dd->set(bc->getPos(),CRGB::Purple);
      }
    case sc->REPEAT:
      bc->handleKeyboard(kc);
      dd->set(bc->getPos(),CRGB::Purple);
      break;
    case sc->PATTERN:
      for (uint8_t k=0;k<16;k++)
        if (kc->getKeyClick(k)){
          pc->setPattern(k);
          mc->readPattern()
        }
      break;
    case sc->PREPATTERN:
      for (uint8_t k=0;k<16;k++)
        if (kc->getKeyClick(k))
          pc->loadPrePattern(k);
      break;
    case sc->SONG:
      break;
    case sc->FILLIN:
      break;
    case sc->COPY:
      break;
    case sc->CLEAR:
      break;
    case sc->RANDOMIZE:
      break;
    default:
      bc->resetRepeat();
      break;
  }

  dd->show();
}
