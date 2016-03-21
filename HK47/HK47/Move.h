#pragma once

#include "BitBoard.h"

class Move
{
	uint64_t location;
	uint64_t destination;

	bool isBackwardsMovement;

	char locCol, locRow, destCol, destRow;

public:
	Move();
	Move(uint64_t l);
	~Move();

	void moveToLocation(uint64_t d);
	void moveToLocation(char row, char col);

	uint64_t convertRowColToBitBoard(char row, char col);
	char convertOpponentViewToMyViewRow(char row);
	char convertOpponentViewToMyViewCol(char col);

};

