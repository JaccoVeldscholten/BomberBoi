#ifndef _INPUTH_
#define _INPUTH_
#pragma once

#define threshold 40
#define bufferOffset 4 // Vervuilde data offset (4 is voldoende)
#include "Player.h"
#include "Startscherm.h"

class Input
{
public:
	Player *player;
	Input() {}
	Input(Player &fl, Startscherm &startscherm1)
	{
		player = &fl;
		startscherm = &startscherm1;
	}

	Startscherm *startscherm;
	void start();
	void loop();
	bool Menu = true;

private:
	void ReadInput();
	void HasInput();
	bool canMove = true;
	volatile uint8_t resetCounter = 0;
	volatile uint8_t buffer = 0;
};
#endif
