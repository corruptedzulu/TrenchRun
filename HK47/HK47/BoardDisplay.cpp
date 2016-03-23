#include "stdafx.h"
#include "BoardDisplay.h"


BoardDisplay::BoardDisplay()
{
}


BoardDisplay::~BoardDisplay()
{
}

void BoardDisplay::createPrintableArrayFromBitBoards(vector<BitBoard> bitboards)
{
	string name, type;
	for each (BitBoard board in bitboards)
	{
		name = board.getName();
		type = board.getType();
		if (type == "Wall")
		{ 
			if (name == "My Left Wall" || name == "My Right Wall")
			{

			}
			else
			{

			}
		}
		else if (type == "Death Star")
		{
			if (name == "My Death Star")
			{

			}
			else
			{

			}
		}
		else if (type == "X Wing")
		{
			if (name == "My X Wing One" || name == "My X Wing Two" || name == "My X Wing Three" || name == "My X Wing Four")
			{

			}
			else
			{

			}
		}
		else if (type == "TIE Fighter")
		{
			if (name == "My Left Wall" || name == "My Right Wall")
			{

			}
			else
			{

			}
		}
		else
		{
			cout << "Unknown type detected: " << type;
		}
	}
}
