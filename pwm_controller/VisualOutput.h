#ifndef VISUALOUTPUT_H
#define VISUALOUTPUT_H

#include "ControllerState.h"

class VisualOutput {
    
  public:
  
  VisualOutput(int pinGreen, int pinRed);
  void update(ControllerState state);
  
  private:
  
  int pinGreen;
  int pinRed;
};

#endif
