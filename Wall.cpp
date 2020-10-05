/*
 * Klasse: Wall.cpp
 * Beschrijving: Sprite van een muur
 * Ontwikkeld door: Richard Rijerse
 * Aangepast  door: Briyan Kleijn
*/
#include "Wall.h"

Wall::Wall()
{
	collision = 1;
}

void Wall::Draw(Adafruit_ILI9341 &tft, uint8_t locationX, uint8_t locationY)
{
	tft.fillRect(locationX, locationY, blockSize, blockSize, 0xA514);						 // block color
	tft.drawFastHLine(locationX, locationY, blockSize, 0xE71C);								 // highlight top
	tft.drawFastVLine(locationX + (blockSize - 1), locationY, blockSize - 2, 0xE71C);		 // highlight right
	tft.drawFastHLine(locationX, locationY + 5, blockSize, color_wall_shadow);				 // shadow bottom
	tft.drawFastHLine(locationX, locationY + 6, blockSize, 0xE71C);							 // highlight top
	tft.drawFastHLine(locationX, locationY + 12, blockSize, color_wall_shadow);				 // shadow bottom
	tft.drawFastHLine(locationX, locationY + 13, blockSize, 0xE71C);						 // highlight top
	tft.drawFastVLine(locationX + 6, locationY, 5, 0xE71C);									 // highlight right
	tft.drawFastVLine(locationX + 7, locationY, 5, color_wall_shadow);						 // highlight right
	tft.drawFastVLine(locationX + 11, locationY + 13, 6, 0xE71C);							 // highlight right
	tft.drawFastVLine(locationX + 12, locationY + 13, 6, color_wall_shadow);				 // highlight right
	tft.drawFastHLine(locationX, locationY + (blockSize - 1), blockSize, color_wall_shadow); // shadow bottom
	tft.drawFastVLine(locationX, locationY, blockSize, color_wall_shadow);					 // shadow left
}
