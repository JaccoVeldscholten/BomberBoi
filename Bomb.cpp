/*
 * Klasse: Bomb.cpp
 * Beschrijving: Tekenen van een bom en timen van ontploffen
 * Ontwikkeld door: Richard Reijerse  & Jacco Veldscholten
 * Aangepast  door: Briyan Kleijn
*/

#include "Bomb.h"

Bomb::Bomb()
{
	bomIsOn = false;
}

Bomb::Bomb(uint8_t &_gameTeller, uint8_t _posX, uint8_t _posY)
{
}

void Bomb::Draw(Adafruit_ILI9341 &tft, uint8_t locationX, uint8_t locationY)
{
}

// Deze functie wou alleen werken op de 1 of andere manier en niet de standaard draw functies
void Bomb::fraw(Adafruit_ILI9341 &tft, uint8_t locationX, uint8_t locationY)
{
	tft.drawLine(locationX + 1, locationY + 15, locationX + 12, locationY + 4, color_player_darkBlue);
	tft.drawLine(locationX + 2, locationY + 15, locationX + 12, locationY + 5, color_player_lightBlue);
	tft.drawLine(locationX + 2, locationY + 16, locationX + 12, locationY + 6, color_player_lightBlue);
	tft.drawLine(locationX + 3, locationY + 16, locationX + 13, locationY + 6, color_player_lightBlue);
	tft.drawLine(locationX + 3, locationY + 17, locationX + 13, locationY + 7, color_player_lightBlue);
	tft.drawLine(locationX + 4, locationY + 17, locationX + 15, locationY + 6, color_player_lightBlue);
	tft.drawLine(locationX + 5, locationY + 17, locationX + 15, locationY + 7, color_player_lightBlue);
	tft.drawLine(locationX + 5, locationY + 18, locationX + 16, locationY + 7, color_player_darkBlue);
	tft.drawLine(locationX + 1, locationY + 16, locationX + 3, locationY + 18, color_player_darkBlue);
	tft.drawPixel(locationX + 4, locationY + 18, color_player_darkBlue);
	tft.drawLine(locationX + 11, locationY + 6, locationX + 13, locationY + 8, color_player_darkBlue);
	tft.drawPixel(locationX + 14, locationY + 8, color_player_darkBlue);
	tft.drawPixel(locationX + 13, locationY + 4, color_player_darkBlue);
	tft.drawPixel(locationX + 16, locationY + 6, color_player_darkBlue);
	tft.drawLine(locationX + 6, locationY + 12, locationX + 11, locationY + 7, color_player_highlightBlue);
	tft.drawLine(locationX + 13, locationY + 5, locationX + 15, locationY + 3, ILI9341_DARKGREY);
	tft.drawLine(locationX + 14, locationY + 6, locationX + 16, locationY + 4, ILI9341_BLACK);
	tft.drawPixel(locationX + 14, locationY + 5, ILI9341_BLACK);
	tft.drawLine(locationX + 15, locationY + 4, locationX + 18, locationY + 1, ILI9341_YELLOW);
	tft.drawLine(locationX + 15, locationY + 1, locationX + 18, locationY + 4, ILI9341_YELLOW);
	tft.drawPixel(locationX + 13, locationY + 2, ILI9341_YELLOW);
	tft.drawPixel(locationX + 19, locationY + 2, ILI9341_YELLOW);
}

void Bomb::start(uint8_t &_gameTeller, uint8_t _posX, uint8_t _posY)
{
	// Bom wordt geactiveerd
	bomIsOn = true;
	// Teller wordt gereset
	startTeller = 0;

	// Positie wordt overgenomen
	posX = _posX;
	posY = _posY;
}

void Bomb::Timer()
{
	// Wanneer de bom aanstaat
	if (bomIsOn)
	{
		// Voor het tellen
		_delay_ms(1);

		// Teller wordt 1 opgeteld
		startTeller++;
			
		// Wanneer de teller groter is dan de bomtimer
		if (startTeller > bombTimer)
		{
			// Explosie wordt aangezet zodat deze opgevangen kan worden in de level.cpp
			bomExplode = true;
			// Bom wordt ontmanteld
			bomIsOn = false;
		}
	}
}

void Bomb::Explosie()
{
}
