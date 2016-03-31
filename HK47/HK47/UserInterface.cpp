#include "stdafx.h"
#include "UserInterface.h"
#include <conio.h>


UserInterface::UserInterface()
{
}


UserInterface::~UserInterface()
{
}

void UserInterface::printBoard(uint64_t board, uint32_t pieces[])
{
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

	/*
	Board Pieces and Representations

	My Pieces:
	Death Star  - *
	Wall        - #
	TIE Fighter - H
	X Wing      - X

	Color: White

	Opponent Pieces:
	Death Star  - *
	Wall        - #
	TIE Fighter - H
	X Wing      - X

	Color: Red



	Background is:
	Blue and Cyan
	Alternating bright, reset?

	*/

	char pieceChars[64];
	int pieceColors[64];
	int pieceBackgrounds[64] = { BLUE, CYAN, BLUE, CYAN, BLUE, CYAN, BLUE, CYAN,
								 CYAN, BLUE, CYAN, BLUE, CYAN, BLUE, CYAN, BLUE,
								 BLUE, CYAN, BLUE, CYAN, BLUE, CYAN, BLUE, CYAN,
								 CYAN, BLUE, CYAN, BLUE, CYAN, BLUE, CYAN, BLUE,
								 BLUE, CYAN, BLUE, CYAN, BLUE, CYAN, BLUE, CYAN,
								 CYAN, BLUE, CYAN, BLUE, CYAN, BLUE, CYAN, BLUE,
								 BLUE, CYAN, BLUE, CYAN, BLUE, CYAN, BLUE, CYAN,
								 CYAN, BLUE, CYAN, BLUE, CYAN, BLUE, CYAN, BLUE
								};


	for (int x = 7; x >= 0; x--) //reverse order because we print downward
	{
		uint32_t one, two, three, four, five, six, seven, eight;




		one = getAttributesOfColumnForRow(pieces[x], 1);
		two = getAttributesOfColumnForRow(pieces[x], 2);
		three = getAttributesOfColumnForRow(pieces[x], 3);
		four = getAttributesOfColumnForRow(pieces[x], 4);
		five = getAttributesOfColumnForRow(pieces[x], 5);
		six = getAttributesOfColumnForRow(pieces[x], 6);
		seven = getAttributesOfColumnForRow(pieces[x], 7);
		eight = getAttributesOfColumnForRow(pieces[x], 8);


		pieceChars[x * 8 + 0] = getCharacterForAttributeNumber(one);
		pieceChars[x * 8 + 1] = getCharacterForAttributeNumber(two);
		pieceChars[x * 8 + 2] = getCharacterForAttributeNumber(three);
		pieceChars[x * 8 + 3] = getCharacterForAttributeNumber(four);
		pieceChars[x * 8 + 4] = getCharacterForAttributeNumber(five);
		pieceChars[x * 8 + 5] = getCharacterForAttributeNumber(six);
		pieceChars[x * 8 + 6] = getCharacterForAttributeNumber(seven);
		pieceChars[x * 8 + 7] = getCharacterForAttributeNumber(eight);


		pieceColors[x * 8 + 0] = getColorForAttributeNumber(one);
		pieceColors[x * 8 + 1] = getColorForAttributeNumber(two);
		pieceColors[x * 8 + 2] = getColorForAttributeNumber(three);
		pieceColors[x * 8 + 3] = getColorForAttributeNumber(four);
		pieceColors[x * 8 + 4] = getColorForAttributeNumber(five);
		pieceColors[x * 8 + 5] = getColorForAttributeNumber(six);
		pieceColors[x * 8 + 6] = getColorForAttributeNumber(seven);
		pieceColors[x * 8 + 7] = getColorForAttributeNumber(eight);



		for (int y = 0; y < 8; y++)
		{

			//textColor(DIM, pieceColors[x * 8 + y], pieceBackgrounds[x * 8 + y]);
			cout << pieceChars[x * 8 + y] << " ";
		}

		cout << endl;
		


	}



	/*string name, type;
	for (int x = 0; x < 7; x++)
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
	}*/
}

