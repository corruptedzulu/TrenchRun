#pragma once

#include "AI.h"
class Game
{
	UserInterface userInterface;
	AI ai;

public:
	Game();
	~Game();

	void gameLoop();
};

