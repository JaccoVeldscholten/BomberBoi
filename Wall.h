#ifndef _WALLH_
#define _WALLH_
#pragma once
#include "GameObject.h"
#define color_wall_shadow 0x4208

class Wall : public GameObject
{
public:
	Wall();
	void Draw(Adafruit_ILI9341 &tft, uint8_t locationX, uint8_t locationY);
};

#endif
