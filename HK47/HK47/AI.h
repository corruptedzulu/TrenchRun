#pragma once

#include "Move.h"
#include "MoveGenerator.h"
#include <stdint.h>
#include <vector>
#include "utils.h"


#define MAX_DEPTH 8

class AI
{
private:
	MoveGenerator movegen;


	//int maxDepth = 5;
	//bool gameOver = false;
	bool humanWon;
	bool computerWon;
	bool drawWon;

	bool movedTieOnLastTurn;
	bool opponentMovedTieOnLastTurn;

	vector<Move> movesUnderAnalysis;
	uint64_t allPiecesBoard;
	uint32_t *attr;// [8];


public:
	AI();
	~AI();


	void setMoveGenerator(MoveGenerator mg);


	Move determineComputerMove(vector<Move> moves, uint64_t board, uint32_t attr[], bool computerDidMoveTIESideways, bool playerDidMoveTIESideaways);

	Move minimax(vector<Move> moves, uint64_t board, uint32_t attr[]);
	int minimaxMax(int depth, uint32_t attr[], int alpha, int beta);
	int minimaxMin(int depth, uint32_t attr[], int alpha, int beta);

	int evaluateMove(uint64_t allPieces, uint32_t attr[]);
	uint32_t makeMove(Move move, uint64_t board, uint32_t attr[]);
	void undoMove(uint64_t board, uint32_t attr[], uint32_t replacedValue);

	bool gameOver();

	int getNibbleFromIndicatedPosition(uint32_t bits, int index);

};

