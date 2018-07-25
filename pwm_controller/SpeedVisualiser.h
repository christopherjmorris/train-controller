#ifndef SPEEDVISUALISER_H
#define SPEEDVISUALISER_H

#include "ControllerState.h"
#include <Adafruit_NeoPixel.h>

class SpeedVisualiser {
    
  public:
  
  SpeedVisualiser(int pinNeopixel) {
    this->pinNeopixel = pinNeopixel;
    strip = Adafruit_NeoPixel(12, pinNeopixel, NEO_GRB + NEO_KHZ400);

    strip.begin();
    strip.show();
    
  }
  void update(ControllerState state) {
    unsigned char speedMsb = state.speed >> 5;
    unsigned char speedLower = (state.speed & 0b00011111) << 2;
    for (int index = 0; index < 8; index++) {
      if (index < speedMsb) {
        strip.setPixelColor(index, 0, 128, 0, 0);
      } else if (index == speedMsb) {
        strip.setPixelColor(index, 0, speedLower, 0, 0);
      }
    }
    strip.show();
  }
  
  private:
  
  int pinNeopixel;
  Adafruit_NeoPixel strip;
};

#endif
