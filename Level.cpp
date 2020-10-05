/*
 * Klasse: Level.cpp
 * Beschrijving: Aanpassen level en tekenen van level
 * Ontwikkeld door: Jacco Veldscholten (Bom), Richard Rijerse (Bom), Sjoerd Balkenende (Random Generatie)
 * Aangepast door: Briyan Kleijn (Aanpassing naar OOP en het vuur stuk) 
*/

#include "Level.h"
Player *player;

Level::Level()
{
}

Level::Level(Adafruit_ILI9341 &_tft, uint8_t &_gametimer)
{
	tft = &_tft;
	// Stelt type vuur in
	fire0.type = 0;// horizontaal
	fire1.type = 1;// center
	fire2.type = 2;// Verticaal

	// Alle indexen
	objects[0] = &ground;
	objects[1] = &wall;
	objects[2] = &crate;
	objects[3] = &fire[0]; //Horizontaal
	objects[4] = &fire[1]; //draw_explosionCenter
	objects[5] = &fire[2]; //
	// zet de gametimer
	gameTimer = &_gametimer;

	bomb[0] = &bomb1;
	bomb[1] = &bomb2;
	bomb[2] = &bomb3;
	bomb[3] = &bomb4;
	bomb[4] = &bomb5;
	bomb[5] = &bomb6;
	bomb[6] = &bomb7;
	bomb[7] = &bomb8;
	bomb[8] = &bomb9;
	bomb[9] = &bomb10;
}

// Verantwoordelijk voor resetten van het level
void Level::Reset()
{
	for (int x = 0; x < 10; x++)
	{
		for (int y = 0; y < 10; y++)
		{
			levelDamage[x][y] = 0;
			ResetPosition(x, y);
		}
	}
}

// Returned het gameobject voor als dit nodig zou zijn
GameObject Level::getLevel()
{
	return GameObject();
}

// Eventuele loop die gebruikt kan worden bij het doorontwikkelen
void Level::Loop()
{
}

// Collision check
bool Level::CheckCollision(uint8_t x, uint8_t y)
{
	if (levelObj[x][y] == destructable_index || levelObj[x][y] == wall_index || levelBomb[x][y] == 1)
	{
		return true;
	}
	return false;
}

// Returned true als het een vuur plek is of false wanneer niet
bool Level::CheckForDeath(uint8_t x, uint8_t y)
{
	if (levelDamage[x][y] >= 1 | levelDamage[x][y] == 60) // De waarde boven de 0 geeft de aan dat er damage is en het getal -1, uitleg staat boven aan de pagina
	{
		return true;
	}
	else
	{
		return false;
	}
}

// Kan de player in ingesteld worden
void Level::SetPlayer(Player &_player)
{
	player = &_player;
}

// Hierin kun je het level laten generen, dus aanvullen van de array
void Level::SetLevel()
{
	set_wall_vert(11);
	set_wall_hor(0);
	set_wall_hor(1);
	set_wall_vert(0);
	set_wall_vert(1);
	set_pillar_wall();
	set_crates();
	// // De loop voor de multi array
	// for (int row = 0; row < 11; row++)
	// {
	// 	for (int col = 0; col < 11; col++)
	// 	{
	// 		// IN dit stuk kun je nu het juiste element aanroepen
	// 		levelObj[row][col] = 1;
	// 	}
	// }
}

// In deze functie wordt een bom toegevoegd
void Level::AddBomb(uint8_t x, uint8_t y)
{
	if (x == 1 & y == 1)
	{
	}
	else if (x == 9 & y == 9)
	{
	}
	else
	{
		bool setBomb = false; // Deze boolean geeft aan of er een plek voor een bom is gevonden
		for (uint8_t i = 0; i < 9; i++)
		{
			// Hierin kun je eruit filteren of de bom al bestaat in het level, vooral handig voor de IR input
			if (bomb[i]->posX == x & bomb[i]->posY == y)
			{
				setBomb = true;
			}
			// Wanneer de bom nog niet geplaatst is in de array
			if (!setBomb)
			{
				if (bomb[i]->bomIsOn)
				{
					// Hierin gebeurd niks, omdat er op deze plek in de array al een bom actief is
				}
				else
				{
					ResetPosition(x, y);

					// Zet de bom
					bomb[i]->fraw(*tft, location(x), location(y)); // Tekent de bom direct

					// Stelt de variable in om aan te geven welke laatste bom er is geplaatst, vooral voor IR
					_lastBomb.posX = x;
					_lastBomb.posY = y;

					// De bomb wordt geactiveerd en de timer gaat lopen
					bomb[i]->start(*gameTimer, x, y);
					levelBomb[x][y] = 1;
					setBomb = true; // bom is gezet
				}
			}
		}
	}
}

