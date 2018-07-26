#ifndef SPEEDVISUALISER_H
#define SPEEDVISUALISER_H

#include "ControllerState.h"
#include <Adafruit_NeoPixel.h>

class SpeedVisualiser {
    
  public:
  
  SpeedVisualiser(int pinNeopixel) {
    strip = Adafruit_NeoPixel(12, pinNeopixel, NEO_GRB + NEO_KHZ800);

    strip.begin();
  }
  void update(ControllerState state) {

    if (state.direction == DIRECTION_STOPPED) {
      ShowRedRing();
      return;
    }
    
    ShowPartialGreen(state.speed);
  }
  
  private:

  void ShowNothing() {
    for (int index = 0; index < strip.numPixels(); index++) {
      strip.setPixelColor(index, 0, 0, 0, 0);
    }
    strip.show();
  }
  
  void ShowRedRing() {
    for (int index = 0; index < strip.numPixels(); index++) {
      strip.setPixelColor(index, 64, 0, 0, 0);
    }
    strip.show();
  }

  void ShowPartialGreen(unsigned char speed) {
    unsigned char speedMsb = speed >> 5;
    unsigned char speedLower = (speed & 0b00011111) << 1;
    int index;
    for (index = 0; index < 8; index++) {
      if (index < speedMsb) {
        strip.setPixelColor(index, 0, 64, 0, 0);
      } else if (index == speedMsb) {
        strip.setPixelColor(index, 0, speedLower, 0, 0);
      }
      else {
        strip.setPixelColor(index, 0, 0, 0, 0);
      }
    }
    for (; index < strip.numPixels(); index++) {
      strip.setPixelColor(index, 0, 0, 0, 0);
    }
    
    strip.show();
  }
  
  Adafruit_NeoPixel strip;
};

#endif
