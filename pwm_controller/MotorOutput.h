#ifndef MOTOROUTPUT_H
#define MOTOROUTPUT_H

#include "ControllerState.h"
class MotorOutput {
    
  public:
  
  MotorOutput(int pinPwm, int pinDirectionA, int pinDirectionB);
  void update(ControllerState state);
  
  private:
  
  int pinPwm;
  int pinDirectionA;
  int pinDirectionB;
};

#endif
