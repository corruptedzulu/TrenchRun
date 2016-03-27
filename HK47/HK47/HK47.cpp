// HK47.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "BitBoard.h"
#include "Move.h"
#include "HK47.h"
#include "Game.h"
#include "UserInterface.h"



//this can determine them for all players
void determineLegalMoves(BitBoard currentState, int humanComputerOrAll)
{
	if (humanComputerOrAll == 0) //all legal moves
	{

	}
	else if (humanComputerOrAll == 1) //computer legal moves
	{

	}
	else if(humanComputerOrAll == 2) //player legal moves
	{

	}
	else
	{
		cout << "Error! determineLegalMoves() not passed a valid int parameter!" << endl;
		exit(-1);
	}
}


int evaluateMove()
{
	return 0;
}

void makeMove()
{


}

void determineMove()
{


}


void getMove()
{


}

void displayBoard()
{


}






int main()
{

	Game *game = new Game();
	//game->initHelpers();
	game->initBoard();
	game->initDisplay();
	game->initAI();

	game->gameLoop();

    return 0;
}

