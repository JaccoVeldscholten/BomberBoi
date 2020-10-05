/*
 * Klasse: Startscherm.cpp
 * Beschrijving: Tekenen van Startscherm
 * Ontwikkeld door: Sjoerd Balkenende
 * Aangepast  door: Briyan Kleijn
*/
#include "Startscherm.h"

uint8_t Startscherm::location(uint8_t coordinate)
{
  return blockSize * coordinate + startingPoint;
}

void Startscherm::Hoofdscherm()
{
  Redraw();
}

void Startscherm::Redraw()
{
  tft->fillScreen(background_colour);
  // Bomberman LOGO
  tft->setCursor(location(2), location(2) - startingPoint);

  tft->setTextSize(3);
  tft->setFont();
  if (winLose == 0)
  {
    tft->setTextColor(ILI9341_BLUE);
    tft->println("Bomberman");
  }
  else if (winLose == 1)
  {
    // Winnaar 
    tft->setTextColor(ILI9341_GREEN);
    tft->println("YOU WIN");
  }
  else if (winLose == 2)
  {
    // Verliezer
    tft->setTextColor(ILI9341_RED);
    tft->println("YOU LOSE");
  }

  //draw the buttons
  uint8_t buttonChoice = 0;
  uint8_t Yloc[] = {4, 6, 8};
  uint8_t Xloc = 3;
  drawButton(Xloc, Yloc[0], "Start Lobby", blockSize * 9, buttonColors[0]);
  drawButton(Xloc, Yloc[1], "Search Lobby", blockSize * 9, buttonColors[1]);
}

// Tekent de knoppen
void Startscherm::drawButton(uint8_t Xloc, uint8_t Yloc, char naam[], uint8_t length1, uint16_t colour)
{
  tft->fillRect(location(Xloc), location(Yloc) - startingPoint - 5, length1, blockSize * 2 - 5, colour);
  tft->setCursor(location(Xloc) + 5, location(Yloc) - 4);
  tft->setFont();
  tft->setTextColor(ILI9341_WHITE);
  tft->setTextSize(2);
  tft->println(naam);
  tft->setFont();
}


void Startscherm::Up()
{
  if (selectNum == 0)
  {
  }
  else
  {
	// Stelt originele kleur weer in
    buttonColors[selectNum] = ILI9341_RED;
    selectNum -= 1;

	// Nieuwe geselecteerde knop krijgt highlight
    buttonColors[selectNum] = homescreenButtonColorHighlight;
    Redraw();
  }
}

void Startscherm::Down()
{
  if (selectNum == 1)
  {
  }
  else
  {
	// Stelt originele kleur weer in
    buttonColors[selectNum] = ILI9341_RED;
    selectNum += 1;

	// Nieuwe geselecteerde knop krijgt highlight
    buttonColors[selectNum] = homescreenButtonColorHighlight;
    Redraw();
  }
}

void Startscherm::Enter()
{
}

void Startscherm::Options()
{
}

void Startscherm::SearchLobby()
{
}
