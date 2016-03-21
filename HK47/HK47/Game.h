#pragma once

#include "AI.h"
#include "UserInterface.h"
#include "BitBoard.h"
#include "MoveGenerator.h"
#include <vector>

class Game
{
	UserInterface userInterface;
	AI ai;
	MoveGenerator mover;

	vector<BitBoard> allPieces;
	vector<BitBoard> myPieces;
	vector<BitBoard> opponentPieces;

	vector<BitBoard> removedMyPieces;
	vector<BitBoard> removedOpponentPieces;



public:
	Game();
	~Game();

	void gameLoop();
	void initHelers();
	void initBoard();
	void initDisplay();
	void initAI();

	void createBitBoards();

};

