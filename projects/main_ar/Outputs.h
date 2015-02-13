#pragma once

#include "Output.h"

class Outputs {
private:
  int _numOutputs;
  Output **_outputs;

public:
  Outputs(int numPwmOutputs, int pwmOutputs[], int numDigitalOutputs, int digitalOutputs[]);
  
  void init();
  
  Output& operator[](int id) { return *_outputs[id]; }
};
