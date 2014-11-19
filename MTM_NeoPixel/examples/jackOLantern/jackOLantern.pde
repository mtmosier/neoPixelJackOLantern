#include <Adafruit_NeoPixel.h>
#include <MTM_NeoPixel.h>
#include <MTM_RGB.h>


#define PIN                 9  // Data output pin on the arduino
#define PIXEL_COUNT        20  // Number of neo-pixels being controlled
#define EYES_START_PIXEL    0
#define EYES_END_PIXEL     10
#define MOUTH_START_PIXEL  10
#define MOUTH_END_PIXEL    20


Adafruit_NeoPixel pixels = Adafruit_NeoPixel(PIXEL_COUNT, PIN);
MTM_NeoPixel eyes = MTM_NeoPixel(&pixels, EYES_START_PIXEL, EYES_END_PIXEL);
MTM_NeoPixel mouth = MTM_NeoPixel(&pixels, MOUTH_START_PIXEL, MOUTH_END_PIXEL);


void setup() {
  randomSeed(analogRead(0));

  pixels.begin();
  pixels.setBrightness(250);

  eyes.setRedBounds(95, 255);  //  min, max  (0 to 255)
  eyes.setGreenBounds(0, 159);  //  min, max  (0 to 255)
  eyes.setBlueBounds(0, 159);  //  min, max  (0 to 255)
  eyes.setTransitionDelays(150, 2500);  //  milliseconds to pause between steps in changing from one color to another, milliseconds to pause on the color once reached
  eyes.setTransitionGranularity(30);  //  number of steps to take when moving from the current color to the new color

  mouth.setRedBounds(0, 255);  //  min, max  (0 to 255)
  mouth.setGreenBounds(0, 255);  //  min, max  (0 to 255)
  mouth.setBlueBounds(0, 255);  //  min, max  (0 to 255)
  mouth.setTransitionDelays(115, 4250);  //  milliseconds to pause between steps in changing from one color to another, milliseconds to pause on the color once reached
  mouth.setTransitionGranularity(50);  //  number of steps to take when moving from the current color to the new color
}

void loop() {
  eyes.update();
  mouth.update();
}