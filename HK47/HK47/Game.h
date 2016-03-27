#pragma once

#include "AI.h"
#include "UserInterface.h"
#include "BitBoard.h"
#include "MoveGenerator.h"
#include "Move.h"
#include <vector>
#include <algorithm>

using namespace std;


#define STARTING_BOARD 0x6D39C701C7396DFF


class Game
{

private:

	bool gameIsInProgress;
	int victor = 0;


	UserInterface userInterface;
	AI ai;
	MoveGenerator mover;

	vector<uint64_t> allPiecesVector;
	vector<uint64_t> myPiecesVector;
	vector<uint64_t> opponentPiecesVecotr;
	//vector<uint64_t> removedMyPieces;
	//vector<uint64_t> removedOpponentPieces;


	// attributes for all of the pieces in play
	// attributes indicate which piece is at that place on the board
	// can also indicate other things if needed
	//
	// 8, 32-bit numbers. one for each row
	// 0-index is the first row. lowest bit is the first column
	// stored in this form:
	// 0000 0000 0000 0000 0000 0000 0000 0000
	//
	// attribute assignments:
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
	uint32_t allPiecesAttr[8];


	// to use the attributes, extract them by turning off the other bits
	// (AND these masks with a copy of the attribute row)
	// flags to do so are:
	uint32_t columnOne =   0xF0000000; // 11110000000000000000000000000000;
	uint32_t columnTwo =   0x0F000000; // 00001111000000000000000000000000;
	uint32_t columnThree = 0x00F00000; // 00000000111100000000000000000000;
	uint32_t columnFour =  0x000F0000; // 00000000000011110000000000000000;
	uint32_t columnFive =  0x0000F000; // 00000000000000001111000000000000;
	uint32_t columnSix =   0x00000F00; // 00000000000000000000111100000000;
	uint32_t columnSeven = 0x000000F0; // 00000000000000000000000011110000;
	uint32_t columnEight = 0x0000000F; // 00000000000000000000000000001111;

	uint64_t pieces;
	
	uint32_t getAttributesOfColumnForRow(uint32_t mask, uint32_t attribute);
	void updateGameBoardWithMove(Move move);
	bool isGameOver();



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

