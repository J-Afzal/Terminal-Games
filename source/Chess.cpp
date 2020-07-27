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
					Board[i][j] = "BQ1";
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
					Board[i][j] = "WQ1";
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
	if (CurrentPlayer == "Black")
		CurrentPlayer = "White";
	else
		CurrentPlayer = "Black";
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
																 const std::string& HumanPlayer,
																 const unsigned int& NumberOfPlayers,
																 const std::vector<std::string>& WhiteCapturedPieces,
																 const std::vector<std::string>& BlackCapturedPieces,
																 const std::vector<unsigned int>& PawnPromotionPieceCount,
																 std::vector<bool>& HasCastlingPiecesMoved)
{
	bool isValueCorrect = false; // Flag for if input value in invalid
	std::string NextMove;

	while (!isValueCorrect)
	{
		std::vector<std::string> ListOfPieces;

		for (unsigned int i = 0; i < Board.size(); i++)
			for (unsigned int j = 0; j < Board.size(); j++)
			{
				if (CurrentPlayer == "White")
				{
					if (Board[i][j][0] == 'W')
						ListOfPieces.push_back(Board[i][j]);
				}

				else
				{
					if (Board[i][j][0] == 'B')
						ListOfPieces.push_back(Board[i][j]);
				}
			}
		
		std::string ChessPiece = ListOfPieces[std::rand() % ListOfPieces.size()];

		unsigned int NewChessPiecePositionColumn, NewChessPiecePositionRow;
		NewChessPiecePositionColumn = (std::rand() % 8) + 1;
		NewChessPiecePositionRow = (std::rand() % 8) + 1;

		if (Is_Next_Move_Legal(Board, NextMove, CurrentPlayer, HumanPlayer, NumberOfPlayers, ChessPiece, NewChessPiecePositionRow, NewChessPiecePositionColumn, WhiteCapturedPieces, BlackCapturedPieces, PawnPromotionPieceCount, HasCastlingPiecesMoved))
			isValueCorrect = true;
	}

	return NextMove;
}

