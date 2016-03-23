#include "stdafx.h"
#include "AI.h"


AI::AI()
{
}


AI::~AI()
{
}

int maxDepth = 5;
bool gameOver = false;
bool humanWon = false;
bool computerWon = false;
bool drawWon = false;




void AI::minimax()
{
	Move bestMove;
	int bestScore = -9999;

	for (int x = 0; x < legalMoves.size(); x++)
	{

	}

}

int AI::minimaxMin(int depth)
{
	if (gameOver)
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

	}

}

int AI::minimaxMax(int depth)
{
	int bestScore = -9999;
	if (gameOver)
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
		for (int x = 0; x < computerMoves.size(); x++)
		{

		}

		return bestScore;
	}

}
