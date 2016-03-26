#pragma once

#include "Move.h"

class AI
{

public:
	AI();
	~AI();



	Move determineComputerMove();

	void minimax();
	int minimaxMax(int depth);
	int minimaxMin(int depth);
};

