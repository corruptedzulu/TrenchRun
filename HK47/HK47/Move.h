#pragma once

#include "BitBoard.h"
#include <ctype.h>

class Move
{
	uint64_t location;
	uint64_t destination;

	bool isBackwardsMovement;
	bool isCapture;

	char locCol, locRow, destCol, destRow;

public:
	Move();
	Move(uint64_t l);
	~Move();

	void setStartLocation(uint64_t start);
	void setDestinationLocation(uint64_t dest);
	void setIsBackwardsMovement(bool back);
	void setIsCapture(bool isCap);

	uint64_t getLocation();
	uint64_t getDestination();

	void moveToLocation(uint64_t d);
	void moveToLocation(char row, char col);

	uint64_t convertColRowToBitBoard(char col, char row);
	char convertOpponentViewToMyViewRow(char row);
	char convertOpponentViewToMyViewCol(char col);


};

