#include "LedChannel.h"

LedChannel ledChannelMono1(9);
LedChannel ledChannelMono2(10);
LedChannel ledChannelMono3(11);

LedChannel ledChannelRgb1R(3);
LedChannel ledChannelRgb1G(5);
LedChannel ledChannelRgb1B(6);

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
  ledChannelMono1.setIntencity(func(f1));
  ledChannelMono2.setIntencity(func(f2));
  ledChannelMono3.setIntencity(func(f3));
  ledChannelRgb1R.setIntencity(func(f1));
  ledChannelRgb1G.setIntencity(func(f2));
  ledChannelRgb1B.setIntencity(func(f3));
  
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
