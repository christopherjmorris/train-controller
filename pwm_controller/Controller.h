#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "ControllerState.h"

const unsigned char MIN_SPEED_SETTING = 90;
class Controller {
  
  public:

  ControllerState update (unsigned char lefts, unsigned char rights, bool button_pressed);

  private:

  int controlState;
  unsigned char currentSpeed = MIN_SPEED_SETTING;
};

#endif
