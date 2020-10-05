#ifndef _STARTSCHERMH_
#define _STARTSCHERMH_
#pragma once
#include "Scherm.h"

#define blockSize 20
#define background_colour ILI9341_BLACK
#define startingPoint 10
// buttons
#define homescreenButtonColor 0x424F
#define homescreenButtonColorShadow 0x318B
#define homescreenButtonColorHighlight 0x6B73

class Startscherm : public Scherm
{
public:
	uint8_t buttonColors[2];

	Startscherm(Adafruit_ILI9341 &_tft) : Scherm(_tft)
	{
		for (uint8_t i = 0; i < 3; i++)
		{
			buttonColors[i] = ILI9341_RED;
		}
	}
	void Hoofdscherm();

	void Up();
	void Down();
	void Enter();

	bool Start = false;

	uint8_t winLose = 0; // Wanneer die 0 is betekend dat de titel moet weergeven worden, 1 is player1 gewonnen, 2 is player 2 gewonnen
private:
	void drawButton(uint8_t Xloc, uint8_t Yloc, char naam[], uint8_t length1, uint16_t colour);

	void Redraw();

	uint8_t location(uint8_t coordinate);

	uint8_t selectNum = 0;

	void Options();
	void SearchLobby();
};
#endif
