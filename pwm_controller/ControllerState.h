#ifndef CONTROLLERSTATE_H
#define CONTROLLERSTATE_H

struct ControllerState {
  int direction;
  unsigned char speed;
};

const int DIRECTION_STOPPED = 0;
const int DIRECTION_LEFT = 1; // Direction the control knob has been turned
const int DIRECTION_RIGHT = -1;
#endif
