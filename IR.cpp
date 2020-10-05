/*
 * Klasse: IR.cpp
 * Beschrijving: Opzetten van IR protocol  (Uitlezen / Versturen)
 * Ontwikkeld door: Jacco Veldscholten & Briyan Kleijn
 * Ontwikkeling protocol: Jacco Veldscholten (Uitlezen / Versturen / Decoderen)
 * Ontwikkeling opzetten data: Briyan Kleijn (Filteren / Encoderen)
*/

#include "IR.h"

IR::IR(Player &_player1, Player &_player2)
{
	player1 = &_player1;
	player2 = &_player2;
}

void IR::Init()
{
	DDRD |= (1 << PD6); // IR pin als output

	// Instellen Timer
	TCCR0A |= (1 << COM0A0); // toggle on CTC
	TCCR0A |= (1 << WGM01);  // CTC mode
	TCCR0B |= (1 << CS01);   // Prescaler 8
	if (mode == 1)
	{
		OCR0A = 53; // Fixed 36Khz wit
	}
	else
	{
		OCR0A = 53; // Fixed 56Khz zwart 17
	}

	// Ticks
	TCCR1B |= (1 << WGM12);  // CTC mode
	TCCR1B |= (1 << CS12);   // Prescaler 256
	TIMSK1 |= (1 << OCIE1A); // Interrupt aanzetten
	OCR1A = 60;				 // Deze kan evt opgevoerd worden (gaat die sneller)

	// Interrupt instellen
	EICRA |= (1 << ISC00); // Interrupt aanzetten
	EIMSK |= (1 << INT0);  // Corroponderende pin voor de interrupt
	TCCR0A &= ~(1 << COM0A0);

	Reset();
}

void IR::Reset()
{
	// Stelt spelers in aan de hand van de modus
	if (mode == 1)
	{
		player1->posX = 9;
		player1->posY = 9;
		player1->playerNum = 2;
		player1->Start();

		player2->IRlastX = 1;
		player2->IRlastY = 1;
		player2->posY = 1;
		player2->posX = 1;
		player2->Start();
		player2->playerNum = 1;
	}
	else
	{
		player1->posX = 1;
		player1->posY = 1;
		player1->playerNum = 1;
		player1->Start();

		player2->IRlastX = 9;
		player2->IRlastY = 9;
		player2->posY = 9;
		player2->posX = 9;
		player2->playerNum = 2;
		player2->Start();
	}
}

void IR::loop()
{
	decodeReceive();
	setSend();
	SetPlayerLocation();
	SetBombLocation();
}

void IR::sendSeed()
{
	// Random number
	uint8_t i;
	uint8_t seed = rand() % 9; // Random nummer van 0 tot 9
	srand(seed);			   // Eigen Seed zetten
	if (seedSended)
	{
		while (i > 5)
		{

			dataSend = ((GAME << 4) + seed); // Versturen van data
			seedSended = true;				 // Afblocken dat die maar 1x mag sturen
			i++;
		}
	}
}

// Stuurt game over voor de toekomst
void IR::sendGameOver()
{
	uint8_t gameOverData = 14;
	dataSend = ((GAME << 4) + gameOverData); // Versturen van data
}

// Pakt de meest voorkomende bom locatie
void IR::SetBombLocation()
{
	uint8_t indexX = 0;
	uint8_t indexY = 0;

	uint8_t countX = 0;
	uint8_t countY = 0;

	uint8_t highestX = 0;
	uint8_t highestY = 0;

	uint8_t x1 = 0;
	uint8_t y1 = 0;

	uint8_t x2 = 0;
	uint8_t y2 = 0;

	for (uint8_t i = 0; i < 5; i++)
	{
		if (x1 == allBombLocX[i])
		{
			countX += 1;

			if (countX >= highestX)
			{
				x2 = allBombLocX[i];
				highestX = countX;
			}
		}
		else
		{
			countX = 1;
			x1 = allBombLocX[i];
		}

		if (y1 == allBombLocY[i])
		{
			countY += 1;

			if (countY >= highestY)
			{
				y2 = allBombLocY[i];
				highestY = countY;
			}
		}
		else
		{
			countY = 1;
			y1 = allBombLocY[i];
		}
	}

	if (player2->level->levelBomb[x2][y2] == 1)
	{
	}
	else
	{
		if (player2->IRlastX == x2 & player2->IRlastY == y2)
		{
			if (gameData)
				player2->level->AddBomb(x2, y2);
		}
	}
}

