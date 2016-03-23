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



	userInterface.refreshBoardDisplay();
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