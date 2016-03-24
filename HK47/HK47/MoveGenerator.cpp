#include "stdafx.h"
#include "MoveGenerator.h"


MoveGenerator::MoveGenerator()
{
}


MoveGenerator::~MoveGenerator()
{
}

void MoveGenerator::findMoves()
{
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


	//if(computerTurn)
	//check my tie fighters

	//check my X wings

	//else
	//check opponent tie fighters

	//check opponent X Wings




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
				tempLocation >> 9;
				locations += tempLocation;
			}

			hasLeftBoard = false;
			tempLocation = location;

			while (!hasLeftBoard)//towards the lower left
			{
				tempLocation >> 7;
				locations += tempLocation;
			}

			hasLeftBoard = false;
			tempLocation = location;

			while (!hasLeftBoard)//towards the upper left
			{
				tempLocation << 7;
				locations += tempLocation;
			}

			hasLeftBoard = false;
			tempLocation = location;

			while (!hasLeftBoard)//towards the upper right
			{
				tempLocation << 9;
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
				tempLocation << 8;
				locations += tempLocation;
			}

			hasLeftBoard = false;
			tempLocation = location;

			while (!hasLeftBoard)//down
			{
				tempLocation >> 8;
				locations += tempLocation;
			}

			hasLeftBoard = false;
			tempLocation = location;

			while (!hasLeftBoard)//left
			{
				tempLocation >> 1;
				locations += tempLocation;
			}

			hasLeftBoard = false;
			tempLocation = location;

			while (!hasLeftBoard)//right
			{
				tempLocation << 1;
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
