#pragma once
class UserInterface
{
public:
	UserInterface();
	~UserInterface();

	void refreshBoardDisplay();
	void printBoard();
	void printComputerMove();
	void printMakeMoveRequest();


	void getNextMove();
	void askWhichPlayerStarts();
	
	void printOpeningMessage();
	void printPlayerVictory();
	void printComputerVictory();
	void printTie();

	void printIllegalMove();

};

