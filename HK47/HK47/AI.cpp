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
		uint32_t replaced = makeMove(moves.front(), allPiecesBoard, attr);

		int testedScore = minimaxMin(maxDepth, attr);

		if (testedScore > bestScore)
		{
			bestScore = testedScore;
			bestMove = moves.front();
		}

		undoMove(allPiecesBoard, attr, replaced);
		moves.erase(moves.begin());
	}

	return bestMove;

}

int AI::minimaxMin(int depth, uint32_t attr[])
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
		return evaluateMove(allPiecesBoard, attr);
	}
	else
	{
		bestScore = 9999;

		vector<Move> moves = movegen.findMoves(allPiecesBoard, attr, false, false);

		for (int x = 0; x < moves.size(); x++)
		{
			uint32_t replaced = makeMove(moves.front(), allPiecesBoard, attr);

			int testedScore = minimaxMax(depth - 1, attr);

			if (testedScore < bestScore)
			{
				bestScore = testedScore;
			}

			undoMove(allPiecesBoard, attr, replaced);

		}

		return bestScore;
	}

}

int AI::minimaxMax(int depth, uint32_t attr[])
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
		return evaluateMove(allPiecesBoard, attr);
	}
	else
	{
		bestScore = -9999;

		vector<Move> moves = movegen.findMoves(allPiecesBoard, attr, true, movedTieOnLastTurn);

		for (int x = 0; x < moves.size(); x++)
		{
			uint32_t replaced = makeMove(moves.front(), allPiecesBoard, attr);

			int testedScore = minimaxMin(depth - 1, attr);

			if (testedScore < bestScore)
			{
				bestScore = testedScore;
			}

			undoMove(allPiecesBoard, attr, replaced);

		}

		if (movedTieOnLastTurn)
		{
			movedTieOnLastTurn = false;
		}

		return bestScore;
	}

}

int AI::evaluateMove(uint64_t allPieces, uint32_t attr[])
{

	/*
	Empty square					  - 0
	Forbidden Square				  - 15

	My Pieces
	Death Star						  - 1
	Wall							  - 2
	TIE Fighter						  - 3
	X Wing							  - 4
	X Wing (non Death Star intercept) - 5


	Opponent Pieces
	Death Star						  - 6
	Wall							  - 7
	TIE Fighter						  - 8
	X Wing							  - 9
	X Wing (non Death Star intercept) - 10
	*/
	int pieceType;

	signed int score = 0;


	//evaluate number of pieces each side has
	for (int x = 0; x < 8; x++)// 8 rows
	{
		for (int y = 0; y < 8; y++)
		{
			pieceType = getNibbleFromIndicatedPosition(attr[x], y);
			
			if (pieceType > 0 && pieceType < 6 && pieceType != 2)
			{
				score++;
			}

			if (pieceType > 5 && pieceType < 11 && pieceType != 7)
			{
				score--;
			}

		}

	}


	return score;
}

uint32_t AI::makeMove(Move move, uint64_t board, uint32_t attr[])
{
	movesUnderAnalysis.push_back(move);

	board = board - move.getLocation();
	board = board + move.getDestination();
	
	int rowLoc = move.getLocation() % 8;
	int colLoc = move.getLocation() / 8;

	int rowDes = move.getDestination() % 8;
	int colDes = move.getDestination() / 8; 

	//set a mask to the desired place for the column
	uint32_t mask = 0xF0000000 >> colLoc;

	//now, get the number from the column on its own
	uint32_t value = mask & attr[rowLoc];

	//remove the value from the current row
	attr[rowLoc] = attr[rowLoc] - value;



	//set a mask to the desired place for the column where we're putting
	uint32_t destMask = 0xF0000000 >> colDes;

	//now, get the number from the column on its own
	uint32_t destValue = destMask & attr[rowDes];

	//remove the value from the current row
	attr[rowDes] = attr[rowDes] - destValue;



	//we've removed the place we're going to from the attributes, so now we add our move's attributes to there
	attr[rowDes] = attr[rowDes] + value;

	return destValue;

}

void AI::undoMove(uint64_t board, uint32_t attr[], uint32_t replacedValue)
{
	Move move = movesUnderAnalysis.back();
	movesUnderAnalysis.pop_back();

	board = board - move.getDestination();
	board = board + move.getLocation();



	int rowLoc = move.getLocation() % 8;
	int colLoc = move.getLocation() / 8;

	int rowDes = move.getDestination() % 8;
	int colDes = move.getDestination() / 8;



	//set a mask to the desired place for the column where we're putting
	uint32_t destMask = 0xF0000000 >> colDes;

	//now, get the number from the column on its own
	uint32_t destValue = destMask & attr[rowDes];

	//remove the value from the current row
	attr[rowDes] = attr[rowDes] - destValue;

	//now, put the value we took out back in
	attr[rowDes] = attr[rowDes] + replacedValue;



	//set a mask to the desired place for the column
	//uint32_t mask = 0xF0000000 >> colLoc;

	//now, get the number from the column on its own
	//uint32_t value = mask & attr[rowLoc];

	//remove the value from the current row
	//attr[rowLoc] = attr[rowLoc] - value;


	
	//we've removed the place we're going to from the attributes, so now we add our move's attributes to there
	attr[rowDes] = attr[rowDes] + destValue;


}

bool AI::gameOver()
{
	return false;
}


int AI::getNibbleFromIndicatedPosition(uint32_t bits, int index)
{
	//char val;
	uint32_t mask = 0xF0000000;

	//shift the mask as far over as needed to match the index 
	mask = mask >> ((index)* 4);

	//AND the input with the mask to remove the other stuff
	bits = bits & mask;

	//shift those bits to be least significant
	//we add one to make sure we're shifting enough (because our parameter is passed as ZERO-index)
	bits = bits >> ((8 - index + 1) * 4);

	return bits;

}