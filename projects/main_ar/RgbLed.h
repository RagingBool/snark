#pragma once

#include "LedChannel.h"

class RgbLed {
private:
  LedChannel &_channelR;
  LedChannel &_channelG;
  LedChannel &_channelB;
  
public:
  RgbLed(LedChannel &channelR, LedChannel &channelG, LedChannel &channelB);
  
  void setColor(int r, int g, int b);
};              
