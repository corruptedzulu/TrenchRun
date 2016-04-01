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



Move AI::determineComputerMove(vector<Move> moves, uint64_t board, uint32_t argattr[], bool computerDidMoveTIESideways, bool playerDidMoveTIESideaways)
{
	movedTieOnLastTurn = computerDidMoveTIESideways;
	opponentMovedTieOnLastTurn = playerDidMoveTIESideaways;
	allPiecesBoard = board;
	attr = argattr;


	return minimax(moves, board, attr);
}

Move AI::minimax(vector<Move> moves, uint64_t board, uint32_t attr[])
{
	Move bestMove;
	int bestScore = -9999;
	bool madeTieMove = false;
	int alpha = -9999;
	int beta = 9999;

	for (int x = 0; x < moves.size(); x++)
	{

		//check if this moves a TIE sideways
		uint64_t rowLoc = moves.at(x).getLocation();
		uint64_t rowDes = moves.at(x).getDestination();

		rowLoc = (int)(log2(rowLoc));
		rowDes = (int)(log2(rowDes));

		rowLoc = rowLoc / 8;
		rowDes = rowDes / 8;


		//if these are on the same row, then it is a sideways move
		if (rowLoc == rowDes)
		{
			madeTieMove = true;
			movedTieOnLastTurn = true;
		}



		uint32_t replaced = makeMove(moves.at(x), allPiecesBoard, attr);

		int testedScore = minimaxMin(0, attr, alpha, beta);

		if (testedScore > bestScore)
		{
			bestScore = testedScore;
			bestMove = moves.at(x);
		}

		undoMove(allPiecesBoard, attr, replaced);

		//if moved TIE sideways, undo
		if (madeTieMove)
		{
			movedTieOnLastTurn = false;
			madeTieMove = false;
		}

		//moves.erase(moves.begin());
	}

	return bestMove;

}

int AI::minimaxMin(int depth, uint32_t attr[], int a, int b)
{
	int alpha = a;
	int beta = b;
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
	else if (depth == MAX_DEPTH)
	{
		return evaluateMove(allPiecesBoard, attr);
	}
	else
	{
		bestScore = beta;
		bool changedTieState = false;
		bool madeTieMove = false;
		vector<Move> moves;

		if (opponentMovedTieOnLastTurn)
		{
			moves = movegen.findMoves(allPiecesBoard, attr, false, opponentMovedTieOnLastTurn);

			opponentMovedTieOnLastTurn = false;
			changedTieState = true;
		}
		else
		{
			moves = movegen.findMoves(allPiecesBoard, attr, false, opponentMovedTieOnLastTurn);
		}
		
		//vector<Move> moves = movegen.findMoves(allPiecesBoard, attr, false, opponentMovedTieOnLastTurn);

		for (int x = 0; x < moves.size(); x++)
		{

			//check if this moves a TIE sideways
			uint64_t rowLoc = moves.at(x).getLocation();
			uint64_t rowDes = moves.at(x).getDestination();

			rowLoc = (int)(log2(rowLoc));
			rowDes = (int)(log2(rowDes));

			rowLoc = rowLoc / 8;
			rowDes = rowDes / 8;


			//if these are on the same row, then it is a sideways move
			if (rowLoc == rowDes)
			{
				madeTieMove = true;
				opponentMovedTieOnLastTurn = true;
			}


			uint32_t replaced = makeMove(moves.at(x), allPiecesBoard, attr);

			int testedScore = minimaxMax(depth + 1, attr, alpha, beta);
			
			if (testedScore < beta)
			{
				beta = testedScore;
			}

			
			

			if (testedScore < bestScore)
			{
				bestScore = testedScore;
			}

			undoMove(allPiecesBoard, attr, replaced);

			//if moved TIE sideways, undo
			if (madeTieMove)
			{
				opponentMovedTieOnLastTurn = false;
				madeTieMove = false;
			}

			if (beta <= alpha)
			{
				break;
				//return beta;
			}

		}

		return beta;
		//return bestScore;
	}

}

