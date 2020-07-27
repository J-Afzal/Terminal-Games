#include "../include/Chess.hpp"

int main(void) {

	std::vector< std::vector<std::string> > Board;
	std::vector<std::string> WhiteCapturedPieces;
	std::vector<std::string> BlackCapturedPieces;
	unsigned int NumberOfPlayers, NumberOfTurns = 0;
	std::vector<unsigned int> PawnPromotionPieceCount = { 2, 2, 2, 1, 2, 2, 2, 1 }; // WhiteRookCount = 2, WhiteKnightCount = 2, WhiteBishopCount = 2, WhiteQueenCount = 1, BlackRookCount = 2, BlackKnightCount = 2, BlackBishopCount = 2, BlackQueenCount = 1
	std::string HumanPlayer, CurrentPlayer;
	bool Stalemate = false;

	Setup_Game(Board, NumberOfPlayers, HumanPlayer, CurrentPlayer);

	while (!Game_Over(Board, CurrentPlayer, Stalemate))
	{
		Toggle_Player(CurrentPlayer);

		std::string NextMove;

		NextMove = Ask_AI_For_Next_Move(Board, CurrentPlayer, HumanPlayer, NumberOfPlayers, WhiteCapturedPieces, BlackCapturedPieces, PawnPromotionPieceCount);

		Execute_Next_Move(Board, NextMove, CurrentPlayer, HumanPlayer, NumberOfPlayers, WhiteCapturedPieces, BlackCapturedPieces, PawnPromotionPieceCount);

		NumberOfTurns++;
	}
	
	return 0;
}
