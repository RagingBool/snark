#include <Arduino.h>

#include "Snark.h"

int Snark::NUM_PWM_CHANNELS = 6;
int Snark::PWM_CHANNELS[] = {3, 5, 6, 9, 10, 11};
int Snark::NUM_DIGITAL_CHANNELS = 6;
int Snark::DIGITAL_CHANNELS[] = {2, 4, 7, 8, 12, 13};

Snark::Snark() {
  _f1 = 0;
  _f2 = 10;
  _f3 = 20;
  _f4 = 30;
}

void Snark::init() {
  _pOutputs = new Outputs(NUM_PWM_CHANNELS, PWM_CHANNELS, NUM_DIGITAL_CHANNELS, DIGITAL_CHANNELS);
  _pLedManager = new LedManager(*_pOutputs);
  
  _pOutputs -> init();
}

void Snark::loop() {
  _pLedManager -> setValue(0, func(_f1));
  _pLedManager -> setValue(1, func(_f2));
  _pLedManager -> setValue(2, func(_f3));
  _pLedManager -> setValue(3, func(_f2));
  _pLedManager -> setValue(4, func(_f3));
  _pLedManager -> setValue(5, func(_f4));
  
  _pLedManager -> setValue(6, func(_f1));
  _pLedManager -> setValue(7, func(_f2));
  _pLedManager -> setValue(8, func(_f3));
  _pLedManager -> setValue(9, func(_f4));
  _pLedManager -> setValue(10, func(_f3));
  _pLedManager -> setValue(11, func(_f2));
  
  _f1 = (_f1 + 1) % 512;
  _f2 = (_f2 + 3) % 512;
  _f3 = (_f3 + 5) % 512;
  _f4 = (_f4 + 7) % 512;
  
  delay(10);
}

int Snark::func(int x) {
  if(x < 256) {
    return x;
  }
  else {
    return 511 - x;
  }
}
