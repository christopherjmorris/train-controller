#ifndef CONTROLLER_H
#define CONTROLLER_H

class Controller {
  
  public:

  void update (unsigned char lefts, unsigned char rights, bool button_pressed);
  unsigned char get_speed (void);

  private:

  unsigned char currentSpeed;
};

#endif
