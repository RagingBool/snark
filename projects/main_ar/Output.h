#pragma once

class Output {
private:
  int _output;
  bool _isPwm;
  
public:
  Output(int output, bool isPwm);
  
  void init();
  
  void setIntencity(int intencity);
};
