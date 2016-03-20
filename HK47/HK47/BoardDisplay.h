#pragma once

#include <vector>
#include "BitBoard.h"

class BoardDisplay
{
public:
	BoardDisplay();
	~BoardDisplay();


	void createPrintableArrayFromBitBoards(vector<BitBoard> bitboards);

};

