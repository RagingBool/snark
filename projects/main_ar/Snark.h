#pragma once

#include "Outputs.h"
#include "LedManager.h"

class Snark {
private:
  static int NUM_PWM_CHANNELS;
  static int PWM_CHANNELS[];
  static int NUM_DIGITAL_CHANNELS;
  static int DIGITAL_CHANNELS[];

  Outputs* _pOutputs;
  LedManager* _pLedManager;
  int _f1;
  int _f2;
  int _f3;
  int _f4;
  
public:
  Snark();
  
  void init();
  
  void loop();
  
private:
  int func(int x);
};
