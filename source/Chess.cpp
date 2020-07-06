//
//  Chess.cpp
//  Chess
//
//  Created by Main on 07/01/2020.
//  Copyright © 2020 Junaid Afzal. All rights reserved.
//

#include "../include/Chess.hpp"
#include <time.h>
#include <string>

void Play_Chess(void)
{
	std::vector< std::vector<std::string> > Board;
	std::vector<std::string> WhiteCapturedPieces;
	std::vector<std::string> BlackCapturedPieces;
	unsigned int NumberOfPlayers;
	std::string HumanPlayer, CurrentPlayer;

	Setup_Game(Board, NumberOfPlayers, HumanPlayer, CurrentPlayer);

	while (!Game_Over())
	{
		Toggle_Player(CurrentPlayer);

		Display_Game(Board);

		std::string NextMove;

		switch (NumberOfPlayers)
		{
		case 0:
			NextMove = Ask_AI_For_Next_Move(Board, CurrentPlayer, WhiteCapturedPieces, BlackCapturedPieces);
			break;

		case 1:
		{
			if (CurrentPlayer == HumanPlayer)
				NextMove = Ask_User_For_Next_Move(Board, CurrentPlayer, WhiteCapturedPieces, BlackCapturedPieces);

			else
				NextMove = Ask_AI_For_Next_Move(Board, CurrentPlayer, WhiteCapturedPieces, BlackCapturedPieces);

			break;
		}

		case 2:
			NextMove = Ask_User_For_Next_Move(Board, CurrentPlayer, WhiteCapturedPieces, BlackCapturedPieces);
			break;

		default:
			std::cout << "Error in number of players switch statement" << '\n';
			break;
		}

		Execute_Next_Move();
	}

	Display_Game(Board);

	Display_Winning_Message();
}

void Test_Chess(void)
{
	std::vector< std::vector<std::string> > Board;
	std::vector<std::string> WhiteCapturedPieces;
	std::vector<std::string> BlackCapturedPieces;
	unsigned int NumberOfPlayers;
	std::string HumanPlayer, CurrentPlayer;

	Setup_Game(Board, NumberOfPlayers, HumanPlayer, CurrentPlayer);

	while (!Game_Over())
	{
		Toggle_Player(CurrentPlayer);

		Display_Game(Board);

		std::string NextMove;

		NextMove = Ask_AI_For_Next_Move(Board, CurrentPlayer, WhiteCapturedPieces, BlackCapturedPieces);

		Execute_Next_Move();
	}

	Display_Game(Board);

	Display_Winning_Message();
}

void Setup_Game(std::vector< std::vector<std::string> >& Board,
				unsigned int& NumberOfPlayers,
				std::string& HumanPlayer,
				std::string& CurrentPlayer) 
{
	std::cout << "--------------------Chess--------------------\n\n";

	for (unsigned int i = 0; i < 8; i++)
	{
		std::vector<std::string> Rows;
		Board.push_back(Rows);

		for (unsigned int j = 0; j < 8; j++)
		{
			Board[i].push_back(" . ");

			if (i == 0)
				switch (j)
				{
				case 0:
					Board[i][j] = "BR1";
					break;

				case 1:
					Board[i][j] = "BK1";
					break;

				case 2:
					Board[i][j] = "BB1";
					break;

				case 3:
					Board[i][j] = "BQ ";
					break;

				case 4:
					Board[i][j] = "BK ";
					break;

				case 5:
					Board[i][j] = "BB2";
					break;

				case 6:
					Board[i][j] = "BK2";
					break;

				case 7:
					Board[i][j] = "BR2";
					break;

				default:
					std::cout << "Error in black pieces setup in Setup_Game()" << '\n';
					break;
				}

			else if (i == 1)
				switch (j)
				{
				case 0:
					Board[i][j] = "BP1";
					break;

				case 1:
					Board[i][j] = "BP2";
					break;

				case 2:
					Board[i][j] = "BP3";
					break;

				case 3:
					Board[i][j] = "BP4";
					break;

				case 4:
					Board[i][j] = "BP5";
					break;

				case 5:
					Board[i][j] = "BP6";
					break;

				case 6:
					Board[i][j] = "BP7";
					break;

				case 7:
					Board[i][j] = "BP8";
					break;

				default:
					std::cout << "Error in black pawn setup in Setup_Game()" << '\n';
					break;
				}

			else if (i == 6)
				switch (j)
				{
				case 0:
					Board[i][j] = "WP1";
					break;

				case 1:
					Board[i][j] = "WP2";
					break;

				case 2:
					Board[i][j] = "WP3";
					break;

				case 3:
					Board[i][j] = "WP4";
					break;

				case 4:
					Board[i][j] = "WP5";
					break;

				case 5:
					Board[i][j] = "WP6";
					break;

				case 6:
					Board[i][j] = "WP7";
					break;

				case 7:
					Board[i][j] = "WP8";
					break;

				default:
					std::cout << "Error in white pawn setup in Setup_Game()" << '\n';
					break;
				}

			else if (i == 7)
				switch (j)
				{
				case 0:
					Board[i][j] = "WR1";
					break;

				case 1:
					Board[i][j] = "WK1";
					break;

				case 2:
					Board[i][j] = "WB1";
					break;

				case 3:
					Board[i][j] = "WQ ";
					break;

				case 4:
					Board[i][j] = "WK ";
					break;

				case 5:
					Board[i][j] = "WB2";
					break;

				case 6:
					Board[i][j] = "WK2";
					break;

				case 7:
					Board[i][j] = "WR2";
					break;

				default:
					std::cout << "Error in white pieces setup in Setup_Game()" << '\n';
					break;
				}		
		}
	}


	NumberOfPlayers = Ask_User_For_Number_Of_Players();

	std::srand((unsigned int)time(0));

	if (NumberOfPlayers == 1)
		HumanPlayer = "WHITE";

	if ((std::rand() % 2) == 0)
		CurrentPlayer = "WHITE";
	else
		CurrentPlayer = "BLACK";
}

