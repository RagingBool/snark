#pragma once

#include "LedManager.h"
#include "signal.h"

class AutoMode {
  class AutoLed;
  
private:
  LedManager& _ledManager;
  
  int _maxAutoLeds;
  int _numAutoLeds;
  AutoMode::AutoLed** _pAutoLeds;
  
  unsigned long _lastUpdateTime;

public:
  AutoMode(LedManager& ledManager);
  
  ~AutoMode();
  
  void update();

protected:
  void addAutoLed(AutoLed* pAutoLed);
  
private:
  void setupModes();
  
private:
  class AutoLed {
  private:
    LedManager& _ledManager;
    int _updateThresholdMillis;
    int _timeSinceUpdate;
      
  public:
    AutoLed(LedManager& ledManager):
      _ledManager(ledManager),
      _updateThresholdMillis(1),
      _timeSinceUpdate(0) { }

    virtual ~AutoLed() { }
    
    void update(int dt);
      
  protected:
    LedManager& getLedManager() { return _ledManager; }
    
    int getupdateThresholdMillis() const { return _updateThresholdMillis; }
    
    void setUpdateThresholdMillis(int updateThresholdMillis) { _updateThresholdMillis = updateThresholdMillis; }
    
    virtual void updateInner(int dt) = 0;
  };
  
  class AutoMonoLed: public AutoLed {
  private:
    int _ledId;
    
  public:
    AutoMonoLed(LedManager& ledManager, int ledId):
      AutoLed(ledManager),
      _ledId(ledId) { }
    
  protected:
    void setValue(int value) { getLedManager().setValue(_ledId, value); }
  };
  
  class AutoRgbLed: public AutoLed {
  private:
    int _ledId;
    
  public:
    AutoRgbLed(LedManager& ledManager, int ledId):
      AutoLed(ledManager),
      _ledId(ledId) { }
    
  protected:
    void setValue(int r, int g, int b) {
      getLedManager().setValue(_ledId + 0, r);
      getLedManager().setValue(_ledId + 1, g);
      getLedManager().setValue(_ledId + 2, b);
    }
  };
  
  class FadingLed: public AutoMonoLed {
  private:
    Lfo _lfo;
    
  public:
    FadingLed(LedManager& ledManager, int ledId, Lfo::LfoFunction lfoFunction, int period, int initialPhase = 0);
    
    virtual void updateInner(int dt);
  };
  
  class CyclingLed: public AutoRgbLed {
  private:
    Lfo _hueLfo;
    Lfo _saturationLfo;
    HsiToRgb _hsiToRgb;
    
    Signal _saturationSig;
    Signal _intensitySig;
    
  public:
    CyclingLed(LedManager& ledManager, int ledId, int huePeriod, int initialHue = 0);
    
    virtual void updateInner(int dt);
  };
};
