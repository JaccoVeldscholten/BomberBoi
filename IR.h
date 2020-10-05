#pragma once
#include "Player.h"
#include "Startscherm.h"

// Game instructions
#define GAME 0b0010  // Game Instructions
#define TESTX 0b0011 // Game Host (master of slave verhouding adress)
#define TESTY 0b0100 // Seed. Deze moet meerder keren overgestuurd gaan worden!!!!!!!!!!

// Player instructions
#define INSTRUCTIONPLAYERX 0b0101 // Player X adress
#define INSTRUCTIONPLAYERY 0b0110 // Player Y adress

// Bomb instructions
#define INSTRUCTIONBOMBX 0b0111   // Bomb X adress
#define INSTRUCTIONBOMBY 0b1000   // Bomb Y adress
#define INSTRUCTIONBOMBXZW 0b1100 // BOMB adress van de zwarte
#define INSTRUCTIONBOMBYZW 0b1110 // BOMB adress van de zwarte

// Overige benodigheden
#define MASK 0b1111		 // Mask voor shiften
#define carbageCounter 0 // In situaties dat er stoorsignalen optreden counter ophogen

enum SetInstruction
{
	X,
	Y
};
enum SendDataType
{
	PLAYER,
	BOMB
};
class IR
{
public:
	IR(Player &_player1, Player &_player2);
	void Init();

	void loop();

	void setSend();
	void decodeReceive();

	void sendByte();
	void receiveHandler();

	void sendSeed();
	void sendGameOver();

	void Reset();

	volatile uint8_t tellerReceive = 0;

	// Data
	int data = 0;
	volatile uint8_t x = 0; // Honkie tonkie
	volatile uint8_t y = 0; // Miss honkt deze wel

	// Receiving Vars
	volatile uint8_t bitReceive = 0;   // high (4) = data, low (0) is pause
	volatile uint8_t dataReceived = 0; // byte which has been received
	volatile bool seedSended = false;
	volatile bool endGame = false;
	volatile uint8_t seed = 0;
	bool gameData = false;

	void SetBombLocation();
	void SetPlayerLocation();

private:
	Player *player1;
	Player *player2;

	bool FilterByte(uint8_t x, uint8_t y);

	SetInstruction setInstruction;
	SendDataType sendDataType = PLAYER;

	// Locatie arrays
	uint8_t allLocationsPlayerX[5];
	uint8_t allLocationsPlayerY[5];
	uint8_t allBombLocX[5];
	uint8_t allBombLocY[5];

	void FillLocationArrayx(uint8_t x);
	void FillLocationArrayy(uint8_t y);

	void FillBombLocationArrayx(uint8_t x);
	void FillBombLocationArrayy(uint8_t y);

	// Voor versturen

	volatile uint8_t buffer = 0; // Buffer for the honk
	volatile uint8_t bombBuf = 0;

	volatile uint8_t countLoc = 0;
	volatile uint8_t countLocb = 0;

	// Voor zenden
	volatile uint8_t dataX = 0;		// DataX voor zenden
	volatile uint8_t dataY = 0;		// DataY voor zenden
	volatile uint8_t dataBombX = 0; // Idem voor bom
	volatile uint8_t dataBombY = 0; // Bodm
	volatile uint8_t irX = 0;
	volatile uint8_t irY = 0;

	volatile uint8_t mode = 0; // 0 for Zwart  1 for WIT.

	// Sending Vars
	volatile uint8_t tellerSend = 0;
	volatile byte dataSend = 0; // <--- Mag ook int zijn idk of dat verschil maakt maar denk nie
	volatile uint8_t bitSend = 0;
	volatile uint8_t lastbitSend = 0;
	volatile uint8_t lastByte = 0;
	volatile uint8_t bitSendTeller = 0;

	bool isFinished; // Om te checken of het verzenden klaar is van een instructie
};
