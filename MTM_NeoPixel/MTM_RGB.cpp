#include "MTM_RGB.h"


MTM_RGB::MTM_RGB()
{
	setRed(0);
	setGreen(0);
	setBlue(0);
}

MTM_RGB::MTM_RGB(uint8_t r, uint8_t g, uint8_t b)
{
	setRed(r);
	setGreen(g);
	setBlue(b);
}

void
MTM_RGB::setRed(uint8_t r)
{
	_r = r;
}

void
MTM_RGB::setGreen(uint8_t g)
{
	_g = g;
}

void
MTM_RGB::setBlue(uint8_t b)
{
	_b = b;
}

uint8_t
MTM_RGB::getRed()
{
	return _r;
}

uint8_t
MTM_RGB::getGreen()
{
	return _g;
}

uint8_t
MTM_RGB::getBlue()
{
	return _b;
}

uint32_t
MTM_RGB::getColor()
{
	uint32_t c;
	c = _r;
	c <<= 8;
	c |= _g;
	c <<= 8;
	c |= _b;
	return c;
}

bool
operator== (MTM_RGB &c1, MTM_RGB &c2)
{
    return (c1._r == c2._r && c1._g == c2._g && c1._b == c2._b);
}

bool
operator!= (MTM_RGB &c1, MTM_RGB &c2)
{
    return !(c1 == c2);
}

void
MTM_RGB::operator= (const MTM_RGB &co)
{
	_r = co._r;
	_g = co._g;
	_b = co._b;
}