// Deze functie regelt alle timers die aangeroepen of bijgehouden moeten worden
void Level::Timer()
{
	// Dit stukje zorgt ervoor dat alle bommen die actief zijn in de array gelooped worden, vanwege de timer die moet doorlopen
	for (int i = 0; i < 9; i++)
	{
		if (bomb[i]->bomIsOn)
		{					  // Wanneer de bom actief is
			bomb[i]->Timer(); // Roept de timer functie aan

			if (bomb[i]->bomExplode)
			{ // Wanneer de bom moet exploderen

				// Verwijderd de bom uit het scherm
				RemoveBomb(bomb[i]->posX, bomb[i]->posY);

				// Locatie wordt gereset
				//bomb[i]->posX = 0;
				//bomb[i]->posY = 0;

				// De bom is nu geexplodeerd, dus kan de boolean weer op niet actief gezet worden
				bomb[i]->bomExplode = false;
			}
		}
	}

	// Is voor het verwijderen van de vuurtjes
	for (uint8_t x = 0; x < 11; x++)
	{
		for (uint8_t y = 0; y < 11; y++)
		{														  // Loop zodat je de x en y as hebt
			if (levelDamage[x][y] >= 1 & levelDamage[x][y] != 60) // Als het boven of gelijk is aan 1 betekend dat er een vuurtje is
			{
				uint8_t index = levelDamage[x][y];
				if (allFire[index] < 80) // Als het vuur nog niet moet verdwijnen telt die er 1 bij op
				{
					allFire[index]++;
				}
				else
				{ // Wanneer het vuur moet verwijderd worden
					cli();
					levelDamage[x][y] = 0;
					// Dit stuk is puur om te kijken welke plekken er vuur zijn en welke die moet verwijderen
					if (!CheckForWall(x - 1, y))
					{
						levelObj[x - 1][y] = ground_index;
						levelDamage[x - 1][y] = 0;
						ResetPosition(x - 1, y);
					}

					if (!CheckForWall(x + 1, y))
					{
						levelObj[x + 1][y] = ground_index;
						levelDamage[x + 1][y] = 0;
						ResetPosition(x + 1, y);
					}

					if (!CheckForWall(x, y + 1))
					{
						levelObj[x][y + 1] = ground_index;
						levelDamage[x][y + 1] = 0;
						ResetPosition(x, y + 1);
					}

					if (!CheckForWall(x, y - 1))
					{
						levelObj[x][y - 1] = ground_index;
						levelDamage[x][y - 1] = 0;
						ResetPosition(x, y - 1);
					}

					allFire[index] = 0;
					ResetPosition(x, y);
					sei();
				}
			}
		}
	}
}

void Level::RemoveBomb(uint8_t x, uint8_t y)
{
	ResetPosition(x, y);
	uint8_t allChecks = 0;
	levelBomb[x][y] = 0;

	// Plaatsen van het vuur
	for (uint8_t i = 0; i < 10; i++)
	{
		// Puur voor testen eerst
		if (i == 0)
		{
			i += 1;
		}

		if (allChecks != 5)
		{ // Anders heeft die alle checks al gedaan
			if (allFire[i] == 0)
			{
				levelDamage[x][y] = i;
				allChecks = 5;
				if (!CheckForWall(x - 1, y))
				{

					ResetPosition(x - 1, y);
					fire0.Draw(*tft, location(x - 1), location(y)); //Horizontaal
					levelDamage[x - 1][y] = 60;
				}

				if (!CheckForWall(x + 1, y))
				{

					ResetPosition(x + 1, y);
					fire0.Draw(*tft, location(x + 1), location(y)); //Horizontaal
					levelDamage[x + 1][y] = 60;
				}

				if (!CheckForWall(x, y + 1))
				{

					ResetPosition(x, y + 1);
					fire2.Draw(*tft, location(x), location(y + 1)); //Verticaal
					levelDamage[x][y + 1] = 60;
				}

				if (!CheckForWall(x, y - 1))
				{
					ResetPosition(x, y - 1);
					fire2.Draw(*tft, location(x), location(y - 1)); //Verticaal
					levelDamage[x][y - 1] = 60;
				}

				levelObj[x][y] = ground_index;
				ResetPosition(x, y);
				fire1.Draw(*tft, location(x), location(y)); //Centerum

				allChecks = 5; // Is klaar met checken
			}
		}
	}
}

