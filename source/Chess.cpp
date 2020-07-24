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
#include <cmath>
#include <conio.h>

void Play_Chess(void)
{
	bool GameIsRunning = true;

	while (GameIsRunning)
	{
		std::vector< std::vector<std::string> > Board;
		std::vector<std::string> WhiteCapturedPieces;
		std::vector<std::string> BlackCapturedPieces;
		unsigned int NumberOfPlayers, NumberOfTurns = 0;
		std::string HumanPlayer, CurrentPlayer;
		bool Stalemate = false;

		Setup_Game(Board, NumberOfPlayers, HumanPlayer, CurrentPlayer);

		while (!Game_Over(Board, CurrentPlayer, Stalemate))
		{
			Toggle_Player(CurrentPlayer);

			Display_Game(Board, WhiteCapturedPieces, BlackCapturedPieces);

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
				std::cout << "Error in number of players switch statement\n";
				break;
			}

			Execute_Next_Move();

			NumberOfTurns++;
		}

		Display_Winning_Message(Board, WhiteCapturedPieces, BlackCapturedPieces, Stalemate, CurrentPlayer, NumberOfTurns, GameIsRunning);
	}
}

void Test_Chess(void)
{
	std::vector< std::vector<std::string> > Board;
	std::vector<std::string> WhiteCapturedPieces;
	std::vector<std::string> BlackCapturedPieces;
	unsigned int NumberOfPlayers;
	std::string HumanPlayer, CurrentPlayer;
	bool Stalemate = false;

	Setup_Game(Board, NumberOfPlayers, HumanPlayer, CurrentPlayer);

	while (!Game_Over(Board, CurrentPlayer, Stalemate))
	{
		Toggle_Player(CurrentPlayer);

		Display_Game(Board, WhiteCapturedPieces, BlackCapturedPieces);

		std::string NextMove;

		NextMove = Ask_AI_For_Next_Move(Board, CurrentPlayer, WhiteCapturedPieces, BlackCapturedPieces);

		Execute_Next_Move();
	}
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
					Board[i][j] = "BN1";
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
					Board[i][j] = "BN2";
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
					Board[i][j] = "WN1";
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
					Board[i][j] = "WN2";
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

bool Game_Over(const std::vector< std::vector<std::string> >& Board, 
			   const std::string& CurrentPlayer,
			   bool& Stalemate)
{
	if (Is_King_In_Check(Board, CurrentPlayer))
	{
		// and all possible moves result in check thus checkmate
	}

	else
	{
		// But if not in check and all possible moves that opponent can play result in check then stalemate
	}

	return false;
}

bool Is_King_In_Check(const std::vector< std::vector<std::string> >& Board,
					  const std::string& CurrentPlayer)
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

void Display_Game(const std::vector< std::vector<std::string> >& Board,
				  const std::vector<std::string>& WhiteCapturedPieces,
				  const std::vector<std::string>& BlackCapturedPieces)
{
	// ***Better alternative needed***
	// Clears terminal window
	system("cls");

	std::cout << "--------------------Chess--------------------\n\n";

	for (unsigned int i = 0; i < 8; i++)
	{
		if (i == 0)
		{
			std::cout << "Captured Pieces: ";
			for (unsigned int i = 0; i < WhiteCapturedPieces.size(); i	++)
				std::cout << WhiteCapturedPieces[i] << "  ";

			std::cout << "\n\n     A   B   C   D   E   F   G   H" << "\n\n";
		}

		for (unsigned int j = 0; j < 8; j++)
		{
			if (j == 0)
				std::cout << " " << 8 - i << "   ";

			std::cout << Board[i][j] << " ";
			
			if (j == 7)
				std::cout << "  " << 8 - i;
		}

		std::cout << "\n\n";

		if (i == 7)
		{
			std::cout << "     A   B   C   D   E   F   G   H" << "\n\n";

			std::cout << "Captured Pieces: ";
			for (unsigned int i = 0; i < BlackCapturedPieces.size(); i++)
				std::cout << BlackCapturedPieces[i] << "  ";
			std::cout << "\n\n\n\n";
		}
	}

	// Some sort of score tracker of pieces captured
}

std::string Ask_AI_For_Next_Move(const std::vector< std::vector<std::string> >& Board,
								 const std::string& CurrentPlayer,
								 const std::vector<std::string> & WhiteCapturedPieces,
								 const std::vector<std::string> & BlackCapturedPieces)
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
				ChessPiece = "WN1";
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
				ChessPiece = "WN2";
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
				ChessPiece = "BN1";
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
				ChessPiece = "BN2";
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

		unsigned int NewChessPiecePositionColumn, NewChessPiecePositionRow;
		NewChessPiecePositionColumn = (std::rand() % 8) + 1;
		NewChessPiecePositionRow = (std::rand() % 8) + 1;

		if (Is_Next_Move_Valid(Board, CurrentPlayer, ChessPiece, NewChessPiecePositionColumn, NewChessPiecePositionRow, WhiteCapturedPieces, BlackCapturedPieces))
			isValueCorrect = true;
	}

	return NextMove;
}

