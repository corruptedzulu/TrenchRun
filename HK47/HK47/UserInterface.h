#pragma once

#include "Move.h"

#define RESET           0
#define BRIGHT          1
#define DIM             2
#define UNDERLINE       3
#define BLINK           4
#define REVERSE         7
#define HIDDEN          8
#define BLACK           0
#define RED             1
#define GREEN           2
#define YELLOW          3
#define BLUE            4
#define MAGENTA         5
#define CYAN            6
#define WHITE           7

class UserInterface
{

private:

	// to use the attributes, extract them by turning off the other bits
	// (AND these masks with a copy of the attribute row)
	// flags to do so are:
	uint32_t columnOne = 0xF0000000; // 11110000000000000000000000000000;
	uint32_t columnTwo = 0x0F000000; // 00001111000000000000000000000000;
	uint32_t columnThree = 0x00F00000; // 00000000111100000000000000000000;
	uint32_t columnFour = 0x000F0000; // 00000000000011110000000000000000;
	uint32_t columnFive = 0x0000F000; // 00000000000000001111000000000000;
	uint32_t columnSix = 0x00000F00; // 00000000000000000000111100000000;
	uint32_t columnSeven = 0x000000F0; // 00000000000000000000000011110000;
	uint32_t columnEight = 0x0000000F; // 00000000000000000000000000001111;

public:
	UserInterface();
	~UserInterface();

	void printBoard(uint64_t board, uint32_t pieces[]);
	void printComputerMove(Move compMove);
	void printMakeMoveRequest();


	Move getNextMove();
	bool askWhichPlayerStarts();
	
	void printOpeningMessage();
	void printPlayerVictory();
	void printComputerVictory();
	void printTie();

	void printIllegalMove();

	void textColor(int attr, int fg, int bg);

	uint32_t getAttributesOfColumnForRow(uint32_t attributes, int index);
	char getCharacterForAttributeNumber(int number);
	int getColorForAttributeNumber(int number);
};

