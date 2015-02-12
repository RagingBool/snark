#include "LedChannels.h"

LedChannels::LedChannels(int numPwmOutputs, int pwmOutputs[], int numDigitalOutputs, int digitalOutputs[]) {
  _numChannels = numPwmOutputs + numDigitalOutputs;
  
  _channels = new LedChannel*[_numChannels];
  
  for(int i = 0; i < numPwmOutputs; i++) {
    _channels[i] = new LedChannel(pwmOutputs[i], true);
  }
  
  for(int i = 0; i < numDigitalOutputs; i++) {
    _channels[numPwmOutputs + i] = new LedChannel(digitalOutputs[i], false);
  }
}

void LedChannels::init() {
  for(int i = 0; i < _numChannels; i++) {
    _channels[i] -> init();
  }
}
