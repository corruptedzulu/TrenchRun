#pragma once

#include "Move.h"
#include "MoveGenerator.h"
#include <vector>

class AI
{
private:
	MoveGenerator movegen;


	int maxDepth = 5;
	//bool gameOver = false;
	bool humanWon = false;
	bool computerWon = false;
	bool drawWon = false;

	bool movedTieOnLastTurn = false;
	bool opponentMovedTieOnLastTurn = false;

	vector<Move> movesUnderAnalysis;
	uint64_t allPiecesBoard;
	uint32_t attr[8];


public:
	AI();
	~AI();


	void setMoveGenerator(MoveGenerator mg);


	Move determineComputerMove(vector<Move> moves, uint64_t board, uint32_t attr[]);

	Move minimax(vector<Move> moves, uint64_t board, uint32_t attr[]);
	int minimaxMax(int depth);
	int minimaxMin(int depth);

	int evaluateMove();
	void makeMove(Move move, uint64_t board);
	void undoMove(uint64_t board);

	bool gameOver();
};

