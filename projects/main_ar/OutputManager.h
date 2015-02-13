#pragma once

#include "Output.h"

class OutputManager {
private:
  int _numOutputs;
  Output **_outputs;

public:
  OutputManager(int numPwmOutputs, int pwmOutputs[], int numDigitalOutputs, int digitalOutputs[]);
  
  void init();
  
  Output& operator[](int id) { return *_outputs[id]; }
};
