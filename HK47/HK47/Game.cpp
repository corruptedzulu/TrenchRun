#include "stdafx.h"
#include "Game.h"





Game::Game()
{
	gameIsInProgress = true;
	victor = 0;

	computerDidMoveTIESideways = false;
	playerDidMoveTIESideways = false;
}


Game::~Game()
{
}


void Game::gameLoop()
{
	vector<Move> possibleMoves;

	userInterface.printOpeningMessage();
	
	bool opponentPlaysFirst = userInterface.askWhichPlayerStarts();

	userInterface.printBoard(pieces, allPiecesAttr);

	if (!opponentPlaysFirst)
	{
		possibleMoves = mover.findMoves(pieces, allPiecesAttr, true, computerDidMoveTIESideways);
		Move computerMove = ai.determineComputerMove(possibleMoves, pieces, allPiecesAttr, computerDidMoveTIESideways, playerDidMoveTIESideways);

		updateGameBoardWithMove(computerMove);

		userInterface.printComputerMove(computerMove);

		userInterface.printBoard(pieces, allPiecesAttr);


		if (isGameOver())
		{
			gameIsInProgress = false;

			//computer wins
			if (victor == 1)
			{
				userInterface.printComputerVictory();
			}
			//opponent wins
			else if (victor == 2)
			{
				userInterface.printPlayerVictory();
			}
			//tie
			else
			{
				userInterface.printTie();
			}

		}
	}


	while (gameIsInProgress)
	{
		//before we ask the user for their next move, let's find the possibilites they can take
		possibleMoves = mover.findMoves(pieces, allPiecesAttr, false, playerDidMoveTIESideways);

		if (possibleMoves.size() == 0)
		{
			userInterface.printComputerVictory();
			break;
		}

		userInterface.printMakeMoveRequest();
		Move opponentMove = userInterface.getNextMove();

		//check move legality
		//vector<Move>::iterator it;
		//it = find(possibleMoves.begin(), possibleMoves.end(), opponentMove);


		//TODO: this is not correctly identifying matches
		Move temp;
		bool illegalMove = true;
		for (int x = 0; x < possibleMoves.size(); x++)
		{
			temp = possibleMoves.at(x);
			uint64_t tempDes = possibleMoves.at(x).getDestination();
			uint64_t tempLoc = possibleMoves.at(x).getLocation();
			uint64_t oppDes = opponentMove.getDestination();
			uint64_t oppLoc = opponentMove.getLocation();

			/*if ( temp.getDestination() == opponentMove.getDestination())
			{
				if (temp.getLocation() == opponentMove.getLocation())
				{
					illegalMove = false;
				}
			}*/

			if (tempDes == oppDes)
			{
				if (tempLoc == oppLoc)
				{
					illegalMove = false;
					break;
				}
			}
		}

		if (illegalMove) //if we did NOT find the match, the move is illegal
		{
			//opponent's move was illegal
			userInterface.printIllegalMove();
			//skip to the next while() iteration and ask for a different move
			continue;
		}

		updateGameBoardWithMove(opponentMove);
		
		userInterface.printBoard(pieces, allPiecesAttr);


		if (playerDidMoveTIESideways)
		{
			playerDidMoveTIESideways = false;
		}


		//TODO: check if player moved a TIE Fighter sideways

		//check if this moves a TIE sideways
		uint64_t rowLoc = opponentMove.getLocation();
		uint64_t rowDes = opponentMove.getDestination();

		rowLoc = log2_64(rowLoc) + 1;
		rowDes = log2_64(rowDes) + 1;

		rowLoc = rowLoc / 8;
		rowDes = rowDes / 8;


		//if these are on the same row, then it is a sideways move
		if (rowLoc == rowDes)
		{
			playerDidMoveTIESideways = true;
			//movedTieOnLastTurn = true;
		}




		if (isGameOver())
		{
			gameIsInProgress = false;

			//computer wins
			if (victor == 1)
			{
				userInterface.printComputerVictory();
			}
			//opponent wins
			else if (victor == 2)
			{
				userInterface.printPlayerVictory();
			}
			//tie
			else
			{
				userInterface.printTie();
			}

			break;
		}

		possibleMoves = mover.findMoves(pieces, allPiecesAttr, true, computerDidMoveTIESideways);

		if (possibleMoves.size() == 0)
		{
			userInterface.printPlayerVictory();
			break;
		}

		Move computerMove = ai.determineComputerMove(possibleMoves, pieces, allPiecesAttr, computerDidMoveTIESideways, playerDidMoveTIESideways);

		updateGameBoardWithMove(computerMove);

		userInterface.printComputerMove(computerMove);

		userInterface.printBoard(pieces, allPiecesAttr);


		if (playerDidMoveTIESideways)
		{
			playerDidMoveTIESideways = false;
		}


		//check if this moves a TIE sideways
		rowLoc = opponentMove.getLocation();
		rowDes = opponentMove.getDestination();

		rowLoc = log2_64(rowLoc) + 1;
		rowDes = log2_64(rowDes) + 1;

		rowLoc = rowLoc / 8;
		rowDes = rowDes / 8;


		//if these are on the same row, then it is a sideways move
		if (rowLoc == rowDes)
		{
			computerDidMoveTIESideways = true;
			//movedTieOnLastTurn = true;
		}




		if (isGameOver())
		{
			gameIsInProgress = false;

			//computer wins
			if (victor == 1)
			{
				userInterface.printComputerVictory();
			}
			//opponent wins
			else if (victor == 2)
			{
				userInterface.printPlayerVictory();
			}
			//tie
			else
			{
				userInterface.printTie();
			}

			break;
		}
		
		
	}

	cout << endl << "Instruction: Press Q to terminate this training scenario, Master. ";
	char answer;
	cin >> answer;
	
	while (answer != 'Q' || answer != 'q')
	{
		cout << endl << "Observation: Droids are far more dextrous than most meatbags. Try again, Master: ";
		cin >> answer;
	}

}

