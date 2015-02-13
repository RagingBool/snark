#pragma once

#include "Outputs.h"
#include "LedManager.h"
#include "AutoMode.h"

class Snark {
private:
  static int NUM_PWM_CHANNELS;
  static int PWM_CHANNELS[];
  static int NUM_DIGITAL_CHANNELS;
  static int DIGITAL_CHANNELS[];

  Outputs* _pOutputs;
  LedManager* _pLedManager;
  AutoMode* _pAutoMode; 
  
public:
  Snark();
  
  void init();
  
  void loop();
};
