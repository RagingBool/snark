#include "AutoMode.h"

AutoMode::AutoMode(LedManager& ledManager):
  _ledManager(ledManager) {
  
  _numAutoLeds = ledManager.getNumChannels();
  
  _pAutoLeds = new AutoLed*[_numAutoLeds];
  for (int i = 0; i < _numAutoLeds; i++) {
    _pAutoLeds[i] = new FadingLed(ledManager, i, i + 2, i * 11);
  }
}

AutoMode::~AutoMode() {
  for (int i = 0; i < _numAutoLeds; i++) {
    delete _pAutoLeds[i];
    _pAutoLeds[i] = 0;
  }
  
  delete[] _pAutoLeds;
  _pAutoLeds = 0;
}
  
void AutoMode::update() {
  for (int i = 0; i < _numAutoLeds; i++) {
    _pAutoLeds[i] -> update();
  }
}

// class FadingLed

void AutoMode::FadingLed::update() {
  int phase = _phase;
  
  int value = (phase < 256) ? phase : 511 - phase;
  
  setValue(value);
  
  _phase = (phase + _step) % 512;
}
