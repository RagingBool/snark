#pragma once

#include "Output.h"

class LedChannels {
private:
  int _numOutputs;
  Output **_outputs;

public:
  LedChannels(int numPwmOutputs, int pwmOutputs[], int numDigitalOutputs, int digitalOutputs[]);
  
  void init();
  
  Output& operator[](int id) { return *_outputs[id]; }
};
