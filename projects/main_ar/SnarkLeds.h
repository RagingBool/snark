#pragma once

#include "LedChannels.h"

class SnarkLeds {
private:
  LedChannels& _channels;

public:
  SnarkLeds(LedChannels& channels);
  
  void setValue(int id, int value);
};
