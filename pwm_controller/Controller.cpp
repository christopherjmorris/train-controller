#include "Controller.h"

void Controller::update (unsigned char lefts, unsigned char rights, bool button_pressed) {
  // Take action if a new command received from the encoder
  if (button_pressed) {
    currentSpeed = 0;
    return;
  }
  
  if (lefts > 0) {
    if (0 < currentSpeed) {
      currentSpeed--;
    }
  }
  
  if (rights > 0) {
    if (currentSpeed < 255) {
      currentSpeed++;
    }
  }
}

unsigned char Controller::get_speed (void) {
  return currentSpeed;
}
