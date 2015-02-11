#pragma once

#include "LedChannel.h"

class MonoLed {
private:
  LedChannel &_channel;
  
public:
  MonoLed(LedChannel &channel);
  
  void setColor(int value);
};                                                                                                     
