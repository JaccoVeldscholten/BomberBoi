/*
 * Klasse: Level.cpp
 * Beschrijving: Aanpassen level en tekenen van level
 * Ontwikkeld door: Jacco Veldscholten (Levens), Briyan Kleijn (Speelbaar maken), Richard Rijerse (Sprites)
*/

#include "Player.h"

Player::Player()
{
}

Player::Player(uint8_t player)
{
}

// Player constructor
Player::Player(uint8_t player, Level &_level)
{
	level = &_level; // Zet de reference
	if (player == 1)
	{

		posX = 1;				 // Start positie
		posY = 1;				 // Start positie
		playerDrawDirection = 1; // Standaard direction

		darkColor = color_player_darkBlue;
		lightColor = color_player_lightBlue;
		highlightColor = color_player_highlightBlue;
	}
	else if (player == 2)
	{
		posX = 2; // Laaste plek spawnen
		posY = 1; // Laaste plek spawnen
		IRlastX = 2;
		IRlastY = 1;
		playerDrawDirection = 1; // Standaard direction

		darkColor = color_player_darkShoe1;
		lightColor = color_player_lightFace1;
		highlightColor = color_player_lightHair1;
	}
}

void Player::Loop()
{
	// Voor het checken van dood
	Death();
}


void Player::Start()
{
	// Start roept de tekenfunctie aan
	Draw(*level->tft, level->location(posX), level->location(posY));

}
// Zorgt voor het drawen van de functie
void Player::Draw(Adafruit_ILI9341 &tft, uint8_t locationX, uint8_t locationY)
{
	level->ResetPosition(lastX, lastY);

	switch (playerDrawDirection)
	{
	case 1: //up
		draw_playerUp_bitmap(tft, locationX, locationY);
		break;

	case 2: //down
		draw_playerDown_bitmap(tft, locationX, locationY);
		break;

	case 3: //right
		draw_playerRight_bitmap(tft, locationX, locationY);
		break;
	case 4: //left
		draw_playerLeft_bitmap(tft, locationX, locationY);
		break;
	}
}

void Player::draw_playerUp_bitmap(Adafruit_ILI9341 &tft, uint8_t x, uint8_t y)
{
	// body
	tft.fillRect(x + 2, y + 9, 16, 4, darkColor);
	tft.drawFastVLine(x + 1, y + 9, 3, darkColor);
	tft.drawFastHLine(x + 2, y + 12, 2, darkColor);
	tft.drawFastHLine(x + 4, y + 13, 12, darkColor);
	tft.drawFastHLine(x + 16, y + 12, 2, darkColor);
	tft.drawFastHLine(x + 2, y + 8, 2, lightColor);
	tft.drawFastHLine(x + 16, y + 8, 2, lightColor);
	tft.drawFastVLine(x + 18, y + 9, 3, lightColor);

	// hat
	tft.fillRect(x + 5, y + 5, 10, 4, lightColor);
	tft.fillRect(x + 9, y + 6, 2, 3, darkColor);
	tft.drawPixel(x + 8, y + 7, darkColor);
	tft.drawPixel(x + 11, y + 7, darkColor);
	tft.drawPixel(x + 5, y + 5, darkColor);
	tft.drawPixel(x + 5, y + 9, darkColor);
	tft.drawPixel(x + 14, y + 9, darkColor);
	tft.drawFastVLine(x + 4, y + 6, 3, darkColor);
	tft.drawFastHLine(x + 6, y + 10, 8, darkColor);
	tft.drawFastHLine(x + 6, y + 4, 8, highlightColor);
	tft.drawPixel(x + 14, y + 5, highlightColor);
	tft.drawFastVLine(x + 15, y + 6, 3, highlightColor);
	// hair
	tft.drawFastVLine(x + 4, y + 9, 2, color_player_darkHair1);
	tft.drawFastHLine(x + 5, y + 11, 3, color_player_darkHair1);
	tft.drawFastHLine(x + 8, y + 12, 4, color_player_darkHair1);
	tft.drawFastHLine(x + 12, y + 11, 3, color_player_darkHair1);
	tft.drawFastVLine(x + 15, y + 9, 2, color_player_darkHair1);
	tft.drawPixel(x + 5, y + 10, color_player_lightHair1);
	tft.drawFastHLine(x + 8, y + 11, 4, color_player_lightHair1);
	tft.drawPixel(x + 14, y + 10, color_player_lightHair1);
	// shoes
	tft.drawFastHLine(x + 5, y + 14, 3, color_player_darkShoe1);
	tft.drawFastHLine(x + 12, y + 14, 3, color_player_darkShoe1);
}

