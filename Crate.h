#ifndef _CRATEH_
#define _CRATEH_
#pragma once
#include "GameObject.h"
class Crate : public GameObject
{
public:
	Crate();
	void Draw(Adafruit_ILI9341 &tft, uint8_t locationX, uint8_t locationY);
};
#endif