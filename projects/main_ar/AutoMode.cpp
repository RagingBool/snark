#include <Arduino.h>

#include "AutoMode.h"

AutoMode::AutoMode(LedManager& ledManager):
  _ledManager(ledManager) {
  
  _maxAutoLeds = ledManager.getNumChannels();
  _pAutoLeds = new AutoLed*[_maxAutoLeds];
  
  _numAutoLeds = 0;
  
  _lastUpdateTime = 0;
  
  setupModes();
}

void AutoMode::setupModes() {
  // mono LEDs
  addAutoLed(new FadingLed(_ledManager, 0, 2, 17));
  addAutoLed(new FadingLed(_ledManager, 1, 3, 17 * 2));
  addAutoLed(new FadingLed(_ledManager, 2, 5, 17 * 3));
  addAutoLed(new FadingLed(_ledManager, 8, 4, 17 * 4));
  addAutoLed(new FadingLed(_ledManager, 7, 7, 17 * 5));
  addAutoLed(new FadingLed(_ledManager, 6, 8, 17 * 6));
  
  // RGB LEDs
  addAutoLed(new FadingLed(_ledManager, 3, 2, 17));
  addAutoLed(new FadingLed(_ledManager, 4, 3, 17 * 2));
  addAutoLed(new FadingLed(_ledManager, 5, 5, 17 * 3));
  addAutoLed(new FadingLed(_ledManager, 9, 4, 17 * 4));
  addAutoLed(new FadingLed(_ledManager, 10, 1, 17 * 5));
  addAutoLed(new FadingLed(_ledManager, 11, 3, 17 * 6));
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
  unsigned long time = millis();

  if(_lastUpdateTime == 0) {
    _lastUpdateTime = time;
    return;
  }
  
  if(time == _lastUpdateTime) {
    return;
  }
  
  int dt = (int)(time - _lastUpdateTime);
  
  for (int i = 0; i < _numAutoLeds; i++) {
    _pAutoLeds[i] -> update(dt);
  }
}

// class FadingLed

void AutoMode::FadingLed::update(int dt) {
  int phase = _phase;
  
  int value = (phase < 256) ? phase : 511 - phase;
  
  setValue(value);
  
  _phase = (phase + _step) % 512;
}
