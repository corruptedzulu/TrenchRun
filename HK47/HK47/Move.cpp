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

void Move::setStartLocation(uint64_t start)
{
	location = start;
}

void Move::setDestinationLocation(uint64_t dest)
{
	destination = dest;
}
void Move::setIsBackwardsMovement(bool back)
{
	isBackwardsMovement = back;
}

void Move::setIsCapture(bool isCap)
{
	isCapture = isCap;
}

uint64_t Move::getLocation()
{
	return location;
}

uint64_t Move::getDestination()
{
	return destination;
}

void Move::moveToLocation(uint64_t d)
{
	//if (location - )
}

void Move::moveToLocation(char row, char col)
{
}

uint64_t Move::convertColRowToBitBoard(char col, char row)
{
	uint64_t thisLoc = (uint64_t)1;

	//these are the bit offsets we're going to use
	//the row is counted numerically, so subtract 49.
	//NOTE: we use 49 (aka 1) because the rows are not zero-indexed when described by RC format
	//multiply by 8 to account for the length of the row
	int rowIncrement = (toupper(row) - 49) * 8; // times 8

	//column, just subtract 65
	int columnIncrement = toupper(col) - 65;


	thisLoc = thisLoc << rowIncrement;
	thisLoc = thisLoc << columnIncrement;

	return thisLoc;
}

char Move::convertOpponentViewToMyViewRow(char row)
{
	return 0;
}

char Move::convertOpponentViewToMyViewCol(char col)
{
	return 0;
}

bool operator==(Move & lhs, Move & rhs)
{

	return lhs.getDestination() == rhs.getDestination() && lhs.getLocation() == rhs.getLocation();
}
