//
//  @File: main.cpp for TicTacToe
//  @Author: Junaid Afzal
//

#include "TicTacToe.hpp"

int main(void)
{
  bool GameIsRunning = true;

  while (GameIsRunning)
  {
    // GameData contains the Tic Tac Toe grid
    unsigned int NumberOfTurns = 0, CurrentPlayer = 0, NumberOfPlayers = 0, UserXOChoice = 0;
    std::vector<std::vector<std::string>> GameData;

    // The user is asked for the number of (human) players
    // If this is 1, the human player is asked if they want to be player X or player O
    // The current player (and thus the player that starts) is assigned pseudo randomly
    Setup_Game(NumberOfTurns, CurrentPlayer, NumberOfPlayers, UserXOChoice, GameData);

    // Loop until a winning condition is met or no more moves are possible
    while (!Game_Over(NumberOfTurns) && !Winning_Conditions_Met(GameData))
    {
      Toggle_Player(CurrentPlayer);

      // Check if user input is required
      if (NumberOfPlayers == 2 || CurrentPlayer == UserXOChoice)
        Ask_User_For_Next_Input(GameData, CurrentPlayer); // Game is displayed before user is asked for an input

      else
        Ask_Computer_For_Next_Input(GameData, CurrentPlayer); // Game is displayed before computer is asked for an input

      NumberOfTurns++;
    }

    // Determine the winner, if there is one, and display winning message
    Display_Game_Over_Message(NumberOfTurns, GameData, CurrentPlayer, GameIsRunning);
  }

  return 0;
}
