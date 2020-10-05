/*
 * Klasse: Fire.cpp
 * Beschrijving: Tekenen van een fire en weergeven van het vuur
 * Ontwikkeld door: Richard Reijerse & Jacco Veldscholten & Briyan Kleijn
 * Aangepast  door: Briyan Kleijn
*/

#include "Fire.h"
Fire::Fire()
{
	type = 1;// Standaard type
}
// Deze wordt aangeroepn om direct de type in te stellen bij het aanmaken
Fire::Fire(uint8_t _type)
{
	collision = 3;
	type = _type;
}

// Zou in de toekomst gebruikt kunnen worden, staat al klaar
void Fire::Timer()
{
}

// Zou ook in de toekomst gebruikt kunnen worden, zou moeten linken aan de timer
void Fire::TurnOn(uint8_t _type, uint8_t x, uint8_t y)
{
	type = _type;
	posX = x;
	posY = y;
	isOn = true;
}

// Tekenfunctie
void Fire::Draw(Adafruit_ILI9341 &tft, uint8_t locationX, uint8_t locationY)
{
	switch (type)
	{
	// Horizontaal vuur
	case 0:
		draw_explosionHor(tft, locationX, locationY);
		break;

	// Center explosie
	case 1:
		draw_explosionCenter(tft, locationX, locationY);
		break;

	// Verticaal vuur
	case 2:
		draw_explosionVer(tft, locationX, locationY);
		break;
	}
}

void Fire::draw_explosionCenter(Adafruit_ILI9341 &tft, uint8_t x, uint8_t y)
{
	tft.fillRect(x + 3, y, 14, 20, color_player_darkBlue);
	tft.fillRect(x, y + 3, 20, 14, color_player_darkBlue);
	tft.fillRect(x + 4, y, 12, 20, color_player_lightBlue);
	tft.fillRect(x, y + 4, 20, 12, color_player_lightBlue);
	tft.fillRect(x + 6, y, 8, 20, color_player_highlightBlue);
	tft.fillRect(x, y + 6, 20, 8, color_player_highlightBlue);
}

void Fire::draw_explosionHor(Adafruit_ILI9341 &tft, uint8_t x, uint8_t y)
{
	tft.fillRect(x, y + 3, 20, 14, color_player_darkBlue);
	tft.fillRect(x, y + 4, 20, 12, color_player_lightBlue);
	tft.fillRect(x, y + 6, 20, 8, color_player_highlightBlue);
}

void Fire::draw_explosionVer(Adafruit_ILI9341 &tft, uint8_t x, uint8_t y)
{
	tft.fillRect(x + 3, y, 14, 20, color_player_darkBlue);
	tft.fillRect(x + 4, y, 12, 20, color_player_lightBlue);
	tft.fillRect(x + 6, y, 8, 20, color_player_highlightBlue);
}
