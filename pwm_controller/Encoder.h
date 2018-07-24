#ifndef ENCODER_H
#define ENCODER_H

#include <util/atomic.h>

struct EncoderDelta {
  byte turnsLeft;
  byte turnsRight;
};

class Encoder {
  public:
  Encoder(int pinA, int pinB) {
    this->pinA = pinA;
    this->pinB = pinB;
  }
  
  void ReadState() {
    
    // Read A and B signals
    boolean A_val = digitalRead(pinA);
    boolean B_val = digitalRead(pinB);

    if (A_val == lastStateA && B_val == lastStateB) {
      // No change since last read
      return;
    }
    
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

    lastStateA = A_val;
    lastStateB = B_val;
  }
  
  EncoderDelta GetTurns() {
    EncoderDelta delta;
    
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
      delta.turnsLeft  = turnsLeft;
      delta.turnsRight = turnsRight;
      
      turnsLeft = 0;
      turnsRight = 0;
    }

    return delta;
  }

  private:

  int pinA;
  int pinB;
  
  volatile boolean lastStateA;
  volatile boolean lastStateB;
  
  volatile byte seqA = 0;
  volatile byte seqB = 0;

  volatile byte turnsLeft = 0;
  volatile byte turnsRight = 0;
};

#endif
