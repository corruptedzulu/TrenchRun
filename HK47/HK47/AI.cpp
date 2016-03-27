#include "stdafx.h"
#include "AI.h"


AI::AI()
{
}


AI::~AI()
{
}

void AI::setMoveGenerator(MoveGenerator mg)
{
	movegen = mg;
}



Move AI::determineComputerMove(vector<Move> moves, uint64_t board, uint32_t attr[])
{
	return minimax(moves, board, attr);
}

Move AI::minimax(vector<Move> moves, uint64_t board, uint32_t attr[])
{
	Move bestMove;
	int bestScore = -9999;

	for (int x = 0; x < moves.size(); x++)
	{
		makeMove(moves.front(), allPiecesBoard);

		int testedScore = minimaxMin(maxDepth);

		if (testedScore > bestScore)
		{
			bestScore = testedScore;
			bestMove = moves.front();
		}

		undoMove(allPiecesBoard);
		moves.erase(moves.begin());
	}

	return bestMove;

}

int AI::minimaxMin(int depth)
{
	int bestScore;
	if (gameOver())
	{
		if (humanWon)
		{
			return -999;
		}

		if (computerWon)
		{
			return 999;
		}

		return 0;
	}
	else if (depth == maxDepth)
	{
		return evaluateMove();
	}
	else
	{
		bestScore = 9999;

		vector<Move> moves = movegen.findMoves(allPiecesBoard, attr, false, false);

		for (int x = 0; x < moves.size(); x++)
		{
			makeMove(moves.front(), allPiecesBoard);

			int testedScore = minimaxMax(depth - 1);

			if (testedScore < bestScore)
			{
				bestScore = testedScore;
			}

			undoMove(allPiecesBoard);

		}

		return bestScore;
	}

}

int AI::minimaxMax(int depth)
{
	int bestScore = -9999;
	if (gameOver())
	{
		if (humanWon)
		{
			return -999;
		}

		if (computerWon)
		{
			return 999;
		}

		return 0;
	}
	else if (depth == maxDepth)
	{
		return evaluateMove();
	}
	else
	{
		bestScore = -9999;

		vector<Move> moves = movegen.findMoves(allPiecesBoard, attr, true, movedTieOnLastTurn);

		for (int x = 0; x < moves.size(); x++)
		{
			makeMove(moves.front(), allPiecesBoard);

			int testedScore = minimaxMin(depth - 1);

			if (testedScore < bestScore)
			{
				bestScore = testedScore;
			}

			undoMove(allPiecesBoard);

		}

		if (movedTieOnLastTurn)
		{
			movedTieOnLastTurn = false;
		}

		return bestScore;
	}

}

int AI::evaluateMove()
{

	return 0;
}

void AI::makeMove(Move move, uint64_t board)
{
	movesUnderAnalysis.push_back(move);

	board = board - move.getLocation();
	board = board + move.getDestination();

}

void AI::undoMove(uint64_t board)
{
	Move move = movesUnderAnalysis.back();
	movesUnderAnalysis.pop_back();

	board = board - move.getDestination();
	board = board + move.getLocation();

}

bool AI::gameOver()
{
	return false;
}
