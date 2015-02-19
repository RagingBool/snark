#pragma once

#include "Outputs.h"

class LedManager {
private:
  Outputs& _outputs;

public:
  LedManager(Outputs& outputs);
  
  int getNumChannels() const { return _outputs.getNumOutputs(); } 
  
  void setValue(int id, int value);
};