int AI::minimaxMax(int depth, uint32_t attr[], int a, int b)
{
	int alpha = a;
	int beta = b;
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
	else if (depth == MAX_DEPTH)
	{
		return evaluateMove(allPiecesBoard, attr);
	}
	else
	{
		bestScore = alpha;
		bool changedTieState = false;
		bool madeTieMove = false;
		vector<Move> moves;


		if (movedTieOnLastTurn)
		{
			moves = movegen.findMoves(allPiecesBoard, attr, true, movedTieOnLastTurn);

			movedTieOnLastTurn = false;
			changedTieState = true;
		}
		else
		{
			moves = movegen.findMoves(allPiecesBoard, attr, true, movedTieOnLastTurn);
		}


		for (int x = 0; x < moves.size(); x++)
		{
			//check if this moves a TIE sideways
			uint64_t rowLoc = moves.at(x).getLocation();
			uint64_t rowDes = moves.at(x).getDestination();

			rowLoc = (int)(log2(rowLoc));
			rowDes = (int)(log2(rowDes));

			rowLoc = rowLoc / 8;
			rowDes = rowDes / 8;


			//if these are on the same row, then it is a sideways move
			if ( rowLoc == rowDes )
			{
				madeTieMove = true;
				movedTieOnLastTurn = true;
			}

			uint32_t replaced = makeMove(moves.at(x), allPiecesBoard, attr);

			int testedScore = minimaxMin(depth + 1, attr, alpha, beta);

			if (testedScore > alpha)
			{
				alpha = testedScore;
			}

			

			if (testedScore > bestScore)
			{
				bestScore = testedScore;
			}

			undoMove(allPiecesBoard, attr, replaced);

			//if moved TIE sideways, undo
			if (madeTieMove)
			{
				movedTieOnLastTurn = false;
				madeTieMove = false;
			}


			if (beta <= alpha)
			{
				break;
				//return alpha;
			}

		}

		if (changedTieState)
		{
			changedTieState = false;
			movedTieOnLastTurn = true;
		}

		return alpha;
		//return bestScore;
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

	int score = 0;


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

	allPiecesBoard = allPiecesBoard - move.getLocation();
	allPiecesBoard = allPiecesBoard + move.getDestination();
	
	int colLoc = (int)(log2(move.getLocation())) % 8;
	int rowLoc = (int)(log2(move.getLocation())) / 8;

	int colDes = (int)(log2(move.getDestination())) % 8;
	int rowDes = (int)(log2(move.getDestination())) / 8;

	//set a mask to the desired place for the column
	uint32_t mask = 0xF0000000 >> (colLoc * 4);

	//now, get the number from the column on its own
	uint32_t value = mask & attr[rowLoc];

	//remove the value from the current row
	attr[rowLoc] = attr[rowLoc] - value;

	if (colDes < colLoc)
	{
		value = value << ((colLoc - colDes) * 4);
	}
	else
	{
		value = value >> ((colDes - colLoc) * 4);
	}

	//set a mask to the desired place for the column where we're putting
	uint32_t destMask = 0xF0000000 >> (colDes * 4);

	
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

	allPiecesBoard = allPiecesBoard - move.getDestination();
	allPiecesBoard = allPiecesBoard + move.getLocation();



	int colLoc = (int)(log2(move.getLocation())) % 8;
	int rowLoc = (int)(log2(move.getLocation())) / 8;

	int colDes = (int)(log2(move.getDestination())) % 8;
	int rowDes = (int)(log2(move.getDestination())) / 8;



	//set a mask to the desired place for the column where we're putting
	uint32_t destMask = 0xF0000000 >> (colDes * 4);

	//now, get the number from the column on its own
	uint32_t destValue = destMask & attr[rowDes];

	//remove the value from the current row
	attr[rowDes] = attr[rowDes] - destValue;

	//now, put the value we took out back in
	attr[rowDes] = attr[rowDes] + replacedValue;


	if (colDes < colLoc)
	{
		destValue = destValue >> ((colLoc - colDes) * 4);
	}
	else
	{
		destValue = destValue << ((colDes - colLoc) * 4);
	}

	//set a mask to the desired place for the column
	uint32_t mask = 0xF0000000 >> (colLoc * 4);

	//now, get the number from the column on its own
	uint32_t value = mask & attr[rowLoc];

	//remove the value from the current row
	attr[rowLoc] = attr[rowLoc] - value;

	attr[rowLoc] = attr[rowLoc] + destValue;


	
	//we've removed the place we're going to from the attributes, so now we add our move's attributes to there
	//attr[rowDes] = attr[rowDes] + destValue;


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
	bits = bits >> ((8 - (index + 1)) * 4);

	return bits;

}