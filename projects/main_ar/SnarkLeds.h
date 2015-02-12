#pragma once

#include "LedChannels.h"
#include "MonoLed.h"
#include "RgbLed.h"

class SnarkLeds {
private:
  int _numRgbLeds;
  RgbLed** _rgbLeds;
  int _numMonoLeds;
  MonoLed** _monoLeds;

public:
  SnarkLeds(LedChannels& channels, int numRgb, int numMono);
  
  void setRgbColor(int id, int r, int g, int b);

  void setMonoColor(int id, int color);
};
