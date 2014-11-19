#ifndef MTM_NEOPIXEL_H
#define MTM_NEOPIXEL_H

#include <Adafruit_NeoPixel.h>
#include "Arduino.h"
#include "MTM_RGB.h"


class MTM_NeoPixel {
  public:
    MTM_NeoPixel(Adafruit_NeoPixel* pixelObj, int pixelStart, int pixelEnd);
	void setRedBounds(uint8_t min, uint8_t max);
	void setGreenBounds(uint8_t min, uint8_t max);
	void setBlueBounds(uint8_t min, uint8_t max);
	void setColor(MTM_RGB color);
	void setTransitionDelays(long stepDelay, long pauseDelay);
	void setTransitionGranularity(int stepCount);
	void update();

  private:
    uint8_t _redMin;
    uint8_t _redMax;
    uint8_t _greenMin;
    uint8_t _greenMax;
    uint8_t _blueMin;
    uint8_t _blueMax;
    float _redStep;
    float _greenStep;
    float _blueStep;
    int _curStep;
    int _stepCount;
    long _stepDelay;
    long _pauseDelay;
    MTM_RGB _curColor;
    MTM_RGB _targetColor;
    Adafruit_NeoPixel* _pixelObj;
    int _pixelStart;
    int _pixelEnd;
    unsigned long _lastTimeMillis;

	void chooseNewColor();
	void showPixels();
	static uint8_t pickSingleColorAdjusted(uint8_t min, uint8_t max);
};


#endif // MTM_NEOPIXEL_H
