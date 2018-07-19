#include "MotorOutput.h"

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#include "pins_arduino.h"
#endif

MotorOutput::MotorOutput(int pinPwm, int pinDirectionA, int pinDirectionB) {
  this->pinPwm = pinPwm;
  this->pinDirectionA = pinDirectionA;
  this->pinDirectionB = pinDirectionB;

  pinMode(pinPwm, OUTPUT);
  pinMode(pinDirectionA, OUTPUT);
  pinMode(pinDirectionB, OUTPUT);

  analogWrite(pinPwm, 0);
  digitalWrite(pinDirectionA, HIGH);
  digitalWrite(pinDirectionB, LOW);
}

void MotorOutput::update(ControllerState state) {
  analogWrite(pinPwm, state.speed);
}

