#ifndef _FIREH_
#define _FIREH_

#include "GameObject.h"

#define color_player_highlightBlue 0x7D9C
#define color_player_darkBlue 0x005F
#define color_player_lightBlue 0x03DF
#define FIRETIME 40

class Fire : public GameObject
{
public:
	Fire();
	Fire(uint8_t _type); // Geeft het type vuur mee, zoals linker, midden, rechts of omhoog
	volatile uint8_t type;// Type vuur
	
	// Variablen voor als de timer naar de klasse wordt verplaatst
	bool isOn;// 
	bool turnedOff;
	void Timer();
	void TurnOn(uint8_t _type, uint8_t x, uint8_t y);


	// Standaard functie
	void Draw(Adafruit_ILI9341 &tft, uint8_t locationX, uint8_t locationY);
	
	
	// Posities
	uint8_t posX, posY;

private:
	uint8_t teller;

	// Tekenfuncties
	void draw_explosionCenter(Adafruit_ILI9341 &tft, uint8_t x, uint8_t y);
	void draw_explosionHor(Adafruit_ILI9341 &tft, uint8_t x, uint8_t y);
	void draw_explosionVer(Adafruit_ILI9341 &tft, uint8_t x, uint8_t y);
};

#endif