int Ask_User_For_Number_Of_Players(void)
{
	bool isValueCorrect = false; // Flag for if input value in invalid
	unsigned int NumberOfPlayers = 0;

	while (!isValueCorrect)
	{
		// Prompt user for next command that will be the next grid position to attack
		std::cout << "Enter the number of human player: ";

		std::cin >> NumberOfPlayers;

		// Check if cin failed
		if (std::cin.fail())
		{
			// Clear buffer and retry
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			isValueCorrect = false;
			continue;
		}

		// Check if value is 0, 1 or 2
		if (NumberOfPlayers != 0 && NumberOfPlayers != 1 && NumberOfPlayers != 2)
			continue;

		// If all checks passed then value is valid
		else
			isValueCorrect = true;
	}

	// This is to clear .22222 in a value 5.22222 as value would assume to be 5
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	return NumberOfPlayers;
}

bool Game_Over()
{
	//*******************************************************
	// Check if WK/BK are in check
	// and all possible moves result in check thus checkmate
	// But if not in check and all possible moves that opponent can play result in check then stalemate
	//*******************************************************

	return false;
}

bool Is_King_In_Check()
{
	return false;
}

void Toggle_Player(std::string& CurrentPlayer)
{
	if (CurrentPlayer == "BLACK")
		CurrentPlayer = "WHITE";
	else
		CurrentPlayer = "BLACK";
}

void Display_Game(const std::vector< std::vector<std::string> >& Board)
{
	// ***Better alternative needed***
	// Clears terminal window
	system("cls");

	std::cout << "--------------------Chess--------------------\n\n";

	for (unsigned int i = 0; i < 8; i++)
	{
		if (i == 0)
			std::cout << "     A   B   C   D   E   F   G   H" << "\n\n";

		for (unsigned int j = 0; j < 8; j++)
		{
			if (j == 0)
				std::cout << " " << 8 - i << "   ";

			std::cout << Board[i][j] << " ";
			
			if (j == 7)
				std::cout << "  " << 8 - i;
		}

		std::cout << '\n';

		if (i == 7)
			std::cout << '\n' << "     A   B   C   D   E   F   G   H" << "\n\n\n";
	}

	// Some sort of score tracker of pieces captured
}

