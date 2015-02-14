#pragma once

#include <stdint.h>

inline uint16_t periodToFrequency(uint16_t periodMillis) { return 0xFFFF / periodMillis; }

class PhaseGenerator {
private:
  int8_t _fixedPointBits;
  uint16_t _phaseFixed;
  uint16_t _frequency;

public:
  PhaseGenerator(int8_t phaseResolutionBits):
    _fixedPointBits(16 - phaseResolutionBits),
    _phaseFixed(0) { setFrequency(1); }
  
  uint16_t getFrequency() const { return _frequency; }
  void setFrequency(uint16_t frequency) { _frequency = frequency; }
  
  uint16_t getPhase() const { return fixedPhaseToPhase(_phaseFixed); }
  void setPhase(uint16_t phase) { _phaseFixed = phaseToFixedPhase(phase); }
  
  void update(uint16_t deltaMillis) { _phaseFixed += deltaMillis * _frequency; }
  
private:
  uint16_t fixedPhaseToPhase(uint16_t fixedPhase) const { return fixedPhase >> _fixedPointBits; }
  uint16_t phaseToFixedPhase(uint16_t phase) const { return phase << _fixedPointBits; }
};

class Lfo {
private:
  PhaseGenerator _phaseGenerator;
  uint16_t _frequency;
  uint8_t _value;
  uint8_t _initialPhase;
  
public:
  Lfo(): _phaseGenerator(9), _value(0) { setFrequency(1); }
  
  uint16_t getFrequency() const { return _phaseGenerator.getFrequency(); }
  void setFrequency(uint16_t frequency) { _phaseGenerator.setFrequency(frequency); }
  
  uint8_t getInitialPhase() const { return _initialPhase; }
  void setInitialPhase(uint8_t initialPhase) { _initialPhase = initialPhase; }
  
  void reset() { _phaseGenerator.setPhase(_initialPhase * 2); }
  
  uint8_t getValue() const { return _value; }
  
  void update(uint16_t deltaMillis);
};

