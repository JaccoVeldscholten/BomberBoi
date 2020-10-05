#ifndef _SPELSCHERMH_
#define _SPELSCHERMH_
#pragma once
#include "Scherm.h"
#include "Level.h"
#include "Player.h"
#include <avr/io.h>

class Spelscherm : public Scherm
{
public:
	Level *level;
	Player *player1;
	Player *player2;
	Adafruit_ILI9341 *tft;
	//Input input;
	void Do();
	void DrawLevel();
	Spelscherm(Adafruit_ILI9341 &_tft, Level &_level, Player &_player1, Player &_player2) : Scherm(_tft)
	{
		tft = &_tft;
		level = &_level;
		player1 = &_player1;
		player2 = &_player2;
	}

	void PlayerInfoBar();
	void draw_playerName(uint8_t Xloc, uint8_t Yloc, uint8_t player);
	void Init();

	bool Dood;

private:
};
#endif