bool Is_Next_Move_Legal(const std::vector< std::vector<std::string> >& Board,
												const std::string& NextMove,
												const std::string& CurrentPlayer,
												const std::string& HumanPlayer,
												const unsigned int& NumberOfPlayers,
												const std::string& ChessPiece,
												const unsigned int& NewChessPiecePositionRow,
												const unsigned int& NewChessPiecePositionColumn,
												const std::vector<std::string>& WhiteCapturedPieces,
												const std::vector<std::string>& BlackCapturedPieces,
												const std::vector<unsigned int>& PawnPromotionPieceCount,
												std::vector<bool>& HasCastlingPiecesMoved)
{
	// Check if piece has been captured
	for (unsigned int i = 0; i < WhiteCapturedPieces.size(); i++)
		if (WhiteCapturedPieces[i] == ChessPiece)
			return false;

	for (unsigned int i = 0; i < BlackCapturedPieces.size(); i++)
		if (BlackCapturedPieces[i] == ChessPiece)
			return false;

	// Find position of current piece
	unsigned int CurrentChessPiecePositionRow = 0, CurrentChessPiecePositionColumn = 0;

	for (unsigned int i = 0; i < Board.size(); i++)
		for (unsigned int j = 0; j < Board.size(); j++)
			if (Board[i][j] == ChessPiece)
			{
				CurrentChessPiecePositionRow = i;
				CurrentChessPiecePositionColumn = j;
				
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

		// If code reaches her then move is valid and will be executed
		if (CurrentPlayer == "WR1")
			HasCastlingPiecesMoved[1] = true;

		if (CurrentPlayer == "WR2")
			HasCastlingPiecesMoved[2] = true;

		if (CurrentPlayer == "BR1")
			HasCastlingPiecesMoved[4] = true;

		if (CurrentPlayer == "BR2")
			HasCastlingPiecesMoved[5] = true;
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
		// Castling = move two to the left or right
		if ((NewChessPiecePositionRow == CurrentChessPiecePositionRow) && ((std::abs((int)NewChessPiecePositionColumn - (int)CurrentChessPiecePositionColumn)) == 2))
		{
			if (CurrentPlayer == "White")
			{
				// Left
				if (NewChessPiecePositionColumn == CurrentChessPiecePositionColumn - 2)
				{
					// Has the King or Rook been moved before
					if (HasCastlingPiecesMoved[0] == true || HasCastlingPiecesMoved[1] == true)
						return false;

					// Is there any obstruction between King and Rook
					if (Board[CurrentChessPiecePositionRow][CurrentChessPiecePositionColumn - 1] != " . " || Board[CurrentChessPiecePositionRow][CurrentChessPiecePositionColumn - 2] != " . " || Board[CurrentChessPiecePositionRow][CurrentChessPiecePositionColumn - 3] != " . ")
						return false;

					// Is the first square to the left under attack (second sqaure, aka where the king lands, will be checked at the end with Is_King_In_Check()) 
					// Check D1 horizontally to the right as left is clear due to above if statement
					for (unsigned int i = CurrentChessPiecePositionColumn + 1; i < Board.size(); i++)
						if (Board[CurrentChessPiecePositionRow][i] != " . ")
						{
							if ((Board[CurrentChessPiecePositionRow][i][0] == 'B') && (Board[CurrentChessPiecePositionRow][i][1] == 'R' || Board[CurrentChessPiecePositionRow][i][1] == 'Q'))
								return false;
						}

					// Check D1 vertcially
					for (unsigned int i = CurrentChessPiecePositionRow; i < 0; i--)
					if (Board[i][CurrentChessPiecePositionColumn - 1] != " . ")
					{
						if ((Board[CurrentChessPiecePositionRow][i][0] == 'B') && (Board[CurrentChessPiecePositionRow][i][1] == 'R' || Board[CurrentChessPiecePositionRow][i][1] == 'Q'))
							return false;
					}

					// Check D1 diagonally top right
					for (unsigned int i = CurrentChessPiecePositionRow, j = CurrentChessPiecePositionColumn - 1; j < Board.size(); i--, j++)
						if (Board[i][j] != " . ")
						{
							if ((Board[CurrentChessPiecePositionRow][i][0] == 'B') && (Board[CurrentChessPiecePositionRow][i][1] == 'B' || Board[CurrentChessPiecePositionRow][i][1] == 'Q'))
								return false;
						}
					
					// Check D1 diagonally top left
					for (unsigned int i = CurrentChessPiecePositionRow, j = CurrentChessPiecePositionColumn - 1; j < 0; i--, j--)
						if (Board[i][j] != " . ")
						{
							if ((Board[CurrentChessPiecePositionRow][i][0] == 'B') && (Board[CurrentChessPiecePositionRow][i][1] == 'B' || Board[CurrentChessPiecePositionRow][i][1] == 'Q'))
								return false;
						}

					// Check C3/E3 B2/F2 for knights
					if (Board[5][2][0] == 'B' && Board[5][2][1] == 'N')
						return false;
					
					if (Board[5][4][0] == 'B' && Board[5][4][1] == 'N')
						return false;
					
					if (Board[6][1][0] == 'B' && Board[6][1][1] == 'N')
						return false;
					
					if (Board[6][5][0] == 'B' && Board[6][5][1] == 'N')
						return false;
				}

				// Right
				else if (NewChessPiecePositionColumn == CurrentChessPiecePositionColumn + 2)
				{
					// Has the King or Rook been moved before
					if (HasCastlingPiecesMoved[0] == true || HasCastlingPiecesMoved[2] == true)
						return false;

					// Is there any obstruction between King and Rook
					if (Board[CurrentChessPiecePositionRow][CurrentChessPiecePositionColumn + 1] != " . " || Board[CurrentChessPiecePositionRow][CurrentChessPiecePositionColumn + 2] != " . ")
						return false;

					// Is the first square to the right under attack (second sqaure, aka where the king lands, will be checked at the end with Is_King_In_Check()) 
					// Check F1 horizontally to the left as right is clear due to above if statement
					for (unsigned int i = CurrentChessPiecePositionColumn - 1; i < 0; i--)
						if (Board[CurrentChessPiecePositionRow][i] != " . ")
						{
							if ((Board[CurrentChessPiecePositionRow][i][0] == 'B') && (Board[CurrentChessPiecePositionRow][i][1] == 'R' || Board[CurrentChessPiecePositionRow][i][1] == 'Q'))
								return false;
						}

					// Check F1 vertcially
					for (unsigned int i = CurrentChessPiecePositionRow; i < 0; i--)
						if (Board[i][CurrentChessPiecePositionColumn + 1] != " . ")
						{
							if ((Board[CurrentChessPiecePositionRow][i][0] == 'B') && (Board[CurrentChessPiecePositionRow][i][1] == 'R' || Board[CurrentChessPiecePositionRow][i][1] == 'Q'))
								return false;
						}

					// Check F1 diagonally top right
					for (unsigned int i = CurrentChessPiecePositionRow, j = CurrentChessPiecePositionColumn + 1; j < Board.size(); i--, j++)
						if (Board[i][j] != " . ")
						{
							if ((Board[CurrentChessPiecePositionRow][i][0] == 'B') && (Board[CurrentChessPiecePositionRow][i][1] == 'B' || Board[CurrentChessPiecePositionRow][i][1] == 'Q'))
								return false;
						}

					// Check F1 diagonally top left
					for (unsigned int i = CurrentChessPiecePositionRow, j = CurrentChessPiecePositionColumn + 1; j < 0; i--, j--)
						if (Board[i][j] != " . ")
						{
							if ((Board[CurrentChessPiecePositionRow][i][0] == 'B') && (Board[CurrentChessPiecePositionRow][i][1] == 'B' || Board[CurrentChessPiecePositionRow][i][1] == 'Q'))
								return false;
						}

					// Check E3/G3 D2/H2 for knights
					if (Board[5][4][0] == 'B' && Board[5][4][1] == 'N')
						return false;

					if (Board[5][6][0] == 'B' && Board[5][6][1] == 'N')
						return false;

					if (Board[6][3][0] == 'B' && Board[6][3][1] == 'N')
						return false;

					if (Board[6][7][0] == 'B' && Board[6][7][1] == 'N')
						return false;
				}
			}

			else
			{
				// Left
				if (NewChessPiecePositionColumn == CurrentChessPiecePositionColumn - 2)
				{
					// Has the King or Rook been moved before
					if (HasCastlingPiecesMoved[3] == true || HasCastlingPiecesMoved[4] == true)
						return false;

					// Is there any obstruction between King and Rook
					if (Board[CurrentChessPiecePositionRow][CurrentChessPiecePositionColumn - 1] != " . " || Board[CurrentChessPiecePositionRow][CurrentChessPiecePositionColumn - 2] != " . " || Board[CurrentChessPiecePositionRow][CurrentChessPiecePositionColumn - 3] != " . ")
						return false;

					// Is the first square to the left under attack (second sqaure, aka where the king lands, will be checked at the end with Is_King_In_Check()) 
					// Check D8 horizontally to the right as left is clear due to above if statement
					for (unsigned int i = CurrentChessPiecePositionColumn + 1; i < Board.size(); i++)
						if (Board[CurrentChessPiecePositionRow][i] != " . ")
						{
							if ((Board[CurrentChessPiecePositionRow][i][0] == 'W') && (Board[CurrentChessPiecePositionRow][i][1] == 'R' || Board[CurrentChessPiecePositionRow][i][1] == 'Q'))
								return false;
						}

					// Check D8 vertcially
					for (unsigned int i = CurrentChessPiecePositionRow; i < Board.size(); i++)
						if (Board[i][CurrentChessPiecePositionColumn - 1] != " . ")
						{
							if ((Board[CurrentChessPiecePositionRow][i][0] == 'W') && (Board[CurrentChessPiecePositionRow][i][1] == 'R' || Board[CurrentChessPiecePositionRow][i][1] == 'Q'))
								return false;
						}

					// Check D8 diagonally bottom right
					for (unsigned int i = CurrentChessPiecePositionRow, j = CurrentChessPiecePositionColumn - 1; j < Board.size(); i++, j++)
						if (Board[i][j] != " . ")
						{
							if ((Board[CurrentChessPiecePositionRow][i][0] == 'W') && (Board[CurrentChessPiecePositionRow][i][1] == 'B' || Board[CurrentChessPiecePositionRow][i][1] == 'Q'))
								return false;
						}

					// Check D8 diagonally bottom left
					for (unsigned int i = CurrentChessPiecePositionRow, j = CurrentChessPiecePositionColumn - 1; j < 0; i++, j--)
						if (Board[i][j] != " . ")
						{
							if ((Board[CurrentChessPiecePositionRow][i][0] == 'W') && (Board[CurrentChessPiecePositionRow][i][1] == 'B' || Board[CurrentChessPiecePositionRow][i][1] == 'Q'))
								return false;
						}

					// Check C6/E6 B7/F7 for knights
					if (Board[2][2][0] == 'B' && Board[2][2][1] == 'N')
						return false;

					if (Board[2][4][0] == 'B' && Board[2][4][1] == 'N')
						return false;

					if (Board[1][1][0] == 'B' && Board[6][1][1] == 'N')
						return false;

					if (Board[1][5][0] == 'B' && Board[1][5][1] == 'N')
						return false;
				}

				// Right
				else if (NewChessPiecePositionColumn == CurrentChessPiecePositionColumn + 2)
				{
					// Has the King or Rook been moved before
					if (HasCastlingPiecesMoved[3] == true || HasCastlingPiecesMoved[5] == true)
						return false;

					// Is there any obstruction between King and Rook
					if (Board[CurrentChessPiecePositionRow][CurrentChessPiecePositionColumn + 1] != " . " || Board[CurrentChessPiecePositionRow][CurrentChessPiecePositionColumn + 2] != " . ")
						return false;

					// Is the first square to the right under attack (second sqaure, aka where the king lands, will be checked at the end with Is_King_In_Check()) 
					// Check F8 horizontally to the left as right is clear due to above if statement
					for (unsigned int i = CurrentChessPiecePositionColumn - 1; i < 0; i--)
						if (Board[CurrentChessPiecePositionRow][i] != " . ")
						{
							if ((Board[CurrentChessPiecePositionRow][i][0] == 'W') && (Board[CurrentChessPiecePositionRow][i][1] == 'R' || Board[CurrentChessPiecePositionRow][i][1] == 'Q'))
								return false;
						}

					// Check F8 vertcially
					for (unsigned int i = CurrentChessPiecePositionRow; i < Board.size(); i++)
						if (Board[i][CurrentChessPiecePositionColumn + 1] != " . ")
						{
							if ((Board[CurrentChessPiecePositionRow][i][0] == 'W') && (Board[CurrentChessPiecePositionRow][i][1] == 'R' || Board[CurrentChessPiecePositionRow][i][1] == 'Q'))
								return false;
						}

					// Check F8 diagonally bottom right
					for (unsigned int i = CurrentChessPiecePositionRow, j = CurrentChessPiecePositionColumn + 1; j < Board.size(); i++, j++)
						if (Board[i][j] != " . ")
						{
							if ((Board[CurrentChessPiecePositionRow][i][0] == 'W') && (Board[CurrentChessPiecePositionRow][i][1] == 'B' || Board[CurrentChessPiecePositionRow][i][1] == 'Q'))
								return false;
						}

					// Check F8 diagonally bottom left
					for (unsigned int i = CurrentChessPiecePositionRow, j = CurrentChessPiecePositionColumn + 1; j < 0; i++, j--)
						if (Board[i][j] != " . ")
						{
							if ((Board[CurrentChessPiecePositionRow][i][0] == 'W') && (Board[CurrentChessPiecePositionRow][i][1] == 'B' || Board[CurrentChessPiecePositionRow][i][1] == 'Q'))
								return false;
						}

					// Check E6/G6 D7/H7 for knights
					if (Board[2][4][0] == 'B' && Board[2][4][1] == 'N')
						return false;

					if (Board[2][6][0] == 'B' && Board[2][6][1] == 'N')
						return false;

					if (Board[1][3][0] == 'B' && Board[1][3][1] == 'N')
						return false;

					if (Board[1][7][0] == 'B' && Board[1][7][1] == 'N')
						return false;
				}
			}

			// Is king currently in check
			if (Is_King_In_Check(Board, CurrentPlayer))
				return false;
		}

		else
		{
			// Check if move is allowed (king only can move diagonals and up/down/left/right one square)
			if ((std::abs((int)NewChessPiecePositionColumn - (int)CurrentChessPiecePositionColumn) > 1) || (std::abs((int)NewChessPiecePositionRow - (int)CurrentChessPiecePositionRow) > 1))
				return false;

			// Check if there is any obtruction between current piece postion to the new piece position
			if ((CurrentPlayer == "White") && (Board[NewChessPiecePositionRow][NewChessPiecePositionColumn][0] == 'W'))
				return false;

			else if ((CurrentPlayer == "Black") && (Board[NewChessPiecePositionRow][NewChessPiecePositionColumn][0] == 'B'))
				return false;
		}

		// If code reaches her then move is valid and will be executed
		if (ChessPiece == "WK")
			HasCastlingPiecesMoved[0] = true;

		if (ChessPiece == "BK")
			HasCastlingPiecesMoved[3] = true;
	}

	else if (ChessPiece[1] == 'P')
	{
		// Check if move is allowed (pawn only can move up one square, except two squares on first move, and diagonal if opponent piece is there or en passant)
		if (CurrentPlayer == "White")
		{
			if ((NewChessPiecePositionRow == CurrentChessPiecePositionRow + 1) && (NewChessPiecePositionColumn == CurrentChessPiecePositionColumn))
			{
				if (Board[NewChessPiecePositionRow][NewChessPiecePositionColumn] != " . ")
					return false;
			}

			else if ((NewChessPiecePositionRow == CurrentChessPiecePositionRow + 2) && (NewChessPiecePositionColumn == CurrentChessPiecePositionColumn))
			{
				if (CurrentChessPiecePositionRow != 1)
					return false;

				if (Board[CurrentChessPiecePositionRow + 1][CurrentChessPiecePositionColumn] != " . " || Board[CurrentChessPiecePositionRow + 2][CurrentChessPiecePositionColumn] != " . ")
					return false;
			}

			else if (((NewChessPiecePositionRow == CurrentChessPiecePositionRow + 1) && (NewChessPiecePositionColumn == CurrentChessPiecePositionColumn + 1)) ||
				     ((NewChessPiecePositionRow == CurrentChessPiecePositionRow + 1) && (NewChessPiecePositionColumn == CurrentChessPiecePositionColumn - 1)))
			{
				if (Board[NewChessPiecePositionRow][NewChessPiecePositionColumn][0] != 'B')
					return false;
			}

			else
				return false;
		}

		else
		{
			if ((NewChessPiecePositionRow == CurrentChessPiecePositionRow - 1) && (NewChessPiecePositionColumn == CurrentChessPiecePositionColumn))
			{
				if (Board[NewChessPiecePositionRow][NewChessPiecePositionColumn] != " . ")
					return false;
			}

			else if ((NewChessPiecePositionRow == CurrentChessPiecePositionRow - 2) && (NewChessPiecePositionColumn == CurrentChessPiecePositionColumn))
			{
				if (CurrentChessPiecePositionRow != 6)
					return false;

				if (Board[CurrentChessPiecePositionRow - 1][CurrentChessPiecePositionColumn] != " . ")
					return false;
			}

			else if (((NewChessPiecePositionRow == CurrentChessPiecePositionRow - 1) && (NewChessPiecePositionColumn == CurrentChessPiecePositionColumn + 1)) ||
				     ((NewChessPiecePositionRow == CurrentChessPiecePositionRow - 1) && (NewChessPiecePositionColumn == CurrentChessPiecePositionColumn - 1)))
			{
				if (Board[NewChessPiecePositionRow][NewChessPiecePositionColumn][0] != 'W')
					return false;
			}

			else
				return false;
		}
	}

	// Check if new position has own colour piece on it
	if ((CurrentPlayer == "White") && (Board[NewChessPiecePositionRow][NewChessPiecePositionColumn][0] == 'W'))
		return false;

	if ((CurrentPlayer == "Black") && (Board[NewChessPiecePositionRow][NewChessPiecePositionColumn][0] == 'B'))
		return false;

	// Check if current player is still in check after move, if so inv
	std::vector< std::vector<std::string> > CopyOfBoard = Board;
	std::vector<std::string> CopyOfWhiteCapturedPieces = WhiteCapturedPieces, CopyOfBlackCapturedPieces = BlackCapturedPieces;
	std::vector<unsigned int> CopyOfPawnPromotionPieceCount = PawnPromotionPieceCount;
	Execute_Next_Move(CopyOfBoard, NextMove, CurrentPlayer, HumanPlayer, NumberOfPlayers, CopyOfWhiteCapturedPieces, CopyOfBlackCapturedPieces, CopyOfPawnPromotionPieceCount);

	if (Is_King_In_Check(CopyOfBoard, CurrentPlayer))
		return false;

	return true;
}

