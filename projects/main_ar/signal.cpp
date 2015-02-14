#include "signal.h"

void Lfo::update(uint16_t deltaMillis) {
  _phaseGenerator.update(deltaMillis);
  
  int phase = _phaseGenerator.getPhase();
  _value = (phase < 256) ? phase : 511 - phase;
}
