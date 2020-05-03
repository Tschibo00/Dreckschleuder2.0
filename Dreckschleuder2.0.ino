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

KeyboardController *kc;
DisplayDriver *dd;
StateController *sc;
BPMController *bc;
PatternController *pc;

void setup() {
  kc=new KeyboardController();
  dd=new DisplayDriver();
  sc=new StateController();
  bc=new BPMController();
  pc=new PatternController();

  cli();//disable interrupts
  //set timer1 interrupt at 10000Hz
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

ISR(TIMER1_COMPA_vect){
  if (bc->runningState!=bc->STOP){
    bc->advance();
    if (bc->getTrigger(true)){        // first trigger all accented drums
      uint8_t triggers=pc->getTriggers(bc->getPos(), true);
      PORTB=PORTB&0b11111110|((triggers&64)>>6);
      PORTC=triggers;
      PORTD=PORTD&0b01111111|0b10000000;
    }
    if (bc->getTrigger(false)){       // then trigger all not accented drums
      uint8_t triggers=pc->getTriggers(bc->getPos(), false);
      PORTB=PORTB&0b11111110|((triggers&64)>>6);
      PORTC=triggers;
      PORTD=PORTD&0b01111111;
    }
    if (!bc->getTrigger(true)&&!bc->getTrigger(false)){   // and if all is done, set trigger outs back to 0
      PORTB=PORTB&0b11111110;
      PORTC=0;
      PORTD=PORTD&0b01111111;
    }
  } else {                            // not running => nothing to play
    bc->reset();
    PORTB=PORTB&0b11111110;
    PORTC=0;
    PORTD=PORTD&0b01111111;
  }
}

void loop() {
  dd->clear();
 
  kc->scanKeyboard();

  if (kc->getKeyClick(23)){
    if (kc->getKeyStatus(22)){
      if (bc->runningState==bc->REC)
        bc->runningState=bc->STOP;
      else
        bc->runningState=bc->REC;
    } else {
      if (bc->runningState==bc->PLAY)
        bc->runningState=bc->STOP;
      else
        bc->runningState=bc->PLAY;
    }
  }

  if (bc->runningState==bc->REC){
    for (uint8_t k=0;k<7;k++){
      if (kc->getKeyStatus(22)){
        if (kc->getKeyStatus(k*2)||kc->getKeyStatus(k*2+1))
          pc->clearTrigger(bc->getPos(), k);
      } else {
        if (kc->getKeyClick(k*2)) pc->setTrigger(bc->getPos(), false, k);
        if (kc->getKeyClick(k*2+1)) pc->setTrigger(bc->getPos(), true, k);
      }
    }
  }

  if (bc->getPos()%4==0){
    if (bc->runningState==bc->PLAY) dd->set(23,CRGB::Green);
    if (bc->runningState==bc->REC) dd->set(23,CRGB::Red);
  }
  dd->set(bc->getOriginalPos(),CRGB::Red);

  sc->setCurrentState(kc);

  switch(sc->getCurrentState()){
    case sc->SET_BPM:
      bc->handleKeyboard(kc);
      if (!bc->repeatPressed)
        dd->drawNumber(bc->getBPM(), 0, CRGB(0, 255, 0));
      else
        dd->set(bc->getPos(),CRGB::Purple);
    case sc->SET_REPEAT:
      bc->handleKeyboard(kc);
      dd->set(bc->getPos(),CRGB::Purple);
      break;
    default:
      bc->resetRepeat();
      break;
  }

  dd->show();
}
