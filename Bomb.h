#ifndef _BOMBH_
#define _BOMBH_
#pragma once
#define color_player_darkBlue 0x005F
#define color_player_lightBlue 0x03DF
#define color_player_darkFace1 0xE448
#define color_player_highlightBlue 0x7D9C
#define color_player_lightFace1 0xFD8C
#define color_player_darkShoe1 0x6180
#define color_player_lightShoe1 0x9326
#define color_player_darkHair1 0x6180
#define color_player_lightHair1 0x9326
#include "GameObject.h"

#define ExplosieTijd 500 // Tijd is in 0.01 variant, dus in dit geval 5 seconden
#define bombTimer 50	 // Tijd wanneer bom moet ontploffen (50 is 7 seconden)

class Bomb : public GameObject
{

public:
	Bomb();
	Bomb(uint8_t &, uint8_t _posX, uint8_t _posY);

	bool bomIsOn = false; // If the bom is running#include "Level.h"
	bool bomExplode = false;

	uint16_t startTeller = 0;

	void Timer();
	void Draw(Adafruit_ILI9341 &tft, uint8_t locationX, uint8_t locationY);
	void fraw(Adafruit_ILI9341 &tft, uint8_t locationX, uint8_t locationY);
	void start(uint8_t &, uint8_t _posX, uint8_t _posY);
	uint8_t posX, posY;

private:
	void Explosie();
};
#endif
