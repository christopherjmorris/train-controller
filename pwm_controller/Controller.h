#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "ControllerState.h"

const unsigned char MAX_SPEED_SETTING = 32;

const int STATE_STOPPED = 0;
const int STATE_DRIVING_A = 1;
const int STATE_DRIVING_B = 2;

class Controller {
  
  public:

  ControllerState update (unsigned char lefts, unsigned char rights, bool button_pressed) {
    
    switch (controlState) {
      case STATE_STOPPED:
        updateStateStopped(lefts, rights, button_pressed);
        break;
      case STATE_DRIVING_A:
        updateStateDrivingDirectionA(lefts, rights, button_pressed);
        break;
      case STATE_DRIVING_B:
        updateStateDrivingDirectionB(lefts, rights, button_pressed);
        break;
    }
    
    return getState();
  }

  private:

  void updateStateStopped (unsigned char lefts, unsigned char rights, bool button_pressed);
  void updateStateDrivingDirectionA (unsigned char lefts, unsigned char rights, bool button_pressed);
  void updateStateDrivingDirectionB (unsigned char lefts, unsigned char rights, bool button_pressed);

  ControllerState getState();
  
  int controlState;
  int currentSpeed = 0;
};

#endif
