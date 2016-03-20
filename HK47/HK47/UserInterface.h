#pragma once

#include "BoardDisplay.h"

class UserInterface
{

private:
	BoardDisplay boardDisplay;


public:
	UserInterface();
	~UserInterface();

	void refreshBoardDisplay();
	void printBoard();
	void printComputerMove();
	void printMakeMoveRequest();


	void getNextMove();
	bool askWhichPlayerStarts();
	
	void printOpeningMessage();
	void printPlayerVictory();
	void printComputerVictory();
	void printTie();

	void printIllegalMove();

};

