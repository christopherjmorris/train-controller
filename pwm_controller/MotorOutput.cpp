#include "MotorOutput.h"

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#include "pins_arduino.h"
#endif

MotorOutput::MotorOutput(int pinOut) {
  pinOutput = pinOut;
}

void MotorOutput::update(unsigned char currentSpeed) {
  analogWrite(pinOutput, currentSpeed);
}

