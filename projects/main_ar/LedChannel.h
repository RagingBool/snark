#pragma once

class LedChannel {
private:
  int _output;
  bool _isPwm;
  
public:
  LedChannel(int output, bool isPwm);
  
  void init();
  
  void setIntencity(int intencity);
};