void Game::initHelers()
{

}

void Game::initBoard()
{
	pieces = STARTING_BOARD;
	allPiecesAttr[0] = 0x0880880F;
	allPiecesAttr[1] = 0x0076700F;
	allPiecesAttr[2] = 0x9A000A9F;
	allPiecesAttr[3] = 0x0000000F;
	allPiecesAttr[4] = 0x4500054F;
	allPiecesAttr[5] = 0x0021200F;
	allPiecesAttr[6] = 0x0330330F;
	allPiecesAttr[7] = 0xFFFFFFFF;

	/*allPiecesAttr[0] = 0xF0880880;
	allPiecesAttr[1] = 0xF0076700;
	allPiecesAttr[2] = 0xF9A000A9;
	allPiecesAttr[3] = 0xF0000000;
	allPiecesAttr[4] = 0xF4500054;
	allPiecesAttr[5] = 0xF0021200;
	allPiecesAttr[6] = 0xF0330330;
	allPiecesAttr[7] = 0xFFFFFFFF;*/
}

void Game::initDisplay()
{
	cout << endl;

}

void Game::initAI()
{

}

void Game::createBitBoards()
{
	BitBoard *myDeathStar = new BitBoard("My Death Star", "Death Star", true, '6', 'D');
BitBoard *opponentDeathStar = new BitBoard("Opponent Death Star", "Death Star", false, '2', 'D');


BitBoard *myWallLeft = new BitBoard("My Left Wall", "Wall", true, '6', 'C');
BitBoard *myWallRight = new BitBoard("My Right Wall", "Wall", true, '6', 'E');;
BitBoard *opponentWallLeft;
BitBoard *opponentWallRight;


BitBoard *myTIEFighterOne;
BitBoard *myTIEFighterTwo;
BitBoard *myTIEFighterThree;
BitBoard *myTIEFighterFour;
BitBoard *opponentTIEFighterOne;
BitBoard *opponentTIEFighterTwo;
BitBoard *opponentTIEFighterThree;
BitBoard *opponentTIEFighterFour;



//X Wings 2 and 3, for both sides, cannot capture the Death Star

BitBoard *myXWingOne;
BitBoard *myXWingTwo;
BitBoard *myXWingThree;
BitBoard *myXWingFour;
BitBoard *opponentXWingOne;
BitBoard *opponentXWingTwo;
BitBoard *opponentXWingThree;
BitBoard *opponentXWingFour;

}

uint32_t Game::getAttributesOfColumnForRow(uint32_t mask, uint32_t attribute)
{
	return attribute & mask;
}

void Game::updateGameBoardWithMove(Move move)
{
	
	pieces = pieces - move.getLocation();
	
	uint64_t boardMask = 0x1 << (int)(log2(move.getDestination()));

	if ((pieces & boardMask) == 0)
	{
		pieces = pieces + move.getDestination();
	}

	uint64_t location = move.getLocation();
	uint64_t destination = move.getDestination();

	int colLoc = (log2_64(location) + 1) % 8;
	int rowLoc = (log2_64(location) + 1) / 8;

	int colDes = (log2_64(destination) + 1) % 8;
	int rowDes = (log2_64(destination) + 1) / 8;

	//set a mask to the desired place for the column
	uint32_t mask = 0xF0000000 >> (colLoc * 4);

	//now, get the number from the column on its own
	uint32_t value = mask & allPiecesAttr[rowLoc];

	//remove the value from the current row
	allPiecesAttr[rowLoc] = allPiecesAttr[rowLoc] - value;


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
	uint32_t destValue = destMask & allPiecesAttr[rowDes];

	//remove the value from the current row
	allPiecesAttr[rowDes] = allPiecesAttr[rowDes] - destValue;



	//we've removed the place we're going to from the attributes, so now we add our move's attributes to there
	allPiecesAttr[rowDes] = allPiecesAttr[rowDes] + value;
}

bool Game::isGameOver()
{
	uint32_t mask = 0xf << (3 * 4);
	if (allPiecesAttr[1] & mask == 0)
	{
		victor = 1;
		return true;
	}

	if (allPiecesAttr[5] & mask == 0)
	{
		victor = 2;
		return true;
	}


	return false;
}
