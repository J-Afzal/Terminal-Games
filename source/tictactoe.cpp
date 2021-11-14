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

void Play_Tic_Tac_Toe(const HANDLE &ConsoleHandle,
                      CONSOLE_CURSOR_INFO &CursorInfo)
{
  bool GameIsRunning = true;

  while (GameIsRunning)
  {
    unsigned int NumberOfTurns = 0, NumberOfPlayers = 0;
    std::string CurrentPlayer, UserPlayerChoice, AIDifficulty = "N/A";
    std::vector<unsigned int> ValidMovesRemaining;
    std::vector<std::vector<std::string>> TicTacToeGrid;

    Setup_Game(TicTacToeGrid, ValidMovesRemaining, NumberOfPlayers, UserPlayerChoice, AIDifficulty, CurrentPlayer);

    while (!Game_Over(NumberOfTurns) && !Winning_Conditions_Met(TicTacToeGrid))
    {
      Toggle_Player(CurrentPlayer);

      // Display_Game() called before either user or AI are asked for an input
      if (NumberOfPlayers == 2 || CurrentPlayer == UserPlayerChoice)
      {
        CursorInfo.bVisible = TRUE;
        SetConsoleCursorInfo(ConsoleHandle, &CursorInfo);
        Get_Next_User_Command(TicTacToeGrid, NumberOfPlayers, AIDifficulty, CurrentPlayer, ValidMovesRemaining, ConsoleHandle);
        CursorInfo.bVisible = FALSE;
        SetConsoleCursorInfo(ConsoleHandle, &CursorInfo);
      }

      else
        Get_Next_AI_Command(TicTacToeGrid, NumberOfPlayers, AIDifficulty, CurrentPlayer, ValidMovesRemaining);

      NumberOfTurns++;
    }

    Display_Game_Over_Message(TicTacToeGrid, NumberOfPlayers, AIDifficulty, CurrentPlayer, NumberOfTurns, GameIsRunning);
  }
}

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

  NumberOfPlayers = Get_Number_Of_Players(TicTacToeGrid);

  // If only one human user, then ask them which player they want to be (X or O)
  if (NumberOfPlayers == 1)
    UserPlayerChoice = Get_User_Player_Choice(TicTacToeGrid, NumberOfPlayers);

  // If AI involved get AI difficulty
  if (NumberOfPlayers < 2)
    AIDifficulty = Get_AI_Difficulty(TicTacToeGrid, NumberOfPlayers);

  std::srand((unsigned int)std::time(0));
  if (std::rand() % 2 == 0)
    CurrentPlayer = "PLAYER ONE"; // X
  else
    CurrentPlayer = "PLAYER TWO"; // O
}


unsigned int Get_Number_Of_Players(const std::vector<std::vector<std::string>> &TicTacToeGrid)
{
  unsigned int CurrentSelection = 0;
  unsigned char KeyPress = 0;

  while (KeyPress != '\r')
  {
    switch (KeyPress)
    {
    case 72: // up arrow key
      if (CurrentSelection == 0)
        CurrentSelection = 2;
      else
        CurrentSelection--;
    break;

    case 80: // down arrow key
      if (CurrentSelection == 2)
        CurrentSelection = 0;
      else
        CurrentSelection++;
    break;

    default:
    break;
    }

    Display_Game(TicTacToeGrid, "N/A", "N/A");

    std::string Output;
    Output.insert(Output.size(), 1, (char)186);
    Output.append(" Please select the number of human players:\t      ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");

    switch (CurrentSelection)
    {
    case 0:
      Output.insert(Output.size(), 1, (char)186);
      Output.append(BLUE);
      Output.append(" > 0\t\t\t\t\t\t      ");
      Output.append(WHITE);
      Output.insert(Output.size(), 1, (char)186);

      Output.append("\n");
      Output.insert(Output.size(), 1, (char)186);
      Output.append("   1\t\t\t\t\t\t      ");
      Output.insert(Output.size(), 1, (char)186);

      Output.append("\n");
      Output.insert(Output.size(), 1, (char)186);
      Output.append("   2\t\t\t\t\t\t      ");
      Output.insert(Output.size(), 1, (char)186);
    break;

    case 1:
      Output.insert(Output.size(), 1, (char)186);
      Output.append("   0\t\t\t\t\t\t      ");
      Output.insert(Output.size(), 1, (char)186);

      Output.append("\n");
      Output.insert(Output.size(), 1, (char)186);
      Output.append(BLUE);
      Output.append(" > 1\t\t\t\t\t\t      ");
      Output.append(WHITE);
      Output.insert(Output.size(), 1, (char)186);

      Output.append("\n");
      Output.insert(Output.size(), 1, (char)186);
      Output.append("   2\t\t\t\t\t\t      ");
      Output.insert(Output.size(), 1, (char)186);
    break;

    case 2:
      Output.insert(Output.size(), 1, (char)186);
      Output.append("   0\t\t\t\t\t\t      ");
      Output.insert(Output.size(), 1, (char)186);

      Output.append("\n");
      Output.insert(Output.size(), 1, (char)186);
      Output.append("   1\t\t\t\t\t\t      ");
      Output.insert(Output.size(), 1, (char)186);

      Output.append("\n");
      Output.insert(Output.size(), 1, (char)186);
      Output.append(BLUE);
      Output.append(" > 2\t\t\t\t\t\t      ");
      Output.append(WHITE);
      Output.insert(Output.size(), 1, (char)186);
    break;

    default:
    break;
    }

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append("\t\t\t\t\t\t      ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)200);
    Output.insert(Output.size(), 53, (char)205);
    Output.insert(Output.size(), 1, (char)188);

    // Bottom bar
    Output.append("\n");
    Output.insert(Output.size(), 1, (char)201);
    Output.insert(Output.size(), 53, (char)205);
    Output.insert(Output.size(), 1, (char)187);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append(RED);
    Output.append("\t\t      Tic Tac Toe\t\t      ");
    Output.append(WHITE);
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)200);
    Output.insert(Output.size(), 53, (char)205);
    Output.insert(Output.size(), 1, (char)188);

    std::cout << Output;

    KeyPress = _getch();
  }

  return CurrentSelection;
}

