#include <math.h>
#include "MTM_NeoPixel.h"


MTM_NeoPixel::MTM_NeoPixel(Adafruit_NeoPixel* pixelObj, int pixelStart, int pixelEnd)
{
	_pixelObj = pixelObj;
	_pixelStart = pixelStart;
	_pixelEnd = pixelEnd;
	_stepCount = 10;
	_curStep = 0;
	_lastTimeMillis = 0;
	_curColor = MTM_RGB();
	_targetColor = MTM_RGB();
	_redMin = 0;
	_redMax = 255;
	_greenMin = 0;
	_greenMax = 255;
	_blueMin = 0;
	_blueMax = 255;
}

void
MTM_NeoPixel::setRedBounds(uint8_t min, uint8_t max)
{
	_redMin = min;
	_redMax = max;
}

void
MTM_NeoPixel::setGreenBounds(uint8_t min, uint8_t max)
{
	_greenMin = min;
	_greenMax = max;
}

void
MTM_NeoPixel::setBlueBounds(uint8_t min, uint8_t max)
{
	_blueMin = min;
	_blueMax = max;
}

void
MTM_NeoPixel::setColor(MTM_RGB color)
{
	_targetColor = color;
	_lastTimeMillis = millis();
	if (_targetColor == _curColor) {
		_curStep = _stepCount;
	} else {
		_curStep = 0;
	}
}

void
MTM_NeoPixel::setTransitionDelays(long stepDelay, long pauseDelay)
{
	_stepDelay = stepDelay;
	_pauseDelay = pauseDelay;
}

void
MTM_NeoPixel::setTransitionGranularity(int stepCount)
{
	_stepCount = stepCount;
}

void
MTM_NeoPixel::update()
{
	unsigned long elapsed = millis() - _lastTimeMillis;

	if (_curStep < _stepCount) {
		if (elapsed >= _stepDelay) {
			if (_curStep == (_stepCount - 1)) {
				_curColor = _targetColor;
			} else {
				_curColor.setRed(lround(_curColor.getRed() + _redStep));
				_curColor.setGreen(lround(_curColor.getGreen() + _greenStep));
				_curColor.setBlue(lround(_curColor.getBlue() + _blueStep));
			}

			showPixels();

			_curStep++;
			_lastTimeMillis = millis();
		}
	} else {
		if (elapsed >= _pauseDelay) {
			chooseNewColor();
		}
	}
}

void
MTM_NeoPixel::chooseNewColor()
{
	uint8_t r = pickSingleColorAdjusted(_redMin, _redMax);
	uint8_t g = pickSingleColorAdjusted(_greenMin, _greenMax);
	uint8_t b = pickSingleColorAdjusted(_blueMin, _blueMax);

	_targetColor = MTM_RGB(r, g, b);

	if (_targetColor == _curColor || (
			_targetColor.getRed() == _targetColor.getGreen() &&
			_targetColor.getRed() == _targetColor.getBlue()
		)) {
		chooseNewColor();
		return;
	}

	_redStep = (r - _curColor.getRed()) / _stepCount;
	_greenStep = (g - _curColor.getGreen()) / _stepCount;
	_blueStep = (b - _curColor.getBlue()) / _stepCount;

	_curStep = 0;
	_lastTimeMillis = millis();
}

uint8_t
MTM_NeoPixel::pickSingleColorAdjusted(uint8_t min, uint8_t max)
{
	static uint8_t edges[5] = { 0, 63, 127, 191, 255 };
	uint8_t closestDistance = 255;
	uint8_t closestValue = 0;
	uint8_t testDistance = 0;
	uint8_t randomColorSelection = random(min, max);

	closestDistance = abs(randomColorSelection - min);
	closestValue = min;

	if (closestDistance > 0) {
		testDistance = abs(randomColorSelection - max);
		if (testDistance < closestDistance) {
			closestDistance = testDistance;
			closestValue = max;
		}

		for (int i = 0; i < 5; i++) {
			if (closestDistance == 0) {
				break;
			}

			testDistance = abs(randomColorSelection - edges[i]);
			if (testDistance < closestDistance) {
				closestDistance = testDistance;
				closestValue = edges[i];
			}
		}
	}

	return closestValue;
}

void
MTM_NeoPixel::showPixels()
{
	uint32_t curColor = _curColor.getColor();

	for (int i = _pixelStart; i < _pixelEnd; i++) {
		_pixelObj->setPixelColor(i, curColor);
	}
	_pixelObj->show();
}
