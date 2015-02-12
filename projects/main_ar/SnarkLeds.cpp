#include "SnarkLeds.h"
  
SnarkLeds::SnarkLeds(LedChannels& channels, int numRgbLeds, int numMonoLeds):
  _numRgbLeds(numRgbLeds),
  _numMonoLeds(numMonoLeds) {

  _rgbLeds = new RgbLed*[_numRgbLeds];
  _monoLeds = new MonoLed*[_numMonoLeds];
  
  int curChannelId = 0;
  
  for(int i = 0; i < _numRgbLeds; i++) {
    _rgbLeds[i] = new RgbLed(channels[curChannelId], channels[curChannelId + 1], channels[curChannelId + 2]);
    curChannelId += 3;
  }
    
  for(int i = 0; i < _numMonoLeds; i++) {
    _monoLeds[i] = new MonoLed(channels[curChannelId]);
    curChannelId++;
  }
}
  
void SnarkLeds::setRgbColor(int id, int r, int g, int b) {
  _rgbLeds[id] -> setColor(r, g, b);
}

void SnarkLeds::setMonoColor(int id, int color) {
  _monoLeds[id] -> setColor(color);
}
