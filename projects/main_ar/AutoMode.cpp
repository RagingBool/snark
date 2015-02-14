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
  addAutoLed(new FadingLed(_ledManager, 0, 1000, 7 * 1));
  addAutoLed(new FadingLed(_ledManager, 1, 500, 7 * 2));
  addAutoLed(new FadingLed(_ledManager, 2, 3000, 7 * 3));
  addAutoLed(new FadingLed(_ledManager, 8, 400, 7 * 4));
  addAutoLed(new FadingLed(_ledManager, 7, 700, 7 * 5));
  addAutoLed(new FadingLed(_ledManager, 6, 800, 7 * 6));

  // RGB LEDs
  addAutoLed(new FadingLed(_ledManager, 3, 8000, 7 * 1));
  addAutoLed(new FadingLed(_ledManager, 4, 3000, 7 * 2));
  addAutoLed(new FadingLed(_ledManager, 5, 5000, 7 * 3));
  addAutoLed(new FadingLed(_ledManager, 9, 4000, 7 * 4));
  addAutoLed(new FadingLed(_ledManager, 10, 6000, 7 * 5));
  addAutoLed(new FadingLed(_ledManager, 11, 3000, 7 * 6));
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

  if (_lastUpdateTime == 0) {
    _lastUpdateTime = time;
    return;
  }

  if (time == _lastUpdateTime) {
    return;
  }

  int dt = (int)(time - _lastUpdateTime);
  for (int i = 0; i < _numAutoLeds; i++) {
    _pAutoLeds[i] -> update(dt);
  }

  _lastUpdateTime = time;
}

// class AutoLed

void AutoMode::AutoLed::update(int dt) {
  int updateThresholdMillis = _updateThresholdMillis;
  int timeSinceUpdate = _timeSinceUpdate + dt;

  if (timeSinceUpdate >= updateThresholdMillis) {
    updateInner(timeSinceUpdate);
    timeSinceUpdate = 0;
  }
  
  _timeSinceUpdate = timeSinceUpdate;
}

// class FadingLed

AutoMode::FadingLed::FadingLed(LedManager& ledManager, int ledId, int period, int initialPhase):
  AutoMonoLed(ledManager, ledId) {
  
  setUpdateThresholdMillis(10);
  
  _lfo.setFrequency(periodToFrequency(period));
  _lfo.setInitialPhase(initialPhase);
  _lfo.reset();
}

void AutoMode::FadingLed::updateInner(int dt) {
  _lfo.update(dt);
  setValue(_lfo.getValue());
}
