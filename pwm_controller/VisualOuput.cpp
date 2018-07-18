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

void VisualOutput::update(unsigned char currentSpeed) {
  if (currentSpeed == 0) {
    digitalWrite(pinGreen, HIGH);
    digitalWrite(pinRed, LOW);
  } else {
    digitalWrite(pinGreen, LOW);
    digitalWrite(pinRed, HIGH);
  }
}

