#include "stdafx.h"
#include "BitBoard.h"







BitBoard::BitBoard()
{

}

BitBoard::BitBoard(string t)
{
	type = t;
}

BitBoard::BitBoard(string n, string t, bool isComp, char row, char col)
{
	type = t;
	name = n;
	isComputerPiece = isComp;
	setBoard(convertRowColToBitBoard(row, col));
}


BitBoard::~BitBoard()
{

}


uint64_t BitBoard::getBoard()
{
	return board;
}

void BitBoard::setBoard(uint64_t b)
{
	board = b;
}

string BitBoard::getType()
{
	return type;
}

string BitBoard::getName()
{
	return name;
}


uint64_t BitBoard::convertRowColToBitBoard(char row, char col)
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

char BitBoard::convertOpponentViewToMyViewRow(char row)
{
	return 0;
}

char BitBoard::convertOpponentViewToMyViewCol(char col)
{
	return 0;
}

bool BitBoard::getIsComputerPiece()
{
	return isComputerPiece;
}