std::string Ask_AI_For_Next_Move(const std::vector< std::vector<std::string> >& Board,
								 const std::string& CurrentPlayer,
								 std::vector<std::string> & WhiteCapturedPieces,
								 std::vector<std::string> & BlackCapturedPieces)
{
	bool isValueCorrect = false; // Flag for if input value in invalid
	std::string NextMove;

	while (!isValueCorrect)
	{
		std::string ChessPiece;

		unsigned int ChessPieceInt = std::rand() % 16;
		if (CurrentPlayer == "WHITE")
			switch (ChessPieceInt)
			{
			case 0:
				ChessPiece = "WR1";
				break;

			case 1:
				ChessPiece = "WK1";
				break;

			case 2:
				ChessPiece = "WB1";
				break;

			case 3:
				ChessPiece = "WQ";
				break;

			case 4:
				ChessPiece = "WK";
				break;

			case 5:
				ChessPiece = "WB2";
				break;

			case 6:
				ChessPiece = "WK2";
				break;

			case 7:
				ChessPiece = "WR2";
				break;

			case 8:
				ChessPiece = "WP1";
				break;

			case 9:
				ChessPiece = "WP2";
				break;

			case 10:
				ChessPiece = "WP3";
				break;

			case 11:
				ChessPiece = "WP4";
				break;

			case 12:
				ChessPiece = "WP5";
				break;

			case 13:
				ChessPiece = "WP6";
				break;

			case 14:
				ChessPiece = "WP7";
				break;

			case 15:
				ChessPiece = "WP8";
				break;
			}

		else if (CurrentPlayer == "BLACK")
			switch (ChessPieceInt)
			{
			case 0:
				ChessPiece = "BR1";
				break;

			case 1:
				ChessPiece = "BK1";
				break;

			case 2:
				ChessPiece = "BB1";
				break;

			case 3:
				ChessPiece = "BQ";
				break;

			case 4:
				ChessPiece = "BK";
				break;

			case 5:
				ChessPiece = "BB2";
				break;

			case 6:
				ChessPiece = "BK2";
				break;

			case 7:
				ChessPiece = "BR2";
				break;

			case 8:
				ChessPiece = "BP1";
				break;

			case 9:
				ChessPiece = "BP2";
				break;

			case 10:
				ChessPiece = "BP3";
				break;

			case 11:
				ChessPiece = "BP4";
				break;

			case 12:
				ChessPiece = "BP5";
				break;

			case 13:
				ChessPiece = "BP6";
				break;

			case 14:
				ChessPiece = "BP7";
				break;

			case 15:
				ChessPiece = "BP8";
				break;
			}

		int NewChessPiecePositionRow, NewChessPiecePositionColumn;
		NewChessPiecePositionRow = (std::rand() % 8) + 1;
		NewChessPiecePositionColumn = (std::rand() % 8) + 1;

		if (Is_Next_Move_Valid(Board, CurrentPlayer, ChessPiece, NewChessPiecePositionRow, NewChessPiecePositionColumn, WhiteCapturedPieces, BlackCapturedPieces))
			isValueCorrect = true;
	}

	return NextMove;
}

