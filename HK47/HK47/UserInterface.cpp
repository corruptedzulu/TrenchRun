#include "stdafx.h"
#include "UserInterface.h"
#include <conio.h>


UserInterface::UserInterface()
{
}


UserInterface::~UserInterface()
{
}

void UserInterface::refreshBoardDisplay()
{
}

void UserInterface::printBoard(vector<BitBoard> pieces)
{
	boardDisplay.createPrintableArrayFromBitBoards(pieces);
}

void UserInterface::printComputerMove()
{
}

void UserInterface::printMakeMoveRequest()
{
	cout << "Request: Please enter your move: ";
}

void UserInterface::getNextMove()
{
	string move = "";
	for (int x = 0; x < 4; x++)
	{
		move += getch();
		beginMoveExecution(move);
	}
}

bool UserInterface::askWhichPlayerStarts()
{
	bool opponentStartsFirst;
	string answer;
	cout << "Interrogative: Would you like to play first? ";
	cin >> answer;

	if (answer == "yes" || answer == "Yes" || answer == "y" || answer == "Y")
	{
		opponentStartsFirst = true;
	}
	else
	{
		opponentStartsFirst = false;
	}

	return opponentStartsFirst;

}

void UserInterface::printOpeningMessage()
{
	cout << "Greeting: This ";
}

void UserInterface::printPlayerVictory()
{
	cout << "Disappointment: You have bested me.";
}

void UserInterface::printComputerVictory()
{
	cout << "Satisfaction: I have won.";
}

void UserInterface::printTie()
{
	cout << "Observation: We are evenly matched."
}

void UserInterface::printIllegalMove()
{
	cout << "Statement: That is not a valid move.";
}