// Verantwoordelijk voor het pakken van de meest voorkomende locatie
void IR::SetPlayerLocation()
{
	uint8_t indexX = 0;
	uint8_t indexY = 0;

	uint8_t countX = 0;
	uint8_t countY = 0;

	uint8_t highestX = 0;
	uint8_t highestY = 0;

	uint8_t x1 = 0;
	uint8_t y1 = 0;

	uint8_t x2 = 0;
	uint8_t y2 = 0;

	for (uint8_t i = 0; i < 5; i++)
	{
		if (x1 == allLocationsPlayerX[i])
		{
			countX += 1;

			if (countX >= highestX)
			{
				x2 = allLocationsPlayerX[i];
				highestX = countX;
			}
		}
		else
		{
			countX = 1;
			x1 = allLocationsPlayerX[i];
		}

		if (y1 == allLocationsPlayerY[i])
		{
			countY += 1;

			if (countY >= highestY)
			{
				y2 = allLocationsPlayerY[i];
				highestY = countY;
			}
		}
		else
		{
			countY = 1;
			y1 = allLocationsPlayerY[i];
		}
	}

	if (FilterByte(x2, y2))
	{
		if (player2->IRlastX == x2 & player2->IRlastY == y2)
		{
		}
		else
		{
			if (gameData)
				player2->MoveIR(x2, y2);
		}
	}
}

void IR::FillBombLocationArrayx(uint8_t x)
{
	allBombLocX[countLocb] = x;
}

void IR::FillBombLocationArrayy(uint8_t y)
{
	allBombLocY[countLocb] = y;
}

void IR::FillLocationArrayx(uint8_t x)
{
	allLocationsPlayerX[countLoc] = x;
}

void IR::FillLocationArrayy(uint8_t y)
{
	allLocationsPlayerY[countLoc] = y;
}

