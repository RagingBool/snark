#include "AutoMode.h"

AutoMode::AutoMode(LedManager& ledManager):
  _ledManager(ledManager) {
  _f1 = 0;
  _f2 = 10;
  _f3 = 20;
  _f4 = 30;
}
  
void AutoMode::update() {
  _ledManager.setValue(0, func(_f1));
  _ledManager.setValue(1, func(_f2));
  _ledManager.setValue(2, func(_f3));
  _ledManager.setValue(3, func(_f2));
  _ledManager.setValue(4, func(_f3));
  _ledManager.setValue(5, func(_f4));
  
  _ledManager.setValue(6, func(_f1));
  _ledManager.setValue(7, func(_f2));
  _ledManager.setValue(8, func(_f3));
  _ledManager.setValue(9, func(_f4));
  _ledManager.setValue(10, func(_f3));
  _ledManager.setValue(11, func(_f2));
  
  _f1 = (_f1 + 1) % 512;
  _f2 = (_f2 + 3) % 512;
  _f3 = (_f3 + 5) % 512;
  _f4 = (_f4 + 7) % 512;
}

int AutoMode::func(int x) {
  if(x < 256) {
    return x;
  }
  else {
    return 511 - x;
  }
}
