#pragma once

#include "OutputManager.h"

class LedManager {
private:
  OutputManager& _outputManager;

public:
  LedManager(OutputManager& outputManager);
  
  void setValue(int id, int value);
};
