#include "VisualOutput.h"

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#include "pins_arduino.h"
#endif

VisualOutput::VisualOutput(int pinGreen, int pinRed) {
  this->pinGreen = pinGreen;
  this->pinRed = pinRed;

  pinMode(pinGreen, OUTPUT);
  pinMode(pinRed, OUTPUT);
}

void VisualOutput::update(ControllerState state) {
  if (state.direction == DIRECTION_STOPPED) {
    digitalWrite(pinGreen, HIGH);
    digitalWrite(pinRed, LOW);
  } else {
    digitalWrite(pinGreen, LOW);
    digitalWrite(pinRed, HIGH);
  }
}