std::string Ask_User_For_Next_Move(const std::vector< std::vector<std::string> >& Board,
																	 const std::string& CurrentPlayer,
																	 const std::string& HumanPlayer,
																	 const unsigned int& NumberOfPlayers,
																	 const std::vector<std::string>& WhiteCapturedPieces,
																	 const std::vector<std::string>& BlackCapturedPieces,
																	 std::vector<unsigned int>& PawnPromotionPieceCount,
																	 std::vector<bool>& HasCastlingPiecesMoved)
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

		if ((CurrentPlayer == "White") && (ChessPiece[0] != 'W'))
			continue;

		if ((CurrentPlayer == "Black") && (ChessPiece[0] != 'B'))
			continue;

		bool DoesPieceExist = false;

		for (unsigned int i = 0; i < Board.size(); i++)
			for (unsigned int j = 0; j < Board.size(); j++)
				if (Board[i][j] == ChessPiece)
				{
					DoesPieceExist = true;
					i = j = Board.size();
					continue;
				}

		if (!DoesPieceExist)
			continue;

		if (NewChessPiecePosition.size() != 2)
			continue;

		if (NewChessPiecePosition[0] >= 65 && NewChessPiecePosition[0] <= 72)
			continue;

		if (NewChessPiecePosition[1] >= 49 && NewChessPiecePosition[1] <= 56)
			continue;

		unsigned int NewChessPiecePositionColumn, NewChessPiecePositionRow;
		ConvertNewChessPiecePosition(NewChessPiecePosition, NewChessPiecePositionColumn, NewChessPiecePositionRow);

		if (Is_Next_Move_Legal(Board, NextMove, CurrentPlayer, HumanPlayer, NumberOfPlayers, ChessPiece, NewChessPiecePositionRow, NewChessPiecePositionColumn, WhiteCapturedPieces, BlackCapturedPieces, PawnPromotionPieceCount, HasCastlingPiecesMoved))
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
																	unsigned int& NewChessPiecePositionRow,
																	unsigned int& NewChessPiecePositionColumn)
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

