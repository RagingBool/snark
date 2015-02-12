#pragma once

#include "LedChannel.h"

class LedChannels {
private:
  int _numChannels;
  LedChannel **_channels;

public:
  LedChannels(int numPwmOutputs, int pwmOutputs[], int numDigitalOutputs, int digitalOutputs[]);
  
  void init();
  
  LedChannel& operator[](int id) { return *_channels[id]; }
};
