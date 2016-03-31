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
vector<Move> MoveGenerator::findMoves(uint64_t pieces, uint32_t attr[], bool computersTurn, bool tieFighterMovedSidewaysInLastTurn)
{
	

	vector<Move> movesAvailable;
	bool notEnded;

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
		int pieceType;
		for (int x = 0; x < 8; x++)// 8 rows
		{
			for (int y = 0; y < 8; y++)
			{
				pieceType = getNibbleFromIndicatedPosition(attr[x], y);
				uint64_t mask = 0x1;
				mask = mask << ((x * 8) + y);
				uint64_t location = pieces & mask;
				uint64_t locationUnchanging = location;
				
				

				switch (pieceType)
				{

				case 3:
					//TIE Fighter

					location = locationUnchanging;
					notEnded = true;
					while (notEnded) // south
					{
						// -8

						//if we subtract 9 from out current location and it becomes greater than our location
						//then we must've gone back around by subtracting past zero. assume this is not valid and terminate
						if ((location >> 8) > location || (location >> 8) == 0)
						{
							notEnded = false;
							break;
						}

						if (((int)(log2((location >> 8)))) % 8 > (int)(log2((location))) % 8)
						{
							//if the remainder (aka the column) after we move is suddenly larger
							//then we wrapped around to the next row, so ignore and quit
							notEnded = false;
							break;
						}

						//move SOUTHWEST
						location = location >> 8;

						//get the current row attributes
						//use the 0-63 bit position since we want the 8th position to still be the first row
						//g eg, 0/8 through 7/8, with 8/8 resulting in array index 1
						uint32_t localAttr = attr[(int)(log2(location)) / 8];



						//get the current column we're checking
						int localIndex = (int)(log2((location))) % 8;
						char movedToContents = getNibbleFromIndicatedPosition(localAttr, localIndex);


						//if target location is open
						if (movedToContents == 0)
						{
							//add target to list of moves
							Move possibleMove;
							possibleMove.setStartLocation(locationUnchanging);
							possibleMove.setDestinationLocation(location);
							movesAvailable.push_back(possibleMove);
						}

						//if occupied by my piece
						if (movedToContents > 0 && movedToContents < 6)
						{
							//stop
							notEnded = false;
							break;
						}

						//if occupied by opponent capturable piece
						if (movedToContents > 6 && movedToContents < 11 && movedToContents != 7) //SKIP THE DEATH STAR! CAN NOT CAPTURE FROM THIS DIRECTION
						{
							//add target to list of moves
							Move possibleMove;
							possibleMove.setStartLocation(locationUnchanging);
							possibleMove.setDestinationLocation(location);
							movesAvailable.push_back(possibleMove);

							//stop
							notEnded = false;
							break;
						}

					}

					location = locationUnchanging;
					notEnded = true;
					while (notEnded) // north
					{
						// +8

						//if we subtract 9 from out current location and it becomes greater than our location
						//then we must've gone back around by subtracting past zero. assume this is not valid and terminate
						if ((location << 8) < location || (location << 8) == 0)
						{
							notEnded = false;
							break;
						}

						if (((int)(log2((location << 8)))) % 8 < (int)(log2((location))) % 8)
						{
							//if the remainder (aka the column) after we move is suddenly larger
							//then we wrapped around to the next row, so ignore and quit
							notEnded = false;
							break;
						}

						//move SOUTHWEST
						location = location << 8;

						//get the current row attributes
						uint32_t localAttr = attr[(int)(log2(location)) / 8];

						//get the current column we're checking
						int localIndex = (int)(log2((location))) % 8;
						char movedToContents = getNibbleFromIndicatedPosition(localAttr, localIndex);


						//TODO: if detect one of my pieces, stop
						if (movedToContents > 0 && movedToContents < 6)
						{
							notEnded = false;
							break;
						}

						//if occupied by opponent capturable piece
						if (movedToContents > 5 && movedToContents < 11 && movedToContents != 7) // CAN CAPTURE DEATH STAR
						{
							//add target to list of moves
							Move possibleMove;
							possibleMove.setStartLocation(locationUnchanging);
							possibleMove.setDestinationLocation(location);
							movesAvailable.push_back(possibleMove);

							//stop
							notEnded = false;
							break;
						}
					}

					if (!tieFighterMovedSidewaysInLastTurn)//did the TIE move last turn? if not, go ahead and check it this turn
					{

						location = locationUnchanging;
						notEnded = true;
						while (notEnded) //east
						{
							// -1

							//if we subtract 9 from out current location and it becomes greater than our location
							//then we must've gone back around by subtracting past zero. assume this is not valid and terminate
							if ((location >> 1) > location || (location >> 1) == 0)
							{
								notEnded = false;
								break;
							}

							if (((int)(log2((location >> 1)))) % 8 > (int)(log2((location))) % 8)
							{
								//if the remainder (aka the column) after we move is suddenly larger
								//then we wrapped around to the next row, so ignore and quit
								notEnded = false;
								break;
							}

							//move SOUTHWEST
							location = location >> 1;

							//get the current row attributes
							uint32_t localAttr = attr[(int)(log2(location)) / 8];

							//get the current column we're checking
							int localIndex = (int)(log2((location))) % 8;
							char movedToContents = getNibbleFromIndicatedPosition(localAttr, localIndex);


							//if target location is open
							if (movedToContents == 0)
							{
								//add target to list of moves
								Move possibleMove;
								possibleMove.setStartLocation(locationUnchanging);
								possibleMove.setDestinationLocation(location);
								movesAvailable.push_back(possibleMove);
							}

							//if occupied by my piece
							if (movedToContents > 0 && movedToContents < 6)
							{
								//stop
								notEnded = false;
								break;
							}

							//if occupied by opponent capturable piece
							if (movedToContents > 6 && movedToContents < 11 && movedToContents != 7) //SKIP THE DEATH STAR! CAN NOT CAPTURE FROM THIS DIRECTION
							{
								//add target to list of moves
								Move possibleMove;
								possibleMove.setStartLocation(locationUnchanging);
								possibleMove.setDestinationLocation(location);
								movesAvailable.push_back(possibleMove);

								//stop
								notEnded = false;
								break;
							}
						}

						location = locationUnchanging;
						notEnded = true;
						while (notEnded) // west
						{
							// +1

							//if we subtract 9 from out current location and it becomes greater than our location
							//then we must've gone back around by subtracting past zero. assume this is not valid and terminate
							if ((location << 1) < location || (location << 1) == 0)
							{
								notEnded = false;
								break;
							}

							if (((int)(log2((location << 1)))) % 8 < (int)(log2((location))) % 8)
							{
								//if the remainder (aka the column) after we move is suddenly larger
								//then we wrapped around to the next row, so ignore and quit
								notEnded = false;
								break;
							}

							//move SOUTHWEST
							location = location << 1;

							//get the current row attributes
							uint32_t localAttr = attr[(int)(log2(location)) / 8];

							//get the current column we're checking
							int localIndex = (int)(log2((location))) % 8;
							char movedToContents = getNibbleFromIndicatedPosition(localAttr, localIndex);

							//if target location is open
							if (movedToContents == 0)
							{
								//add target to list of moves
								Move possibleMove;
								possibleMove.setStartLocation(locationUnchanging);
								possibleMove.setDestinationLocation(location);
								movesAvailable.push_back(possibleMove);
							}

							//if occupied by my piece
							if (movedToContents > 0 && movedToContents < 6)
							{
								//stop
								notEnded = false;
								break;
							}

							//if occupied by opponent capturable piece
							if (movedToContents > 5 && movedToContents < 11 && movedToContents != 7) // CAN CAPTURE DEATH STAR
							{
								//add target to list of moves
								Move possibleMove;
								possibleMove.setStartLocation(locationUnchanging);
								possibleMove.setDestinationLocation(location);
								movesAvailable.push_back(possibleMove);

								//stop
								notEnded = false;
								break;
							}
						}

					}

					break;

				case 4:
					//X Wing (CAN attack Death Star)

					//uint64_t locationsToMoveTo;
					//locationsToMoveTo = *adjustDiagonalForPieceLocation(pieces, true);
					//locationsToMoveTo += *adjustDiagonalForPieceLocation(pieces, false);

					//locationsToMoveTo has all of the locations that this could move to


					//figure out ne(back), nw (back), se, sw possible moves
					//back moves only count if they are a capture. figure out caputure with attr

					location = locationUnchanging;
					notEnded = true;
					while (notEnded)//sw
					{
						//if we subtract 9 from out current location and it becomes greater than our location
						//then we must've gone back around by subtracting past zero. assume this is not valid and terminate
						if ((location >> 9) > location || (location >> 9) == 0)
						{
							notEnded = false;
							break;
						}

						if (((int)(log2((location >> 9)))) % 8 > (int)(log2((location))) % 8)
						{
							//if the remainder (aka the column) after we move is suddenly larger
							//then we wrapped around to the next row, so ignore and quit
							notEnded = false;
							break;
						}

						//move SOUTHWEST
						location = location >> 9;

						//get the current row attributes
						uint32_t localAttr = attr[(int)(log2(location)) / 8];

						//get the current column we're checking
						int localIndex = (int)(log2((location))) % 8;
						char movedToContents = getNibbleFromIndicatedPosition(localAttr, localIndex);


						//if target location is open
						if (movedToContents == 0)
						{
							//add target to list of moves
							Move possibleMove;
							possibleMove.setStartLocation(locationUnchanging);
							possibleMove.setDestinationLocation(location);
							movesAvailable.push_back(possibleMove);
						}
						
						//if occupied by my piece
						if ((movedToContents > 0 && movedToContents < 6) || (movedToContents == 6 || movedToContents == 7))
						{
							//stop
							notEnded = false;
							break;
						}
						
						//if occupied by opponent capturable piece
						if (movedToContents > 6 && movedToContents < 11 && movedToContents != 7) //SKIP THE DEATH STAR! CAN NOT CAPTURE FROM THIS DIRECTION
						{
							//add target to list of moves
							Move possibleMove;
							possibleMove.setStartLocation(locationUnchanging);
							possibleMove.setDestinationLocation(location);
							movesAvailable.push_back(possibleMove);

							//stop
							notEnded = false;
							break;
						}
						
						
					}

					location = locationUnchanging;
					notEnded = true;
					while (notEnded)//se
					{
						//minus 7
						//if we subtract 7 from out current location and it becomes greater than our location
						//then we must've gone back around by subtracting past zero. assume this is not valid and terminate
						if ((location >> 7) > location || (location >> 7) == 0)
						{
							notEnded = false;
							break;
						}

						if (((int)(log2((location >> 7)))) % 8 < (int)(log2((location))) % 8)
						{
							//if the remainder (aka the column) after we move is suddenly larger
							//then we wrapped around to the next row, so ignore and quit
							notEnded = false;
							break;
						}

						//move SOUTHWEST
						location = location >> 7;

						//get the current row attributes
						uint32_t localAttr = attr[(int)(log2(location)) / 8];

						//get the current column we're checking
						int localIndex = (int)(log2((location))) % 8;
						char movedToContents = getNibbleFromIndicatedPosition(localAttr, localIndex);


						//if target location is open
						if (movedToContents == 0)
						{
							//add target to list of moves
							Move possibleMove;
							possibleMove.setStartLocation(locationUnchanging);
							possibleMove.setDestinationLocation(location);
							movesAvailable.push_back(possibleMove);
						}

						//if occupied by my piece
						if ((movedToContents > 0 && movedToContents < 6) || (movedToContents == 6 || movedToContents == 7))
						{
							//stop
							notEnded = false;
							break;
						}

						//if occupied by opponent capturable piece
						if (movedToContents > 6 && movedToContents < 11 && movedToContents != 7) //SKIP THE DEATH STAR! CAN NOT CAPTURE FROM THIS DIRECTION
						{
							//add target to list of moves
							Move possibleMove;
							possibleMove.setStartLocation(locationUnchanging);
							possibleMove.setDestinationLocation(location);
							movesAvailable.push_back(possibleMove);

							//stop
							notEnded = false;
							break;
						}


					}


					//only look for a capture
					location = locationUnchanging;
					notEnded = true;
					while (notEnded)//nw
					{
						//plus 7
						//if we add 7 from out current location and it becomes less than our location
						//then we must've gone back around by adding past MAX. assume this is not valid and terminate
						if ((location << 7) < location || (location << 7) == 0)
						{
							notEnded = false;
							break;
						}

						if (((int)(log2((location << 7)))) % 8 > (int)(log2((location))) % 8)
						{
							//if the remainder (aka the column) after we move is suddenly smaller
							//then we wrapped around to the next row, so ignore and quit
							notEnded = false;
							break;
						}

						//move SOUTHWEST
						location = location << 7;

						//get the current row attributes
						uint32_t localAttr = attr[(int)(log2(location)) / 8];

						//get the current column we're checking
						int localIndex = (int)(log2((location))) % 8;
						char movedToContents = getNibbleFromIndicatedPosition(localAttr, localIndex);

						//TODO: if detect one of my pieces, stop
						if (movedToContents > 0 && movedToContents < 6)
						{
							notEnded = false;
							break;
						}


						//if occupied by opponent capturable piece
						if (movedToContents > 5 && movedToContents < 11 && movedToContents != 7) //DO NOT SKIP DEATH STAR! WE WOULD BE GOING BACKWARDS IN THIS MOVE, WHICH IS ALLOWED
						{
							//add target to list of moves
							Move possibleMove;
							possibleMove.setStartLocation(locationUnchanging);
							possibleMove.setDestinationLocation(location);
							movesAvailable.push_back(possibleMove);

							//stop
							notEnded = false;
							break;
						}
					}

					location = locationUnchanging;
					notEnded = true;
					while (notEnded)//ne
					{
						//plus 9
						//if we add 9 from out current location and it becomes less than our location
						//then we must've gone back around by adding past MAX. assume this is not valid and terminate
						if ((location << 9) < location || (location << 9) == 0)
						{
							notEnded = false;
							break;
						}

						if (((int)(log2((location << 9)))) % 8 < (int)(log2((location))) % 8)
						{
							//if the remainder (aka the column) after we move is suddenly smaller
							//then we wrapped around to the next row, so ignore and quit
							notEnded = false;
							break;
						}

						//move SOUTHWEST
						location = location << 9;

						//get the current row attributes
						uint32_t localAttr = attr[(int)(log2(location)) / 8];

						//get the current column we're checking
						int localIndex = (int)(log2((location))) % 8;
						char movedToContents = getNibbleFromIndicatedPosition(localAttr, localIndex);


						//TODO: if detect one of my pieces, stop
						if (movedToContents > 0 && movedToContents < 6)
						{
							notEnded = false;
							break;
						}

						//if occupied by opponent capturable piece
						if (movedToContents > 5 && movedToContents < 11 && movedToContents != 7) //DO NOT SKIP DEATH STAR! WE WOULD BE GOING BACKWARDS IN THIS MOVE, WHICH IS ALLOWED
						{
							//add target to list of moves
							Move possibleMove;
							possibleMove.setStartLocation(locationUnchanging);
							possibleMove.setDestinationLocation(location);
							movesAvailable.push_back(possibleMove);

							//stop
							notEnded = false;
							break;
						}
					}


					break;

				case 5:
					//X Wing (CAN NOT attack Death Star)

					//uint64_t locationsToMoveTo;
					//locationsToMoveTo = *adjustDiagonalForPieceLocation(pieces, true);
					//locationsToMoveTo += *adjustDiagonalForPieceLocation(pieces, false);

					//locationsToMoveTo has all of the locations that this could move to


					//figure out ne(back), nw (back), se, sw possible moves
					//back moves only count if they are a capture. figure out caputure with attr

					location = locationUnchanging;
					notEnded = true;
					while (notEnded)//sw
					{
						//if we subtract 9 from out current location and it becomes greater than our location
						//then we must've gone back around by subtracting past zero. assume this is not valid and terminate
						if ((location >> 9) > location || (location >> 9) == 0)
						{
							notEnded = false;
							break;
						}

						if (((int)(log2((location >> 9)))) % 8 > (int)(log2((location))) % 8)
						{
							//if the remainder (aka the column) after we move is suddenly larger
							//then we wrapped around to the next row, so ignore and quit
							notEnded = false;
							break;
						}

						//move SOUTHWEST
						location = location >> 9;

						//get the current row attributes
						uint32_t localAttr = attr[(int)(log2(location)) / 8];

						//get the current column we're checking
						int localIndex = (int)(log2((location))) % 8;
						char movedToContents = getNibbleFromIndicatedPosition(localAttr, localIndex);


						//if target location is open
						if (movedToContents == 0)
						{
							//add target to list of moves
							Move possibleMove;
							possibleMove.setStartLocation(locationUnchanging);
							possibleMove.setDestinationLocation(location);
							movesAvailable.push_back(possibleMove);
						}

						//if occupied by my piece
						if ((movedToContents > 0 && movedToContents < 6) || (movedToContents == 7))
						{
							//stop
							notEnded = false;
							break;
						}

						//if occupied by opponent capturable piece
						if (movedToContents > 6 && movedToContents < 11 && movedToContents != 7) //SKIP THE DEATH STAR! CAN NOT CAPTURE FROM THIS DIRECTION
						{
							//add target to list of moves
							Move possibleMove;
							possibleMove.setStartLocation(locationUnchanging);
							possibleMove.setDestinationLocation(location);
							movesAvailable.push_back(possibleMove);

							//stop
							notEnded = false;
							break;
						}


					}

					location = locationUnchanging;
					notEnded = true;
					while (notEnded)//se
					{
						//minus 7
						//if we subtract 7 from out current location and it becomes greater than our location
						//then we must've gone back around by subtracting past zero. assume this is not valid and terminate
						if ((location >> 7) > location || (location >> 7) == 0)
						{
							notEnded = false;
							break;
						}

						if (((int)(log2((location >> 7)))) % 8 < (int)(log2((location))) % 8)
						{
							//if the remainder (aka the column) after we move is suddenly larger
							//then we wrapped around to the next row, so ignore and quit
							notEnded = false;
							break;
						}

						//move SOUTHWEST
						location = location >> 7;

						//get the current row attributes
						uint32_t localAttr = attr[(int)(log2(location)) / 8];

						//get the current column we're checking
						int localIndex = (int)(log2((location))) % 8;
						char movedToContents = getNibbleFromIndicatedPosition(localAttr, localIndex);


						//if target location is open
						if (movedToContents == 0)
						{
							//add target to list of moves
							Move possibleMove;
							possibleMove.setStartLocation(locationUnchanging);
							possibleMove.setDestinationLocation(location);
							movesAvailable.push_back(possibleMove);
						}

						//if occupied by my piece
						if ((movedToContents > 0 && movedToContents < 6) || (movedToContents == 7))
						{
							//stop
							notEnded = false;
							break;
						}

						//if occupied by opponent capturable piece
						if (movedToContents > 6 && movedToContents < 11 && movedToContents != 7) //SKIP THE DEATH STAR! CAN NOT CAPTURE FROM THIS DIRECTION
						{
							//add target to list of moves
							Move possibleMove;
							possibleMove.setStartLocation(locationUnchanging);
							possibleMove.setDestinationLocation(location);
							movesAvailable.push_back(possibleMove);

							//stop
							notEnded = false;
							break;
						}


					}


					//only look for a capture
					location = locationUnchanging;
					notEnded = true;
					while (notEnded)//nw
					{
						//plus 7
						//if we add 7 from out current location and it becomes less than our location
						//then we must've gone back around by adding past MAX. assume this is not valid and terminate
						if ((location << 7) < location || (location << 7) == 0)
						{
							notEnded = false;
							break;
						}

						if (((int)(log2((location << 7)))) % 8 > (int)(log2((location))) % 8)
						{
							//if the remainder (aka the column) after we move is suddenly smaller
							//then we wrapped around to the next row, so ignore and quit
							notEnded = false;
							break;
						}

						//move SOUTHWEST
						location = location << 7;

						//get the current row attributes
						uint32_t localAttr = attr[(int)(log2(location)) / 8];

						//get the current column we're checking
						int localIndex = (int)(log2((location))) % 8;
						char movedToContents = getNibbleFromIndicatedPosition(localAttr, localIndex);

						//TODO: if detect one of my pieces, stop
						if (movedToContents > 0 && movedToContents < 6)
						{
							notEnded = false;
							break;
						}


						//if occupied by opponent capturable piece
						if (movedToContents > 5 && movedToContents < 11 && movedToContents != 7) //DO NOT SKIP DEATH STAR! WE WOULD BE GOING BACKWARDS IN THIS MOVE, WHICH IS ALLOWED
						{
							//add target to list of moves
							Move possibleMove;
							possibleMove.setStartLocation(locationUnchanging);
							possibleMove.setDestinationLocation(location);
							movesAvailable.push_back(possibleMove);

							//stop
							notEnded = false;
							break;
						}
					}

					location = locationUnchanging;
					notEnded = true;
					while (notEnded)//ne
					{
						//plus 9
						//if we add 9 from out current location and it becomes less than our location
						//then we must've gone back around by adding past MAX. assume this is not valid and terminate
						if ((location << 9) < location || (location << 9) == 0)
						{
							notEnded = false;
							break;
						}

						if (((int)(log2((location << 9)))) % 8 < (int)(log2((location))) % 8)
						{
							//if the remainder (aka the column) after we move is suddenly smaller
							//then we wrapped around to the next row, so ignore and quit
							notEnded = false;
							break;
						}

						//move SOUTHWEST
						location = location << 9;

						//get the current row attributes
						uint32_t localAttr = attr[(int)(log2(location)) / 8];

						//get the current column we're checking
						int localIndex = (int)(log2((location))) % 8;
						char movedToContents = getNibbleFromIndicatedPosition(localAttr, localIndex);

						//TODO: if detect one of my pieces, stop
						if (movedToContents > 0 && movedToContents < 6)
						{
							notEnded = false;
							break;
						}

						//if occupied by opponent capturable piece
						if (movedToContents > 5 && movedToContents < 11 && movedToContents != 7) //DO NOT SKIP DEATH STAR! WE WOULD BE GOING BACKWARDS IN THIS MOVE, WHICH IS ALLOWED
						{
							//add target to list of moves
							Move possibleMove;
							possibleMove.setStartLocation(locationUnchanging);
							possibleMove.setDestinationLocation(location);
							movesAvailable.push_back(possibleMove);

							//stop
							notEnded = false;
							break;
						}
					}


					break;
				}

			}
		}
	}
	else
	{
		int pieceType;
		for (int x = 0; x < 8; x++)// 8 rows
		{
			for (int y = 0; y < 8; y++)
			{
				pieceType = getNibbleFromIndicatedPosition(attr[x], y);
				uint64_t mask = 0x1;
				mask = mask << ((x * 8) + y);
				uint64_t location = pieces & mask;
				uint64_t locationUnchanging = location;


				int test = log2(8);

				switch (pieceType)
				{

				case 8:
					//TIE Fighter

					location = locationUnchanging;
					notEnded = true;
					while (notEnded) // North
					{
						// +8

						//if we subtract 9 from out current location and it becomes greater than our location
						//then we must've gone back around by subtracting past zero. assume this is not valid and terminate
						if ((location << 8) < location || (location << 8) == 0)
						{
							notEnded = false;
							break;
						}

						if ((int)(log2((location << 8))) % 8 < (int)(log2(location)) % 8)
						{
							//if the remainder (aka the column) after we move is suddenly larger
							//then we wrapped around to the next row, so ignore and quit
							notEnded = false;
							break;
						}

						//move SOUTHWEST
						location = location << 8;

						//get the current row attributes
						uint32_t localAttr = attr[(int)(log2(location)) / 8];

						//get the current column we're checking
						int localIndex = (int)(log2((location))) % 8;
						char movedToContents = getNibbleFromIndicatedPosition(localAttr, localIndex);


						//if target location is open
						if (movedToContents == 0)
						{
							//add target to list of moves
							Move possibleMove;
							possibleMove.setStartLocation(locationUnchanging);
							possibleMove.setDestinationLocation(location);
							movesAvailable.push_back(possibleMove);
						}

						//if occupied by my piece
						if (movedToContents > 6 && movedToContents < 11)
						{
							//stop
							notEnded = false;
							break;
						}

						//if occupied by opponent capturable piece
						if (movedToContents > 0 && movedToContents < 6 && movedToContents != 2) //SKIP THE DEATH STAR! CAN NOT CAPTURE FROM THIS DIRECTION
						{
							//add target to list of moves
							Move possibleMove;
							possibleMove.setStartLocation(locationUnchanging);
							possibleMove.setDestinationLocation(location);
							movesAvailable.push_back(possibleMove);

							//stop
							notEnded = false;
							break;
						}

					}

					location = locationUnchanging;
					notEnded = true;
					while (notEnded) // south
					{
						// -8

						//if we subtract 9 from out current location and it becomes greater than our location
						//then we must've gone back around by subtracting past zero. assume this is not valid and terminate
						
						if ((location >> 8) > location || (location >> 8) == 0)
						{
							//we moved the location completely out of bounds, so it became ZERO and we can just stop
							notEnded = false;
							break;
						}
						
						/*if ((location >> 8) > location)
						{
							notEnded = false;
							break;
						}

						// this might not be needed since this part is only going vertically, no need to worry about row-wrapping
						if (((int)(log2(location >> 8))) % 8 > (int)(log2(location)) % 8)
						{
							//if the remainder (aka the column) after we move is suddenly larger
							//then we wrapped around to the next row, so ignore and quit
							notEnded = false;
							break;
						}*/

						//move SOUTHWEST
						location = location >> 8;

						//get the current row attributes
						uint32_t localAttr = attr[(int)(log2(location)) / 8];

						//get the current column we're checking
						int localIndex = (int)(log2((location))) % 8;
						char movedToContents = getNibbleFromIndicatedPosition(localAttr, localIndex);

						//TODO: if detect one of my pieces, stop
						if (movedToContents > 5 && movedToContents < 11)
						{
							notEnded = false;
							break;
						}

						//if occupied by opponent capturable piece
						if (movedToContents > 0 && movedToContents < 6 && movedToContents != 2) // CAN CAPTURE DEATH STAR
						{
							//add target to list of moves
							Move possibleMove;
							possibleMove.setStartLocation(locationUnchanging);
							possibleMove.setDestinationLocation(location);
							movesAvailable.push_back(possibleMove);

							//stop
							notEnded = false;
							break;
						}
					}

					if (!tieFighterMovedSidewaysInLastTurn)//did the TIE move last turn? if not, go ahead and check it this turn
					{

						location = locationUnchanging;
						notEnded = true;
						while (notEnded) //east
						{
							// -1

							//if we subtract 9 from out current location and it becomes greater than our location
							//then we must've gone back around by subtracting past zero. assume this is not valid and terminate
							if ((location >> 1) > location || (location >> 1) == 0)
							{
								notEnded = false;
								break;
							}

							if (((int)(log2((location >> 1)))) % 8 > ((int)(log2((location)))) % 8)
							{
								//if the remainder (aka the column) after we move is suddenly larger
								//then we wrapped around to the next row, so ignore and quit
								notEnded = false;
								break;
							}

							//move SOUTHWEST
							location = location >> 1;

							//get the current row attributes
							uint32_t localAttr = attr[(int)(log2(location)) / 8];

							//get the current column we're checking
							int localIndex = (int)(log2((location))) % 8;
							char movedToContents = getNibbleFromIndicatedPosition(localAttr, localIndex);


							//if target location is open
							if (movedToContents == 0)
							{
								//add target to list of moves
								Move possibleMove;
								possibleMove.setStartLocation(locationUnchanging);
								possibleMove.setDestinationLocation(location);
								movesAvailable.push_back(possibleMove);
							}

							//if occupied by my piece
							if (movedToContents > 6 && movedToContents < 11)
							{
								//stop
								notEnded = false;
								break;
							}


							//if occupied by opponent capturable piece
							if (movedToContents > 0 && movedToContents < 6 && movedToContents != 2) //SKIP THE DEATH STAR! CAN NOT CAPTURE FROM THIS DIRECTION
							{
								//add target to list of moves
								Move possibleMove;
								possibleMove.setStartLocation(locationUnchanging);
								possibleMove.setDestinationLocation(location);
								movesAvailable.push_back(possibleMove);

								//stop
								notEnded = false;
								break;
							}
						}

						location = locationUnchanging;
						notEnded = true;
						while (notEnded) // west
						{
							// +1

							//if we subtract 9 from out current location and it becomes greater than our location
							//then we must've gone back around by subtracting past zero. assume this is not valid and terminate
							if ((location << 1) < location || (location << 1) == 0)
							{
								notEnded = false;
								break;
							}

							if (((int)(log2((location << 1)))) % 8 < (int)(log2((location))) % 8)
							{
								//if the remainder (aka the column) after we move is suddenly larger
								//then we wrapped around to the next row, so ignore and quit
								notEnded = false;
								break;
							}

							//move SOUTHWEST
							location = location << 1;

							//get the current row attributes
							uint32_t localAttr = attr[(int)(log2(location)) / 8];

							//get the current column we're checking
							int localIndex = (int)(log2((location))) % 8;
							char movedToContents = getNibbleFromIndicatedPosition(localAttr, localIndex);

							//if target location is open
							if (movedToContents == 0)
							{
								//add target to list of moves
								Move possibleMove;
								possibleMove.setStartLocation(locationUnchanging);
								possibleMove.setDestinationLocation(location);
								movesAvailable.push_back(possibleMove);
							}

							//if occupied by my piece
							if (movedToContents > 6 && movedToContents < 11)
							{
								//stop
								notEnded = false;
								break;
							}

							//if occupied by opponent capturable piece
							if (movedToContents > 0 && movedToContents < 6 && movedToContents != 2) // CAN CAPTURE DEATH STAR
							{
								//add target to list of moves
								Move possibleMove;
								possibleMove.setStartLocation(locationUnchanging);
								possibleMove.setDestinationLocation(location);
								movesAvailable.push_back(possibleMove);

								//stop
								notEnded = false;
								break;
							}
						}

					}

					break;

				case 9:
					//X Wing (CAN attack Death Star)

					//figure out ne(back), nw (back), se, sw possible moves
					//back moves only count if they are a capture. figure out caputure with attr

					location = locationUnchanging;
					notEnded = true;
					while (notEnded)//ne
					{
						//if we subtract 9 from out current location and it becomes greater than our location
						//then we must've gone back around by subtracting past zero. assume this is not valid and terminate
						if ((location << 9) < location || (location << 9) == 0)
						{
							notEnded = false;
							break;
						}

						if (((int)(log2((location << 9)))) % 8 < (int)(log2((location))) % 8)
						{
							//if the remainder (aka the column) after we move is suddenly larger
							//then we wrapped around to the next row, so ignore and quit
							notEnded = false;
							break;
						}

						//move SOUTHWEST
						location = location << 9;

						//get the current row attributes
						uint32_t localAttr = attr[(int)(log2(location)) / 8];

						//get the current column we're checking
						int localIndex = (int)(log2((location))) % 8;
						char movedToContents = getNibbleFromIndicatedPosition(localAttr, localIndex);


						//if target location is open
						if (movedToContents == 0)
						{
							//add target to list of moves
							Move possibleMove;
							possibleMove.setStartLocation(locationUnchanging);
							possibleMove.setDestinationLocation(location);
							movesAvailable.push_back(possibleMove);
						}

						//if occupied by my piece OR is the opponent's Death Star or Wall. Cannot capture walls. Cannot capture DS from this direction
						if ( (movedToContents > 6 && movedToContents < 11) || (movedToContents == 1 || movedToContents == 2 ))
						{
							//stop
							notEnded = false;
							break;
						}

						//if occupied by opponent capturable piece
						if (movedToContents > 1 && movedToContents < 6 && movedToContents != 2) //SKIP THE DEATH STAR! CAN NOT CAPTURE FROM THIS DIRECTION
						{
							//add target to list of moves
							Move possibleMove;
							possibleMove.setStartLocation(locationUnchanging);
							possibleMove.setDestinationLocation(location);
							movesAvailable.push_back(possibleMove);

							//stop
							notEnded = false;
							break;
						}


					}

					location = locationUnchanging;
					notEnded = true;
					while (notEnded)//nw
					{
						//minus 7
						//if we subtract 7 from out current location and it becomes greater than our location
						//then we must've gone back around by subtracting past zero. assume this is not valid and terminate
						if ((location << 7) < location || (location << 7) == 0)
						{
							notEnded = false;
							break;
						}

						if (((int)(log2((location << 7)))) % 8 > (int)(log2((location))) % 8)
						{
							//if the remainder (aka the column) after we move is suddenly larger
							//then we wrapped around to the next row, so ignore and quit
							notEnded = false;
							break;
						}

						//move SOUTHWEST
						location = location << 7;

						//get the current row attributes
						uint32_t localAttr = attr[(int)(log2(location)) / 8];

						//get the current column we're checking
						int localIndex = (int)(log2((location))) % 8;
						char movedToContents = getNibbleFromIndicatedPosition(localAttr, localIndex);


						//if target location is open
						if (movedToContents == 0)
						{
							//add target to list of moves
							Move possibleMove;
							possibleMove.setStartLocation(locationUnchanging);
							possibleMove.setDestinationLocation(location);
							movesAvailable.push_back(possibleMove);
						}

						//if occupied by my piece
						if ((movedToContents > 6 && movedToContents < 11) || (movedToContents == 1 || movedToContents == 2))
						{
							//stop
							notEnded = false;
							break;
						}

						//if occupied by opponent capturable piece
						if (movedToContents > 1 && movedToContents < 6 && movedToContents != 2) //SKIP THE DEATH STAR! CAN NOT CAPTURE FROM THIS DIRECTION
						{
							//add target to list of moves
							Move possibleMove;
							possibleMove.setStartLocation(locationUnchanging);
							possibleMove.setDestinationLocation(location);
							movesAvailable.push_back(possibleMove);

							//stop
							notEnded = false;
							break;
						}


					}


					//only look for a capture
					location = locationUnchanging;
					notEnded = true;
					while (notEnded)//se
					{
						//plus 7
						//if we add 7 from out current location and it becomes less than our location
						//then we must've gone back around by adding past MAX. assume this is not valid and terminate
						if ((location >> 7) > location || (location >> 7) == 0)
						{
							notEnded = false;
							break;
						}

						if (((int)(log2((location >> 7)))) % 8 < (int)(log2((location))) % 8)
						{
							//if the remainder (aka the column) after we move is suddenly smaller
							//then we wrapped around to the next row, so ignore and quit
							notEnded = false;
							break;
						}

						//move SOUTHWEST
						location = location >> 7;

						//get the current row attributes
						uint32_t localAttr = attr[(int)(log2(location)) / 8];

						//get the current column we're checking
						int localIndex = (int)(log2((location))) % 8;
						char movedToContents = getNibbleFromIndicatedPosition(localAttr, localIndex);


						//TODO: if detect one of my pieces, stop
						if (movedToContents > 5 && movedToContents < 11)
						{
							notEnded = false;
							break;
						}

						//if occupied by opponent capturable piece
						if (movedToContents > 0 && movedToContents < 6 && movedToContents != 2) //DO NOT SKIP THE DEATH STAR! CAN CAPTURE FROM THIS DIRECTION!
						{
							//add target to list of moves
							Move possibleMove;
							possibleMove.setStartLocation(locationUnchanging);
							possibleMove.setDestinationLocation(location);
							movesAvailable.push_back(possibleMove);

							//stop
							notEnded = false;
							break;
						}
					}

					location = locationUnchanging;
					notEnded = true;
					while (notEnded)//sw
					{
						//plus 9
						//if we add 9 from out current location and it becomes less than our location
						//then we must've gone back around by adding past MAX. assume this is not valid and terminate
						if ((location >> 9) > location || (location >> 9) == 0)
						{
							notEnded = false;
							break;
						}

						if (((int)(log2((location >> 9)))) % 8 > (int)(log2((location))) % 8)
						{
							//if the remainder (aka the column) after we move is suddenly smaller
							//then we wrapped around to the next row, so ignore and quit
							notEnded = false;
							break;
						}

						//move SOUTHWEST
						location = location >> 9;

						//get the current row attributes
						uint32_t localAttr = attr[(int)(log2(location)) / 8];

						//get the current column we're checking
						int localIndex = (int)(log2((location))) % 8;
						char movedToContents = getNibbleFromIndicatedPosition(localAttr, localIndex);

						//TODO: if detect one of my pieces, stop
						if (movedToContents > 5 && movedToContents < 11)
						{
							notEnded = false;
							break;
						}

						//if occupied by opponent capturable piece
						if (movedToContents > 0 && movedToContents < 6 && movedToContents != 2) //DO NOT SKIP THE DEATH STAR! CAN CAPTURE FROM THIS DIRECTION!
						{
							//add target to list of moves
							Move possibleMove;
							possibleMove.setStartLocation(locationUnchanging);
							possibleMove.setDestinationLocation(location);
							movesAvailable.push_back(possibleMove);

							//stop
							notEnded = false;
							break;
						}
					}


					break;

				case 10:
					//X Wing (CAN NOT attack Death Star)

					//figure out ne(back), nw (back), se, sw possible moves
					//back moves only count if they are a capture. figure out caputure with attr

					location = locationUnchanging;
					notEnded = true;
					while (notEnded)//ne
					{
						//if we subtract 9 from out current location and it becomes greater than our location
						//then we must've gone back around by subtracting past zero. assume this is not valid and terminate
						if ((location << 9) < location || (location << 9) == 0)
						{
							notEnded = false;
							break;
						}

						if (((int)(log2((location << 9)))) % 8 < (int)(log2((location))) % 8)
						{
							//if the remainder (aka the column) after we move is suddenly larger
							//then we wrapped around to the next row, so ignore and quit
							notEnded = false;
							break;
						}

						//move SOUTHWEST
						location = location << 9;

						//get the current row attributes
						uint32_t localAttr = attr[(int)(log2(location)) / 8];

						//get the current column we're checking
						int localIndex = (int)(log2((location))) % 8;
						char movedToContents = getNibbleFromIndicatedPosition(localAttr, localIndex);


						//if target location is open
						if (movedToContents == 0)
						{
							//add target to list of moves
							Move possibleMove;
							possibleMove.setStartLocation(locationUnchanging);
							possibleMove.setDestinationLocation(location);
							movesAvailable.push_back(possibleMove);
						}

						//if occupied by my piece
						if ((movedToContents > 6 && movedToContents < 11) || (movedToContents == 2))
						{
							//stop
							notEnded = false;
							break;
						}

						//if occupied by opponent capturable piece
						if (movedToContents > 0 && movedToContents < 6 && movedToContents != 2) //SKIP THE DEATH STAR! CAN NOT CAPTURE FROM THIS DIRECTION
						{
							//add target to list of moves
							Move possibleMove;
							possibleMove.setStartLocation(locationUnchanging);
							possibleMove.setDestinationLocation(location);
							movesAvailable.push_back(possibleMove);

							//stop
							notEnded = false;
							break;
						}


					}

					location = locationUnchanging;
					notEnded = true;
					while (notEnded)//nw
					{
						//minus 7
						//if we subtract 7 from out current location and it becomes greater than our location
						//then we must've gone back around by subtracting past zero. assume this is not valid and terminate
						if ((location << 7) < location || (location << 7) == 0)
						{
							notEnded = false;
							break;
						}

						if (((int)(log2((location << 7)))) % 8 > (int)(log2((location))) % 8)
						{
							//if the remainder (aka the column) after we move is suddenly larger
							//then we wrapped around to the next row, so ignore and quit
							notEnded = false;
							break;
						}

						//move SOUTHWEST
						location = location << 7;

						//get the current row attributes
						uint32_t localAttr = attr[(int)(log2(location)) / 8];

						//get the current column we're checking
						int localIndex = (int)(log2((location))) % 8;
						char movedToContents = getNibbleFromIndicatedPosition(localAttr, localIndex);


						//if target location is open
						if (movedToContents == 0)
						{
							//add target to list of moves
							Move possibleMove;
							possibleMove.setStartLocation(locationUnchanging);
							possibleMove.setDestinationLocation(location);
							movesAvailable.push_back(possibleMove);
						}

						//if occupied by my piece
						if ((movedToContents > 6 && movedToContents < 11) || (movedToContents == 2))
						{
							//stop
							notEnded = false;
							break;
						}

						//if occupied by opponent capturable piece
						if (movedToContents > 0 && movedToContents < 6 && movedToContents != 2) //SKIP THE DEATH STAR! CAN NOT CAPTURE FROM THIS DIRECTION
						{
							//add target to list of moves
							Move possibleMove;
							possibleMove.setStartLocation(locationUnchanging);
							possibleMove.setDestinationLocation(location);
							movesAvailable.push_back(possibleMove);

							//stop
							notEnded = false;
							break;
						}


					}


					//only look for a capture
					location = locationUnchanging;
					notEnded = true;
					while (notEnded)//se
					{
						//plus 7
						//if we add 7 from out current location and it becomes less than our location
						//then we must've gone back around by adding past MAX. assume this is not valid and terminate
						if ((location >> 7) > location || (location >> 7) == 0)
						{
							notEnded = false;
							break;
						}

						if (((int)(log2((location >> 7)))) % 8 < (int)(log2((location))) % 8)
						{
							//if the remainder (aka the column) after we move is suddenly smaller
							//then we wrapped around to the next row, so ignore and quit
							notEnded = false;
							break;
						}

						//move SOUTHWEST
						location = location >> 7;

						//get the current row attributes
						uint32_t localAttr = attr[(int)(log2(location)) / 8];

						//get the current column we're checking
						int localIndex = (int)(log2((location))) % 8;
						char movedToContents = getNibbleFromIndicatedPosition(localAttr, localIndex);


						//TODO: if detect one of my pieces, stop
						if (movedToContents > 5 && movedToContents < 11)
						{
							notEnded = false;
							break;
						}

						//if occupied by opponent capturable piece
						if (movedToContents > 0 && movedToContents < 6 && movedToContents != 2) //SKIP THE DEATH STAR! CAN NOT CAPTURE FROM THIS DIRECTION
						{
							//add target to list of moves
							Move possibleMove;
							possibleMove.setStartLocation(locationUnchanging);
							possibleMove.setDestinationLocation(location);
							movesAvailable.push_back(possibleMove);

							//stop
							notEnded = false;
							break;
						}
					}

					location = locationUnchanging;
					notEnded = true;
					while (notEnded)//sw
					{
						//plus 9
						//if we add 9 from out current location and it becomes less than our location
						//then we must've gone back around by adding past MAX. assume this is not valid and terminate
						if ((location >> 9) > location || (location >> 9) == 0)
						{
							notEnded = false;
							break;
						}

						if (((int)(log2((location >> 9)))) % 8 > (int)(log2((location))) % 8)
						{
							//if the remainder (aka the column) after we move is suddenly smaller
							//then we wrapped around to the next row, so ignore and quit
							notEnded = false;
							break;
						}

						//move SOUTHWEST
						location = location >> 9;

						//get the current row attributes
						uint32_t localAttr = attr[(int)(log2(location)) / 8];

						//get the current column we're checking
						int localIndex = (int)(log2((location))) % 8;
						char movedToContents = getNibbleFromIndicatedPosition(localAttr, localIndex);

						//TODO: if detect one of my pieces, stop
						if (movedToContents > 5 && movedToContents < 11)
						{
							notEnded = false;
							break;
						}

						//if occupied by opponent capturable piece
						if (movedToContents > 0 && movedToContents < 6 && movedToContents != 2) //SKIP THE DEATH STAR! CAN NOT CAPTURE FROM THIS DIRECTION
						{
							//add target to list of moves
							Move possibleMove;
							possibleMove.setStartLocation(locationUnchanging);
							possibleMove.setDestinationLocation(location);
							movesAvailable.push_back(possibleMove);

							//stop
							notEnded = false;
							break;
						}
					}


					break;
				}

			}
		}
	}

 	return movesAvailable;
}

int MoveGenerator::getNibbleFromIndicatedPosition(uint32_t bits, int index)
{
	//char val;
	uint32_t mask = 0xF0000000;

	//shift the mask as far over as needed to match the index 
	mask = mask >> ((index) * 4);

	//AND the input with the mask to remove the other stuff
	bits = bits & mask;

	//shift those bits to be least significant
	//we add one to make sure we're shifting enough (because our parameter is passed as ZERO-index)
	bits = bits >> ((8 - (index + 1)) * 4);
	
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
