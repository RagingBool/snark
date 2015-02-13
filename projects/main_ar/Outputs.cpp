#include "Outputs.h"

Outputs::Outputs(int numPwmOutputs, int pwmOutputs[], int numDigitalOutputs, int digitalOutputs[]) {
  _numOutputs = numPwmOutputs + numDigitalOutputs;

  _pOutputs = new Output*[_numOutputs];

  for (int i = 0; i < numPwmOutputs; i++) {
    _pOutputs[i] = new Output(pwmOutputs[i], true);
  }

  for (int i = 0; i < numDigitalOutputs; i++) {
    _pOutputs[numPwmOutputs + i] = new Output(digitalOutputs[i], false);
  }
}

void Outputs::init() {
  for (int i = 0; i < _numOutputs; i++) {
    _pOutputs[i] -> init();
  }
}
