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
	while (gameIsInProgress)
	{
		userInterface.printMakeMoveRequest();
		Move opponentMove = userInterface.getNextMove();

		//check move legality
		if (move is NOT legal)
		{
			//opponent's move was illegal
			userInterface.printIllegalMove();
			//skip to the next while() iteration and ask for a different move
			continue;
		}

		updateGameBoardWithMove(opponentMove);
		
		userInterface.refreshBoardDisplay();

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


		Move computerMove = ai.determineComputerMove();

		updateGameBoardWithMove(computerMove);

		userInterface.printComputerMove();

		userInterface.refreshBoardDisplay();


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
	createBitBoards();
}

void Game::initDisplay()
{

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
}

bool Game::isGameOver()
{
	return false;
}
