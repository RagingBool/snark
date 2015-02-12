#pragma once

#include "LedChannel.h"

class LedChannels {
private:
  int _numChannels;
  LedChannel **_channels;

public:
  LedChannels(int pwmOutputs[], int numPwmOutputs);
  
  void init();
  
  LedChannel& operator[](int id) { return *_channels[id]; }
};
