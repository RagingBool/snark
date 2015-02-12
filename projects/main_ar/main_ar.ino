#include "LedChannel.h"
#include "LedChannels.h"
#include "MonoLed.h"
#include "RgbLed.h"

int pwmChannels[] = {3, 5, 6, 9, 10, 11};
int numPwmChannels = 6;

LedChannels ledChannels(pwmChannels, numPwmChannels);

RgbLed rgbLed1(ledChannels[0], ledChannels[1], ledChannels[2]);

MonoLed monoLed1(ledChannels[3]);
MonoLed monoLed2(ledChannels[4]);
MonoLed monoLed3(ledChannels[5]);

void setup() {
  ledChannels.init();
}

int f1 = 0;
int f2 = 0;
int f3 = 0;

void loop() {
  monoLed1.setColor(func(f1));
  monoLed2.setColor(func(f2));
  monoLed3.setColor(func(f3));
  rgbLed1.setColor(func(f1), func(f2), func(f3));
  
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
