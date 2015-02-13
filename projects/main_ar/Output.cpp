#include "Arduino.h"

#include "Output.h"

Output::Output(int pinNumber, bool isPwm):
  _pinNumber(pinNumber),
  _isPwm(isPwm) { }

void Output::init() {
  pinMode(_pinNumber, OUTPUT);
}

void Output::setValue(int value) {
  if(_isPwm) {
    analogWrite(_pinNumber, value);
  }
  else {
    digitalWrite(_pinNumber, (value < 127) ? LOW : HIGH);
  }
}
