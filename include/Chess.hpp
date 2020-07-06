//
//  Chess.hpp
//  Chess
//
//  Created by Main on 07/01/2020.
//  Copyright © 2020 Junaid Afzal. All rights reserved.
//

#ifndef Chess_hpp
#define Chess_hpp

#include <iostream>
#include <vector>

void Play_Chess(void);

void Test_Chess(void);

void Setup_Game(std::vector< std::vector<std::string> >& Board, 
				unsigned int& NumberOfPlayers, 
				std::string& HumanPlayer, 
				std::string& CurrentPlayer);

int Ask_User_For_Number_Of_Players(void);

bool Game_Over();

bool Is_King_In_Check();

void Toggle_Player(std::string& CurrentPlayer);

void Display_Game(const std::vector< std::vector<std::string> >& Board);

std::string Ask_AI_For_Next_Move(const std::vector< std::vector<std::string> >& Board, 
								 const std::string& CurrentPlayer,
								 std::vector<std::string>& WhiteCapturedPieces,
								 std::vector<std::string>& BlackCapturedPieces);

bool Is_Next_Move_Valid(const std::vector< std::vector<std::string> >& Board, 
						const std::string& CurrentPlayer, 
						const std::string& ChessPiece, 
					    const int& ChessPieceNewPositionRow, 
						const int& ChessPieceNewPositionColumn,
						std::vector<std::string>& WhiteCapturedPieces,
						std::vector<std::string>& BlackCapturedPieces);

std::string Ask_User_For_Next_Move(const std::vector< std::vector<std::string> >& Board, 
								   const std::string& CurrentPlayer,
								   std::vector<std::string>& WhiteCapturedPieces,
								   std::vector<std::string>& BlackCapturedPieces);

void Capitalise_String(std::string& aString);

void ConvertChessPieceNewPosition(std::string ChessPieceNewPosition, int& ChessPieceNewPositionRow, int& ChessPieceNewPositionColumn);

void Execute_Next_Move();

void Display_Winning_Message();

#endif /* Chess_hpp */