void Player::draw_playerDown_bitmap(Adafruit_ILI9341 &tft, uint8_t x, uint8_t y)
{
	/*
	tft.fillRect(location(x), location(y), blockSize, blockSize, ILI9341_BLUE);
	tft.drawRect(location(x), location(y), blockSize, blockSize, ILI9341_BLACK);
	*/
	// face
	tft.fillRect(x + 5, y + 10, 10, 3, color_player_darkFace1);
	tft.drawFastHLine(x + 9, y + 13, 2, color_player_darkFace1);
	tft.drawFastHLine(x + 6, y + 11, 8, color_player_lightFace1);
	tft.drawFastHLine(x + 9, y + 12, 2, color_player_lightFace1);
	tft.drawPixel(x + 7, y + 11, ILI9341_WHITE);
	tft.drawPixel(x + 8, y + 11, ILI9341_BLACK);
	tft.drawPixel(x + 11, y + 11, ILI9341_BLACK);
	tft.drawPixel(x + 12, y + 11, ILI9341_WHITE);

	// hat + clothing
	tft.fillRect(x + 5, y + 5, 10, 5, lightColor);
	tft.drawFastHLine(x + 6, y + 4, 8, highlightColor);
	tft.drawFastHLine(x + 6, y + 10, 8, darkColor);
	tft.drawFastHLine(x + 6, y + 10, 8, darkColor);
	tft.fillRect(x + 9, y + 5, 2, 3, darkColor);
	tft.drawPixel(x + 8, y + 6, darkColor);
	tft.drawPixel(x + 11, y + 6, darkColor);
	tft.drawPixel(x + 5, y + 5, darkColor);
	tft.drawPixel(x + 14, y + 5, highlightColor);
	tft.drawPixel(x + 5, y + 9, darkColor);
	tft.drawPixel(x + 14, y + 9, darkColor);
	tft.drawFastVLine(x + 4, y + 6, 6, darkColor);
	tft.drawFastVLine(x + 4, y + 9, 2, highlightColor);
	tft.drawFastVLine(x + 15, y + 6, 3, highlightColor);
	tft.drawFastVLine(x + 15, y + 9, 3, darkColor);
	tft.drawFastHLine(x + 2, y + 7, 2, highlightColor);
	tft.drawFastHLine(x + 2, y + 11, 2, darkColor);
	tft.drawFastHLine(x + 16, y + 7, 2, highlightColor);
	tft.drawFastHLine(x + 16, y + 11, 2, darkColor);
	tft.fillRect(x + 2, y + 8, 2, 3, lightColor);
	tft.fillRect(x + 16, y + 8, 2, 3, lightColor);
	tft.drawFastVLine(x + 1, y + 8, 3, darkColor);
	tft.drawFastVLine(x + 18, y + 8, 3, highlightColor);

	// shoes
	tft.fillRect(x + 5, y + 13, 3, 2, color_player_darkShoe1);
	tft.fillRect(x + 12, y + 13, 3, 2, color_player_darkShoe1);
	tft.drawPixel(x + 5, y + 12, color_player_darkShoe1);
	tft.drawPixel(x + 14, y + 13, color_player_darkShoe1);
	tft.drawPixel(x + 6, y + 13, color_player_lightShoe1);
	tft.drawPixel(x + 13, y + 13, color_player_lightShoe1);
}

