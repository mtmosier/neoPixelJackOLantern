#ifndef MTM_RGB_H
#define MTM_RGB_H

#include "Arduino.h"


class MTM_RGB {
  public:
    MTM_RGB();
    MTM_RGB(uint8_t r, uint8_t g, uint8_t b);
    void setRed(uint8_t r);
    void setGreen(uint8_t g);
    void setBlue(uint8_t b);
    uint8_t getRed();
    uint8_t getGreen();
    uint8_t getBlue();
    uint32_t getColor();

	friend bool operator== (MTM_RGB &c1, MTM_RGB &c2);
	friend bool operator!= (MTM_RGB &c1, MTM_RGB &c2);
	void operator=(const MTM_RGB &D);

  private:
    uint8_t _r;
    uint8_t _g;
    uint8_t _b;
};


#endif // MTM_RGB_H
