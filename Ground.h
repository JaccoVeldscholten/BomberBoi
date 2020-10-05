#ifndef _GROUNDH_
#define _GROUNDH_
#pragma once
#include "GameObject.h"

// Grond klasse, grond heeft geen echt doel behalve een vakje tekenen
class Ground : public GameObject
{
public:
	Ground();
	void Draw(Adafruit_ILI9341 &tft, uint8_t locationX, uint8_t locationY);
};
#endif