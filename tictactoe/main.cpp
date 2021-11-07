/**
 * @file main.cpp
 * @author Junaid Afzal
 * @brief Game loop for Tic Tac Toe
 * @version 1.0
 * @date 07-11-2021
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "tictactoe.hpp"
#include "functions.hpp"

int main(void)
{
  bool GameIsRunning = true;

  while (GameIsRunning)
  {
    unsigned int NumberOfTurns = 0, NumberOfPlayers = 0;
    std::string CurrentPlayer, UserPlayerChoice, AIDifficulty;
    std::vector<unsigned int> ValidMovesRemaining;
    std::vector<std::vector<std::string>> TicTacToeGrid;

    Setup_Game(TicTacToeGrid, ValidMovesRemaining, NumberOfPlayers, UserPlayerChoice, AIDifficulty, CurrentPlayer);

    while (!Game_Over(NumberOfTurns) && !Winning_Conditions_Met(TicTacToeGrid))
    {
      Toggle_Player(CurrentPlayer);

      // Display_Game() called before either user or AI are asked for an input
      if (NumberOfPlayers == 2 || CurrentPlayer == UserPlayerChoice)
        Get_Next_User_Command(TicTacToeGrid, NumberOfPlayers, AIDifficulty, CurrentPlayer, ValidMovesRemaining);

      else
        Get_Next_AI_Command(TicTacToeGrid, NumberOfPlayers, AIDifficulty, CurrentPlayer, ValidMovesRemaining);

      NumberOfTurns++;
    }

    Display_Game_Over_Message(TicTacToeGrid, NumberOfPlayers, AIDifficulty, CurrentPlayer, NumberOfTurns, GameIsRunning);
  }

  return 0;
}
