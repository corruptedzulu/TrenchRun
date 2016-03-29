#pragma once

#include "BitBoard.h"
#include "Move.h"
#include <vector>

class MoveGenerator
{
private:

	char swneDiagonal[8] = {static_cast<char>(128), static_cast<char>(64), static_cast<char>(32), static_cast<char>(16), static_cast<char>(8), static_cast<char>(4), static_cast<char>(2), static_cast<char>(1)};
	char senwDiagonal[8] = {static_cast<char>(1), static_cast<char>(2), static_cast<char>(4), static_cast<char>(8), static_cast<char>(16), static_cast<char>(32), static_cast<char>(64), static_cast<char>(128)};

	//char swneDiagonal[8] = { '128' - '0', '64' - '0', '32' - '0', '16' - '0', '8' - '0', '4' - '0', '2' - '0', '1' - '0' };
	//char senwDiagonal[8] = { '1' - '0', '2' - '0', '4' - '0', '8' - '0', '16' - '0', '32' - '0', '64' - '0', '128' - '0' };


public:
	MoveGenerator();
	~MoveGenerator();

	vector<Move> findMoves(uint64_t pieces, uint32_t attr[], bool computersTurn, bool tieFighterMovedInLastTurn);


	void findMovesForPiece(BitBoard piece);
	void comparePossibleMovesWithBoard(BitBoard piece, BitBoard otherPieces);

	int getNibbleFromIndicatedPosition(uint32_t bits, int index);
	char* adjustDiagonalForPieceLocation(uint64_t loc, bool swnediag);
};

