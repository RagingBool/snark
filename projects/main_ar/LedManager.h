#pragma once

#include "Outputs.h"

class LedManager {
private:
  Outputs& _outputs;

public:
  LedManager(Outputs& outputs);
  
  void setValue(int id, int value);
};