bool Is_Next_Move_Valid(const std::vector< std::vector<std::string> >& Board,
						const std::string& CurrentPlayer,
						const std::string& ChessPiece,
						const unsigned int& NewChessPiecePositionColumn,
						const unsigned int& NewChessPiecePositionRow,
						const std::vector<std::string>& WhiteCapturedPieces,
						const std::vector<std::string>& BlackCapturedPieces) 
{
	// Check if piece has been captured
	for (unsigned int i = 0; i < WhiteCapturedPieces.size(); i++)
		if (WhiteCapturedPieces[i] == ChessPiece)
			return false;

	for (unsigned int i = 0; i < BlackCapturedPieces.size(); i++)
		if (BlackCapturedPieces[i] == ChessPiece)
			return false;

	// Find position of current piece
	unsigned int CurrentChessPiecePositionColumn = 0, CurrentChessPiecePositionRow = 0;

	for (unsigned int i = 0; i < Board.size(); i++)
		for (unsigned int j = 0; j < Board.size(); j++)
			if (Board[i][j] == ChessPiece)
			{
				CurrentChessPiecePositionColumn = j;
				CurrentChessPiecePositionRow = i;

				i = j = Board.size();
				continue;
			}

	if (ChessPiece[1] == 'R')
	{	
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
				for (unsigned int i = CurrentChessPiecePositionColumn + 1; i < NewChessPiecePositionColumn; i++)
					if (Board[CurrentChessPiecePositionRow][i] != " . ")
						return false;
			}

			else
			{
				for (unsigned int i = NewChessPiecePositionColumn + 1; i < CurrentChessPiecePositionColumn; i++)
					if (Board[CurrentChessPiecePositionRow][i] != " . ")
						return false;
			}
		}

		else
		{
			if (NewChessPiecePositionRow > CurrentChessPiecePositionRow)
			{
				for (unsigned int i = CurrentChessPiecePositionRow + 1; i < NewChessPiecePositionRow; i++)
					if (Board[i][CurrentChessPiecePositionColumn] != " . ")
						return false;
			}

			else
			{
				for (unsigned int i = NewChessPiecePositionColumn + 1; i < CurrentChessPiecePositionRow; i++)
					if (Board[i][CurrentChessPiecePositionColumn] != " . ")
						return false;
			}
		}
	}

	else if (ChessPiece[1] == 'N')
	{
		// Check if move is allowed (knights can move in L shape, despite obstruction)
		bool IsMoveLegal = false;

		if ((NewChessPiecePositionColumn == (CurrentChessPiecePositionColumn + 3)) && ((NewChessPiecePositionRow == (CurrentChessPiecePositionRow + 1)) || (NewChessPiecePositionRow == (CurrentChessPiecePositionRow - 1))))
			IsMoveLegal = true;
		
		else if ((NewChessPiecePositionColumn == (CurrentChessPiecePositionColumn - 3)) && ((NewChessPiecePositionRow == (CurrentChessPiecePositionRow + 1)) || (NewChessPiecePositionRow == (CurrentChessPiecePositionRow - 1))))
			IsMoveLegal = true;
		
		else if ((NewChessPiecePositionRow == (CurrentChessPiecePositionRow + 3)) && ((NewChessPiecePositionColumn == (CurrentChessPiecePositionColumn + 1)) || (NewChessPiecePositionColumn == (CurrentChessPiecePositionColumn - 1))))
			IsMoveLegal = true;

		else if ((NewChessPiecePositionRow == (CurrentChessPiecePositionRow - 3)) && ((NewChessPiecePositionColumn == (CurrentChessPiecePositionColumn + 1)) || (NewChessPiecePositionColumn == (CurrentChessPiecePositionColumn - 1))))
			IsMoveLegal = true;

		if (!IsMoveLegal)
			return false;
	}

	else if (ChessPiece[1] == 'B')
	{
		// Check if move is allowed (bishops can move in diagonals any amount of sqaures)
		if (std::abs((int)NewChessPiecePositionColumn - (int)CurrentChessPiecePositionColumn) != std::abs((int)NewChessPiecePositionRow - (int)CurrentChessPiecePositionRow))
			return false;

		// Check if there is any obtruction between current piece postion to the new piece position
		if (NewChessPiecePositionRow > CurrentChessPiecePositionRow)
		{
			if (NewChessPiecePositionColumn > CurrentChessPiecePositionColumn)
			{
				for (unsigned int i = CurrentChessPiecePositionRow + 1, j = CurrentChessPiecePositionColumn + 1; i < NewChessPiecePositionColumn; i++, j++)
					if (Board[i][j] != " . ")
						return false;
			}

			else
			{
				for (unsigned int i = CurrentChessPiecePositionRow - 1, j = CurrentChessPiecePositionColumn + 1; i < NewChessPiecePositionColumn; i--, j++)
					if (Board[i][j] != " . ")
						return false;
			}
		}

		else
		{
			if (NewChessPiecePositionColumn > CurrentChessPiecePositionColumn)
			{
				for (unsigned int i = CurrentChessPiecePositionRow + 1, j = CurrentChessPiecePositionColumn - 1; i < NewChessPiecePositionRow; i++, j--)
					if (Board[i][j] != " . ")
						return false;
			}

			else
			{
				for (unsigned int i = CurrentChessPiecePositionRow - 1, j = CurrentChessPiecePositionColumn - 1; i < NewChessPiecePositionRow; i--, j--)
					if (Board[i][j] != " . ")
						return false;
			}
		}
	}

	else if (ChessPiece[1] == 'Q')
	{
		// Check if move is allowed (queen can move in diagonals and up/down/left/right any amount of sqaures, thus equal to rook + bishop)
		// Diagonals
		if (std::abs((int)NewChessPiecePositionColumn - (int)CurrentChessPiecePositionColumn) != std::abs((int)NewChessPiecePositionRow - (int)CurrentChessPiecePositionRow))
			return false;

		// Up/down/left/right
		if (NewChessPiecePositionRow == CurrentChessPiecePositionRow)
		{
			if (NewChessPiecePositionColumn == CurrentChessPiecePositionColumn)
				return false;
		}

		else if (NewChessPiecePositionColumn != CurrentChessPiecePositionColumn)
			return false;

		// Check if there is any obtruction between current piece postion to the new piece position
		// Diagonals
		if (NewChessPiecePositionRow > CurrentChessPiecePositionRow)
		{
			if (NewChessPiecePositionColumn > CurrentChessPiecePositionColumn)
			{
				for (unsigned int i = CurrentChessPiecePositionRow + 1, j = CurrentChessPiecePositionColumn + 1; i < NewChessPiecePositionColumn; i++, j++)
					if (Board[i][j] != " . ")
						return false;
			}

			else
			{
				for (unsigned int i = CurrentChessPiecePositionRow - 1, j = CurrentChessPiecePositionColumn + 1; i < NewChessPiecePositionColumn; i--, j++)
					if (Board[i][j] != " . ")
						return false;
			}
		}

		else
		{
			if (NewChessPiecePositionColumn > CurrentChessPiecePositionColumn)
			{
				for (unsigned int i = CurrentChessPiecePositionRow + 1, j = CurrentChessPiecePositionColumn - 1; i < NewChessPiecePositionRow; i++, j--)
					if (Board[i][j] != " . ")
						return false;
			}

			else
			{
				for (unsigned int i = CurrentChessPiecePositionRow - 1, j = CurrentChessPiecePositionColumn - 1; i < NewChessPiecePositionRow; i--, j--)
					if (Board[i][j] != " . ")
						return false;
			}
		}

		// Up/down/left/right
		if (NewChessPiecePositionRow == CurrentChessPiecePositionRow)
		{
			if (NewChessPiecePositionColumn > CurrentChessPiecePositionColumn)
			{
				for (unsigned int i = CurrentChessPiecePositionColumn + 1; i < NewChessPiecePositionColumn; i++)
					if (Board[CurrentChessPiecePositionRow][i] != " . ")
						return false;
			}

			else
			{
				for (unsigned int i = NewChessPiecePositionRow + 1; i < CurrentChessPiecePositionColumn; i++)
					if (Board[CurrentChessPiecePositionRow][i] != " . ")
						return false;
			}
		}

		else
		{
			if (NewChessPiecePositionRow > CurrentChessPiecePositionRow)
			{
				for (unsigned int i = CurrentChessPiecePositionRow + 1; i < NewChessPiecePositionRow; i++)
					if (Board[i][CurrentChessPiecePositionColumn] != " . ")
						return false;
			}

			else
			{
				for (unsigned int i = NewChessPiecePositionRow + 1; i < CurrentChessPiecePositionColumn; i++)
					if (Board[i][CurrentChessPiecePositionColumn] != " . ")
						return false;
			}
		}
	}

	else if (ChessPiece[1] == 'K')
	{
		// Check if move is allowed (king only can move diagonals and up/down/left/right one square)
		if ((std::abs((int)NewChessPiecePositionColumn - (int)CurrentChessPiecePositionColumn) > 1) || (std::abs((int)NewChessPiecePositionRow - (int)CurrentChessPiecePositionRow) > 1))
			return false;
			
		// Check if there is any obtruction between current piece postion to the new piece position
		if ((CurrentPlayer == "WHITE") && (Board[NewChessPiecePositionRow][NewChessPiecePositionColumn][0] == 'W'))
			return false;

		else if ((CurrentPlayer == "BLACK") && (Board[NewChessPiecePositionRow][NewChessPiecePositionColumn][0] == 'B'))
			return false;
	}

	else if (ChessPiece[1] == 'P')
	{
		// Check if move is allowed (pawn only can move up one square, except two squares on first move, and diagonal if opponent piece is there)
		
		//*********************No boolean as if not on second rank then has moved then cannot move two squares**************************

		// Check if there is any obtruction between current piece postion to the new piece position
	}

	// Check if new position has own colour piece on it


	// Check if current player is still in check after move

	//*******************Update a copy of baord with the new move and check if king is still in check***************************
	std::vector< std::vector<std::string> > CopyOfBoard = Board;

	if (Is_King_In_Check(CopyOfBoard, CurrentPlayer))
		return false;

	return true;
}

