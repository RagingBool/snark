#pragma once

#include "LedManager.h"

class AutoMode {
private:
  LedManager& _ledManager;

  int _f1;
  int _f2;
  int _f3;
  int _f4;

public:
  AutoMode(LedManager& ledManager);
  
  void update();

private:
  int func(int x);
};
