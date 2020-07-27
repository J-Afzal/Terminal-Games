#include "../include/Chess.hpp"

int main(void) {

	bool GameIsRunning = true;

	while (GameIsRunning)
	{
		std::vector< std::vector<std::string> > Board;
		std::vector<std::string> WhiteCapturedPieces;
		std::vector<std::string> BlackCapturedPieces;
		unsigned int NumberOfPlayers, NumberOfTurns = 0;
		std::vector<unsigned int> PawnPromotionPieceCount = { 2, 2, 2, 1, 2, 2, 2, 1 }; // WhiteRookCount = 2, WhiteKnightCount = 2, WhiteBishopCount = 2, WhiteQueenCount = 1, BlackRookCount = 2, BlackKnightCount = 2, BlackBishopCount = 2, BlackQueenCount = 1
		std::string HumanPlayer, CurrentPlayer;
		bool Stalemate = false;
		std::vector<bool> HasCastlingPiecesMoved = { false, false, false, false, false, false }; // WK, WR1, WR2, BK, BR1, BR2

		Setup_Game(Board, NumberOfPlayers, HumanPlayer, CurrentPlayer);

		while (!Game_Over(Board, CurrentPlayer, Stalemate))
		{
			Toggle_Player(CurrentPlayer);

			Display_Game(Board, WhiteCapturedPieces, BlackCapturedPieces);

			std::string NextMove;

			switch (NumberOfPlayers)
			{
			case 0:
				NextMove = Ask_AI_For_Next_Move(Board, CurrentPlayer, HumanPlayer, NumberOfPlayers, WhiteCapturedPieces, BlackCapturedPieces, PawnPromotionPieceCount, HasCastlingPiecesMoved);
				break;

			case 1:
			{
				if (CurrentPlayer == HumanPlayer)
					NextMove = Ask_User_For_Next_Move(Board, CurrentPlayer, HumanPlayer, NumberOfPlayers, WhiteCapturedPieces, BlackCapturedPieces, PawnPromotionPieceCount, HasCastlingPiecesMoved);

				else
					NextMove = Ask_AI_For_Next_Move(Board, CurrentPlayer, HumanPlayer, NumberOfPlayers, WhiteCapturedPieces, BlackCapturedPieces, PawnPromotionPieceCount, HasCastlingPiecesMoved);

				break;
			}

			case 2:
				NextMove = Ask_User_For_Next_Move(Board, CurrentPlayer, HumanPlayer, NumberOfPlayers, WhiteCapturedPieces, BlackCapturedPieces, PawnPromotionPieceCount, HasCastlingPiecesMoved);
				break;

			default:
				std::cout << "Error in number of players switch statement\n";
				break;
			}

			Execute_Next_Move(Board, NextMove, CurrentPlayer, HumanPlayer, NumberOfPlayers, WhiteCapturedPieces, BlackCapturedPieces, PawnPromotionPieceCount);

			NumberOfTurns++;
		}

		Display_Winning_Message(Board, WhiteCapturedPieces, BlackCapturedPieces, Stalemate, CurrentPlayer, NumberOfTurns, GameIsRunning);
	}

    return 0;
}
