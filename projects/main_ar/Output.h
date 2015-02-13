#pragma once

class Output {
private:
  int _pinNumber;
  bool _isPwm;
  
public:
  Output(int pinNumber, bool isPwm);
  
  int getPinNumber() const { return _pinNumber; }
  
  bool isPwm() const { return _isPwm; }
  
  void init();
  
  void setValue(int intencity);
};