std::string Get_User_Player_Choice(const std::vector<std::vector<std::string>> &TicTacToeGrid,
                                   const unsigned int &NumberOfPlayers)
{
  unsigned int CurrentSelection = 0;
  unsigned char KeyPress = 0;

  while (KeyPress != '\r')
  {
    switch (KeyPress)
    {
    case 72: // up arrow key
      if (CurrentSelection == 0)
        CurrentSelection = 1;
      else
        CurrentSelection--;
    break;

    case 80: // down arrow key
      if (CurrentSelection == 1)
        CurrentSelection = 0;
      else
        CurrentSelection++;
    break;

    default:
    break;
    }

    Display_Game(TicTacToeGrid, std::to_string(NumberOfPlayers), "N/A");

    std::string Output;
    Output.insert(Output.size(), 1, (char)186);
    Output.append(" Please select what player you would like to be:     ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");

    switch (CurrentSelection)
    {
    case 0:
      Output.insert(Output.size(), 1, (char)186);
      Output.append(BLUE);
      Output.append(" > PLAYER X\t\t\t\t\t      ");
      Output.append(WHITE);
      Output.insert(Output.size(), 1, (char)186);

      Output.append("\n");
      Output.insert(Output.size(), 1, (char)186);
      Output.append("   PLAYER O\t\t\t\t\t      ");
      Output.insert(Output.size(), 1, (char)186);
    break;

    case 1:
      Output.insert(Output.size(), 1, (char)186);
      Output.append("   PLAYER X\t\t\t\t\t      ");
      Output.insert(Output.size(), 1, (char)186);

      Output.append("\n");
      Output.insert(Output.size(), 1, (char)186);
      Output.append(BLUE);
      Output.append(" > PLAYER O\t\t\t\t\t      ");
      Output.append(WHITE);
      Output.insert(Output.size(), 1, (char)186);
    break;

    default:
    break;
    }
    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append("\t\t\t\t\t\t      ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append("\t\t\t\t\t\t      ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)200);
    Output.insert(Output.size(), 53, (char)205);
    Output.insert(Output.size(), 1, (char)188);

    // Bottom bar
    Output.append("\n");
    Output.insert(Output.size(), 1, (char)201);
    Output.insert(Output.size(), 53, (char)205);
    Output.insert(Output.size(), 1, (char)187);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append(RED);
    Output.append("\t\t      Tic Tac Toe\t\t      ");
    Output.append(WHITE);
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)200);
    Output.insert(Output.size(), 53, (char)205);
    Output.insert(Output.size(), 1, (char)188);

    std::cout << Output;

    KeyPress = _getch();
  }

  return CurrentSelection == 0 ? "PLAYER ONE" : "PLAYER TWO";
}


