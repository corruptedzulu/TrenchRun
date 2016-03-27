#include "stdafx.h"
#include "MoveGenerator.h"


MoveGenerator::MoveGenerator()
{
}


MoveGenerator::~MoveGenerator()
{
}


// Purpose: take the current board state and the attributes and determine all of the moves that
// the indicated player can take
// accept: the current board state, board attributes, and who is playing this turn
// return: vector of Move objects for each legal move
vector<Move> MoveGenerator::findMoves(uint64_t pieces, uint32_t attr[], bool computersTurn, bool tieFighterMovedInLastTurn)
{
	

	vector<Move> movesAvailable;

	//move types
	
	//tie fighter
	//forward
		//move all
	//left
	//right
	//backward for capture
	
	//x wing
	//forward right
	//forward left
	//backward left for capture
	//backward right for capture

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


	if (computersTurn)
	{
		//look at the attributes of each row
		char pieceType;
		for (int x = 0; x < 8; x++)// 8 rows
		{
			for (int y = 0; y < 8; y++)
			{
				pieceType = getNibbleFromIndicatedPosition(attr[x], y);

				switch (pieceType)
				{
				case 3:
					//TIE Fighter
					if (!tieFighterMovedInLastTurn)//did the TIE move last turn? if not, go ahead and check it this turn
					{

					}

					break;
				case 4:
					//X Wing (CAN attack Death Star)

					uint64_t locationsToMoveTo;
					locationsToMoveTo = *adjustDiagonalForPieceLocation(pieces, true);
					locationsToMoveTo += *adjustDiagonalForPieceLocation(pieces, false);



					break;
				case 5:
					//X Wing (CAN NOT attack Death Star)

					break;
				}

			}
		}
	}
	else
	{

	}
	//if(computerTurn)
	//check my tie fighters

	//check my X wings

	//else
	//check opponent tie fighters

	//check opponent X Wings



	return movesAvailable;
}

char MoveGenerator::getNibbleFromIndicatedPosition(uint32_t bits, int index)
{
	//char val;
	uint32_t mask = 0xF0000000;

	//shift the mask as far over as needed to match the index 
	mask = mask >> ((index) * 4);

	//AND the input with the mask to remove the other stuff
	bits = bits & mask;

	//shift those bits to be least significant
	//we add one to make sure we're shifting enough (because our parameter is passed as ZERO-index)
	bits = bits >> ((8 - index + 1) * 4);
	
	return bits;

}

char* MoveGenerator::adjustDiagonalForPieceLocation(uint64_t loc, bool swnediag)
{
	char answer[8];

	//int rowShift = loc / 8;
	
	//loc = loc << (rowShift * 8);
	
	//
	int columnShift = loc % 8;

	if (swnediag)//right shifts >>
	{
		for (int x = 0; x < 8; x++)
		{
			answer[x] = swneDiagonal[x] >> columnShift;
		}
	}
	else // left shifts <<
	{
		for (int x = 0; x < 8; x++)
		{
			answer[x] = swneDiagonal[x] << columnShift;
		}
	}
	
	return answer;
}

void MoveGenerator::findMovesForPiece(BitBoard piece)
{
	string type = piece.getType();
	string name = piece.getName();
	bool computerPiece = piece.getIsComputerPiece();

	if (type == "X Wing")
	{
		if (computerPiece)
		{
			//determine all of the places the piece could move to, based on it's location
			uint64_t location = piece.getBoard();
			uint64_t tempLocation = location;
			uint64_t locations = 0;
			bool hasLeftBoard = false;

			while (!hasLeftBoard)//towards the lower right
			{
				//tempLocation = location;
				tempLocation = tempLocation >> 9;
				locations += tempLocation;
			}

			hasLeftBoard = false;
			tempLocation = location;

			while (!hasLeftBoard)//towards the lower left
			{
				tempLocation = tempLocation >> 7;
				locations += tempLocation;
			}

			hasLeftBoard = false;
			tempLocation = location;

			while (!hasLeftBoard)//towards the upper left
			{
				tempLocation = tempLocation << 7;
				locations += tempLocation;
			}

			hasLeftBoard = false;
			tempLocation = location;

			while (!hasLeftBoard)//towards the upper right
			{
				tempLocation = tempLocation << 9;
				locations += tempLocation;
			}

		}
		else
		{

		}
	}
	else if(type == "TIE Fighter")
	{
		if (computerPiece)
		{
			//determine all of the places the piece could move to, based on it's location
			uint64_t location = piece.getBoard();
			uint64_t tempLocation = location;
			uint64_t locations = 0;
			bool hasLeftBoard = false;

			while (!hasLeftBoard)//up
			{
				//tempLocation = location;
				tempLocation = tempLocation << 8;
				locations += tempLocation;
			}

			hasLeftBoard = false;
			tempLocation = location;

			while (!hasLeftBoard)//down
			{
				tempLocation = tempLocation >> 8;
				locations += tempLocation;
			}

			hasLeftBoard = false;
			tempLocation = location;

			while (!hasLeftBoard)//left
			{
				tempLocation = tempLocation >> 1;
				locations += tempLocation;
			}

			hasLeftBoard = false;
			tempLocation = location;

			while (!hasLeftBoard)//right
			{
				tempLocation = tempLocation << 1;
				locations += tempLocation;
			}


		}
		else
		{

		}
	}
	else
	{

	}

}

void MoveGenerator::comparePossibleMovesWithBoard(BitBoard piece, BitBoard otherPieces)
{
	//take the piece (and all of it's possible moves
	//compare with the board to find all of the valid moves

}
