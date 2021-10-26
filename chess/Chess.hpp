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

void Setup_Game(std::vector<std::vector<std::string>> &Board,
								unsigned int &NumberOfPlayers,
								std::string &HumanPlayer,
								std::string &CurrentPlayer);

int Ask_User_For_Number_Of_Players(void);

bool Game_Over(const std::vector<std::vector<std::string>> &Board,
							 const std::string &CurrentPlayer,
							 bool &Stalemate);

bool Is_King_In_Check(const std::vector<std::vector<std::string>> &Board,
											const std::string &CurrentPlayer);

void Toggle_Player(std::string &CurrentPlayer);

void Display_Game(const std::vector<std::vector<std::string>> &Board,
									const std::vector<std::string> &WhiteCapturedPieces,
									const std::vector<std::string> &BlackCapturedPieces);

std::string Ask_AI_For_Next_Move(const std::vector<std::vector<std::string>> &Board,
																 const std::string &CurrentPlayer,
																 const std::string &HumanPlayer,
																 const unsigned int &NumberOfPlayers,
																 const std::vector<std::string> &WhiteCapturedPieces,
																 const std::vector<std::string> &BlackCapturedPieces,
																 const std::vector<unsigned int> &PawnPromotionPieceCount,
																 std::vector<bool> &HasCastlingPiecesMoved);

bool Is_Next_Move_Legal(const std::vector<std::vector<std::string>> &Board,
												const std::string &NextMove,
												const std::string &CurrentPlayer,
												const std::string &HumanPlayer,
												const unsigned int &NumberOfPlayers,
												const std::string &ChessPiece,
												const unsigned int &NewChessPiecePositionRow,
												const unsigned int &NewChessPiecePositionColumn,
												const std::vector<std::string> &WhiteCapturedPieces,
												const std::vector<std::string> &BlackCapturedPieces,
												const std::vector<unsigned int> &PawnPromotionPieceCount,
												std::vector<bool> &HasCastlingPiecesMoved);

std::string Ask_User_For_Next_Move(const std::vector<std::vector<std::string>> &Board,
																	 const std::string &CurrentPlayer,
																	 const std::string &HumanPlayer,
																	 const unsigned int &NumberOfPlayers,
																	 const std::vector<std::string> &WhiteCapturedPieces,
																	 const std::vector<std::string> &BlackCapturedPieces,
																	 std::vector<unsigned int> &PawnPromotionPieceCount,
																	 std::vector<bool> &HasCastlingPiecesMoved);

void Capitalise_String(std::string &aString);

void ConvertNewChessPiecePosition(const std::string NewChessPiecePosition,
																	unsigned int &NewChessPiecePositionRow,
																	unsigned int &NewChessPiecePositionColumn);

void Execute_Next_Move(std::vector<std::vector<std::string>> &Board,
											 const std::string &NextMove,
											 const std::string &CurrentPlayer,
											 const std::string &HumanPlayer,
											 const unsigned int &NumberOfPlayers,
											 std::vector<std::string> &WhiteCapturedPieces,
											 std::vector<std::string> &BlackCapturedPieces,
											 std::vector<unsigned int> &PawnPromotionPieceCount);

std::string Get_Pawn_Promotion_Choice(const unsigned int &NumberOfPlayers,
																			const std::string &CurrentPlayer,
																			const std::string &HumanPlayer);

std::string Ask_AI_For_Pawn_Promotion_Choice(void);

std::string Ask_User_For_Pawn_Promotion_Choice(void);

void Display_Winning_Message(const std::vector<std::vector<std::string>> &Board,
														 const std::vector<std::string> &WhiteCapturedPieces,
														 const std::vector<std::string> &BlackCapturedPieces,
														 const bool &Stalemate,
														 const std::string &CurrentPlayer,
														 const unsigned int &NumberOfTurns,
														 bool &GameIsRunning);

#endif /* Chess_hpp */
