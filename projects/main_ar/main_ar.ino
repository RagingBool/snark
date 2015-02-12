#include "LedChannels.h"
#include "SnarkLeds.h"

int numPwmChannels = 6;
int pwmChannels[] = {3, 5, 6, 9, 10, 11};
LedChannels ledChannels(numPwmChannels, pwmChannels);

SnarkLeds leds(ledChannels, 1, 3);

void setup() {
  ledChannels.init();
}

int f1 = 0;
int f2 = 0;
int f3 = 0;

void loop() {
  leds.setMonoColor(0, func(f1));
  leds.setMonoColor(1, func(f2));
  leds.setMonoColor(2, func(f3));
  leds.setRgbColor(0, func(f1), func(f2), func(f3));
  
  f1 = (f1 + 1) % 512;
  f2 = (f2 + 3) % 512;
  f3 = (f3 + 5) % 512;

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