void UserInterface::printComputerMove()
{
	string pieceName;
	string startingLocation;
	string endingLocation;

	cout << "Statement: I am moving my " << pieceName << " from " << startingLocation << " to " << endingLocation << "." << endl;
}

void UserInterface::printMakeMoveRequest()
{
	cout << "Request: Please enter your move: ";
}

Move UserInterface::getNextMove()
{
	string move = "";
	Move desiredMove;
	
	/*char movePart;
	for (int x = 0; x < 4; x++)
	{
		movePart = getch();
		cout << movePart;
		move += movePart;
		beginMoveExecution(move);
	}*/

	cin >> move;

	//convert the first two characters (respresenting ROW and COLUMN) into a bitboard of that location
	//set that as the starting location
	desiredMove.setStartLocation(desiredMove.convertColRowToBitBoard(move[0], move[1]));

	//convert the second two characters (representing ROW and COLUMN) into a bitboard of that location
	//have the Move generated the ending location
	//desiredMove.moveToLocation(desiredMove.convertRowColToBitBoard(move[2], move[3]));
	desiredMove.setDestinationLocation(desiredMove.convertColRowToBitBoard(move[2], move[3]));

	desiredMove.setIsBackwardsMovement(move[1] > move[3]);

	return desiredMove;

}

bool UserInterface::askWhichPlayerStarts()
{
	bool opponentStartsFirst;
	string answer;
	cout << "Interrogative: Would you like to play first? ";
	cin >> answer;

	if (answer == "yes" || answer == "Yes" || answer == "y" || answer == "Y")
	{
		opponentStartsFirst = true;
	}
	else
	{
		opponentStartsFirst = false;
	}

	return opponentStartsFirst;

}

void UserInterface::printOpeningMessage()
{
	cout << "Greeting: This ";
}

void UserInterface::printPlayerVictory()
{
	cout << "Disappointment: You have bested me.";
}

void UserInterface::printComputerVictory()
{
	cout << "Satisfaction: I have won.";
}

void UserInterface::printTie()
{
	cout << "Observation: We are evenly matched.";
}

void UserInterface::printIllegalMove()
{
	cout << "Statement: That is not a valid move.";
}


void UserInterface::textColor(int attr, int fg, int bg)
{
	char command[13];
	sprintf_s(command, "%c[%d;%d;%dm", 0x1B, attr, fg + 30, bg + 40);
	printf("%s", command);
}



uint32_t UserInterface::getAttributesOfColumnForRow(uint32_t attributes, int index)
{
	//char val;
	uint32_t mask = 0xF0000000;

	//shift down one for ZEROindexing
	index--;

	//shift the mask as far over as needed to match the index 
	mask = mask >> ((index)* 4);

	//AND the input with the mask to remove the other stuff
	attributes = attributes & mask;

	//shift those bits to be least significant
	//we add one to make sure we're shifting enough (because our parameter is passed as ZERO-index)
	attributes = attributes >> ((8 - (index + 1)) * 4);

	return attributes;
}

char UserInterface::getCharacterForAttributeNumber(int number)
{
	char returnable = ' ';
	switch (number)
	{
	case 0:
		returnable = ' ';
		break;
	case 1:
		returnable = '*';
		break;
	case 2:
		returnable = '#';
		break;
	case 3:
		returnable = 'H';
		break;
	case 4:
		returnable = 'X';
		break;
	case 5:
		returnable = 'X';
		break;
	case 6:
		returnable = '*';
		break;
	case 7:
		returnable = '#';
		break;
	case 8:
		returnable = 'H';
		break;
	case 9:
		returnable = 'X';
		break;
	case 10:
		returnable = 'X';
		break;
	case 11:
		returnable = ' ';
		break;
	case 12:
		returnable = ' ';
		break;
	case 13:
		returnable = ' ';
		break;
	case 14:
		returnable = ' ';
		break;
	case 15:
		returnable = ' ';
		break;
	}


	return returnable;
}

int UserInterface::getColorForAttributeNumber(int number)
{
	if (number < 6 && number > 0)
	{
		//mine
		return WHITE;
	}

	if (number > 5 && number < 11)
	{
		//opponent
		return RED;
	}

	return HIDDEN;//dunno?
}
