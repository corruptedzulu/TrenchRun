#pragma once

#include "BitBoard.h"
#include <vector>

class MoveGenerator
{
public:
	MoveGenerator();
	~MoveGenerator();

	void findMoves();


	void findMovesForPiece(BitBoard piece);
	void comparePossibleMovesWithBoard(BitBoard piece, BitBoard otherPieces);
};

