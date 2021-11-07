/**
 * @file tictactoe.cpp
 * @author Junaid Afzal
 * @brief Implementation of tictactoe.hpp
 * @version 1.0
 * @date 07-11-2021
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "tictactoe.hpp"
#include "functions.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <conio.h>

void Setup_Game(std::vector<std::vector<std::string>> &TicTacToeGrid,
                std::vector<unsigned int> &ValidMovesRemaining,
                unsigned int &NumberOfPlayers,
                std::string &UserPlayerChoice,
                std::string &AIDifficulty,
                std::string &CurrentPlayer)
{
  for (unsigned int i = 0, GridNumber = 0; i < 3; i++)
  {
    std::vector<std::string> Rows;
    TicTacToeGrid.push_back(Rows);

    for (unsigned int j = 0; j < 3; j++, GridNumber++)
    {
      TicTacToeGrid[i].push_back(" ");
      ValidMovesRemaining.push_back(GridNumber); // 0-8
    }
  }

  // Ask user for number of players until correct number given
  do
  {
    Display_Game(TicTacToeGrid, "N/A", "N/A");
    std::cout << "Please enter the number of human players: ";
  }
  while(!Get_Number_Of_Players(NumberOfPlayers, 0, 2));

  // If only one human user, then ask them which player they want to be (X or O)
  if (NumberOfPlayers == 1)
  {
    do
    {
      Display_Game(TicTacToeGrid, std::to_string(NumberOfPlayers), "N/A");
      std::cout << "What player would you like to be? (Player One = X and Player Two = O): ";
    }
    while(!Get_User_Player_Choice(UserPlayerChoice));
  }

  // If AI involved get AI difficulty
  if (NumberOfPlayers < 2)
  {
    do
    {
      Display_Game(TicTacToeGrid, std::to_string(NumberOfPlayers), "N/A");
      std::cout << "Please enter the AI difficulty (EASY or HARD): ";
    }
    while (!Get_AI_Difficulty(AIDifficulty));
  }

  if (NumberOfPlayers == 2)
    AIDifficulty = "N/A";

  // Set seed to system time at 0 to create pseudo random numbers
  std::srand((unsigned int)std::time(0));
  if (std::rand() % 2 == 0)
    CurrentPlayer = "PLAYER ONE"; // X
  else
    CurrentPlayer = "PLAYER TWO"; // O
}

void Display_Game(const std::vector<std::vector<std::string>> &TicTacToeGrid,
                  const std::string &NumberOfPlayers,
                  const std::string &AIDifficulty)
{
  Clear_Terminal();

  // Line 1
  std::string Output = " ";
  Output.append(TicTacToeGrid[0][0] + " ");
  Output.insert(Output.size(), 1, (char)179);
  Output.append(" " + TicTacToeGrid[0][1] + " ");
  Output.insert(Output.size(), 1, (char)179);
  Output.append(" " + TicTacToeGrid[0][2] + " ");
  Output.append(" \t    Tic Tac Toe    \t 1 ");
  Output.insert(Output.size(), 1, (char)179);
  Output.append(" 2 ");
  Output.insert(Output.size(), 1, (char)179);
  Output.append(" 3 \n");

  // Line 2
  Output.insert(Output.size(), 3, (char)196);
  Output.insert(Output.size(), 1, (char)197);
  Output.insert(Output.size(), 3, (char)196);
  Output.insert(Output.size(), 1, (char)197);
  Output.insert(Output.size(), 3, (char)196);
  Output.append("\t\t\t\t");
  Output.insert(Output.size(), 3, (char)196);
  Output.insert(Output.size(), 1, (char)197);
  Output.insert(Output.size(), 3, (char)196);
  Output.insert(Output.size(), 1, (char)197);
  Output.insert(Output.size(), 3, (char)196);

  // Line 3
  Output.append("\n " + TicTacToeGrid[1][0] + " ");
  Output.insert(Output.size(), 1, (char)179);
  Output.append(" " + TicTacToeGrid[1][1] + " ");
  Output.insert(Output.size(), 1, (char)179);
  Output.append(" " + TicTacToeGrid[1][2] + " ");
  if (NumberOfPlayers == "N/A")
    Output.append("\t# of Players = " + NumberOfPlayers + "\t 4 ");
  else
    Output.append("\t  # of Players = " + NumberOfPlayers + "\t 4 ");
  Output.insert(Output.size(), 1, (char)179);
  Output.append(" 5 ");
  Output.insert(Output.size(), 1, (char)179);
  Output.append(" 6 \n");

  // Line 4
  Output.insert(Output.size(), 3, (char)196);
  Output.insert(Output.size(), 1, (char)197);
  Output.insert(Output.size(), 3, (char)196);
  Output.insert(Output.size(), 1, (char)197);
  Output.insert(Output.size(), 3, (char)196);
  Output.append("\t\t\t\t");
  Output.insert(Output.size(), 3, (char)196);
  Output.insert(Output.size(), 1, (char)197);
  Output.insert(Output.size(), 3, (char)196);
  Output.insert(Output.size(), 1, (char)197);
  Output.insert(Output.size(), 3, (char)196);

  // Line 5
  Output.append("\n " + TicTacToeGrid[2][0] + " ");
  Output.insert(Output.size(), 1, (char)179);
  Output.append(" " + TicTacToeGrid[2][1] + " ");
  Output.insert(Output.size(), 1, (char)179);
  Output.append(" " + TicTacToeGrid[2][2] + " \tAI Difficulty = " + AIDifficulty + "\t 7 ");
  Output.insert(Output.size(), 1, (char)179);
  Output.append(" 8 ");
  Output.insert(Output.size(), 1, (char)179);
  Output.append(" 9 \n\n");

  std::cout << Output;
}

void Get_Next_User_Command(std::vector<std::vector<std::string>> &TicTacToeGrid,
                           const unsigned int &NumberOfPlayers,
                           const std::string &AIDifficulty,
                           const std::string &CurrentPlayer,
                           std::vector<unsigned int> &ValidMovesRemaining)
{
  bool IsValueCorrect = false;
  std::string Input;
  unsigned int UserCommand, Row, Column;

  while (!IsValueCorrect)
  {
    Display_Game(TicTacToeGrid, std::to_string(NumberOfPlayers), AIDifficulty);
    if (CurrentPlayer == "PLAYER ONE")
      std::cout << "Player X, please enter your next command: ";
    else
      std::cout << "Player O, please enter your next command: ";
    std::getline(std::cin, Input);

    if (Input.size() != 1)
      continue;

    if (Input[0] < '1' || Input[0] > '9')
      continue;

    // Minus one to get UserCommand into range of 0-8
    UserCommand = std::stoi(Input, nullptr, 10) - 1;

    auto CommandPosition = std::find(ValidMovesRemaining.begin(), ValidMovesRemaining.end(), UserCommand);

    if (CommandPosition != ValidMovesRemaining.end())
    {
      IsValueCorrect = true;

      Column = UserCommand % 3;
      Row = UserCommand / 3;

      if (CurrentPlayer == "PLAYER ONE")
        TicTacToeGrid[Row][Column] = "X";
      else
        TicTacToeGrid[Row][Column] = "O";

      ValidMovesRemaining.erase(CommandPosition);
    }
  }
}

void Get_Next_AI_Command(std::vector<std::vector<std::string>> &TicTacToeGrid,
                         const unsigned int &NumberOfPlayers,
                         const std::string &AIDifficulty,
                         const std::string &CurrentPlayer,
                         std::vector<unsigned int> &ValidMovesRemaining)
{
  unsigned int AICommand, Row, Column;

  Display_Game(TicTacToeGrid, std::to_string(NumberOfPlayers), AIDifficulty);

  AICommand = ValidMovesRemaining[std::rand() % ValidMovesRemaining.size()];
  auto CommandPosition = std::find(ValidMovesRemaining.begin(), ValidMovesRemaining.end(), AICommand);
  ValidMovesRemaining.erase(CommandPosition);

  Column = AICommand % 3;
  Row = AICommand / 3;

  if (CurrentPlayer == "PLAYER ONE")
    TicTacToeGrid[Row][Column] = "X";
  else
    TicTacToeGrid[Row][Column] = "O";
}

bool Game_Over(const unsigned int &NumberOfTurns)
{
  if (NumberOfTurns == 9)
    return true;
  else
    return false;
}

bool Winning_Conditions_Met(const std::vector<std::vector<std::string>> &TicTacToeGrid)
{
  // Check Horizontals
  if (TicTacToeGrid[0][0]!= " " && TicTacToeGrid[0][0] == TicTacToeGrid[0][1] && TicTacToeGrid[0][1] == TicTacToeGrid[0][2])
    return true;

  else if (TicTacToeGrid[1][0]!= " " && TicTacToeGrid[1][0] == TicTacToeGrid[1][1] && TicTacToeGrid[1][1] == TicTacToeGrid[1][2])
    return true;

  else if (TicTacToeGrid[2][0]!= " " && TicTacToeGrid[2][0] == TicTacToeGrid[2][1] && TicTacToeGrid[2][1] == TicTacToeGrid[2][2])
    return true;

  // Check verticals
  else if (TicTacToeGrid[0][0]!= " " && TicTacToeGrid[0][0] == TicTacToeGrid[1][0] && TicTacToeGrid[1][0] == TicTacToeGrid[2][0])
    return true;

  else if (TicTacToeGrid[0][1]!= " " && TicTacToeGrid[0][1] == TicTacToeGrid[1][1] && TicTacToeGrid[1][1] == TicTacToeGrid[2][1])
    return true;

  else if (TicTacToeGrid[0][2]!= " " && TicTacToeGrid[0][2] == TicTacToeGrid[1][2] && TicTacToeGrid[1][2] == TicTacToeGrid[2][2])
    return true;

  // Check diagonals
  else if (TicTacToeGrid[0][0]!= " " && TicTacToeGrid[0][0] == TicTacToeGrid[1][1] && TicTacToeGrid[1][1] == TicTacToeGrid[2][2])
    return true;

  else if (TicTacToeGrid[2][0]!= " " && TicTacToeGrid[2][0] == TicTacToeGrid[1][1] && TicTacToeGrid[1][1] == TicTacToeGrid[0][2])
    return true;

  else
    return false;
}

void Display_Game_Over_Message(const std::vector<std::vector<std::string>> &TicTacToeGrid,
                               const unsigned int &NumberOfPlayers,
                               const std::string &AIDifficulty,
                               const std::string &CurrentPlayer,
                               const unsigned int &NumberOfTurns,
                               bool &GameIsRunning)
{
  Display_Game(TicTacToeGrid, std::to_string(NumberOfPlayers), AIDifficulty);

  if (Winning_Conditions_Met(TicTacToeGrid))
  {
    if (CurrentPlayer == "PLAYER ONE")
      std::cout << "\t\t     GAME OVER\n\n    Player X has won! The game lasted " << NumberOfTurns << " turns.";
    else
      std::cout << "\t\t     GAME OVER\n\n    Player O has won! The game lasted " << NumberOfTurns << " turns.";
  }
  else  // No winner so a draw
    std::cout << "\t\t     GAME OVER\n\n      It is a draw! The game lasted " << NumberOfTurns << " turns.";

  std::cout << "\n\nPress 'Q' to quit OR any other key to play again...";

  if (_getch() == 'q')
  {
    GameIsRunning = false;
    Clear_Terminal();
  }
}
