/*
 * Klasse: Input.cpp
 * Beschrijving: Tekenen van een grondvlak
 * Ontwikkeld door: Briyan Kleijn
*/

#include "Input.h"
#include "Nunchuk.h"// Is static, dit was de beste manier om te includen


void Input::start()
{
	nunchuk_init_power(); // A1 and A2 is power supply
	nunchuk_init();
}

void Input::loop()
{
	// Wanneer er input is
	if (nunchuk_read())
	{
		buffer++;
		if (buffer > bufferOffset)
		{ // Filter vervuilde data (bij starten i2c)
			if (!nunchuk_buttonC())
			{
				// Draw player
				ReadInput();
				HasInput();
				//_delay_ms(25);
			}
			else
			{
				// Wanneer het menu actief is
				if (Menu)
				{
					startscherm->Start = true;// Dit zorgt ervoor dat het spelscherm wordt gestart via de main.cpp
				}else player->BombDropCheck();
			}
		}
		if (nunchuk_buttonZ)
		{
			resetCounter++;
			if (resetCounter > 100)
			{
				void (*resetFunc)(void) = 0;
			}
		}
	}
}

// Leest de input uit
void Input::ReadInput()
{
	if (canMove)
	{
		canMove = false;

		if (threshold < nunchuk_joystickX())
		{ // right
			if (Menu) 
			{
				
			}
			else
				player->Move(3);
		}
		else if (-threshold > nunchuk_joystickX())
		{ // left
			if (Menu)
			{
				
			}
			else
				player->Move(4);
		}
		else if (-threshold > nunchuk_joystickY())
		{ // down
			if (Menu)
			{
				startscherm->Down();
			}
			else
				player->Move(2);
		}
		else if (threshold < nunchuk_joystickY())
		{ // up
			if (Menu)
			{

				startscherm->Up();
			}
			else
				player->Move(1);
		}
	}
}

void Input::HasInput()
{
	if (nunchuk_joystickX() <= 40 & nunchuk_joystickX() >= -40 & nunchuk_joystickY() <= 40 & nunchuk_joystickY() >= -40)
	{
		canMove = true;
	}
}
