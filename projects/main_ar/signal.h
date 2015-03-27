#pragma once

#include <stdint.h>

inline uint16_t periodToFrequency(uint16_t periodMillis) { return 0xFFFF / periodMillis; }

class Signal {
private:
  uint16_t _value;
  
public:
  Signal(): _value(0) { }
  
  uint16_t getValue() const { return _value; }
  
  void setValue(uint16_t newValue) { _value = newValue; }
};

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
public:
  enum LfoFunction {
    SAW_UP,
    SAW_DOWN,
    TRIANGLE,
    SQUARE,
    SIN_WAVE,
  };

private:
  PhaseGenerator _phaseGenerator;
  LfoFunction _lfoFunction;
  uint8_t _initialPhase;
  uint16_t _frequency;
  Signal _outputSig;
  
public:
  Lfo(): _phaseGenerator(9) { setLfoFunction(SAW_UP); setFrequency(1); setInitialPhase(0); }
  
  void setLfoFunction(LfoFunction lfoFunction) { _lfoFunction = lfoFunction; }
  LfoFunction getLfoFunction() const { return _lfoFunction; }
  
  uint16_t getFrequency() const { return _phaseGenerator.getFrequency(); }
  void setFrequency(uint16_t frequency) { _phaseGenerator.setFrequency(frequency); }
  
  uint8_t getInitialPhase() const { return _initialPhase; }
  void setInitialPhase(uint8_t initialPhase) { _initialPhase = initialPhase; }
  
  void reset() { _phaseGenerator.setPhase(_initialPhase * 2); }
  
  Signal* getOutputSig() { return &_outputSig; }
  
  uint16_t getOutput() const { return _outputSig.getValue(); }
  
  void update(uint16_t deltaMillis);
};

class HsiToRgb {
private:
  Signal* _pHueInputSig;
  Signal* _pSaturationInputSig;
  Signal* _pIntensityInputSig;
  
  Signal _redOutputSig;
  Signal _greenOutputSig;
  Signal _blueOutputSig;

public:
  HsiToRgb(): _pHueInputSig(0), _pSaturationInputSig(0), _pIntensityInputSig(0) { }
  
  Signal* getHueInputSig() const { return _pHueInputSig; }
  Signal* getSaturationInputSig() const { return _pSaturationInputSig; }
  Signal* getIntensityInputSig() const { return _pIntensityInputSig; }
  
  void setHueInputSig(Signal* pSig) { _pHueInputSig = pSig; }
  void setSaturationInputSig(Signal* pSig) { _pSaturationInputSig = pSig; }
  void setIntensityInputSig(Signal* pSig) { _pIntensityInputSig = pSig; }
  
  Signal* getRedOutputSig() { return &_redOutputSig; }
  Signal* getGreenOutputSig() { return &_greenOutputSig; }
  Signal* getBlueOutputSig() { return &_blueOutputSig; }
  
  uint16_t getRedOutput() const { return _redOutputSig.getValue(); }
  uint16_t getGreenOutput() const { return _greenOutputSig.getValue(); }
  uint16_t getBlueOutput() const { return _blueOutputSig.getValue(); }
  
  void update(uint16_t deltaMillis);
  
private:
  static void hsiToRgb(uint16_t hue, uint16_t saturation, uint16_t intensity, uint16_t& redOut, uint16_t& greenOut, uint16_t& blueOut);
};

