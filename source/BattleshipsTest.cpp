#include "Battleships.hpp"

int main(void) {

  // Variables needed for the game
  std::vector< std::vector<char> > PlayerOneBoard, PlayerOneOpponentBoard, PlayerTwoBoard, PlayerTwoOpponentBoard;
  std::string CurrentPlayer;
  unsigned int NumberOfPlayers = 0, NumberOfTurns = 0;

  // Board size is a standard 10 x 10
  unsigned int NumberOfRows = 10, NumberOfColumns = 10;

  // The ComputerBoard and UserBoard will be filled with spaces while the opponent boards will be filled
  // with incrementing numbers from 0 - 99, left to right and then top to bottom
  for (unsigned int i = 0, CurrentPosition = 0; i < NumberOfRows; i++)
  {
    std::vector<char> Row;

    PlayerOneBoard.push_back(Row);
    PlayerOneOpponentBoard.push_back(Row);
    PlayerTwoBoard.push_back(Row);
    PlayerTwoOpponentBoard.push_back(Row);

    for (unsigned int j = 0; j < NumberOfColumns; j++, CurrentPosition++)
    {
      PlayerOneBoard[i].push_back('.');
      PlayerOneOpponentBoard[i].push_back(CurrentPosition);
      PlayerTwoBoard[i].push_back('.');
      PlayerTwoOpponentBoard[i].push_back(CurrentPosition);
    }
  }

  // Set seed for std::rand() to system time at 0
  std::srand((unsigned int)std::time(0));

  // Ask computer for the ship positions and update computer board
  Ask_Computer_For_Ship_Positions(PlayerOneBoard);

  // Ask computer for the ship positions and update computer board
  Ask_Computer_For_Ship_Positions(PlayerTwoBoard);

  // Use std::rand() to randomly choose the player to start
  if ((std::rand() % 2) == 0)
    CurrentPlayer = "PLAYER_ONE";
  else
    CurrentPlayer = "PLAYER_TWO";

  //Loop until a winning condition on either board exists
  while (!Winning_Conditions_Met(PlayerOneBoard, PlayerTwoBoard))
  {
    // Change to the other player
    Toggle_Player(CurrentPlayer);

    // Player is the computer
    if (CurrentPlayer == "PLAYER_ONE")
    {
      //Ask computer for a grid position that they want to attack
      unsigned int Command = Ask_Computer_For_Next_Command(PlayerOneOpponentBoard);

      // Carry out the attack and update the corresponding boards
      Execute_Next_Turn(PlayerOneBoard, PlayerOneOpponentBoard, PlayerTwoBoard, PlayerTwoOpponentBoard, CurrentPlayer, Command);
    }

    // Player is the computer
    else
    {
      //Ask computer for a grid position that they want to attack
      unsigned int Command = Ask_Computer_For_Next_Command(PlayerTwoOpponentBoard);

      // Carry out the attack and update the corresponding boards
      Execute_Next_Turn(PlayerOneBoard, PlayerOneOpponentBoard, PlayerTwoBoard, PlayerTwoOpponentBoard, CurrentPlayer, Command);
    }

    // Increment the number of turns
    NumberOfTurns++;
  }

  return 0;
}