void IR::setSend()
{
	sei(); // Inschakelen van interrupts voor versturen

	if (sendDataType == BOMB) // Wanneer er een bom moet overgestuurd worden
	//if (player1->placedBomb)// Wanneer er een bom moet overgestuurd worden
	{
		dataBombX = player1->lastBomb.posX;
		dataBombY = player1->lastBomb.posY;

		// Als x verstuurd moet worden
		if (setInstruction == X)
		{
			if (isFinished)
			{						// Als de overdracht al klaar is
				setInstruction = Y; // De volgende byte die verstuurd moet worden zal de x zijn
				isFinished = false; // Om de volgende byte te kunnen versturen moet isfinished op false gezet worden
			}
			else
			{ // Anders zet die de datsend
				if (mode == 1)
				{
					dataSend = ((INSTRUCTIONBOMBXZW << 4) + dataBombX); // Voor witte
				}
				else
				{
					dataSend = ((INSTRUCTIONBOMBX << 4) + dataBombX); // Voor witte
				}
				//dataSend = ((TESTX << 4) + dataBombX);// Voor zwarte
			}
		}
		else if (setInstruction == Y)
		{ // Wanneer de y moet worden verstuurd
			// Als de overdracht klaar is
			if (isFinished)
			{
				setInstruction = X;			 // Zet die de te versturen instructie op x
				player1->placedBomb = false; // de positie is doorgestuurd, dus wordt deze boolean op false gezet
				isFinished = false;			 // De volgende overdracht kan beginnen, hiervoor wordt isfinished weer op false gezet
				sendDataType = PLAYER;
				if (bombBuf == 10)
				{
					bombBuf = 0;
					player1->lastBomb.posX = 0;
					player1->lastBomb.posY = 0;
				}
				else
				{
					bombBuf += 1;
				}
			}
			else
			{ // Anders set die de datasend
				if (mode == 1)
				{
					dataSend = ((INSTRUCTIONBOMBYZW << 4) + dataBombY); // Voor witte
				}
				else
				{
					dataSend = ((INSTRUCTIONBOMBY << 4) + dataBombY); // Voor witte
																	  //dataSend = ((TESTY << 4) + dataBombY); // Voor zwarte
				}
			}
		}
	}
	else if(sendDataType == PLAYER)
	{
		//else if (player1->positionChanged) {
		dataX = player1->posX;
		dataY = player1->posY;

		// Als x verstuurd moet worden
		if (setInstruction == X)
		{
			if (isFinished)
			{						// Als de overdracht al klaar is
				setInstruction = Y; // De volgende byte die verstuurd moet worden zal de x zijn
				isFinished = false; // Om de volgende byte te kunnen versturen moet isfinished op false gezet worden
			}
			else
			{ // Anders zet die de datsend
				if (mode == 1)
				{ //wit
					dataSend = ((TESTX << 4) + dataX);
				}
				else
				{
					dataSend = ((INSTRUCTIONPLAYERX << 4) + dataX);
				}
			}
		}
		else if (setInstruction == Y)
		{ // Wanneer de y moet worden verstuurd
			// Als de overdracht klaar is
			if (isFinished)
			{
				setInstruction = X;				  // Zet die de te versturen instructie op x
				player1->positionChanged = false; // de positie is doorgestuurd, dus wordt deze boolean op false gezet
				isFinished = false;				  // De volgende overdracht kan beginnen, hiervoor wordt isfinished weer op false gezet
				sendDataType = BOMB;
			}
			else
			{ // Anders set die de datasend
				if (mode == 1)
				{ // wit
					dataSend = ((TESTY << 4) + dataY);
				}
				else
				{
					dataSend = ((INSTRUCTIONPLAYERY << 4) + dataY);
				}
			}
		}
	}
}

void IR::decodeReceive()
{
	cli(); // Uitschakelen van interrupts om data te verwerken
	if (dataReceived != NULL)
	{
		buffer++; // Carbage collector omdat die soms kots uitkraamt in begin
		if (buffer > carbageCounter)
		{
			byte instruction = (dataReceived >> 4 & MASK); // Shiften van Byte naar Nibble voor instructie
			byte data = (dataReceived & MASK);			   // Overige deel van byte is de data

			switch (instruction)
			{
			case GAME:
				// Seed
				if (data > 1 || 10 < data)
				{
					srand(data);
					seedSended = true;
				}
				if (data == 14)
				{ // Data 14 is einde game
					endGame = true;
				}
			// Instruction players voor wit
			case INSTRUCTIONPLAYERX:
				if (mode == 1)
				{
					if (data > 0 || data < 9)
					{
						x = data; // Controle of data binnen spel bevat (Carbage data)
					}
				}
				break;
			case INSTRUCTIONPLAYERY:
				if (mode == 1)
				{
					if (data > 0 || data < 9)
					{
						y = data; // Controle of data binnen spel bevat (Carbage data)
					}
				}
				break;

			// Instruction player zwart
			case TESTX:
				if (mode == 0)
				{
					if (data > 0 || data < 9)
					{
						x = data; // Controle of data binnen spel bevat (Carbage data)
					}
				}
				break;
			case TESTY:
				if (mode == 0)
				{
					if (data > 0 || data < 9)
					{
						y = data; // Controle of data binnen spel bevat (Carbage data)
					}
				}
				break;

			case INSTRUCTIONBOMBXZW:
				if (mode == 0)
				{
					if (data > 0 || data < 9)
					{
						irX = data; // Controle of data binnen spel bevat (Carbage data)
					}
				}
				break;

			case INSTRUCTIONBOMBYZW:
				if (mode == 0)
				{
					if (data > 0 || data < 9)
					{
						irY = data; // Controle of data binnen spel bevat (Carbage data)
					}
				}
				break;

			case INSTRUCTIONBOMBX:
				// X voor bom
				if (mode == 1)
				{
					if (data > 0 || data < 9)
					{
						irX = data; // Controle of data binnen spel bevat (Carbage data)
					}
				}
				break;
			case INSTRUCTIONBOMBY:
				// Y voor bom
				if (mode == 1)
				{
					if (data > 0 || data < 9)
					{
						irY = data; // Controle of data binnen spel bevat (Carbage data)
					}
				}
				break;
			default:
				// Foute data.
				break;
			}

			if (FilterByte(x, y))
			{
				if (countLoc == 4)
				{
					countLoc = 0;
					FillLocationArrayx(x);
					FillLocationArrayy(y);
				}
				else
				{
					countLoc += 1;
					FillLocationArrayx(x);
					FillLocationArrayy(y);
				}
			}

			if (irX > 0 & irY > 0 & irX < 10 & irY < 10)
			{

				if (countLocb == 4)
				{
					countLocb = 0;
				}
				else
				{
					countLocb += 1;
				}

				FillBombLocationArrayx(irX);
				FillBombLocationArrayy(irY);
			}
		}
	}
}