std::string Ask_User_For_Next_Move(const std::vector< std::vector<std::string> >& Board, 
						           const std::string& CurrentPlayer, 
								   const std::vector<std::string>& WhiteCapturedPieces,
								   const std::vector<std::string>& BlackCapturedPieces)
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
			if (ChessPiece != "WK" && ChessPiece != "WQ" && ChessPiece != "WB1" && ChessPiece != "WB2" && ChessPiece != "WK1" && ChessPiece != "WN2" && ChessPiece != "WR1" && ChessPiece != "WR2" &&
				ChessPiece != "WP1" && ChessPiece != "WP2" && ChessPiece != "WP3" && ChessPiece != "WP4" && ChessPiece != "WP5" && ChessPiece != "WP6" && ChessPiece != "WP7" && ChessPiece != "WP8")
				continue;
		
		else if (CurrentPlayer == "BLACK")
			if (ChessPiece != "BK" && ChessPiece != "BQ" && ChessPiece != "BB1" && ChessPiece != "BB2" && ChessPiece != "BN1" && ChessPiece != "BN2" && ChessPiece != "BR1" && ChessPiece != "BR2" &&
			    ChessPiece != "BP1" && ChessPiece != "BP2" && ChessPiece != "BP3" && ChessPiece != "BP4" && ChessPiece != "BP5" && ChessPiece != "BP6" && ChessPiece != "BP7" && ChessPiece != "BP8")
				continue;

		if (NewChessPiecePosition.size() != 2)
			continue;

		if (NewChessPiecePosition[0] >= 65 && NewChessPiecePosition[0] <= 72)
			continue;

		if (NewChessPiecePosition[1] >= 49 && NewChessPiecePosition[1] <= 56)
			continue;

		unsigned int NewChessPiecePositionColumn, NewChessPiecePositionRow;
		ConvertNewChessPiecePosition(NewChessPiecePosition, NewChessPiecePositionColumn, NewChessPiecePositionRow);

		if (Is_Next_Move_Valid(Board, CurrentPlayer, ChessPiece, NewChessPiecePositionColumn, NewChessPiecePositionRow, WhiteCapturedPieces, BlackCapturedPieces))
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

