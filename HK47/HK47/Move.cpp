#include "stdafx.h"
#include "Move.h"


Move::Move()
{
}

Move::Move(uint64_t l)
{
}


Move::~Move()
{
}

void Move::moveToLocation(uint64_t d)
{
}

uint64_t Move::convertRowColToBitBoard(char row, char col)
{
	uint64_t thisLoc = 1;

	//these are the bit offsets we're going to use
	//the row is counted numerically, so subtract 49.
	//NOTE: we use 49 (aka 1) because the rows are not zero-indexed when described by RC format
	//multiply by 8 to account for the length of the row
	int rowIncrement = (row - 49) * 8; // times 8

	//column, just subtract 65
	int columnIncrement = col - 65;


	thisLoc << rowIncrement;
	thisLoc << columnIncrement;

	return uint64_t();
}

char Move::convertOpponentViewToMyViewRow(char row)
{
	return 0;
}

char Move::convertOpponentViewToMyViewCol(char col)
{
	return 0;
}
