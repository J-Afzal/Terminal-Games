/**
 * @file main.cpp
 * @author Junaid Afzal
 * @brief Game loop for Battleships
 * @version 1.0
 * @date 07-11-2021
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "Battleships.hpp"
#include "Functions.hpp"

int main(void)
{
  bool GameIsRunning = true;

  while (GameIsRunning)
  {
    std::vector<std::vector<std::string>> PlayerOneBoard, PlayerTwoBoard;
    std::vector<unsigned int> PlayerOneValidMovesRemaining, PlayerTwoValidMovesRemaining;
    std::map<std::string, unsigned int> PlayerOneShipsRemaining, PlayerTwoShipsRemaining;
    unsigned int NumberOfPlayers, NumberOfTurns = 0;
    std::string CurrentPlayer, AIDifficulty;

    Setup_Game(PlayerOneBoard, PlayerTwoBoard, PlayerOneValidMovesRemaining, PlayerTwoValidMovesRemaining, PlayerOneShipsRemaining, PlayerTwoShipsRemaining, NumberOfPlayers, AIDifficulty, CurrentPlayer);

    while (!Winning_Conditions_Met(PlayerOneBoard, PlayerTwoBoard))
    {
      Toggle_Player(CurrentPlayer);

      unsigned int Command;

      // Display_Game() called before either user or AI are asked for an input
      if (NumberOfPlayers == 1 && CurrentPlayer == "PLAYER ONE")
        Command = Get_Next_User_Command(PlayerOneBoard, PlayerTwoBoard, PlayerOneShipsRemaining, PlayerTwoShipsRemaining, NumberOfPlayers, AIDifficulty);
      else
        Command = Get_Next_AI_Command(PlayerOneBoard, PlayerTwoBoard, PlayerOneShipsRemaining, PlayerTwoShipsRemaining, PlayerOneValidMovesRemaining, PlayerTwoValidMovesRemaining, NumberOfPlayers, AIDifficulty, CurrentPlayer);

      Execute_Next_Turn(PlayerOneBoard, PlayerTwoBoard, PlayerOneShipsRemaining, PlayerTwoShipsRemaining, CurrentPlayer, Command);

      NumberOfTurns++;
    }

    Display_Game_Over_Message(PlayerOneBoard, PlayerTwoBoard, PlayerOneShipsRemaining, PlayerTwoShipsRemaining, NumberOfPlayers, AIDifficulty, CurrentPlayer, NumberOfTurns, GameIsRunning);
  }

  return 0;
}