void ConvertNewChessPiecePosition(const std::string NewChessPiecePosition,
								  unsigned int& NewChessPiecePositionColumn,
								  unsigned int& NewChessPiecePositionRow)
{
	if (NewChessPiecePosition[0] == 'A')
		NewChessPiecePositionColumn = 1;

	else if (NewChessPiecePosition[0] == 'B')
		NewChessPiecePositionColumn = 2;

	else if (NewChessPiecePosition[0] == 'C')
		NewChessPiecePositionColumn = 3;

	else if (NewChessPiecePosition[0] == 'D')
		NewChessPiecePositionColumn = 4;

	else if (NewChessPiecePosition[0] == 'E')
		NewChessPiecePositionColumn = 5;

	else if (NewChessPiecePosition[0] == 'F')
		NewChessPiecePositionColumn = 6;

	else if (NewChessPiecePosition[0] == 'G')
		NewChessPiecePositionColumn = 7;

	else if (NewChessPiecePosition[0] == 'H')
		NewChessPiecePositionColumn = 8;


	NewChessPiecePositionRow = NewChessPiecePosition[1];
}

void Execute_Next_Move()
{
	// update board and remove pieces 
}

void Display_Winning_Message(const std::vector< std::vector<std::string> >& Board,
							 const std::vector<std::string>& WhiteCapturedPieces,
							 const std::vector<std::string>& BlackCapturedPieces,
							 const bool& Stalemate,
							 const std::string& CurrentPlayer,
							 const unsigned int& NumberOfTurns,
							 bool& GameIsRunning)
{
	Display_Game(Board, WhiteCapturedPieces, BlackCapturedPieces);

	if(!Stalemate)
		std::cout << "GAME OVER\n\n" << CurrentPlayer << " has won! The game lasted " << NumberOfTurns << " turns.\n\n";

	else
		std::cout << "GAME OVER\n\nIt is a draw! The game lasted " << NumberOfTurns << " turns.\n\n";

	std::cout << "Press 'Q' to quit the game OR press any other key to play again.\n";

	// ***Better alternative needed***
	// Gets key pressed and then clears terminal window
	char Decision = _getch();
	system("cls");

	if (Decision == 'q')
		GameIsRunning = false;
}

// Pawn in is move valid AND check if new position has own piece colour on
// pawn promotion (if white on 8th or black on 1st then after is_king_in_check ask user for what pice to promote to and name apropiatley) 
// Caslting (when the king moves to spaces and check if it hasnt been moved before and no pieces in between it and rook)
// En passant
// Is_King_In_Check()
// Execute_Next_Move()
// comments 