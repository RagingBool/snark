#pragma once

#include "OutputManager.h"

class SnarkLeds {
private:
  OutputManager& _outputManager;

public:
  SnarkLeds(OutputManager& outputManager);
  
  void setValue(int id, int value);
};
