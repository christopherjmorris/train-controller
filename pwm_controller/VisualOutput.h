#ifndef VISUALOUTPUT_H
#define VISUALOUTPUT_H

class VisualOutput {
    
  public:
  
  VisualOutput(int pinGreen, int pinRed);
  void update(unsigned char currentSpeed);
  
  private:
  
  int pinGreen;
  int pinRed;
};

#endif
