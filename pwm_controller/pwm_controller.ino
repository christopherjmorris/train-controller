#include <util/atomic.h>
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

Controller controller;
MotorOutput motor_output (PIN_PWM_OUTPUT, PIN_DIRECTION_A, PIN_DIRECTION_B);
VisualOutput visual_output (5, 4);

void setup() {
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  
  // Enable internal pull-up resistors
  //digitalWrite(A0, HIGH);
  digitalWrite(A1, HIGH);
  digitalWrite(A2, HIGH);
  
  PCICR =  0b00000010; // 1. PCIE1: Pin Change Interrupt Enable 1
  PCMSK1 = 0b00000111; // Enable Pin Change Interrupt for A0, A1, A2
}

void loop() {
  
  byte lefts;
  byte rights;
  bool button_pressed;
  
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
  {
    lefts  = turnsLeft;
    rights = turnsRight;
    button_pressed = button;
    
    turnsLeft = 0;
    turnsRight = 0;
    button = false;
  }

  ControllerState state = controller.update(lefts, rights, button_pressed);
  motor_output.update(state);
  visual_output.update(state);
}

ISR (PCINT1_vect) {
  // button press pulls the input high
  if (digitalRead(A0)) {
    // If interrupt is triggered by the button
    button = true;
  } else {
    // Else if interrupt is triggered by encoder signals
    
    // Read A and B signals
    boolean A_val = digitalRead(A1);
    boolean B_val = digitalRead(A2);
    
    // Record the A and B signals in seperate sequences
    seqA <<= 1;
    seqA |= A_val;
    
    seqB <<= 1;
    seqB |= B_val;
    
    // Mask the MSB four bits
    seqA &= 0b00001111;
    seqB &= 0b00001111;
    
    // Compare the recorded sequence with the expected sequence
    if (seqA == 0b00001001 && seqB == 0b00000011) {
      turnsLeft++;
    }
    
    if (seqA == 0b00000011 && seqB == 0b00001001) {
      turnsRight++;
    }
  }
}
