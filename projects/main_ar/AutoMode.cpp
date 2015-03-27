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
  addAutoLed(new FadingLed(_ledManager, 0, Lfo::SIN_WAVE, 1000, 7 * 1));
  addAutoLed(new FadingLed(_ledManager, 1, Lfo::TRIANGLE, 500, 7 * 2));
  addAutoLed(new FadingLed(_ledManager, 2, Lfo::SAW_DOWN, 2000, 7 * 3));
  addAutoLed(new FadingLed(_ledManager, 8, Lfo::SQUARE, 700, 64));
  addAutoLed(new FadingLed(_ledManager, 7, Lfo::SQUARE, 700, 128));
  addAutoLed(new FadingLed(_ledManager, 6, Lfo::SQUARE, 700, 192));

  // RGB LEDs
  addAutoLed(new CyclingLed(_ledManager, 3, 30000));
  addAutoLed(new CyclingLed(_ledManager, 9, 2000));
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

AutoMode::FadingLed::FadingLed(LedManager& ledManager, int ledId, Lfo::LfoFunction lfoFunction, int period, int initialPhase):
  AutoMonoLed(ledManager, ledId) {
  
  setUpdateThresholdMillis(10);
  
  _lfo.setLfoFunction(lfoFunction);
  _lfo.setFrequency(periodToFrequency(period));
  _lfo.setInitialPhase(initialPhase);
  _lfo.reset();
}

void AutoMode::FadingLed::updateInner(int dt) {
  _lfo.update(dt);
  setValue(_lfo.getOutput());
}

// class CyclingLed

AutoMode::CyclingLed::CyclingLed(LedManager& ledManager, int ledId, int huePeriod, int initialHue):
  AutoRgbLed(ledManager, ledId) {
  
  setUpdateThresholdMillis(10);
  
  _hueLfo.setLfoFunction(Lfo::SAW_DOWN);
  _hueLfo.setFrequency(periodToFrequency(huePeriod));
  _hueLfo.setInitialPhase(initialHue);
  _hueLfo.reset();
  
  _saturationSig.setValue(255);
  _intensitySig.setValue(255);
  
  _hsiToRgb.setHueInputSig(_hueLfo.getOutputSig());
  _hsiToRgb.setSaturationInputSig(&_saturationSig);
  _hsiToRgb.setIntensityInputSig(&_intensitySig);
}

void AutoMode::CyclingLed::updateInner(int dt) {
  _hueLfo.update(dt);
  _hsiToRgb.update(dt);
  setValue(_hsiToRgb.getRedOutput(), _hsiToRgb.getGreenOutput(), _hsiToRgb.getBlueOutput());
}
