#pragma once

#include "Output.h"

class Outputs {
private:
  int _numOutputs;
  Output **_pOutputs;

public:
  Outputs(int numPwmOutputs, int pwmOutputs[], int numDigitalOutputs, int digitalOutputs[]);
  
  void init();
  
  Output& operator[](int id) { return *_pOutputs[id]; }
};
