#include "TicTacToe.hpp"

int main(void)
{
  // Variables for the TicTacToe game
  //  - UserXOChoice is used when there is only one player and contains the 'X' or 'O' that the user has chosen to be
  //  - GameData contains the game info of the TicTacToe grid
  unsigned int NumberOfTurns = 0, CurrentPlayer = 0, NumberOfPlayers = 0, UserXOChoice = 0;
  std::vector< std::vector<int> > GameData;

  // Set seed to system time at 0 to create pseudo random numbers
  std::srand((unsigned int)std::time(0));

  // Assign currentplayer, and thus player to play first, randomly
  if (std::rand() % 2 == 0)
    CurrentPlayer = 'X'; // It will be converted to 88
  else
    CurrentPlayer = 'O'; // It will be converted to 79

// The for loops add the 3 rows and columns to the grid and the the appropriate grid values
  for (unsigned int i = 0, GridNumber = 0; i < 3; i++)
  {
    std::vector<int> Rows;
    GameData.push_back(Rows);

    for (int j = 0; j < 3; j++, GridNumber++)
      GameData[i].push_back(GridNumber);
  }

  // Loop until a winning condition is met or no more moves are possible and game is over
  while (!Winning_Conditions_Met(GameData) && !Game_Over(GameData))
  {
    CurrentPlayer = Toggle_Player(CurrentPlayer);

    Ask_Computer_For_Next_Input(GameData, CurrentPlayer);

    NumberOfTurns++;

    std::cout << "\n\n\n";
  }

    return 0;
}
