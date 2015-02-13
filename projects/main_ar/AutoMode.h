#pragma once

#include "LedManager.h"

class AutoMode {
  class AutoLed;
  
private:
  LedManager& _ledManager;
  
  int _numAutoLeds;
  AutoMode::AutoLed** _pAutoLeds;

public:
  AutoMode(LedManager& ledManager);
  
  ~AutoMode();
  
  void update();
  
private:
  class AutoLed {
  private:
    LedManager& _ledManager;
      
  public:
    AutoLed(LedManager& ledManager): _ledManager(ledManager) { }
    
    virtual ~AutoLed() { }
    
    virtual void update() = 0;
      
  protected:
    LedManager& getLedManager() { return _ledManager; }
  };
  
  class AutoMonoLed: public AutoLed {
  private:
    int _ledId;
    
  public:
    AutoMonoLed(LedManager& ledManager, int ledId): AutoLed(ledManager), _ledId(ledId) { }
    
  protected:
    void setValue(int value) { getLedManager().setValue(_ledId, value); }
  };
  
  class FadingLed: public AutoMonoLed {
  private:
    int _step;
    int _phase;
    
  public:
    FadingLed(LedManager& ledManager, int ledId, int step, int startingPhase = 0):
      AutoMonoLed(ledManager, ledId), _step(step), _phase(startingPhase) { }
    
    virtual void update();
  };
};
