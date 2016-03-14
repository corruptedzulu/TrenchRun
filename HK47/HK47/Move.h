#pragma once

#include "BitBoard.h"

class Move
{
	uint64_t location;
	uint64_t destination;

public:
	Move();
	Move(uint64_t l);
	~Move();

	void moveToLocation(uint64_t d);
};

