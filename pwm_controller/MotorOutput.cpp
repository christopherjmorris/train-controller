#include "MotorOutput.h"
#include "Controller.h"

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#include "pins_arduino.h"
#endif

const int MIN_DUTY_CYCLE = 90;
const int MAX_DUTY_CYCLE = 255;

int dutyCycleFromSpeedSetting(unsigned char speed) {
  if (speed == 0) {
    return 0;
  }

  return MIN_DUTY_CYCLE + ((speed * (MAX_DUTY_CYCLE - MIN_DUTY_CYCLE)) / MAX_SPEED_SETTING);
}

MotorOutput::MotorOutput(int pinPwm, int pinDirectionA, int pinDirectionB) {
  this->pinPwm = pinPwm;
  this->pinDirectionA = pinDirectionA;
  this->pinDirectionB = pinDirectionB;

  pinMode(pinPwm, OUTPUT);
  pinMode(pinDirectionA, OUTPUT);
  pinMode(pinDirectionB, OUTPUT);

  analogWrite(pinPwm, 0);
  digitalWrite(pinDirectionA, LOW);
  digitalWrite(pinDirectionB, LOW);
}

void MotorOutput::update(ControllerState state) {
  switch (state.direction) {
    case DIRECTION_STOPPED:
      digitalWrite(pinDirectionA, LOW);
      digitalWrite(pinDirectionB, LOW);
      analogWrite(pinPwm, 0);
      break;
    case DIRECTION_LEFT:
      digitalWrite(pinDirectionB, LOW);
      digitalWrite(pinDirectionA, HIGH);
      analogWrite(pinPwm, dutyCycleFromSpeedSetting(state.speed));
      break;
     case DIRECTION_RIGHT:
      digitalWrite(pinDirectionA, LOW);
      digitalWrite(pinDirectionB, HIGH);
      analogWrite(pinPwm, dutyCycleFromSpeedSetting(state.speed));
      break;
  }
}