bool Is_Next_Move_Valid(const std::vector< std::vector<std::string> >& Board,
						const std::string& CurrentPlayer,
						const std::string& ChessPiece,
						const int& NewChessPiecePositionRow,
						const int& NewChessPiecePositionColumn,
						std::vector<std::string>& WhiteCapturedPieces,
						std::vector<std::string>& BlackCapturedPieces) 
{
	if (ChessPiece == "WR1" || ChessPiece == "WR2" || ChessPiece == "BR1" || ChessPiece == "BR2")
	{
		// Check if piece has been captured
		for (unsigned int i = 0; i < WhiteCapturedPieces.size(); i++)
			if (WhiteCapturedPieces[i] == ChessPiece)
				return false;

		for (unsigned int i = 0; i < BlackCapturedPieces.size(); i++)
			if (BlackCapturedPieces[i] == ChessPiece)
				return false;

		// Find position of current piece
		int CurrentChessPiecePositionRow = -1, CurrentChessPiecePositionColumn = -1;

		for (unsigned int i = 0; i < Board.size(); i++)
			for (unsigned int j = 0; j < Board.size(); j++)
				if (Board[i][j] == ChessPiece)
				{
					CurrentChessPiecePositionRow = i;
					CurrentChessPiecePositionColumn = j;
						
					i = j = Board.size();
					continue;
				}
			
		// Check if move is allowed (rooks only can move up/down/left/right any amount of squares, so XOR on Row and Column)
		if (NewChessPiecePositionRow == CurrentChessPiecePositionRow)
		{
			if (NewChessPiecePositionColumn == CurrentChessPiecePositionColumn)
				return false;
		}

		else if (NewChessPiecePositionColumn != CurrentChessPiecePositionColumn)
			return false;
			
		// Check if there is any obtruction between current piece postion to the new piece position
		if (NewChessPiecePositionRow == CurrentChessPiecePositionRow)
		{
			if (NewChessPiecePositionColumn > CurrentChessPiecePositionColumn)
			{
				for (unsigned int i = CurrentChessPiecePositionColumn; i < NewChessPiecePositionColumn; i++)
					if (Board[CurrentChessPiecePositionRow][i] != " . ")
						return false;
			}

			else
			{
				for (unsigned int i = CurrentChessPiecePositionColumn; i < NewChessPiecePositionColumn; i--)
					if (Board[CurrentChessPiecePositionRow][i] != " . ")
						return false;
			}
		}

		else
		{
			if (NewChessPiecePositionRow > CurrentChessPiecePositionRow)
			{
				for (unsigned int i = CurrentChessPiecePositionRow; i < NewChessPiecePositionRow; i++)
					if (Board[CurrentChessPiecePositionColumn][i] != " . ")
						return false;
			}

			else
			{
				for (unsigned int i = CurrentChessPiecePositionRow; i < NewChessPiecePositionRow; i--)
					if (Board[CurrentChessPiecePositionColumn][i] != " . ")
						return false;
			}
		}
			
		// Check if current player is still in check after move
		if (Is_King_In_Check())
			return false;
	}

	else if (ChessPiece == "WK1" || ChessPiece == "WK2" || ChessPiece == "BK1" || ChessPiece == "BK2")
	{
		//*******************************************************
		// code to check if command is legal, using playername for colour so BLACKBISHOP1
		//*******************************************************


		if (Is_King_In_Check())
			return false;
	}

	else if (ChessPiece == "WB1" || ChessPiece == "WB2" || ChessPiece == "BB1" || ChessPiece == "BB2")
	{
		//*******************************************************
		// code to check if command is legal, using playername for colour so BLACKBISHOP1
		//*******************************************************


		if (Is_King_In_Check())
			return false;

	}

	else if (ChessPiece == "WQ" || ChessPiece == "BQ")
	{
		//*******************************************************
		// code to check if command is legal, using playername for colour so BLACKBISHOP1
		//*******************************************************


		if (Is_King_In_Check())
			return false;
	}

	else if (ChessPiece == "WK" || ChessPiece == "BK")
	{
		//*******************************************************
		// code to check if command is legal, using playername for colour so BLACKBISHOP1
		//*******************************************************


		if (Is_King_In_Check())
			return false;
	}

	else if (ChessPiece == "WP1" || ChessPiece == "WP2" || ChessPiece == "WP3" || ChessPiece == "WP4" || ChessPiece == "WP5" || ChessPiece == "WP6" || ChessPiece == "WP7" || ChessPiece == "WP8" ||
			 ChessPiece == "BP1" || ChessPiece == "BP2" || ChessPiece == "BP3" || ChessPiece == "BP4" || ChessPiece == "BP5" || ChessPiece == "BP6" || ChessPiece == "BP7" || ChessPiece == "BP8")
	{
		//*******************************************************
		// code to check if command is legal, using playername for colour so BLACKBISHOP1 also 2 spaces first move and diagonal capture and en passant
		//*******************************************************


		if (Is_King_In_Check())
			return false;
	}

	return true;
}

std::string Ask_User_For_Next_Move(const std::vector< std::vector<std::string> >& Board, 
						           const std::string& CurrentPlayer, 
								   std::vector<std::string>& WhiteCapturedPieces,
								   std::vector<std::string>& BlackCapturedPieces)
{
	bool isValueCorrect = false; // Flag for if input value in invalid
	std::string NextMove;

	while (!isValueCorrect)
	{
		// Prompt user for next command that will be the next grid position to attack
		std::cout << "Enter your next move (e.g. WP1 A4): ";

		getline(std::cin, NextMove);

		// Check if cin failed
		if (std::cin.fail())
		{
			// Clear buffer and retry
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}

		Capitalise_String(NextMove);

		std::string ChessPiece, NewChessPiecePosition;

		for (unsigned int currentPosition = 0, spaceCount = 0; currentPosition < NextMove.size(); currentPosition++) //Iterate across the line
		{
			if (NextMove[currentPosition] == ' ') //If a space is reached then whatever is in 'Placeholder' must be read in
				spaceCount++; //Increment space count

			else if (spaceCount == 0)
				ChessPiece.push_back(NextMove[currentPosition]); //If current position in current line is NOT a space then read in the value

			else
				NewChessPiecePosition.push_back(NextMove[currentPosition]);
		}

		if (CurrentPlayer == "WHITE")
			if (ChessPiece != "WK" && ChessPiece != "WQ" && ChessPiece != "WB1" && ChessPiece != "WB2" && ChessPiece != "WK1" && ChessPiece != "WK2" && ChessPiece != "WR1" && ChessPiece != "WR2" &&
				ChessPiece != "WP1" && ChessPiece != "WP2" && ChessPiece != "WP3" && ChessPiece != "WP4" && ChessPiece != "WP5" && ChessPiece != "WP6" && ChessPiece != "WP7" && ChessPiece != "WP8")
				continue;
		
		else if (CurrentPlayer == "BLACK")
			if (ChessPiece != "BK" && ChessPiece != "BQ" && ChessPiece != "BB1" && ChessPiece != "BB2" && ChessPiece != "BK1" && ChessPiece != "BK2" && ChessPiece != "BR1" && ChessPiece != "BR2" &&
			    ChessPiece != "BP1" && ChessPiece != "BP2" && ChessPiece != "BP3" && ChessPiece != "BP4" && ChessPiece != "BP5" && ChessPiece != "BP6" && ChessPiece != "BP7" && ChessPiece != "BP8")
				continue;

		if (NewChessPiecePosition.size() != 2)
			continue;

		if (NewChessPiecePosition[0] >= 65 && NewChessPiecePosition[0] <= 72)
			continue;

		if (NewChessPiecePosition[1] >= 49 && NewChessPiecePosition[1] <= 56)
			continue;

		int NewChessPiecePositionRow, NewChessPiecePositionColumn;
		ConvertChessPieceNewPosition(NewChessPiecePosition, NewChessPiecePositionRow, NewChessPiecePositionColumn);

		if (Is_Next_Move_Valid(Board, CurrentPlayer, ChessPiece, NewChessPiecePositionRow, NewChessPiecePositionColumn, WhiteCapturedPieces, BlackCapturedPieces))
			isValueCorrect = true;
	}

	return NextMove;
}

