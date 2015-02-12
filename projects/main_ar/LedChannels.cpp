#include "LedChannels.h"

LedChannels::LedChannels(int numPwmOutputs, int pwmOutputs[]) {
  _numChannels = numPwmOutputs;
  
  _channels = new LedChannel*[_numChannels];
  
  for(int i = 0; i < numPwmOutputs; i++) {
    _channels[i] = new LedChannel(pwmOutputs[i]);
  }
}

void LedChannels::init() {
  for(int i = 0; i < _numChannels; i++) {
    _channels[i] -> init();
  }
}
