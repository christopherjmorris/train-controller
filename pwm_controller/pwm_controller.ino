#include "Encoder.h"
#include "Controller.h"
#include "MotorOutput.h"
#include "VisualOutput.h"

volatile byte seqA = 0;
volatile byte seqB = 0;

volatile byte turnsLeft = 0;
volatile byte turnsRight = 0;

volatile boolean button = false;

const int PIN_PWM_OUTPUT = 6;
const int PIN_DIRECTION_A = 12;
const int PIN_DIRECTION_B = 11;

Encoder encoder(A1, A2);
Controller controller;
MotorOutput motor_output (PIN_PWM_OUTPUT, PIN_DIRECTION_A, PIN_DIRECTION_B);
VisualOutput visual_output (5, 4);

void setup() {
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  
  // Enable internal pull-up resistors
  digitalWrite(A1, HIGH);
  digitalWrite(A2, HIGH);
  
  PCICR =  0b00000010; // 1. PCIE1: Pin Change Interrupt Enable 1
  PCMSK1 = 0b00000110; // Enable Pin Change Interrupt for A1, A2
}

void loop() {

  bool button_pressed = digitalRead(A0);
  EncoderDelta delta = encoder.GetTurns();

  ControllerState state = controller.update(delta.turnsLeft, delta.turnsRight, button_pressed);
  
  motor_output.update(state);
  visual_output.update(state);
}

ISR (PCINT1_vect) {
  encoder.ReadState();
}
