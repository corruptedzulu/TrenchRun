#include "stdafx.h"
#include "Game.h"





Game::Game()
{
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
		possibleMoves = mover.findMoves(pieces, allPiecesAttr, true, false);
		Move computerMove = ai.determineComputerMove(possibleMoves, pieces, allPiecesAttr);

		updateGameBoardWithMove(computerMove);

		userInterface.printComputerMove();

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
		possibleMoves = mover.findMoves(pieces, allPiecesAttr, false, false);

		userInterface.printMakeMoveRequest();
		Move opponentMove = userInterface.getNextMove();

		//check move legality
		//vector<Move>::iterator it;
		//it = find(possibleMoves.begin(), possibleMoves.end(), opponentMove);

		Move temp;
		bool illegalMove = false;
		for (int x = 0; x < possibleMoves.size(); x++)
		{
			temp = possibleMoves.at(x);
			if (temp.getDestination() == temp.getDestination() && temp.getLocation() == temp.getLocation())
			{
				illegalMove == true;
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

			continue;
		}

		possibleMoves = mover.findMoves(pieces, allPiecesAttr, true, false);
		Move computerMove = ai.determineComputerMove(possibleMoves, pieces, allPiecesAttr);

		updateGameBoardWithMove(computerMove);

		userInterface.printComputerMove();

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

			continue;
		}
		
		
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
	pieces = pieces + move.getDestination();
}

bool Game::isGameOver()
{
	return false;
}
