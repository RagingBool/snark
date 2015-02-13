#include "Outputs.h"

Outputs::Outputs(int numPwmOutputs, int pwmOutputs[], int numDigitalOutputs, int digitalOutputs[]) {
  _numOutputs = numPwmOutputs + numDigitalOutputs;

  _outputs = new Output*[_numOutputs];

  for (int i = 0; i < numPwmOutputs; i++) {
    _outputs[i] = new Output(pwmOutputs[i], true);
  }

  for (int i = 0; i < numDigitalOutputs; i++) {
    _outputs[numPwmOutputs + i] = new Output(digitalOutputs[i], false);
  }
}

void Outputs::init() {
  for (int i = 0; i < _numOutputs; i++) {
    _outputs[i] -> init();
  }
}
