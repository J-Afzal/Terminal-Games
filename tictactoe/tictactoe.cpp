//
//  @File: TicTacToe.cpp
//  @Author: Junaid Afzal
//

// to prevent max error with windows.h redefining it
// https://stackoverflow.com/questions/7035023/stdmax-expected-an-identifier/7035078
#define NOMINMAX
#include <windows.h>

#include "tictactoe.hpp"
#include "functions.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <conio.h>

void Setup_Game(std::vector<std::vector<std::string>> &GameData,
                std::vector<unsigned int> &ValidMovesRemaining,
                unsigned int &NumberOfPlayers,
                std::string &UserPlayerChoice,
                std::string &AIDifficulty,
                std::string &CurrentPlayer)
{
  // The for loops add the 3 rows and columns to the grid and the the appropriate grid values
  for (unsigned int i = 0, GridNumber = 0; i < 3; i++)
  {
    std::vector<std::string> Rows;
    GameData.push_back(Rows);

    for (unsigned int j = 0; j < 3; j++, GridNumber++)
    {
      GameData[i].push_back(" ");
      ValidMovesRemaining.push_back(GridNumber);
    }
  }

  // Ask user for number of players until correct number given
  do
  {
    Display_Game(GameData, "N/A", "N/A");
    std::cout << "\n\nPlease enter the number of human players: ";
  }
  while(!Get_Number_Of_Players(NumberOfPlayers, 0, 2));

  // If only one human user then ask them for which player they want to be (X or O)
  if (NumberOfPlayers == 1)
  {
    do
    {
      Display_Game(GameData, std::to_string(NumberOfPlayers), "N/A");
      std::cout << "\n\nWhat player would you like to be? (Player One = X and Player Two = O): ";
    }
    while(Get_User_Player_Choice(UserPlayerChoice));
  }

  // If AI involved get difficulty
  if (NumberOfPlayers < 2)
  {
    do
    {
      Display_Game(GameData, std::to_string(NumberOfPlayers), "N/A");
      std::cout << "\n\nPlease enter the AI difficulty (EASY or HARD): ";
    }
    while (Get_AI_Difficulty(AIDifficulty));
  }

  // Set seed to system time at 0 to create pseudo random numbers
  std::srand((unsigned int)std::time(0));

  // Assign CurrentPlayer, and thus player to play first, randomly
  if (std::rand() % 2 == 0)
    CurrentPlayer = "PLAYER ONE"; // X
  else
    CurrentPlayer = "PLAYER TWO"; // O
}

void Display_Game(const std::vector<std::vector<std::string>> &GameData,
                  const std::string &NumberOfPlayers,
                  const std::string &AIDifficulty)
{
  // Start from blank terminal
  Clear_Terminal();

  // Line 1
  std::cout << ' ' << GameData[0][0] << ' ' << (char)179 << ' ' << GameData[0][1] << ' ' << (char)179 << ' ' << GameData[0][2] << ' ';
  std::cout << "\t    Tic Tac Toe    \t";
  std::cout << " 1 " << (char)179 << " 2 " << (char)179 << " 3 \n";

  // Line 2
  std::cout << (char)196 << (char)196 << (char)196 << (char)197 << (char)196 << (char)196 << (char)196 << (char)197 << (char)196 << (char)196 << (char)196;
  std::cout << "\t\t\t\t";
  std::cout << (char)196 << (char)196 << (char)196 << (char)197 << (char)196 << (char)196 << (char)196 << (char)197 << (char)196 << (char)196 << (char)196;

  // Line 3
  std::cout << "\n " << GameData[1][0] << ' ' << (char)179 << ' ' << GameData[1][1] << ' ' << (char)179 << ' ' << GameData[1][2] << ' ';
  if (NumberOfPlayers == "N/A")
    std::cout << "\t # of Players = " << NumberOfPlayers << '\t';
  else
    std::cout << "\t  # of Players = " << NumberOfPlayers << '\t';
  std::cout << " 4 " << (char)179 << " 5 " << (char)179 << " 6 \n";

  // Line 4
  std::cout << (char)196 << (char)196 << (char)196 << (char)197 << (char)196 << (char)196 << (char)196 << (char)197 << (char)196 << (char)196 << (char)196;
  std::cout << "\t\t\t\t";
  std::cout << (char)196 << (char)196 << (char)196 << (char)197 << (char)196 << (char)196 << (char)196 << (char)197 << (char)196 << (char)196 << (char)196;

  // Line 5
  std::cout << "\n " << GameData[2][0] << ' ' << (char)179 << ' ' << GameData[2][1] << ' ' << (char)179 << ' ' << GameData[2][2] << ' ';
  std::cout << "\tAI Difficulty = " << AIDifficulty << '\t';
  std::cout << " 7 " << (char)179 << " 8 " << (char)179 << " 9 \n";
}

