#include "Controller.h"

void Controller::updateStateStopped (unsigned char lefts, unsigned char rights, bool button_pressed) {
  if (0 < lefts) {
    currentSpeed = MIN_SPEED_SETTING;
    controlState = STATE_DRIVING_A;
  } else if  (0 < rights) {
    currentSpeed = MIN_SPEED_SETTING;
    controlState = STATE_DRIVING_B;
  }
}

void Controller::updateStateDrivingDirectionA (unsigned char lefts, unsigned char rights, bool button_pressed) {
  
  if (button_pressed) {
    controlState = STATE_STOPPED;
    return;
  }

  currentSpeed += lefts;
  currentSpeed -= rights;
  
  if (currentSpeed < MIN_SPEED_SETTING) {
    currentSpeed = MIN_SPEED_SETTING;
  }
  if (MAX_SPEED_SETTING < currentSpeed) {
    currentSpeed = MAX_SPEED_SETTING;
  }
}

void Controller::updateStateDrivingDirectionB (unsigned char lefts, unsigned char rights, bool button_pressed) {
  
  if (button_pressed) {
    controlState = STATE_STOPPED;
    return;
  }

  currentSpeed += rights;
  currentSpeed -= lefts;
  
  if (currentSpeed < MIN_SPEED_SETTING) {
    currentSpeed = MIN_SPEED_SETTING;
  }
  if (MAX_SPEED_SETTING < currentSpeed) {
    currentSpeed = MAX_SPEED_SETTING;
  }
}

ControllerState Controller::getState() {
  
  ControllerState state;
  
  if (controlState == STATE_DRIVING_A)  {
    state.direction = DIRECTION_LEFT;
    state.speed = currentSpeed;
  } else if (controlState == STATE_DRIVING_B) {
    state.direction = DIRECTION_RIGHT;
    state.speed = currentSpeed;
  } else {
    state.direction = DIRECTION_STOPPED;
    state.speed = 0;
  }
  
  return state;
}