std::string Get_AI_Difficulty(const std::vector<std::vector<std::string>> &TicTacToeGrid,
                              const unsigned int &NumberOfPlayers)
{
  unsigned int CurrentSelection = 0;
  unsigned char KeyPress = 0;

  while (!(KeyPress == '\r' && CurrentSelection == 0))
  {
    switch (KeyPress)
    {
    case 72: // up arrow key
      if (CurrentSelection == 0)
        CurrentSelection = 1;
      else
        CurrentSelection--;
    break;

    case 80: // down arrow key
      if (CurrentSelection == 1)
        CurrentSelection = 0;
      else
        CurrentSelection++;
    break;

    default:
    break;
    }

    Display_Game(TicTacToeGrid, std::to_string(NumberOfPlayers), "N/A");

    std::string Output;
    Output.insert(Output.size(), 1, (char)186);
    Output.append(" Please select the AI difficulty:\t\t      ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");

    switch (CurrentSelection)
    {
    case 0:
      Output.insert(Output.size(), 1, (char)186);
      Output.append(BLUE);
      Output.append(" > EASY\t\t\t\t\t      ");
      Output.append(WHITE);
      Output.insert(Output.size(), 1, (char)186);

      Output.append("\n");
      Output.insert(Output.size(), 1, (char)186);
      Output.append("   HARD (Coming Soon!)\t\t\t\t      ");
      Output.insert(Output.size(), 1, (char)186);
    break;

    case 1:
      Output.insert(Output.size(), 1, (char)186);
      Output.append("   EASY\t\t\t\t\t      ");
      Output.insert(Output.size(), 1, (char)186);

      Output.append("\n");
      Output.insert(Output.size(), 1, (char)186);
      Output.append(BLUE);
      Output.append(" > HARD (Coming Soon!)\t\t\t\t      ");
      Output.append(WHITE);
      Output.insert(Output.size(), 1, (char)186);
    break;

    default:
    break;
    }

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append("\t\t\t\t\t\t      ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append("\t\t\t\t\t\t      ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)200);
    Output.insert(Output.size(), 53, (char)205);
    Output.insert(Output.size(), 1, (char)188);

    // Bottom bar
    Output.append("\n");
    Output.insert(Output.size(), 1, (char)201);
    Output.insert(Output.size(), 53, (char)205);
    Output.insert(Output.size(), 1, (char)187);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append(RED);
    Output.append("\t\t      Tic Tac Toe\t\t      ");
    Output.append(WHITE);
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)200);
    Output.insert(Output.size(), 53, (char)205);
    Output.insert(Output.size(), 1, (char)188);

    std::cout << Output;

    KeyPress = _getch();
  }

  return CurrentSelection == 0 ? "EASY" : "HARD";
}

