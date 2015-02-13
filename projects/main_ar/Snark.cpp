#include <Arduino.h>

#include "Snark.h"

int Snark::NUM_PWM_CHANNELS = 6;
int Snark::PWM_CHANNELS[] = {3, 5, 6, 9, 10, 11};
int Snark::NUM_DIGITAL_CHANNELS = 6;
int Snark::DIGITAL_CHANNELS[] = {2, 4, 7, 8, 12, 13};

Snark::Snark() { }

void Snark::init() {
  _pOutputs = new Outputs(NUM_PWM_CHANNELS, PWM_CHANNELS, NUM_DIGITAL_CHANNELS, DIGITAL_CHANNELS);
  _pLedManager = new LedManager(*_pOutputs);
  _pAutoMode = new AutoMode(*_pLedManager);
  
  _pOutputs -> init();
}

void Snark::loop() {
  _pAutoMode -> update();
  
  delay(10);
}

