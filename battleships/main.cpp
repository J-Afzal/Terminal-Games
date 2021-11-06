//
//  @File: main.cpp for Battleships
//  @Author: Junaid Afzal
//

#include "Battleships.hpp"
#include "Functions.hpp"

int main(void)
{
  bool GameIsRunning = true;

  while (GameIsRunning)
  {
    // Variables needed for the game
    std::vector<std::vector<std::string>> PlayerOneBoard, PlayerTwoBoard;
    std::string CurrentPlayer, AIDifficulty;
    std::vector<unsigned int> PlayerOneValidMovesRemaining, PlayerTwoValidMovesRemaining;
    std::map<std::string, unsigned int> PlayerOneShipsRemaining, PlayerTwoShipsRemaining;
    unsigned int NumberOfPlayers, NumberOfTurns = 0;

    // Setups all the variables so that game can be played
    Setup_Game(PlayerOneBoard, PlayerTwoBoard, NumberOfPlayers, CurrentPlayer, AIDifficulty, PlayerOneValidMovesRemaining, PlayerTwoValidMovesRemaining, PlayerOneShipsRemaining, PlayerTwoShipsRemaining);

    // Loop until a winning condition on either board exists
    while (!Winning_Conditions_Met(PlayerOneBoard, PlayerTwoBoard))
    {
      Toggle_Player(CurrentPlayer);

      unsigned int Command;

      // Human player is PLAYER ONE by default
      if (NumberOfPlayers == 1 && CurrentPlayer == "PLAYER ONE")
        Command = Ask_User_For_Next_Command(PlayerOneBoard, PlayerTwoBoard, NumberOfPlayers, AIDifficulty, PlayerOneShipsRemaining, PlayerTwoShipsRemaining);
      else
        Command = Ask_Computer_For_Next_Command(PlayerOneBoard, PlayerTwoBoard, PlayerOneValidMovesRemaining, PlayerTwoValidMovesRemaining, NumberOfPlayers, CurrentPlayer, AIDifficulty, PlayerOneShipsRemaining, PlayerTwoShipsRemaining);

      // Carry out the attack and update the corresponding boards
      Execute_Next_Turn(PlayerOneBoard, PlayerTwoBoard, PlayerOneShipsRemaining, PlayerTwoShipsRemaining, CurrentPlayer, Command);

      // Increment the number of turns
      NumberOfTurns++;
    }

    // Display the winning message as game is now over
    Display_Game_Over_Message(CurrentPlayer, NumberOfTurns, GameIsRunning, PlayerOneBoard, PlayerTwoBoard, NumberOfPlayers, AIDifficulty, PlayerOneShipsRemaining, PlayerTwoShipsRemaining);
  }

  Clear_Terminal();

  return 0;
}