void Get_Next_User_Command(std::vector<std::vector<std::string>> &GameData,
                           const unsigned int &NumberOfPlayers,
                           const std::string &AIDifficulty,
                           const std::string &CurrentPlayer,
                           std::vector<unsigned int> &ValidMovesRemaining)
{
  bool IsValueCorrect = false; // Flag for if input value is valid
  std::string Input;
  unsigned int UserCommand, Row, Column;

  while (!IsValueCorrect)
  {
    Display_Game(GameData, std::to_string(NumberOfPlayers), AIDifficulty);
    if (CurrentPlayer == "PLAYER ONE")
      std::cout << "\n\nPlayer X, please enter your command ";
    else
      std::cout << "\n\nPlayer O, please enter your command ";

    std::getline(std::cin, Input);

    // Only one character allowed
    if (Input.size() != 1)
      continue;

    // Only 1-9 allowed
    if (Input[0] < '1' || Input[0] > '9')
      continue;

    // To get it into range of 0-8
    UserCommand = std::stoi(Input, nullptr, 10) - 1;

    auto CommandPosition = std::find(ValidMovesRemaining.begin(), ValidMovesRemaining.end(), UserCommand);

    if (CommandPosition != ValidMovesRemaining.end())
    {
      IsValueCorrect = true;

      Column = UserCommand % 3;
      Row = UserCommand / 3;

      if (CurrentPlayer == "PLAYER ONE")
        GameData[Row][Column] = "X";
      else
        GameData[Row][Column] = "O";

      ValidMovesRemaining.erase(CommandPosition);
    }
  }
}

void Get_Next_AI_Command(std::vector<std::vector<std::string>> &GameData,
                         const unsigned int &NumberOfPlayers,
                         const std::string &AIDifficulty,
                         const std::string &CurrentPlayer,
                         std::vector<unsigned int> &ValidMovesRemaining)
{
  unsigned int AICommand, Row, Column;

  Display_Game(GameData, std::to_string(NumberOfPlayers), AIDifficulty);

  AICommand = ValidMovesRemaining[std::rand() % ValidMovesRemaining.size()];
  auto CommandPosition = std::find(ValidMovesRemaining.begin(), ValidMovesRemaining.end(), AICommand);
  ValidMovesRemaining.erase(CommandPosition);

  Column = AICommand % 3;
  Row = AICommand / 3;

  // Go to the command position in the grid and overwrite with the current player
  if (CurrentPlayer == "PLAYER ONE")
    GameData[Row][Column] = "X";
  else
    GameData[Row][Column] = "O";
}

bool Game_Over(const unsigned int &NumberOfTurns)
{
  // End the game once 9 turns have taken place
  if (NumberOfTurns == 9)
    return true;

  else
    return false;
}

bool Winning_Conditions_Met(const std::vector<std::vector<std::string>> &GameData)
{
  // Check Horizontals
  if (GameData[0][0]!= " " && GameData[0][0] == GameData[0][1] && GameData[0][1] == GameData[0][2])
    return true;

  else if (GameData[1][0]!= " " && GameData[1][0] == GameData[1][1] && GameData[1][1] == GameData[1][2])
    return true;

  else if (GameData[2][0]!= " " && GameData[2][0] == GameData[2][1] && GameData[2][1] == GameData[2][2])
    return true;

  // Check verticals
  else if (GameData[0][0]!= " " && GameData[0][0] == GameData[1][0] && GameData[1][0] == GameData[2][0])
    return true;

  else if (GameData[0][1]!= " " && GameData[0][1] == GameData[1][1] && GameData[1][1] == GameData[2][1])
    return true;

  else if (GameData[0][2]!= " " && GameData[0][2] == GameData[1][2] && GameData[1][2] == GameData[2][2])
    return true;

  // Check diagonals
  else if (GameData[0][0]!= " " && GameData[0][0] == GameData[1][1] && GameData[1][1] == GameData[2][2])
    return true;

  else if (GameData[2][0]!= " " && GameData[2][0] == GameData[1][1] && GameData[1][1] == GameData[0][2])
    return true;

  else
    return false;
}

void Display_Game_Over_Message(const std::vector<std::vector<std::string>> &GameData,
                               const unsigned int &NumberOfPlayers,
                               const std::string &AIDifficulty,
                               const std::string &CurrentPlayer,
                               const unsigned int &NumberOfTurns,
                               bool &GameIsRunning)
{
  Display_Game(GameData, std::to_string(NumberOfPlayers), AIDifficulty);

  // Winner will be current player as Toggle_Player() function has not been called
  // from receiving input and determining winner
  if (Winning_Conditions_Met(GameData))
  {
    if (CurrentPlayer == "PLAYER ONE")
      std::cout << "\n\n\t\t     GAME OVER\n\n    Player X has won! The game lasted " << NumberOfTurns << " turns.";

    else
      std::cout << "\n\n\t\t     GAME OVER\n\n    Player O has won! The game lasted " << NumberOfTurns << " turns.";
  }

  // No winner so a draw
  else
    std::cout << "\n\n\t\t     GAME OVER\n\n      It is a draw! The game lasted " << NumberOfTurns << " turns.";

  std::cout << "\n\nPress 'Q' to quit OR any other key to play again...";

  // Gets key pressed and then checks and clears terminal window if replaying
  if (_getch() == 'q')
    GameIsRunning = false;

  else
    // Start from blank terminal
    Clear_Terminal();
}
