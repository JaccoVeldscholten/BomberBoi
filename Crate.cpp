/*
 * Klasse: Crate.cpp
 * Beschrijving: Tekenen van een krat
 * Ontwikkeld door: Richard Reijerse
 * Aangepast  door: Briyan Kleijn
*/

#include "Crate.h"

Crate::Crate()
{
	collision = 2;// Heeft een collision
}

// Standaard tekenfunctie
void Crate::Draw(Adafruit_ILI9341 &tft, uint8_t locationX, uint8_t locationY)
{
	tft.fillRect(locationX, locationY, blockSize, blockSize, 0x9A00);				  // block color
	tft.drawFastHLine(locationX, locationY + (blockSize - 2), blockSize, 0x3900);	 // shadow bottom
	tft.drawFastVLine(locationX + (blockSize - 1), locationY, blockSize - 2, 0xDC00); // highlight right
	tft.drawFastHLine(locationX, locationY + 4, blockSize, 0x3900);					  // shadow stripe 1
	tft.drawFastHLine(locationX, locationY + 5, blockSize, 0xDC00);					  // highlight stripe 1
	tft.drawFastHLine(locationX, locationY + 9, blockSize, 0x3900);					  // shadow stripe 2
	tft.drawFastHLine(locationX, locationY + 10, blockSize, 0xDC00);				  // highlight stripe 2
	tft.drawFastHLine(locationX, locationY + 14, blockSize, 0x3900);				  // shadow stripe 3
	tft.drawFastHLine(locationX, locationY + 15, blockSize, 0xDC00);				  // highlight stripe 3
	tft.drawFastHLine(locationX + 1, locationY, blockSize - 1, 0xDC00);				  // highlight top
	tft.drawFastVLine(locationX, locationY, blockSize, 0x3900);						  // shadow left
	tft.fillRect(locationX + 3, locationY, 4, blockSize, 0x9A00);					  // plank left color
	tft.drawFastHLine(locationX + 3, locationY, 4, 0xDC00);							  // highlight top
	tft.drawFastVLine(locationX + 3, locationY, blockSize, 0x3900);					  // plank left shadow
	tft.drawFastVLine(locationX + 7, locationY, blockSize, 0xDC00);					  // plank left highlight
	tft.fillRect(locationX + (blockSize - 8), locationY, 4, blockSize, 0x9A00);		  // plank right color
	tft.drawFastHLine(locationX + (blockSize - 8), locationY, 4, 0xDC00);			  // highlight top
	tft.drawFastVLine(locationX + (blockSize - 8), locationY, blockSize, 0x3900);	 // plank right shadow
	tft.drawFastVLine(locationX + (blockSize - 4), locationY, blockSize, 0xDC00);	 // plank right highlight
	tft.drawFastHLine(locationX, locationY + (blockSize - 1), blockSize, 0x3900);	 // shadow bottom
}