void Player::draw_playerLeft_bitmap(Adafruit_ILI9341 &tft, uint8_t x, uint8_t y)
{
	// face
	tft.drawFastHLine(x + 8, y + 4, 2, color_player_darkFace1);
	tft.drawFastVLine(x + 7, y + 5, 7, color_player_darkFace1);
	tft.drawFastVLine(x + 6, y + 7, 2, color_player_darkFace1);
	tft.drawFastHLine(x + 8, y + 12, 3, color_player_darkFace1);
	tft.drawFastHLine(x + 7, y + 7, 2, color_player_lightFace1);
	tft.fillRect(x + 8, y + 10, 2, 2, color_player_lightFace1);
	tft.drawPixel(x + 8, y + 5, ILI9341_WHITE);
	tft.drawPixel(x + 8, y + 6, ILI9341_BLACK);
	tft.drawPixel(x + 8, y + 8, ILI9341_BLACK);
	tft.drawPixel(x + 8, y + 9, ILI9341_WHITE);
	// hair
	tft.drawPixel(x + 10, y + 11, color_player_darkHair1);
	tft.drawFastHLine(x + 11, y + 12, 3, color_player_darkHair1);
	// hat
	tft.fillRect(x + 10, y + 4, 5, 7, lightColor);
	tft.drawFastVLine(x + 9, y + 5, 5, darkColor);
	tft.drawPixel(x + 10, y + 10, darkColor);
	tft.drawFastHLine(x + 11, y + 11, 4, darkColor);
	tft.drawPixel(x + 14, y + 10, darkColor);
	tft.drawFastVLine(x + 15, y + 7, 4, darkColor);
	tft.fillRect(x + 12, y + 6, 3, 2, darkColor);
	tft.drawPixel(x + 13, y + 5, darkColor);
	tft.drawPixel(x + 13, y + 8, darkColor);
	tft.drawPixel(x + 10, y + 4, highlightColor);
	tft.drawFastHLine(x + 11, y + 3, 3, highlightColor);
	tft.drawPixel(x + 14, y + 4, highlightColor);
	tft.drawFastVLine(x + 15, y + 5, 2, highlightColor);
	// left arm
	tft.fillRect(x + 9, y + 13, 3, 4, lightColor);
	tft.drawFastVLine(x + 8, y + 13, 4, darkColor);
	tft.drawFastHLine(x + 9, y + 15, 3, darkColor);
	tft.drawFastHLine(x + 9, y + 17, 3, darkColor);
	tft.drawPixel(x + 12, y + 16, darkColor);
	tft.drawFastVLine(x + 12, y + 13, 3, highlightColor);
	tft.drawPixel(x + 8, y + 17, color_player_darkFace1);
	tft.drawFastHLine(x + 9, y + 18, 2, color_player_darkFace1);
	// right arm
	tft.drawFastHLine(x + 9, y + 2, 3, lightColor);
	tft.drawPixel(x + 8, y + 2, darkColor);
	tft.drawFastHLine(x + 8, y + 3, 3, darkColor);
	tft.drawFastHLine(x + 9, y + 1, 3, highlightColor);
	tft.drawPixel(x + 12, y + 2, highlightColor);
	// right shoe
	tft.drawPixel(x + 6, y + 5, color_player_darkShoe1);
	tft.drawFastVLine(x + 5, y + 6, 2, color_player_darkShoe1);
	tft.drawPixel(x + 6, y + 6, color_player_lightShoe1);
	// left shoe
	tft.drawPixel(x + 6, y + 11, color_player_darkShoe1);
	tft.drawFastVLine(x + 5, y + 12, 2, color_player_darkShoe1);
	tft.drawFastHLine(x + 6, y + 13, 2, color_player_darkShoe1);
	tft.drawFastHLine(x + 6, y + 12, 2, color_player_lightShoe1);
}

void Player::draw_playerRight_bitmap(Adafruit_ILI9341 &tft, uint8_t x, uint8_t y)
{
	// face
	tft.drawFastHLine(x + 10, y + 4, 2, color_player_darkFace1);
	tft.drawFastVLine(x + 12, y + 5, 2, color_player_darkFace1);
	tft.drawFastVLine(x + 13, y + 7, 2, color_player_darkFace1);
	tft.drawFastVLine(x + 12, y + 8, 4, color_player_darkFace1);
	tft.drawFastHLine(x + 9, y + 12, 3, color_player_darkFace1);
	tft.drawFastHLine(x + 11, y + 7, 2, color_player_lightFace1);
	tft.fillRect(x + 10, y + 10, 2, 2, color_player_lightFace1);
	tft.drawPixel(x + 11, y + 5, ILI9341_WHITE);
	tft.drawPixel(x + 11, y + 6, ILI9341_BLACK);
	tft.drawPixel(x + 11, y + 8, ILI9341_BLACK);
	tft.drawPixel(x + 11, y + 9, ILI9341_WHITE);
	// hair
	tft.drawPixel(x + 9, y + 11, color_player_darkHair1);
	tft.drawFastHLine(x + 6, y + 12, 3, color_player_darkHair1);
	// hat
	tft.fillRect(x + 5, y + 4, 5, 7, lightColor);
	tft.drawFastVLine(x + 4, y + 5, 6, darkColor);
	tft.drawFastVLine(x + 5, y + 10, 2, darkColor);
	tft.drawFastHLine(x + 6, y + 11, 3, darkColor);
	tft.drawPixel(x + 9, y + 10, darkColor);
	tft.drawFastVLine(x + 10, y + 7, 3, darkColor);
	tft.fillRect(x + 5, y + 6, 3, 2, darkColor);
	tft.drawPixel(x + 6, y + 5, darkColor);
	tft.drawPixel(x + 6, y + 8, darkColor);
	tft.drawPixel(x + 5, y + 4, highlightColor);
	tft.drawFastHLine(x + 6, y + 3, 3, highlightColor);
	tft.drawPixel(x + 9, y + 4, highlightColor);
	tft.drawFastVLine(x + 10, y + 5, 2, highlightColor);
	// left arm
	tft.drawFastHLine(x + 8, y + 2, 3, lightColor);
	tft.drawPixel(x + 7, y + 2, darkColor);
	tft.drawFastHLine(x + 9, y + 3, 2, darkColor);
	tft.drawFastHLine(x + 8, y + 1, 3, highlightColor);
	tft.drawFastVLine(x + 11, y + 2, 2, highlightColor);
	// right arm
	tft.fillRect(x + 8, y + 13, 3, 4, lightColor);
	tft.drawFastVLine(x + 7, y + 13, 4, darkColor);
	tft.drawFastHLine(x + 8, y + 17, 3, darkColor);
	tft.drawFastHLine(x + 8, y + 15, 3, darkColor);
	tft.drawPixel(x + 11, y + 16, darkColor);
	tft.drawFastVLine(x + 11, y + 13, 3, highlightColor);
	// right shoe
	tft.drawPixel(x + 13, y + 5, color_player_darkShoe1);
	tft.drawFastVLine(x + 14, y + 6, 2, color_player_darkShoe1);
	tft.drawPixel(x + 13, y + 6, color_player_lightShoe1);
	// left shoe
	tft.drawPixel(x + 13, y + 11, color_player_darkShoe1);
	tft.drawFastVLine(x + 14, y + 12, 2, color_player_darkShoe1);
	tft.drawFastHLine(x + 12, y + 13, 2, color_player_darkShoe1);
	tft.drawFastHLine(x + 12, y + 12, 2, color_player_lightShoe1);
}

