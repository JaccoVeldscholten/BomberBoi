/*
 * Klasse: Ground.cpp
 * Beschrijving: Tekenen van een grondvlak
 * Ontwikkeld door: Richard Rijerse
 * Aangepast  door: Briyan Kleijn
*/

#include "Ground.h"

Ground::Ground()
{
}
// Standaard functie
void Ground::Draw(Adafruit_ILI9341 &tft, uint8_t locationX, uint8_t locationY)
{
	tft.fillRect(locationX, locationY, blockSize, blockSize, 0x4D20); // block color
}