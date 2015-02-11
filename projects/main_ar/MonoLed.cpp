#include "MonoLed.h"

MonoLed::MonoLed(LedChannel &channel):
  _channel(channel) { }
  
void MonoLed::setColor(int value) {
  _channel.setIntencity(value);
}
