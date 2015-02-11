#include "RgbLed.h"

RgbLed::RgbLed(LedChannel &channelR, LedChannel &channelG, LedChannel &channelB):
  _channelR(channelR),
  _channelG(channelG),
  _channelB(channelB) { }
  
void RgbLed::setColor(int r, int g, int b) {
  _channelR.setIntencity(r);
  _channelG.setIntencity(g);
  _channelB.setIntencity(b);
}
