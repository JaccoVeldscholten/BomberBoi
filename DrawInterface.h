#ifndef _DRAWINTERFACEH_
#define _DRAWINTERFACEH_
#pragma once
#include "libraries/Adafruit_ILI9341/Adafruit_ILI9341.h"
#include <stdint.h>
class DrawInterface
{
public:
	virtual void Draw(Adafruit_ILI9341 &tft, uint8_t locationX, uint8_t locationY){};
};
#endif