bool IR::FilterByte(uint8_t x, uint8_t y)
{
	if (!player1->level->CheckCollision(x, y))
	{
		uint8_t xDif = player2->IRlastX - x;
		uint8_t yDif = player2->IRlastY - y;

		if (x != 0 & y != 0)
		{
			if (x > 0 & y > 0 & x < 10 & y < 10)
			{
				return true;
			}
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

void IR::sendByte()
{
	if (bitSendTeller == 9)
	{ // Bit teller is hoger dan 9. Start cyclus opnieuw
		bitSendTeller = 0;
		isFinished = true;
		lastByte = dataSend; // 9e bit bereikt dus we starten opnieuw (9e bit is stopbit)
	}

	if (dataSend != lastByte)
	{											   // Alleen byte sturen als die nog niet geweest is
		bitSend = dataSend << (7 - bitSendTeller); // Zet hex om naar Bit voor versturen (Dmv shiften)
		bitSend = bitSend >> 7;					   // Shift bit goede kant op. (Zodat er 1 en 0 onstaan)
		if (tellerSend <= 1)
		{
			lastbitSend = bitSend; // Registreer lastbit zodat deze niet opnieuw gestuurd kan worden
			if ((TCCR0B & (1 << CS01) && TCCR0A & (1 << COM0A0)) || (dataSend < 128 && bitSendTeller == 9))
			{
				TCCR0B &= ~(1 << CS01);   // Uitzetten van Timer dmv Presacler
				TCCR0A &= ~(1 << COM0A0); // Uitzetten output van Timer (voor zekerheid)
				bitSendTeller++;		  // Bit teller omhoog voor volgende bit
			}
			else if (!(TCCR0B & (1 << CS01)) && !(TCCR0A & (1 << COM0A0)))
			{
				TCCR0B |= (1 << CS01);   // Aanzetten van Timer dmv Prescaler
				TCCR0A |= (1 << COM0A0); // Aanzetten van Timer dmv Poort
			}
		}
		if (tellerSend < 4 && lastbitSend == 1)
		{
			tellerSend++; // Controle of we klaar zijn
		}
		if (tellerSend >= 4 && lastbitSend == 1)
		{							  // Deze bit is al verstuurd. Dan beginnen we opnieuw
			tellerSend = 0;			  // Teller op 0
			TCCR0B &= ~(1 << CS01);   // Timer 1 uit zodat er niet verzonden kan worden
			TCCR0A &= ~(1 << COM0A0); // Timer 1 output uit
		}
	}
}

void IR::receiveHandler()
{
	bitReceive = (PIND & (1 << PIND2));

	if (!bitReceive)
	{
		if (tellerReceive == 2)
		{ // received 0
			dataReceived >>= 1;
		}
		else if (tellerReceive == 4)
		{						 // received 1
			dataReceived >>= 1;  // Write 1 on dataReceived
			dataReceived += 128; // Make place
		}
		else if (tellerReceive > 4)
		{ // stop
			dataReceived = 0;
		}
		tellerReceive = 0; // reset teller
	}
}