void Display_Game(const std::vector<std::vector<std::string>> &TicTacToeGrid,
                  const std::string &NumberOfPlayers,
                  const std::string &AIDifficulty)
{
  Clear_Terminal();

  std::string Output;

  // Top bar
  Output.append(WHITE);
  Output.insert(Output.size(), 1, (char)201);
  Output.insert(Output.size(), 53, (char)205);
  Output.insert(Output.size(), 1, (char)187);

  Output.append("\n");
  Output.insert(Output.size(), 1, (char)186);
  Output.append(RED);
  Output.append("\t\t    Terminal-Games\t\t      ");
  Output.append(WHITE);
  Output.insert(Output.size(), 1, (char)186);

  Output.append("\n");
  Output.insert(Output.size(), 1, (char)200);
  Output.insert(Output.size(), 53, (char)205);
  Output.insert(Output.size(), 1, (char)188);

  // Centre information
  Output.append("\n");
  Output.insert(Output.size(), 1, (char)201);
  Output.insert(Output.size(), 53, (char)205);
  Output.insert(Output.size(), 1, (char)187);

  // Line 1
  Output.append("\n");
  Output.insert(Output.size(), 1, (char)186);
  Output.append("  " + TicTacToeGrid[0][0] + " ");
  Output.insert(Output.size(), 1, (char)179);
  Output.append(" " + TicTacToeGrid[0][1] + " ");
  Output.insert(Output.size(), 1, (char)179);
  Output.append(" " + TicTacToeGrid[0][2] + "\t\t\t\t\t      ");
  Output.insert(Output.size(), 1, (char)186);

  // Line 2
  Output.append("\n");
  Output.insert(Output.size(), 1, (char)186);
  Output.append(" ");
  Output.insert(Output.size(), 3, (char)196);
  Output.insert(Output.size(), 1, (char)197);
  Output.insert(Output.size(), 3, (char)196);
  Output.insert(Output.size(), 1, (char)197);
  Output.insert(Output.size(), 3, (char)196);
  if (NumberOfPlayers == "N/A")
    Output.append("     # of Players = " + NumberOfPlayers + "\t\t      ");
  else
    Output.append("      # of Players = " + NumberOfPlayers + "\t\t      ");
  Output.insert(Output.size(), 1, (char)186);

  // Line 3
  Output.append("\n");
  Output.insert(Output.size(), 1, (char)186);
  Output.append("  " + TicTacToeGrid[1][0] + " ");
  Output.insert(Output.size(), 1, (char)179);
  Output.append(" " + TicTacToeGrid[1][1] + " ");
  Output.insert(Output.size(), 1, (char)179);
  Output.append(" " + TicTacToeGrid[1][2] + "\t\t\t\t\t      ");
  Output.insert(Output.size(), 1, (char)186);

  // Line 4
  Output.append("\n");
  Output.insert(Output.size(), 1, (char)186);
  Output.append(" ");
  Output.insert(Output.size(), 3, (char)196);
  Output.insert(Output.size(), 1, (char)197);
  Output.insert(Output.size(), 3, (char)196);
  Output.insert(Output.size(), 1, (char)197);
  Output.insert(Output.size(), 3, (char)196);
  if (AIDifficulty == "N/A")
    Output.append("     AI Difficulty = " + AIDifficulty + "\t\t      ");
  else
    Output.append("    AI Difficulty = " + AIDifficulty + "\t\t      ");
  Output.insert(Output.size(), 1, (char)186);

  // Line 5
  Output.append("\n");
  Output.insert(Output.size(), 1, (char)186);
  Output.append("  " + TicTacToeGrid[2][0] + " ");
  Output.insert(Output.size(), 1, (char)179);
  Output.append(" " + TicTacToeGrid[2][1] + " ");
  Output.insert(Output.size(), 1, (char)179);
  Output.append(" " + TicTacToeGrid[2][2] + "\t\t\t\t\t      ");
  Output.insert(Output.size(), 1, (char)186);

  Output.append("\n");
  Output.insert(Output.size(), 1, (char)186);
  Output.append("\t\t\t\t\t\t      ");
  Output.insert(Output.size(), 1, (char)186);

  Output.append("\n");

  std::cout << Output;
}

void Get_Next_User_Command(std::vector<std::vector<std::string>> &TicTacToeGrid,
                           const unsigned int &NumberOfPlayers,
                           const std::string &AIDifficulty,
                           const std::string &CurrentPlayer,
                           std::vector<unsigned int> &ValidMovesRemaining,
                           const HANDLE &ConsoleHandle)
{
  bool InputValid = false;
  unsigned int UserCommand, Row = ValidMovesRemaining[0] / 3, Column = ValidMovesRemaining[0] % 3;
  unsigned char KeyPress = 0;

  std::string Output;
  Output.insert(Output.size(), 1, (char)186);
  Output.append("\t\t\t\t\t\t      ");
  Output.insert(Output.size(), 1, (char)186);

  Output.append("\n");
  Output.insert(Output.size(), 1, (char)186);
  if (CurrentPlayer == "PLAYER ONE")
    Output.append("Player X, please enter your next command!");
  else
    Output.append("Player O, please enter your next command!");
  Output.append("\t      ");
  Output.insert(Output.size(), 1, (char)186);

  Output.append("\n");
  Output.insert(Output.size(), 1, (char)186);
  Output.append("\t\t\t\t\t\t      ");
  Output.insert(Output.size(), 1, (char)186);

  Output.append("\n");
  Output.insert(Output.size(), 1, (char)186);
  Output.append("\t\t\t\t\t\t      ");
  Output.insert(Output.size(), 1, (char)186);

  Output.append("\n");
  Output.insert(Output.size(), 1, (char)186);
  Output.append("\t\t\t\t\t\t      ");
  Output.insert(Output.size(), 1, (char)186);

  Output.append("\n");
  Output.insert(Output.size(), 1, (char)186);
  Output.append("\t\t\t\t\t\t      ");
  Output.insert(Output.size(), 1, (char)186);

  Output.append("\n");
  Output.insert(Output.size(), 1, (char)200);
  Output.insert(Output.size(), 53, (char)205);
  Output.insert(Output.size(), 1, (char)188);

  // Bottom bar
  Output.append("\n");
  Output.insert(Output.size(), 1, (char)201);
  Output.insert(Output.size(), 53, (char)205);
  Output.insert(Output.size(), 1, (char)187);

  Output.append("\n");
  Output.insert(Output.size(), 1, (char)186);
  Output.append(RED);
  Output.append("\t\t      Tic Tac Toe\t\t      ");
  Output.append(WHITE);
  Output.insert(Output.size(), 1, (char)186);

  Output.append("\n");
  Output.insert(Output.size(), 1, (char)200);
  Output.insert(Output.size(), 53, (char)205);
  Output.insert(Output.size(), 1, (char)188);

  while (!InputValid)
  {
    while (KeyPress != '\r')
    {
      switch (KeyPress)
      {
      case 72: // up arrow key
        if (Row == 0)
          Row = 2;
        else
          Row--;
      break;

      case 80: // down arrow key
        if (Row == 2)
          Row = 0;
        else
          Row++;
      break;

      case 75: // left arrow key
        if (Column == 0)
          Column = 2;
        else
          Column--;
      break;

      case 77: // right arrow key
        if (Column == 2)
          Column = 0;
        else
          Column++;
      break;

      default:
      break;
      }

      Display_Game(TicTacToeGrid, std::to_string(NumberOfPlayers), AIDifficulty);
      std::cout << Output;

      COORD CursorPosition;
      CursorPosition.X = 3+Column*4;
      CursorPosition.Y = 4+Row*2;

      SetConsoleCursorPosition(ConsoleHandle, CursorPosition);

      KeyPress = _getch();
    }

    UserCommand = Row*3+Column;
    auto CommandPosition = std::find(ValidMovesRemaining.begin(), ValidMovesRemaining.end(), UserCommand);

    if (CommandPosition != ValidMovesRemaining.end())
    {
      InputValid = true;

      if (CurrentPlayer == "PLAYER ONE")
        TicTacToeGrid[Row][Column] = "X";
      else
        TicTacToeGrid[Row][Column] = "O";

      ValidMovesRemaining.erase(CommandPosition);
    }
    else
      KeyPress = 0;
  }
}