void Execute_Next_Move(std::vector< std::vector<std::string> >& Board,
											 const std::string& NextMove,
											 const std::string& CurrentPlayer,
											 const std::string& HumanPlayer,
											 const unsigned int& NumberOfPlayers,
											 std::vector<std::string>& WhiteCapturedPieces,
											 std::vector<std::string>& BlackCapturedPieces,
											 std::vector<unsigned int>& PawnPromotionPieceCount)
{ 
	// Get chess piece
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

	// Get new position of the chess piece
	unsigned int NewChessPiecePositionColumn, NewChessPiecePositionRow;
	ConvertNewChessPiecePosition(NewChessPiecePosition, NewChessPiecePositionColumn, NewChessPiecePositionRow);

	// Find position of current piece
	unsigned int CurrentChessPiecePositionRow = 0, CurrentChessPiecePositionColumn = 0;

	for (unsigned int i = 0; i < Board.size(); i++)
		for (unsigned int j = 0; j < Board.size(); j++)
			if (Board[i][j] == ChessPiece)
			{
				CurrentChessPiecePositionRow = i;
				CurrentChessPiecePositionColumn = j;

				i = j = Board.size();
				continue;
			}

	// Execute the move
	Board[CurrentChessPiecePositionRow][CurrentChessPiecePositionColumn] = " . ";

	if (CurrentPlayer == "White")
	{
		if (Board[NewChessPiecePositionRow][NewChessPiecePositionColumn] != " . ")
			BlackCapturedPieces.push_back(Board[NewChessPiecePositionRow][NewChessPiecePositionColumn]);

		Board[NewChessPiecePositionRow][NewChessPiecePositionColumn] = ChessPiece;

		// Pawn Promotion Check
		if (ChessPiece[1] == 'P')
			if (NewChessPiecePositionRow == 7)
			{
				std::string Pawn_Promotion_Choice = Get_Pawn_Promotion_Choice(NumberOfPlayers, CurrentPlayer, HumanPlayer);

				if (Pawn_Promotion_Choice == "ROOK")
				{
					std::string PawnPromotionChessPiece = "WR";
					PawnPromotionPieceCount[0]++;
					PawnPromotionChessPiece += std::to_string(PawnPromotionPieceCount[0]);

					Board[NewChessPiecePositionRow][NewChessPiecePositionColumn] = PawnPromotionChessPiece;
				}

				if (Pawn_Promotion_Choice == "KNIGHT")
				{
					std::string PawnPromotionChessPiece = "WN";
					PawnPromotionPieceCount[1]++;
					PawnPromotionChessPiece += std::to_string(PawnPromotionPieceCount[1]);

					Board[NewChessPiecePositionRow][NewChessPiecePositionColumn] = PawnPromotionChessPiece;
				}

				if (Pawn_Promotion_Choice == "BISHOP")
				{
					std::string PawnPromotionChessPiece = "WB";
					PawnPromotionPieceCount[2]++;
					PawnPromotionChessPiece += std::to_string(PawnPromotionPieceCount[2]);

					Board[NewChessPiecePositionRow][NewChessPiecePositionColumn] = PawnPromotionChessPiece;
				}

				if (Pawn_Promotion_Choice == "QUEEN")
				{
					std::string PawnPromotionChessPiece = "WQ";
					PawnPromotionPieceCount[3]++;
					PawnPromotionChessPiece += std::to_string(PawnPromotionPieceCount[3]);

					Board[NewChessPiecePositionRow][NewChessPiecePositionColumn] = PawnPromotionChessPiece;
				}
			}
	}

	else
	{
		if (Board[NewChessPiecePositionRow][NewChessPiecePositionColumn] != " . ")
			WhiteCapturedPieces.push_back(Board[NewChessPiecePositionRow][NewChessPiecePositionColumn]);

		Board[NewChessPiecePositionRow][NewChessPiecePositionColumn] = ChessPiece;

		// Pawn Promotion Check
		if (ChessPiece[1] == 'P')
			if (NewChessPiecePositionRow == 0)
			{
				std::string Pawn_Promotion_Choice = Get_Pawn_Promotion_Choice(NumberOfPlayers, CurrentPlayer, HumanPlayer);

				if (Pawn_Promotion_Choice == "ROOK")
				{
					std::string PawnPromotionChessPiece = "BR";
					PawnPromotionPieceCount[4]++;
					PawnPromotionChessPiece += std::to_string(PawnPromotionPieceCount[4]);

					Board[NewChessPiecePositionRow][NewChessPiecePositionColumn] = PawnPromotionChessPiece;
				}

				if (Pawn_Promotion_Choice == "KNIGHT")
				{
					std::string PawnPromotionChessPiece = "BN";
					PawnPromotionPieceCount[5]++;
					PawnPromotionChessPiece += std::to_string(PawnPromotionPieceCount[5]);

					Board[NewChessPiecePositionRow][NewChessPiecePositionColumn] = PawnPromotionChessPiece;
				}

				if (Pawn_Promotion_Choice == "BISHOP")
				{
					std::string PawnPromotionChessPiece = "BB";
					PawnPromotionPieceCount[6]++;
					PawnPromotionChessPiece += std::to_string(PawnPromotionPieceCount[6]);

					Board[NewChessPiecePositionRow][NewChessPiecePositionColumn] = PawnPromotionChessPiece;
				}

				if (Pawn_Promotion_Choice == "QUEEN")
				{
					std::string PawnPromotionChessPiece = "BQ";
					PawnPromotionPieceCount[7]++;
					PawnPromotionChessPiece += std::to_string(PawnPromotionPieceCount[7]);

					Board[NewChessPiecePositionRow][NewChessPiecePositionColumn] = PawnPromotionChessPiece;
				}
			}
	}
}

