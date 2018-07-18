#ifndef MOTOROUTPUT_H
#define MOTOROUTPUT_H

class MotorOutput {
    
  public:
  
  MotorOutput(int pinOut);
  void update(unsigned char currentSpeed);
  
  private:
  
  int pinOutput;
};

#endif