void Capitalise_String(std::string& aString)
{
	// Takes a string and replaces every lowercase occurrence of a letter
	// and replaces it with its corresponding uppercase letter
	for (unsigned int i = 0; i < aString.size(); i++)
	{
		switch (aString[i]) {
		case 'a':
			aString[i] = 'A';
			break;

		case 'b':
			aString[i] = 'B';
			break;

		case 'c':
			aString[i] = 'C';
			break;

		case 'd':
			aString[i] = 'D';
			break;

		case 'e':
			aString[i] = 'E';
			break;

		case 'f':
			aString[i] = 'F';
			break;

		case 'g':
			aString[i] = 'G';
			break;

		case 'h':
			aString[i] = 'H';
			break;

		case 'i':
			aString[i] = 'I';
			break;

		case 'j':
			aString[i] = 'J';
			break;

		case 'k':
			aString[i] = 'K';
			break;

		case 'l':
			aString[i] = 'L';
			break;

		case 'm':
			aString[i] = 'M';
			break;

		case 'n':
			aString[i] = 'N';
			break;

		case 'o':
			aString[i] = 'O';
			break;

		case 'p':
			aString[i] = 'P';
			break;

		case 'q':
			aString[i] = 'Q';
			break;

		case 'r':
			aString[i] = 'R';
			break;

		case 's':
			aString[i] = 'S';
			break;

		case 't':
			aString[i] = 'T';
			break;

		case 'u':
			aString[i] = 'U';
			break;

		case 'v':
			aString[i] = 'V';
			break;

		case 'w':
			aString[i] = 'W';
			break;

		case 'x':
			aString[i] = 'X';
			break;

		case 'y':
			aString[i] = 'Y';
			break;

		case 'z':
			aString[i] = 'Z';
			break;

		default:
			break;
		}
	}
}

void ConvertChessPieceNewPosition(std::string ChessPieceNewPosition, int& ChessPieceNewPositionRow, int& ChessPieceNewPositionColumn)
{
	if (ChessPieceNewPosition[0] == 'A')
		ChessPieceNewPositionRow = 1;

	else if (ChessPieceNewPosition[0] == 'B')
		ChessPieceNewPositionRow = 2;

	else if (ChessPieceNewPosition[0] == 'C')
		ChessPieceNewPositionRow = 3;

	else if (ChessPieceNewPosition[0] == 'D')
		ChessPieceNewPositionRow = 4;

	else if (ChessPieceNewPosition[0] == 'E')
		ChessPieceNewPositionRow = 5;

	else if (ChessPieceNewPosition[0] == 'F')
		ChessPieceNewPositionRow = 6;

	else if (ChessPieceNewPosition[0] == 'G')
		ChessPieceNewPositionRow = 7;

	else if (ChessPieceNewPosition[0] == 'H')
		ChessPieceNewPositionRow = 8;


	ChessPieceNewPositionColumn = ChessPieceNewPosition[1];
}

void Execute_Next_Move()
{
	// update board and remove pieces if needed and pawn rule if it reaches other end, 
}

void Display_Winning_Message()
{
	// maybe while loop with option to quit and restart and add to other games
}