void Get_Next_AI_Command(std::vector<std::vector<std::string>> &TicTacToeGrid,
                         const unsigned int &NumberOfPlayers,
                         const std::string &AIDifficulty,
                         const std::string &CurrentPlayer,
                         std::vector<unsigned int> &ValidMovesRemaining)
{
  unsigned int AICommand, Row, Column;

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

  std::string Output;
  Output.insert(Output.size(), 1, (char)186);
  Output.append("\t\t       GAME OVER\t\t      ");
  Output.insert(Output.size(), 1, (char)186);

  Output.append("\n");
  Output.insert(Output.size(), 1, (char)186);
  Output.append("\t\t\t\t\t\t      ");
  Output.insert(Output.size(), 1, (char)186);

  Output.append("\n");
  Output.insert(Output.size(), 1, (char)186);
  if (Winning_Conditions_Met(TicTacToeGrid))
  {
    if (CurrentPlayer == "PLAYER ONE")
      Output.append("     Player X has won! The game lasted " + std::to_string(NumberOfTurns) + " turns.      ");
    else
      Output.append("     Player O has won! The game lasted " + std::to_string(NumberOfTurns) + " turns.      ");
  }
  else
     Output.append("       It is a draw! The game lasted " + std::to_string(NumberOfTurns) + " turns.\t      ");
  Output.insert(Output.size(), 1, (char)186);

  Output.append("\n");
  Output.insert(Output.size(), 1, (char)186);
  Output.append("\t\t\t\t\t\t      ");
  Output.insert(Output.size(), 1, (char)186);

  Output.append("\n");
  Output.insert(Output.size(), 1, (char)186);
  Output.append(" Press 'Q' to quit OR any other key to play again... ");
  Output.insert(Output.size(), 1, (char)186);

  Output.append("\n");
  Output.insert(Output.size(), 1, (char)200);
  Output.insert(Output.size(), 53, (char)205);
  Output.insert(Output.size(), 1, (char)188);

  // Bottom bar
  Output.append("\n");
  Output.insert(Output.size(), 1, (char)201);
  Output.insert(Output.size(), 53, (char)205);
  Output.insert(Output.size(), 1, (char)187);

  Output.append("\n");
  Output.insert(Output.size(), 1, (char)186);
  Output.append(RED);
  Output.append("\t\t      Tic Tac Toe\t\t      ");
  Output.append(WHITE);
  Output.insert(Output.size(), 1, (char)186);

  Output.append("\n");
  Output.insert(Output.size(), 1, (char)200);
  Output.insert(Output.size(), 53, (char)205);
  Output.insert(Output.size(), 1, (char)188);

  std::cout << Output;

  char temp = _getch();

  if (temp == 'q')
  {
    GameIsRunning = false;
    Clear_Terminal();
  }
}
