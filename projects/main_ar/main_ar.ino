#include "OutputManager.h"
#include "LedManager.h"

int numPwmChannels = 6;
int pwmChannels[] = {3, 5, 6, 9, 10, 11};
int numDigitalChannels = 6;
int digitalChannels[] = {2, 4, 7, 8, 12, 13};
OutputManager outputManager(numPwmChannels, pwmChannels, numDigitalChannels, digitalChannels);

LedManager leds(outputManager);

void setup() {
  outputManager.init();
}

int f1 = 0;
int f2 = 10;
int f3 = 20;
int f4 = 30;

void loop() {
  leds.setValue(0, func(f1));
  leds.setValue(1, func(f2));
  leds.setValue(2, func(f3));
  leds.setValue(3, func(f2));
  leds.setValue(4, func(f3));
  leds.setValue(5, func(f4));
  
  leds.setValue(6, func(f1));
  leds.setValue(7, func(f2));
  leds.setValue(8, func(f3));
  leds.setValue(9, func(f4));
  leds.setValue(10, func(f3));
  leds.setValue(11, func(f2));
  
  f1 = (f1 + 1) % 512;
  f2 = (f2 + 3) % 512;
  f3 = (f3 + 5) % 512;
  f4 = (f4 + 7) % 512;
  
  delay(10);
}

int func(int x)
{
  if(x < 256)
  {
    return x;
  }
  else
  {
    return 511 - x;
  }
}
