#include "Controller.h"
const int STOPPED = 0;
const int DRIVING = 1;

ControllerState Controller::update (unsigned char lefts, unsigned char rights, bool button_pressed) {

  // Take action if a new command received from the encoder
  if (button_pressed) {
    
    controlState = STOPPED;
    currentSpeed = MIN_SPEED_SETTING;
    
  } else {

    if (lefts > 0) {
      controlState = DRIVING;
      
      if (0 < currentSpeed) {
        currentSpeed--;
      }
    }
    
    if (rights > 0) {
      controlState = DRIVING;
      
      if (currentSpeed < 255) {
        currentSpeed++;
      }
    }
  }

  ControllerState state;
  if (controlState == STOPPED) {
    state.direction = 0;
    state.speed = 0;
  } else {
    state.direction = 1;
    state.speed = currentSpeed;
  }
  
  return state;
}