void Player::SpawnPlayer()
{
}

// Deze functie wordt aangeroepen om de player te besturen via IR
void Player::MoveIR(uint8_t IRposX, uint8_t IRposY)
{
	// Player 2
	level->ResetPosition(IRlastX, IRlastY);

	// Dit stuk code zorgt ervoor dat er een directie achterhaald wordt
	if (IRlastY == IRposY)
	{
		if ((IRposX - IRlastX) < 0)
		{
			playerDrawDirection = 3;
		}
		else if ((IRposX - IRlastX) > 0)
		{
			playerDrawDirection = 4;
		}
	}
	else
	{
		if ((IRposY - IRlastY) < 0)
		{
			playerDrawDirection = 1;
		}
		else
		{
			playerDrawDirection = 2;
		}
	}

	// Tekent de player
	Draw(*level->tft, level->location(IRposX), level->location(IRposY));

	// Registreert
	IRlastX = IRposX;
	IRlastY = IRposY;
	posX = IRposX;
	posY = IRposY;
}

// Beweegt de speler rond
void Player::Move(uint8_t _direction)
{
	positionChanged = true;
	if (playerMayMove)
	{
		playerMayMove = false;

		lastX = posX;
		lastY = posY;
		switch (_direction)
		{

		case 1: //up
			posY--;
			playerMayMove = false;
			break;

		case 2: //down
			posY++;
			playerMayMove = false;
			break;

		case 3: //right
			playerMayMove = false;
			posX++;
			break;

		case 4: //left
			playerMayMove = false;
			posX--;
			break;
		}

		if (level->CheckCollision(posX, posY)) // Checkt voor collision in level
		{
			posX = lastX;
			posY = lastY;
			playerMayMove = true;
		}
		else
		{
			playerDrawDirection = _direction;
			Draw(*level->tft, level->location(posX), level->location(posY));
			playerMayMove = true;
		}
	}
}

// Deze functie regelt de dood
void Player::Death()
{
	// Check voor de dood
	if (level->CheckForDeath(posX, posY))
	{
		if (playerNum == 1)
		{
			levens--;
			life.Death();
			//life1.setLife(levens);
			if (levens < 0)
			{
				// Dood.
				// Roep hier eindscherm op + IR sendGameOver()
			}
			level->ResetPosition(posX, posY);

			// Reset de positie
			IRlastX = 1;
			IRlastY = 1;
			posX = 1;
			posY = 1;
			Start();
		}
		else
		{
			//life1.setLife(levens);
			levens--;
			life.Death();
			if (levens < 0)
			{
				// Dood.
				// Roep hier eindscherm op + IR sendGameOver()
			}
			level->ResetPosition(posX, posY);

			// Reset de positie
			IRlastX = 9;
			IRlastY = 9;
			posX = 9;
			posY = 9;
			Start();
		}
	}
}

void Player::SetCurrentLocation(uint8_t x, uint8_t y)
{
}

// Deze functie wordt aangeroepen wanneer er een bom geplaatst moet worden vanuit de input
void Player::BombDropCheck()
{
	if (posX == 0 & posY == 0)// Deze positie mag geen bom (Spawn)
	{
	}
	else if (posX == 9 & posY == 9)// Deze positie mag geen bom (Spawn)
	{
	}
	else if (canDropBomb)
	{
		canDropBomb = false;

		// Stelt de laatst geplaatste bom in
		lastBomb.posX = posX;
		lastBomb.posY = posY;

		//Geeft aan de er een bom is gedropped
		placedBomb = true;

		// Voegt de bom toe aan het level
		level->AddBomb(posX, posY);

		canDropBomb = true;
	}
}
