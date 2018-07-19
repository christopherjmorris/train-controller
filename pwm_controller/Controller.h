#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "ControllerState.h"

class Controller {
  
  public:

  ControllerState update (unsigned char lefts, unsigned char rights, bool button_pressed);

  private:

  int controlState;
  unsigned char currentSpeed;
};

#endif