bool Level::CheckForWall(uint8_t x, uint8_t y)
{
	if (levelObj[x][y] == wall_index)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Level::set_crates()
{
	unset_crates(); // rid the level of destructibles
	uint8_t dLocationX;
	uint8_t dLocationY;
	uint8_t i = 0;
	while (i < getAmountOfCrates())
	{ // check on collision with new box
		dLocationX = (rand() % 9) + 1;
		dLocationY = (rand() % 9) + 1;
		if (!((dLocationX == 1 && dLocationY == 1) || // spawn 1
			  (dLocationX == 1 && dLocationY == 2) ||
			  (dLocationX == 2 && dLocationY == 1) ||

			  (dLocationX == 9 && dLocationY == 9) || // spawn 2
			  (dLocationX == 9 && dLocationY == 8) ||
			  (dLocationX == 8 && dLocationY == 9) ||

			  (levelObj[dLocationX][dLocationY] == wall_index) || // other object
			  (levelObj[dLocationX][dLocationY] == destructable_index)))
		{
			levelObj[dLocationX][dLocationY] = destructable_index;
			i++;
		}
	}
}

void Level::unset_crates()
{ // rid the level of instructibles
	for (uint8_t X = 1; X < gridSize; X++)
	{
		for (uint8_t Y = 1; Y < gridSize; Y++)
		{
			if (levelObj[X][Y] == destructable_index)
			{
				levelObj[X][Y] = ground_index;
			}
		}
	}
}

void Level::ResetPosition(uint8_t x, uint8_t y)
{
	if (levelBomb[x][y] == 1)
	{
		bomb1.fraw(*tft, location(x), location(y));
	}
	else if (levelDamage[x][y] >= 1 | levelDamage[x][y] == -1)
	{
		fire[0].Draw(*tft, location(x), location(y)); //Horizontaal
	}
	else
	{
		objects[levelObj[x][y]]->Draw(*tft, location(x), location(y));
	}
}

void Level::set_wall_vert(uint8_t x_start)
{ // if x == true: draw left wall, if x == false: draw right wall
	uint8_t x;
	if (x_start)
	{
		x = 0;
	}
	else
	{
		x = 10;
	}
	for (uint8_t y = 1; y <= 9; y++)
	{
		levelObj[x][y] = wall_index;
	}
}

void Level::set_wall_hor(uint8_t y_start)
{ // if y == true: draw up wall, if y == false: draw down wall
	uint8_t y;
	if (y_start)
	{
		y = 0;
	}
	else
	{
		y = 10;
	}
	for (uint8_t x = 0; x <= 10; x++)
	{
		levelObj[x][y] = wall_index;
	}
}

void Level::set_pillar_wall()
{ // draw field pillars
	uint8_t y;
	for (uint8_t x = 2; x <= 8; x += 2)
	{
		for (y = 2; y <= 8; y += 2)
		{
			levelObj[x][y] = wall_index;
		}
	}
}

void Level::DrawLevel()
{
	// De loop voor de multi array
	for (int row = 0; row < 11; row++)
	{
		for (int col = 0; col < 11; col++)
		{
			// IN dit stuk kun je nu het juiste element aanroepen
			objects[levelObj[row][col]]->Draw(*tft, location(row), location(col));

			// Tekenen van de bom
			if (levelBomb[row][col] == 1)
			{
				objects[2]->Draw(*tft, location(row), location(col));
			}
		}
	}
}

uint8_t Level::location(uint8_t coordinate)
{
	return blockSize * coordinate + startingPoint;
}

void Level::setAmountOfCrates(uint8_t amount)
{
	amCrates = amount;
}
uint8_t Level::getAmountOfCrates()
{
	return amCrates;
}
