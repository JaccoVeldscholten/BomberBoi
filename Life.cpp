/*
 * Klasse: Life.cpp
 * Beschrijving: Levens versturen via I2C
 * Ontwikkeld door: Briyan Kleijn
*/


#include "Life.h"
#include "Wire.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define dead 0x00  // Everything off
#define one 0x01   // p0 ON
#define two 0x03   // p0 and p1 ON
#define three 0x07 // p0, p1 and p2 ON

// Stelt het adress in
Life::Life(uint8_t _adress)
{
	adress = _adress;
}

// Initialiseert de boel
void Life::Init()
{
	sei();

	Wire.beginTransmission(adress);
	Wire.write(0xFF);
	Wire.endTransmission();
}

// Returned de life van dezeklasse
uint8_t Life::getLife()
{
	return life;
}

// Stelt het leven in 
void Life::setLife(uint8_t _life)
{

	if (_life != -1)
		life = _life;
	switch (life)
	{
	case 0:
		setLed(0x00);// no output, oftewel alle ledjes uit
		break;

	case 1:
		setLed(one);
		break;

	case 2:
		setLed(two);
		break;

	case 3:
		setLed(three);
		break;
	}
}

// Stelt de led in aan de hand van een byte
void Life::setLed(uint8_t _byte)
{
	sei();
	Wire.beginTransmission(adress);
	Wire.write(_byte);
	Wire.endTransmission();
}

void Life::Death()
{
	setLife(getLife() - 1);
}
