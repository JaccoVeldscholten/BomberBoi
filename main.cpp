/*
 * Main: Main.cpp
 * Beschrijving: Aanroepen van cruciale items, functioneert als een soort 
 * control centrum voor het aanelkaar knopen van alles
 * Ontwikkeld door: Jacco Veldscholten & Briyan Kleijn
*/


#include "Bomb.h"
#include "Player.h"
#include "GameObject.h"
#include "Level.h"
#include "Input.h"
#include "IR.h"
#include "Spelscherm.h"
#include "Startscherm.h"
#include "Life.h"

#define F_CPU 16000000UL
#include <avr/io.h>		   //Importeer io.h library voor de IO functionaliteit
#include <avr/interrupt.h> //Importeer interrupt.h library om interrupts te kunnen gebruiken
#include <util/delay.h>

uint8_t teller = 0;

volatile uint8_t ticks = 0;
Adafruit_ILI9341 tft(10, 9);

Level level(tft, teller);
Player flayer(1, level);
Player player2(2, level);

IR ir(flayer, player2);
Spelscherm spelscherm(tft, level, flayer, player2);
Startscherm startscherm(tft);
Input input(flayer, startscherm);

Life life(0x20);

ISR(TIMER1_COMPA_vect)
{
	ir.sendByte();
	ir.tellerReceive++;
}

ISR(INT0_vect)
{
	cli();
	ir.receiveHandler();

	sei();
}

int main(void)
{
	sei();
	Serial.begin(9600);
	tft.begin();
	tft.setRotation(1);
	tft.fillScreen(0x1212);
	input.start();
	ir.Init();
	startscherm.Hoofdscherm();
	life.Init();

	uint8_t stage = 0;

	while (1)
	{
		if (!ir.endGame)
		{ // Wordt aangezet als game wordt opgestart
			if (startscherm.Start)
			{
				ir.gameData = true;
				if (!ir.seedSended)
				{
					ir.sendSeed();
				}
				// Als het gestart wordt
				if (stage == 0)
				{
					tft.fillScreen(0x1212);
					spelscherm.Init();
					input.Menu = false;
					stage = 1;
				}
				else
				{
					Serial.println(flayer.levens);
					if (flayer.levens >= 0)
					{
						life.setLife(flayer.levens);
					}

					if (flayer.levens < 1)
					{
						startscherm.winLose = 2;
						ir.endGame = true;
					}
					else
						spelscherm.Do();
				}
			}
			else
			{
				ir.gameData = false;
			}
		}
		else
		{	
			// Stage 1 zorgt er voor dat het initialiseert
			if (stage == 1)
			{
				ir.gameData = false;
				level.Reset();
				flayer.levens = 3;
				player2.levens = 3;
				input.Menu = true;
				ir.Reset();
				tft.fillScreen(0x1212);
				startscherm.Hoofdscherm();
				startscherm.Start = false;

				stage = 0;
				ir.endGame = false;
			}

			// Game is einde want andere speler heeft opgegeven dat die dood is.
			// Dit betekend dus dat jij de winaar bent.
			// Roep functie eindscherm aan + parameter winnaar
		}
		_delay_ms(30);
		input.loop();
		ir.loop();
		//Serial.println(ir.dataReceived);
	}
}
