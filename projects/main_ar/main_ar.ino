#include "LedChannel.h"
#include "MonoLed.h"
#include "RgbLed.h"

LedChannel ledChannelMono1(9);
LedChannel ledChannelMono2(10);
LedChannel ledChannelMono3(11);

LedChannel ledChannelRgb1R(3);
LedChannel ledChannelRgb1G(5);
LedChannel ledChannelRgb1B(6);

MonoLed monoLed1(ledChannelMono1);
MonoLed monoLed2(ledChannelMono2);
MonoLed monoLed3(ledChannelMono3);

RgbLed rgbLed1(ledChannelRgb1R, ledChannelRgb1G, ledChannelRgb1B);

void setup() {
  ledChannelMono1.init();
  ledChannelMono2.init();
  ledChannelMono3.init();
  ledChannelRgb1R.init();
  ledChannelRgb1G.init();
  ledChannelRgb1B.init();
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
