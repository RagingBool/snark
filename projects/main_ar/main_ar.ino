#include "LedChannels.h"
#include "SnarkLeds.h"

int numPwmChannels = 6;
int pwmChannels[] = {3, 5, 6, 9, 10, 11};
int numDigitalChannels = 6;
int digitalChannels[] = {2, 4, 7, 8, 12, 13};
LedChannels ledChannels(numPwmChannels, pwmChannels, numDigitalChannels, digitalChannels);

SnarkLeds leds(ledChannels, 2, 6);

void setup() {
  ledChannels.init();
}

int f1 = 0;
int f2 = 10;
int f3 = 20;
int f4 = 30;

void loop() {
  leds.setRgbColor(0, func(f1), func(f2), func(f3));
  leds.setRgbColor(1, func(f2), func(f3), func(f4));
  
  leds.setMonoColor(0, func(f1));
  leds.setMonoColor(1, func(f2));
  leds.setMonoColor(2, func(f3));
  leds.setMonoColor(3, func(f4));
  leds.setMonoColor(4, func(f3));
  leds.setMonoColor(5, func(f2));
  
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
