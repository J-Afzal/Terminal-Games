//
//  @File: main.cpp for TicTacToe
//  @Author: Junaid Afzal
//

#include "tictactoe.hpp"
#include "functions.hpp"

int main(void)
{
  bool GameIsRunning = true;

  while (GameIsRunning)
  {
    // GameData contains the Tic Tac Toe grid
    unsigned int NumberOfTurns = 0, NumberOfPlayers = 0;
    std::string CurrentPlayer, UserPlayerChoice, AIDifficulty = "N/A";
    std::vector<std::vector<std::string>> GameData;
    std::vector<unsigned int> ValidMovesRemaining;

    // The user is asked for the number of (human) players
    // If this is 1, the human player is asked if they want to be player X or player O
    // The current player (and thus the player that starts) is assigned pseudo randomly
    Setup_Game(GameData, ValidMovesRemaining, NumberOfPlayers, UserPlayerChoice, AIDifficulty, CurrentPlayer);

    // Loop until a winning condition is met or no more moves are possible
    while (!Game_Over(NumberOfTurns) && !Winning_Conditions_Met(GameData))
    {
      Toggle_Player(CurrentPlayer);

      // Check if user input is required
      if (NumberOfPlayers == 2 || CurrentPlayer == UserPlayerChoice)
        Get_Next_User_Command(GameData, NumberOfPlayers, AIDifficulty, CurrentPlayer, ValidMovesRemaining); // Game is displayed before user is asked for an input

      else
        Get_Next_AI_Command(GameData, NumberOfPlayers, AIDifficulty, CurrentPlayer, ValidMovesRemaining); // Game is displayed before AI  is asked for an input

      NumberOfTurns++;
    }

    // Determine the winner, if there is one, and display winning message
    Display_Game_Over_Message(GameData, NumberOfPlayers, AIDifficulty, CurrentPlayer, NumberOfTurns, GameIsRunning);
  }

  Clear_Terminal();

  return 0;
}
