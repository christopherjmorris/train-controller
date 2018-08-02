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

    // Max speed value is 32:
    
    unsigned char speedHigher = (speed & 0b00111100) >> 2; // bits 3,4,5 in range 0-7. Include bit 6 to account for top speed of 32
    unsigned char speedLower = (speed & 0b00000011) << 6; // bits 1&2 in range 0-255
    
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
      int rgb [3] = {};
      IntensityToRgb(index, intensities[index], rgb);
      strip.setPixelColor(pixelIndex, rgb[0], rgb[1], rgb[2], 0);
    }
    
    strip.show();
  }

  void IntensityToRgb(int index, unsigned char intensity, int rgb[]) {
    rgb[0] = (3 < index) ? intensity >> 2 : 0;
    rgb[1] = (index < 6) ? intensity >> 2 : 0;
    rgb[2] = 0;
  }
  
  
  Adafruit_NeoPixel strip;
};

#endif
