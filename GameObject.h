#ifndef _GAMEOBJECTH_
#define _GAMEOBJECTH_
#pragma once
#include "DrawInterface.h"
#define blockSize 20
// Check klassendiagram om verband te zien
class GameObject : public DrawInterface
{
public:
	virtual void Draw(Adafruit_ILI9341 &tft, uint8_t locationX, uint8_t locationY){

	};

	volatile uint8_t collision = 0; // Wat voor type object
};
#endif
