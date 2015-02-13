#pragma once

#include "Output.h"

class Outputs {
private:
  int _numOutputs;
  Output **_pOutputs;

public:
  Outputs(int numPwmOutputs, int pwmOutputs[], int numDigitalOutputs, int digitalOutputs[]);
  
  ~Outputs();
  
  void init();
  
  int getNumOutputs() const { return _numOutputs; }
  
  Output& operator[](int id) const { return *_pOutputs[id]; }
};
