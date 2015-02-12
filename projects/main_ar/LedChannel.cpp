#include "Arduino.h"

#include "LedChannel.h"

LedChannel::LedChannel(int output, bool isPwm):
  _output(output),
  _isPwm(isPwm) { }

void LedChannel::init() {
  pinMode(_output, OUTPUT);
}

void LedChannel::setIntencity(int intencity) {
  if(_isPwm) {
    analogWrite(_output, intencity);
  }
  else {
    if(intencity < 127) {
      digitalWrite(_output, LOW);
    }
    else {
      digitalWrite(_output, HIGH);
    }  
  }
}
