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

    ShowPartialGreen(state.speed, state.direction == DIRECTION_LEFT);
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
      strip.setPixelColor(index, 32, 0, 0, 0);
    }
    strip.show();
  }

  void ShowPartialGreen(unsigned char speed, boolean isDirectionLeft) {

    // Convert speed to intensities
    unsigned char intensities [8] = {};
    
    unsigned char speedHigher = speed >> 5; // Top three bits in the range 0-7
    unsigned char speedLower = (speed & 0b00011111) << 3; // lower 5 bits in the range 0-255
    
    for (int index = 0; index < 8; index++) {
      if (index < speedHigher) {
        intensities[index] = 255;
      } else if (index == speedHigher) {
        intensities[index] = speedLower;
      } else {
        intensities[index] = 0;
      }
    }

    // Control NeoPixel
    strip.setPixelColor(0, 0, 0, 0, 0);
    strip.setPixelColor(1, 0, 0, 0, 0);
    strip.setPixelColor(10, 0, 0, 0, 0);
    strip.setPixelColor(11, 0, 0, 0, 0);
    
    for (int index = 0; index < 8; index++) {
      int pixelIndex = isDirectionLeft ? 9 - index : index + 2; // If direction == left, start from the right and go left-wards
      strip.setPixelColor(pixelIndex, 0, intensities[index] >> 2, 0, 0);
    }
    
    strip.show();
  }
  
  Adafruit_NeoPixel strip;
};

#endif
