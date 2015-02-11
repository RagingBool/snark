#pragma once

class LedChannel {
private:
  int _output;
  
public:
  LedChannel(int output);
  
  void init();
  
  void setIntencity(int intencity);
};
