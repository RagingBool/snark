#pragma once

#include <stdint.h>

class PhaseGenerator {
private:
  int8_t _fixedPointBits;
  uint16_t _phaseFixed;
  uint16_t _stepPerMillisecondFixed;
  uint16_t _periodMillis;

public:
  PhaseGenerator(int8_t phaseResolutionBits):
    _fixedPointBits(16 - phaseResolutionBits),
    _phaseFixed(0) { setPeriodMillis(1000); }
  
  uint16_t getPeriodMillis() const { return _periodMillis; }
  void setPeriodMillis(uint16_t periodMillis) { _periodMillis = periodMillis; _stepPerMillisecondFixed = 0xFFFF / periodMillis; }
  
  uint16_t getPhase() const { return fixedPhaseToPhase(_phaseFixed); }
  void setPhase(uint16_t phase) { _phaseFixed = phaseToFixedPhase(phase); }
  
  void update(uint16_t deltaMillis) { _phaseFixed += deltaMillis * _stepPerMillisecondFixed; }
  
private:
  uint16_t fixedPhaseToPhase(uint16_t fixedPhase) const { return fixedPhase >> _fixedPointBits; }
  uint16_t phaseToFixedPhase(uint16_t phase) const { return phase << _fixedPointBits; }
};