std::string Get_Pawn_Promotion_Choice(const unsigned int& NumberOfPlayers,
																			const std::string& CurrentPlayer,
																			const std::string& HumanPlayer)
{
	std::string Pawn_Promotion_Choice;

	switch (NumberOfPlayers)
	{
	case 0:
		Pawn_Promotion_Choice = Ask_AI_For_Pawn_Promotion_Choice();
		break;

	case 1:
	{
		if (CurrentPlayer == HumanPlayer)
			Pawn_Promotion_Choice = Ask_User_For_Pawn_Promotion_Choice();

		else
			Pawn_Promotion_Choice = Ask_AI_For_Pawn_Promotion_Choice();

		break;
	}

	case 2:
		Pawn_Promotion_Choice = Ask_User_For_Pawn_Promotion_Choice();
		break;

	default:
		std::cout << "Error in Get_Pawn_Promotion_Choice() switch statement\n";
		break;
	}

	return Pawn_Promotion_Choice;
}

std::string Ask_AI_For_Pawn_Promotion_Choice(void)
{
	bool isValueCorrect = false; // Flag for if input value in invalid
	std::string Pawn_Promotion_Choice;

	switch (std::rand() % 4)
	{
	case 0:
		Pawn_Promotion_Choice = "ROOK";
		break;

	case 1:
		Pawn_Promotion_Choice = "KNIGHT";
		break;

	case 2:
		Pawn_Promotion_Choice = "BISHOP";
		break;

	case 3:
		Pawn_Promotion_Choice = "QUEEN";
		break;
	}

	return Pawn_Promotion_Choice;
}

std::string Ask_User_For_Pawn_Promotion_Choice(void)
{
	bool isValueCorrect = false; // Flag for if input value in invalid
	std::string Pawn_Promotion_Choice;

	while (!isValueCorrect)
	{
		// Prompt user for next command that will be the next grid position to attack
		std::cout << "Enter your pawn promotion choice (E.g. QUEEN): ";

		getline(std::cin, Pawn_Promotion_Choice);

		// Check if cin failed
		if (std::cin.fail())
		{
			// Clear buffer and retry
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}

		Capitalise_String(Pawn_Promotion_Choice);

		if (Pawn_Promotion_Choice == "ROOK" || Pawn_Promotion_Choice == "KNIGHT" || Pawn_Promotion_Choice == "BISHOP" || Pawn_Promotion_Choice == "QUEEN")
		{
			isValueCorrect = true;
			continue;
		}
	}

	return Pawn_Promotion_Choice;
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

// Castling in Execute_Next_Move()
// Is_King_In_Check()
// Ask user for colour for if one player chosen

// En passant (only pawns can do it and must be done straight away by oppennent)

// Comments

// move tictactoe play and test in to their mains and do this for all other games
// Smaller tabs indents for other games
// unisgend int
// include name and then cmakelist and ctest