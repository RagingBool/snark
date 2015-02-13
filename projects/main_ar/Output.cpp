#include "Arduino.h"

#include "Output.h"

Output::Output(int output, bool isPwm):
  _output(output),
  _isPwm(isPwm) { }

void Output::init() {
  pinMode(_output, OUTPUT);
}

void Output::setIntencity(int intencity) {
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
