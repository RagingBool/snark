#include "Arduino.h"

#include "LedChannel.h"

LedChannel::LedChannel(int output):
  _output(output) { }

void LedChannel::init() {
  pinMode(_output, OUTPUT);
}

void LedChannel::setIntencity(int intencity) {
  analogWrite(_output, intencity);
}
