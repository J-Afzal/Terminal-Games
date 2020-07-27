#include "TicTacToe.hpp"

int main(void)
{
  bool GameIsRunning = true;

  while (GameIsRunning)
  {
    // UserXOChoice is used when there is only one player and contains the 'X' or 'O' that the user has chosen to be
    // GameData contains the Tic Tac Toe grid
    unsigned int NumberOfTurns = 0, CurrentPlayer = 0, NumberOfPlayers = 0, UserXOChoice = 0;
    std::vector< std::vector<int> > GameData;

    // The current player (and thus the player that starts) is assigned pseudo randomly; user is asked for the size of the
    // TicTacToe grid and is created; user is asked for the number of players; if players is 1 then human user asked if they
    // want to be player X or player O
    Setup_Game(NumberOfTurns, CurrentPlayer, NumberOfPlayers, UserXOChoice, GameData);

    // Loop until a winning condition is met or no more moves are possible and game is over
    while (!Game_Over(GameData) && !Winning_Conditions_Met(GameData))
    {
      // Displays the current TicTacToe grid
      Display_Game(GameData);

      CurrentPlayer = Toggle_Player(CurrentPlayer);

      // Check if user input is required
      if (NumberOfPlayers == 2 || CurrentPlayer == UserXOChoice)
        Ask_User_For_Next_Input(GameData, CurrentPlayer);

      else
        Ask_Computer_For_Next_Input(GameData, CurrentPlayer);

      NumberOfTurns++;

      std::cout << "\n\n\n";
    }

    // Determine the winner, if there is one, and display winning message
    Display_Game_Over_Message(NumberOfTurns, GameData, CurrentPlayer, GameIsRunning);
  }
  
  return 0;
}
