#ifndef CONTROLLERSTATE_H
#define CONTROLLERSTATE_H

struct ControllerState {
  int direction;
  unsigned char speed;
};

const int DIRECTION_STOPPED = 0;
const int DIRECTION_A = 1;
const int DIRECTION_B = -1;
#endif
