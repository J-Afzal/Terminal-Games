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

bool Game_Over(const std::vector< std::vector<std::string> >& Board, 
			   const std::string& CurrentPlayer,
			   bool& Stalemate);

bool Is_King_In_Check(const std::vector< std::vector<std::string> >& Board,
					  const std::string& CurrentPlayer);

void Toggle_Player(std::string& CurrentPlayer);

void Display_Game(const std::vector< std::vector<std::string> >& Board,
				  const std::vector<std::string>& WhiteCapturedPieces,
				  const std::vector<std::string>& BlackCapturedPieces);

std::string Ask_AI_For_Next_Move(const std::vector< std::vector<std::string> >& Board, 
								 const std::string& CurrentPlayer,
								 const std::vector<std::string>& WhiteCapturedPieces,
								 const std::vector<std::string>& BlackCapturedPieces);

bool Is_Next_Move_Valid(const std::vector< std::vector<std::string> >& Board, 
						const std::string& CurrentPlayer, 
						const std::string& ChessPiece, 
						const unsigned int& NewChessPieceNewPositionColumn,
					    const unsigned int& NewChessPieceNewPositionRow,
						const std::vector<std::string>& WhiteCapturedPieces,
						const std::vector<std::string>& BlackCapturedPieces);

std::string Ask_User_For_Next_Move(const std::vector< std::vector<std::string> >& Board, 
								   const std::string& CurrentPlayer,
								   const std::vector<std::string>& WhiteCapturedPieces,
								   const std::vector<std::string>& BlackCapturedPieces);

void Capitalise_String(std::string& aString);

void ConvertNewChessPiecePosition(const std::string NewChessPiecePosition, 
								  unsigned int& NewChessPiecePositionColumn, 
								  unsigned int& NewChessPiecePositionRow);

void Execute_Next_Move();

void Display_Winning_Message(const std::vector< std::vector<std::string> >& Board,
							 const std::vector<std::string>& WhiteCapturedPieces,
							 const std::vector<std::string>& BlackCapturedPieces,
							 const bool& Stalemate,
							 const std::string& CurrentPlayer,
							 const unsigned int& NumberOfTurns,
							 bool& GameIsRunning);

#endif /* Chess_hpp */
