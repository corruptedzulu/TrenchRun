/*

		BitBoard class
		
		Represents a portion of the board state as an integer
		Using multiple bitboards and logical ops, we can make 
		determinations about the game.



		Our game, Trench Run, uses a 7x7 board. Standard bit boards are 8x8.
		So, we'll do the same, but just exclude the outer perimeter (opposite of starting index).

		Like this (X is board square, 0 is excluded):

		0 0 0 0 0 0 0 0
		X X X X X X X 0
		X X X X X X X 0
		X X X X X X X 0
		X X X X X X X 0
		X X X X X X X 0
		X X X X X X X 0
		X X X X X X X 0

		The lower left hand corner is index ZERO (0).
		The indexing increases left to right, bottom to top.
		All values in row 7 or column 7 are ignored.
		So, 
			if (INDEX + 1 % 8 == 0)  IGNORE;
			if (INDEX + 1 >= 56) IGNORE;



		The Opponent board is like this:

		0 X X X X X X X
		0 X X X X X X X
		0 X X X X X X X 
		0 X X X X X X X
		0 X X X X X X X
		0 X X X X X X X
		0 X X X X X X X
		0 0 0 0 0 0 0 0
	




*/






#pragma once

#include <string>

using namespace std;
class BitBoard
{
private:
	string type;
	uint64_t board;

	uint64_t convertRowColToBitBoard(char row, char col);
	char convertOpponentViewToMyViewRow(char row);
	char convertOpponentViewToMyViewCol(char col);

public:
	BitBoard();
	BitBoard(string t);
	BitBoard(string t, char row, char col);
	~BitBoard();

	void setBoard(uint64_t b);
	string getType();

};

