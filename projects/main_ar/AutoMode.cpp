#include "AutoMode.h"

AutoMode::AutoMode(LedManager& ledManager):
  _ledManager(ledManager) {
  
  _maxAutoLeds = ledManager.getNumChannels();
  _pAutoLeds = new AutoLed*[_maxAutoLeds];
  
  _numAutoLeds = 0;
  
  // mono LEDs
  addAutoLed(new FadingLed(ledManager, 0, 2, 17));
  addAutoLed(new FadingLed(ledManager, 1, 3, 17 * 2));
  addAutoLed(new FadingLed(ledManager, 2, 5, 17 * 3));
  addAutoLed(new FadingLed(ledManager, 8, 4, 17 * 4));
  addAutoLed(new FadingLed(ledManager, 7, 7, 17 * 5));
  addAutoLed(new FadingLed(ledManager, 6, 8, 17 * 6));
  
  // RGB LEDs
  addAutoLed(new FadingLed(ledManager, 3, 2, 17));
  addAutoLed(new FadingLed(ledManager, 4, 3, 17 * 2));
  addAutoLed(new FadingLed(ledManager, 5, 5, 17 * 3));
  addAutoLed(new FadingLed(ledManager, 9, 4, 17 * 4));
  addAutoLed(new FadingLed(ledManager, 10, 1, 17 * 5));
  addAutoLed(new FadingLed(ledManager, 11, 3, 17 * 6));
}

AutoMode::~AutoMode() {
  for (int i = 0; i < _numAutoLeds; i++) {
    delete _pAutoLeds[i];
    _pAutoLeds[i] = 0;
  }
  
  delete[] _pAutoLeds;
  _pAutoLeds = 0;
}

void AutoMode::addAutoLed(AutoLed* pAutoLed) {
  int nextLed = _numAutoLeds;
  
  _pAutoLeds[nextLed] = pAutoLed;
  _numAutoLeds = nextLed + 1;
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
