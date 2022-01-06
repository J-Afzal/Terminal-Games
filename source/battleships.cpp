/**
 * @file battleships.cpp
 * @author Junaid Afzal
 * @brief Implementation of battlships.hpp
 * @version 1.0
 * @date 07-11-2021
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "battleships.hpp"
#include "functions.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <conio.h>

void Play_Battleships(const HANDLE &ConsoleHandle,
                      CONSOLE_CURSOR_INFO &CursorInfo)
{
  bool GameIsRunning = true;

  while (GameIsRunning)
  {
    std::vector<std::vector<std::string>> PlayerOneBoard, PlayerTwoBoard;
    std::vector<unsigned int> PlayerOneValidMovesRemaining, PlayerTwoValidMovesRemaining;
    std::map<std::string, unsigned int> PlayerOneShipsRemaining, PlayerTwoShipsRemaining;
    unsigned int NumberOfPlayers, NumberOfTurns = 0;
    std::string CurrentPlayer, AIDifficulty;

    Setup_Game(PlayerOneBoard, PlayerTwoBoard, PlayerOneValidMovesRemaining, PlayerTwoValidMovesRemaining, PlayerOneShipsRemaining, PlayerTwoShipsRemaining, NumberOfPlayers, AIDifficulty, CurrentPlayer, ConsoleHandle);

    while (!Winning_Conditions_Met(PlayerOneBoard, PlayerTwoBoard))
    {
      Toggle_Player(CurrentPlayer);

      unsigned int Command;

      // Display_Game() called before either user or AI are asked for an input
      if (NumberOfPlayers == 1 && CurrentPlayer == "PLAYER ONE")
      {
        CursorInfo.bVisible = TRUE;
        SetConsoleCursorInfo(ConsoleHandle, &CursorInfo);
        Command = Get_Next_User_Command(PlayerOneBoard, PlayerTwoBoard, PlayerOneShipsRemaining, PlayerTwoShipsRemaining, PlayerOneValidMovesRemaining, NumberOfPlayers, AIDifficulty, ConsoleHandle);
        CursorInfo.bVisible = FALSE;
        SetConsoleCursorInfo(ConsoleHandle, &CursorInfo);
      }
      else
        Command = Get_Next_AI_Command(PlayerOneBoard, PlayerTwoBoard, PlayerOneShipsRemaining, PlayerTwoShipsRemaining, PlayerOneValidMovesRemaining, PlayerTwoValidMovesRemaining, NumberOfPlayers, AIDifficulty, CurrentPlayer);

      Execute_Next_Turn(PlayerOneBoard, PlayerTwoBoard, PlayerOneShipsRemaining, PlayerTwoShipsRemaining, CurrentPlayer, Command);

      NumberOfTurns++;
    }

    Display_Game_Over_Message(PlayerOneBoard, PlayerTwoBoard, PlayerOneShipsRemaining, PlayerTwoShipsRemaining, NumberOfPlayers, AIDifficulty, CurrentPlayer, NumberOfTurns, GameIsRunning);
  }
}

void Setup_Game(std::vector<std::vector<std::string>> &PlayerOneBoard,
                std::vector<std::vector<std::string>> &PlayerTwoBoard,
                std::vector<unsigned int> &PlayerOneValidMovesRemaining,
                std::vector<unsigned int> &PlayerTwoValidMovesRemaining,
                std::map<std::string, unsigned int> &PlayerOneShipsRemaining,
                std::map<std::string, unsigned int> &PlayerTwoShipsRemaining,
                unsigned int &NumberOfPlayers,
                std::string &AIDifficulty,
                std::string &CurrentPlayer,
                const HANDLE &ConsoleHandle)
{
  for (unsigned int i = 0, GridNumber = 0; i < 10; i++)
  {
    std::vector<std::string> Row;

    PlayerOneBoard.push_back(Row);
    PlayerTwoBoard.push_back(Row);

    for (unsigned int j = 0; j < 10; j++, GridNumber++)
    {
      PlayerOneBoard[i].push_back(" ");
      PlayerTwoBoard[i].push_back(" ");
      PlayerOneValidMovesRemaining.push_back(GridNumber);
      PlayerTwoValidMovesRemaining.push_back(GridNumber);
    }
  }

  PlayerOneShipsRemaining["C"] = 5;
  PlayerOneShipsRemaining["B"] = 4;
  PlayerOneShipsRemaining["D"] = 3;
  PlayerOneShipsRemaining["S"] = 3;
  PlayerOneShipsRemaining["P"] = 2;

  PlayerTwoShipsRemaining["C"] = 5;
  PlayerTwoShipsRemaining["B"] = 4;
  PlayerTwoShipsRemaining["D"] = 3;
  PlayerTwoShipsRemaining["S"] = 3;
  PlayerTwoShipsRemaining["P"] = 2;

  std::srand((unsigned int)std::time(0));

  NumberOfPlayers = Get_Number_Of_Players(PlayerOneBoard, PlayerTwoBoard, PlayerOneShipsRemaining, PlayerTwoShipsRemaining);

  AIDifficulty = Get_AI_Difficulty(PlayerOneBoard, PlayerTwoBoard, PlayerOneShipsRemaining, PlayerTwoShipsRemaining, NumberOfPlayers);

  if (NumberOfPlayers == 1)
    Get_User_Ship_Positions(PlayerOneBoard, PlayerTwoBoard, PlayerOneShipsRemaining, PlayerTwoShipsRemaining, NumberOfPlayers, AIDifficulty, ConsoleHandle);
  else
    Get_AI_Ship_Positions(PlayerOneBoard);

  // Player two will always be AI controlled
  Get_AI_Ship_Positions(PlayerTwoBoard);

  if ((std::rand() % 2) == 0)
    CurrentPlayer = "PLAYER ONE";
  else
    CurrentPlayer = "PLAYER TWO";
}

unsigned int Get_Number_Of_Players(const std::vector<std::vector<std::string>> &PlayerOneBoard,
                                   const std::vector<std::vector<std::string>> &PlayerTwoBoard,
                                   const std::map<std::string, unsigned int> &PlayerOneShipsRemaining,
                                   const std::map<std::string, unsigned int> &PlayerTwoShipsRemaining)
{
  unsigned int CurrentSelection = 0;
  unsigned char KeyPress = 0;

  std::string CommonString = Battleships_Game_Display(PlayerOneBoard, PlayerTwoBoard, PlayerOneShipsRemaining, PlayerTwoShipsRemaining, "N/A", "N/A", false);
  CommonString.append(Battleships_New_Line(" Please select the number of human players:                                                                                                        "));

  std::string CaseZero = CommonString;
  CaseZero.append(Battleships_New_Line(BLUE + " > 0                                                                                                                                               " + WHITE));
  CaseZero.append(Battleships_New_Line("   1                                                                                                                                               "));
  CaseZero.append(Battleships_Empty_Line());
  CaseZero.append(Battleships_Empty_Line());
  CaseZero.append(Battleships_Bottom_Line());
  CaseZero.append(Battleships_Bottom_Bar());

  std::string CaseOne = CommonString;
  CaseOne.append(Battleships_New_Line("   0                                                                                                                                               "));
  CaseOne.append(Battleships_New_Line(BLUE + " > 1                                                                                                                                               " + WHITE));
  CaseOne.append(Battleships_Empty_Line());
  CaseOne.append(Battleships_Empty_Line());
  CaseOne.append(Battleships_Bottom_Line());
  CaseOne.append(Battleships_Bottom_Bar());

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

    Clear_Terminal();

    switch (CurrentSelection)
    {
    case 0:
      std::cout << CaseZero;
      break;

    case 1:
      std::cout << CaseOne;
      break;
    }

    KeyPress = _getch();
  }

  return CurrentSelection;
}

std::string Get_AI_Difficulty(const std::vector<std::vector<std::string>> &PlayerOneBoard,
                              const std::vector<std::vector<std::string>> &PlayerTwoBoard,
                              const std::map<std::string, unsigned int> &PlayerOneShipsRemaining,
                              const std::map<std::string, unsigned int> &PlayerTwoShipsRemaining,
                              const unsigned int &NumberOfPlayers)
{
  unsigned int CurrentSelection = 0;
  unsigned char KeyPress = 0;

  std::string CommonString = Battleships_Game_Display(PlayerOneBoard, PlayerTwoBoard, PlayerOneShipsRemaining, PlayerTwoShipsRemaining, std::to_string(NumberOfPlayers), "N/A", false);
  CommonString.append(Battleships_New_Line(" Please select the AI difficulty:                                                                                                                  "));

  std::string CaseZero = CommonString;
  CaseZero.append(Battleships_New_Line(BLUE + " > EASY                                                                                                                                            " + WHITE));
  CaseZero.append(Battleships_New_Line("   HARD (Coming Soon!)                                                                                                                             "));
  CaseZero.append(Battleships_Empty_Line());
  CaseZero.append(Battleships_Empty_Line());
  CaseZero.append(Battleships_Bottom_Line());
  CaseZero.append(Battleships_Bottom_Bar());

  std::string CaseOne = CommonString;
  CaseOne.append(Battleships_New_Line("   EASY                                                                                                                                            "));
  CaseOne.append(Battleships_New_Line(BLUE + " > HARD (Coming Soon!)                                                                                                                             " + WHITE));
  CaseOne.append(Battleships_Empty_Line());
  CaseOne.append(Battleships_Empty_Line());
  CaseOne.append(Battleships_Bottom_Line());
  CaseOne.append(Battleships_Bottom_Bar());

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

    Clear_Terminal();

    switch (CurrentSelection)
    {
    case 0:
      std::cout << CaseZero;
      break;

    case 1:
      std::cout << CaseOne;
      break;
    }

    KeyPress = _getch();
  }

  return CurrentSelection == 0 ? "EASY" : "HARD";
}

void Get_User_Ship_Positions(std::vector<std::vector<std::string>> &PlayerOneBoard,
                             const std::vector<std::vector<std::string>> &PlayerTwoBoard,
                             const std::map<std::string, unsigned int> &PlayerOneShipsRemaining,
                             const std::map<std::string, unsigned int> &PlayerTwoShipsRemaining,
                             const unsigned int &NumberOfPlayers,
                             const std::string &AIDifficulty,
                             const HANDLE &ConsoleHandle)
{
  std::vector<std::string> ShipCommands = {
      " Please enter the 5 grid locations for the Carrier:                                                                                                ",
      " Please enter the 4 grid locations for the Battleship:                                                                                             ",
      " Please enter the 3 grid locations for the Destroyer:                                                                                              ",
      " Please enter the 3 grid locations for the Submarine:                                                                                              ",
      " Please enter the 2 grid locations for the Patrol Boat:                                                                                            "};
  std::vector<unsigned int> ShipSizes = {5, 4, 3, 3, 2};
  std::vector<std::string> ShipLetters = {"C", "B", "D", "S", "P"};
  std::vector<short> ShipCursorPosition = {53, 56, 55, 55, 57};
  std::vector<unsigned int> ShipPositionRows, ShipPositionColumns;

  for (unsigned int i = 0; i < 5; i++)
  {
    std::string Output = Battleships_Game_Display(PlayerOneBoard, PlayerTwoBoard, PlayerOneShipsRemaining, PlayerTwoShipsRemaining, std::to_string(NumberOfPlayers), AIDifficulty, false);
    Output.append(Battleships_New_Line(ShipCommands[i]));
    Output.append(Battleships_Empty_Line());
    Output.append(Battleships_Empty_Line());
    Output.append(Battleships_Empty_Line());
    Output.append(Battleships_Empty_Line());
    Output.append(Battleships_Bottom_Line());
    Output.append(Battleships_Bottom_Bar());

    bool InputInvalid = true;
    std::string Input;

    while (InputInvalid)
    {
      Clear_Terminal();

      std::cout << Output;

      SetConsoleCursorPosition(ConsoleHandle, {ShipCursorPosition[i], 29});

      std::getline(std::cin, Input);

      if (!Error_Checking_On_User_Ship_Positions(PlayerOneBoard, Input, ShipPositionRows, ShipPositionColumns, ShipSizes[i]))
        continue;

      InputInvalid = false;

      Place_Ship(PlayerOneBoard, ShipPositionRows, ShipPositionColumns, ShipLetters[i]);
    }
  }
}

bool Error_Checking_On_User_Ship_Positions(std::vector<std::vector<std::string>> &PlayerOneBoard,
                                           std::string &Input,
                                           std::vector<unsigned int> &ShipPositionRows,
                                           std::vector<unsigned int> &ShipPositionColumns,
                                           const unsigned int &ShipSize)
{
  Capitalise_Word(Input);

  // Add a space to help with next step
  if (Input.back() != ' ')
    Input.push_back(' ');

  // Input separated in to individual co-ordinates
  std::vector<std::string> IndividualCoordinates;
  std::string Temp;
  for (unsigned int i = 0; i < Input.size(); i++)
  {
    if (Input[i] == ' ')
    {
      IndividualCoordinates.push_back(Temp);
      Temp.clear();
    }
    else
      Temp.push_back(Input[i]);
  }

  if (IndividualCoordinates.size() != ShipSize)
    return false;

  // Check that each co-ordinate is size of two that the first character
  // is a letter and the second is a number
  for (unsigned int i = 0; i < IndividualCoordinates.size(); i++)
  {
    if (IndividualCoordinates[i].size() != 2)
      return false;
    if (IndividualCoordinates[i][0] < 'A' || IndividualCoordinates[i][0] > 'J')
      return false;
    if (IndividualCoordinates[i][1] < '0' || IndividualCoordinates[i][1] > '9')
      return false;
  }

  // Check whether letters or numbers of all co-ordinates are identical
  bool LettersIdentical = true, NumbersIdentical = true;

  for (unsigned int i = 1; i < IndividualCoordinates.size(); i++)
  {
    if (IndividualCoordinates[i][0] != IndividualCoordinates[0][0])
      LettersIdentical = false;
    if (IndividualCoordinates[i][1] != IndividualCoordinates[0][1])
      NumbersIdentical = false;
  }

  if (LettersIdentical && !NumbersIdentical) // Vertical
  {
    // Check that number is increment by one after each co-ordinate
    for (unsigned int i = 1; i < IndividualCoordinates.size(); i++)
      if (IndividualCoordinates[i][1] != (IndividualCoordinates[i - 1][1] + 1))
        return false;
  }
  else if (NumbersIdentical && !LettersIdentical) // Horizontal
  {
    // Check that letter is increment by one after each co-ordinate
    for (unsigned int i = 1; i < IndividualCoordinates.size(); i++)
      if (IndividualCoordinates[i][0] != (IndividualCoordinates[i - 1][0] + 1))
        return false;
  }
  else // No diagonals allowed
    return false;

  ShipPositionRows.clear();
  ShipPositionColumns.clear();

  // Convert A0, B5, etc to row and columns
  for (unsigned int i = 0; i < IndividualCoordinates.size(); i++)
  {
    Temp = IndividualCoordinates[i][1];
    ShipPositionRows.push_back(std::stoi(Temp, nullptr, 10));
    Temp = (IndividualCoordinates[i][0] - 17);
    ShipPositionColumns.push_back(std::stoi(Temp, nullptr, 10));
  }

  // Check if any of the ship positions are already occupied by another ship
  for (unsigned int i = 0; i < IndividualCoordinates.size(); i++)
  {
    if (PlayerOneBoard[ShipPositionRows[i]][ShipPositionColumns[i]] == "C" ||
        PlayerOneBoard[ShipPositionRows[i]][ShipPositionColumns[i]] == "B" ||
        PlayerOneBoard[ShipPositionRows[i]][ShipPositionColumns[i]] == "D" ||
        PlayerOneBoard[ShipPositionRows[i]][ShipPositionColumns[i]] == "S" ||
        PlayerOneBoard[ShipPositionRows[i]][ShipPositionColumns[i]] == "P")
      return false;
  }

  return true;
}

void Get_AI_Ship_Positions(std::vector<std::vector<std::string>> &AIBoard)
{
  std::vector<unsigned int> ShipSizes = {5, 4, 3, 3, 2};
  std::vector<std::string> ShipLetters = {"C", "B", "D", "S", "P"};
  std::vector<unsigned int> ShipPositionRows, ShipPositionColumns;

  for (unsigned int i = 0; i < 5; i++)
  {
    bool InputInvalid = true;

    while (InputInvalid)
    {
      Generate_AI_Ship_Positions(ShipPositionRows, ShipPositionColumns, ShipSizes[i]);

      if (!Error_Checking_On_AI_Ship_Positions(AIBoard, ShipPositionRows, ShipPositionColumns))
        continue;

      InputInvalid = false;

      Place_Ship(AIBoard, ShipPositionRows, ShipPositionColumns, ShipLetters[i]);
    }
  }
}

void Generate_AI_Ship_Positions(std::vector<unsigned int> &ShipPositionRows,
                                std::vector<unsigned int> &ShipPositionColumns,
                                const unsigned int &ShipSize)

{
  unsigned int Column, Row;
  ShipPositionRows.clear();
  ShipPositionColumns.clear();

  if ((std::rand() % 2) == 0) // Horizontal
  {
    // A max column number exists, as ship is horizontal, which is linked with the size of the ship
    // with the assumption being this value will be the first and smallest of the positions
    Column = std::rand() % (11 - ShipSize);

    Row = std::rand() % 10; // Any row number allowed as ship is horizontal

    // Horizontal positions have a difference in columns of 1
    for (unsigned int i = 0; i < ShipSize; i++)
    {
      ShipPositionRows.push_back(Row);
      ShipPositionColumns.push_back(Column + i);
    }
  }

  else // Vertical
  {
    Column = std::rand() % 10; // Any column number allowed as ship is vertical

    // A max row number exists, as ship is vertical, which is linked with the size of the ship
    // with the assumption being this value will be the first and smallest of the positions
    Row = std::rand() % (11 - ShipSize);

    // Vertical positions have a difference in rows of 1
    for (unsigned int i = 0; i < ShipSize; i++)
    {
      ShipPositionRows.push_back(Row + i);
      ShipPositionColumns.push_back(Column);
    }
  }
}

bool Error_Checking_On_AI_Ship_Positions(const std::vector<std::vector<std::string>> &AIBoard,
                                         const std::vector<unsigned int> &ShipPositionRows,
                                         const std::vector<unsigned int> &ShipPositionColumns)
{
  for (unsigned int i = 0; i < ShipPositionRows.size(); i++)
  {
    if (AIBoard[ShipPositionRows[i]][ShipPositionColumns[i]] == "C" ||
        AIBoard[ShipPositionRows[i]][ShipPositionColumns[i]] == "B" ||
        AIBoard[ShipPositionRows[i]][ShipPositionColumns[i]] == "D" ||
        AIBoard[ShipPositionRows[i]][ShipPositionColumns[i]] == "S" ||
        AIBoard[ShipPositionRows[i]][ShipPositionColumns[i]] == "P")
      return false;
  }

  return true;
}

void Place_Ship(std::vector<std::vector<std::string>> &anyBoard,
                const std::vector<unsigned int> &ShipPositionRows,
                const std::vector<unsigned int> &ShipPositionColumns,
                const std::string ShipName)
{
  for (unsigned int i = 0; i < ShipPositionRows.size(); i++)
    anyBoard[ShipPositionRows[i]][ShipPositionColumns[i]] = ShipName;
}

std::string Battleships_Game_Display(const std::vector<std::vector<std::string>> &PlayerOneBoard,
                                     const std::vector<std::vector<std::string>> &PlayerTwoBoard,
                                     const std::map<std::string, unsigned int> &PlayerOneShipsRemaining,
                                     const std::map<std::string, unsigned int> &PlayerTwoShipsRemaining,
                                     const std::string &NumberOfPlayers,
                                     const std::string &AIDifficulty,
                                     const bool &GameOver)
{
  Clear_Terminal();

  std::string Output;

  // Top bar
  Output.insert(Output.size(), WHITE);
  Output.insert(Output.size(), 1, (char)201);
  Output.insert(Output.size(), 147, (char)205);
  Output.insert(Output.size(), 1, (char)187);
  Output.insert(Output.size(), Battleships_New_Line(RED + "                                                                  Terminal-Games                                                                   " + WHITE));
  Output.insert(Output.size(), Battleships_Bottom_Line());

  // Main game box
  Output.insert(Output.size(), Battleships_Top_Line());

  // Top Row of both boards
  Output.insert(Output.size(), Battleships_New_Line("                    PLAYER ONE                                                                                       PLAYER TWO                    "));

  Output.insert(Output.size(), "\n");
  Output.insert(Output.size(), 1, (char)186);
  Output.insert(Output.size(), "   ");
  for (unsigned int i = 0; i < 2; i++)
  {
    Output.insert(Output.size(), 1, (char)218);
    Output.insert(Output.size(), 3, (char)196);
    for (unsigned int j = 0; j < 10; j++)
    {
      Output.insert(Output.size(), 1, (char)194);
      Output.insert(Output.size(), 3, (char)196);
    }
    Output.insert(Output.size(), 1, (char)191);

    if (i == 0)
      Output.insert(Output.size(), "                                                   ");
  }
  Output.insert(Output.size(), "   ");
  Output.insert(Output.size(), 1, (char)186);

  Output.insert(Output.size(), "\n");
  Output.insert(Output.size(), 1, (char)186);
  Output.insert(Output.size(), "   ");
  for (unsigned int i = 0; i < 2; i++)
  {
    Output.insert(Output.size(), 1, (char)179);
    Output.insert(Output.size(), "   ");
    Output.insert(Output.size(), 1, (char)179);
    Output.insert(Output.size(), " A ");
    Output.insert(Output.size(), 1, (char)179);
    Output.insert(Output.size(), " B ");
    Output.insert(Output.size(), 1, (char)179);
    Output.insert(Output.size(), " C ");
    Output.insert(Output.size(), 1, (char)179);
    Output.insert(Output.size(), " D ");
    Output.insert(Output.size(), 1, (char)179);
    Output.insert(Output.size(), " E ");
    Output.insert(Output.size(), 1, (char)179);
    Output.insert(Output.size(), " F ");
    Output.insert(Output.size(), 1, (char)179);
    Output.insert(Output.size(), " G ");
    Output.insert(Output.size(), 1, (char)179);
    Output.insert(Output.size(), " H ");
    Output.insert(Output.size(), 1, (char)179);
    Output.insert(Output.size(), " I ");
    Output.insert(Output.size(), 1, (char)179);
    Output.insert(Output.size(), " J ");
    Output.insert(Output.size(), 1, (char)179);

    if (i == 0)
      Output.insert(Output.size(), "                                                   ");
  }
  Output.insert(Output.size(), "   ");
  Output.insert(Output.size(), 1, (char)186);

  // Main parts of both boards and centre information
  for (unsigned int i = 0; i < 10; i++)
  {
    // Part 1
    Output.insert(Output.size(), "\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.insert(Output.size(), "   ");

    // Player One Board horizontal dividers Part 1
    Output.insert(Output.size(), 1, (char)195);
    Output.insert(Output.size(), 3, (char)196);
    for (unsigned int j = 0; j < 10; j++)
    {
      Output.insert(Output.size(), 1, (char)197);
      Output.insert(Output.size(), 3, (char)196);
    }
    Output.insert(Output.size(), 1, (char)180);

    // Centre information Part 1
    switch (i)
    {
    case 3:
      Output.insert(Output.size(), "   Carrier                               Carrier   ");
      break;

    case 5: // Battleship
      Output.insert(Output.size(), "   ");
      for (unsigned int j = 0; j < 4; j++)
      {
        if (j < PlayerOneShipsRemaining.at("B"))
          Output.insert(Output.size(), 3, (char)178);
        else
          Output.insert(Output.size(), 3, (char)176);
        Output.insert(Output.size(), " ");
      }
      Output.insert(Output.size(), "              ");
      for (unsigned int j = 0; j < 4; j++)
      {
        if (j < (4 - PlayerTwoShipsRemaining.at("B")))
          Output.insert(Output.size(), 3, (char)176);
        else
          Output.insert(Output.size(), 3, (char)178);
        Output.insert(Output.size(), " ");
      }
      Output.insert(Output.size(), "  ");
      break;

    case 6:
      Output.insert(Output.size(), "   Destroyer                           Destroyer   ");
      break;

    case 8: // Submarine
      Output.insert(Output.size(), "   ");
      for (unsigned int j = 0; j < 3; j++)
      {
        if (j < PlayerOneShipsRemaining.at("S"))
          Output.insert(Output.size(), 3, (char)178);
        else
          Output.insert(Output.size(), 3, (char)176);
        Output.insert(Output.size(), " ");
      }
      Output.insert(Output.size(), "                      ");
      for (unsigned int j = 0; j < 3; j++)
      {
        if (j < (3 - PlayerTwoShipsRemaining.at("S")))
          Output.insert(Output.size(), 3, (char)176);
        else
          Output.insert(Output.size(), 3, (char)178);
        Output.insert(Output.size(), " ");
      }
      Output.insert(Output.size(), "  ");
      break;

    case 9:
      Output.insert(Output.size(), "   Patrol Boat                       Patrol Boat   ");
      break;

    default:
      Output.insert(Output.size(), "                                                   ");
      break;
    }

    // Player Two Board horizontal dividers Part 1
    Output.insert(Output.size(), 1, (char)195);
    Output.insert(Output.size(), 3, (char)196);
    for (unsigned int j = 0; j < 10; j++)
    {
      Output.insert(Output.size(), 1, (char)197);
      Output.insert(Output.size(), 3, (char)196);
    }
    Output.insert(Output.size(), 1, (char)180);
    Output.insert(Output.size(), "   ");
    Output.insert(Output.size(), 1, (char)186);

    // Player One Board Part 2
    Output.insert(Output.size(), "\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.insert(Output.size(), "   ");
    Output.insert(Output.size(), 1, (char)179);
    Output.insert(Output.size(), " ");
    Output.insert(Output.size(), 1, i + 48);
    Output.insert(Output.size(), " ");
    Output.insert(Output.size(), 1, (char)179);

    for (unsigned int j = 0; j < 10; j++)
    {
      if (PlayerOneBoard[i][j] == "C" || PlayerOneBoard[i][j] == "B" || PlayerOneBoard[i][j] == "D" || PlayerOneBoard[i][j] == "S" || PlayerOneBoard[i][j] == "P")
        Output.insert(Output.size(), 3, (char)178);
      else if (PlayerOneBoard[i][j] == "Hit")
        Output.insert(Output.size(), 3, (char)176);
      else if (PlayerOneBoard[i][j] == "Miss")
      {
        Output.insert(Output.size(), " ");
        Output.insert(Output.size(), 1, (char)250);
        Output.insert(Output.size(), " ");
      }
      else
        Output.insert(Output.size(), "   ");
      Output.insert(Output.size(), 1, (char)179);
    }

    // Centre Information Part 2
    switch (i)
    {
    case 0:
      if (NumberOfPlayers == "N/A")
        Output.insert(Output.size(), "                # of Players = " + NumberOfPlayers + "                 ");
      else
        Output.insert(Output.size(), "                 # of Players = " + NumberOfPlayers + "                  ");
      break;

    case 1:
      if (AIDifficulty == "N/A")
        Output.insert(Output.size(), "                AI Difficulty = " + AIDifficulty + "                ");
      else
        Output.insert(Output.size(), "               AI Difficulty = " + AIDifficulty + "                ");
      break;

    case 3: // Carrier
      Output.insert(Output.size(), "   ");
      for (unsigned int j = 0; j < 5; j++)
      {
        if (j < PlayerOneShipsRemaining.at("C"))
          Output.insert(Output.size(), 3, (char)178);
        else
          Output.insert(Output.size(), 3, (char)176);
        Output.insert(Output.size(), " ");
      }
      Output.insert(Output.size(), "      ");
      for (unsigned int j = 0; j < 5; j++)
      {
        if (j < (5 - PlayerTwoShipsRemaining.at("C")))
          Output.insert(Output.size(), 3, (char)176);
        else
          Output.insert(Output.size(), 3, (char)178);
        Output.insert(Output.size(), " ");
      }
      Output.insert(Output.size(), "  ");
      break;

    case 4:
      Output.insert(Output.size(), "   Battleship                         Battleship   ");
      break;

    case 6: // Destroyer
      Output.insert(Output.size(), "   ");
      for (unsigned int j = 0; j < 3; j++)
      {
        if (j < PlayerOneShipsRemaining.at("D"))
          Output.insert(Output.size(), 3, (char)178);
        else
          Output.insert(Output.size(), 3, (char)176);
        Output.insert(Output.size(), " ");
      }
      Output.insert(Output.size(), "                      ");
      for (unsigned int j = 0; j < 3; j++)
      {
        if (j < (3 - PlayerTwoShipsRemaining.at("D")))
          Output.insert(Output.size(), 3, (char)176);
        else
          Output.insert(Output.size(), 3, (char)178);
        Output.insert(Output.size(), " ");
      }
      Output.insert(Output.size(), "  ");
      break;

    case 7:
      Output.insert(Output.size(), "   Submarine                           Submarine   ");
      break;

    case 9: // Patrol Boat
      Output.insert(Output.size(), "   ");
      for (unsigned int j = 0; j < 2; j++)
      {
        if (j < PlayerOneShipsRemaining.at("P"))
          Output.insert(Output.size(), 3, (char)178);
        else
          Output.insert(Output.size(), 3, (char)176);
        Output.insert(Output.size(), " ");
      }
      Output.insert(Output.size(), "                              ");
      for (unsigned int j = 0; j < 2; j++)
      {
        if (j < (2 - PlayerTwoShipsRemaining.at("P")))
          Output.insert(Output.size(), 3, (char)176);
        else
          Output.insert(Output.size(), 3, (char)178);
        Output.insert(Output.size(), " ");
      }
      Output.insert(Output.size(), "  ");
      break;

    default:
      Output.insert(Output.size(), "                                                   ");
      break;
    }

    // Player Two Board Part 2
    Output.insert(Output.size(), 1, (char)179);
    Output.insert(Output.size(), " ");
    Output.insert(Output.size(), 1, i + 48);
    Output.insert(Output.size(), " ");
    Output.insert(Output.size(), 1, (char)179);
    for (unsigned int j = 0; j < 10; j++)
    {
      if ((GameOver || NumberOfPlayers == "0") && (PlayerTwoBoard[i][j] == "C" || PlayerTwoBoard[i][j] == "B" || PlayerTwoBoard[i][j] == "D" || PlayerTwoBoard[i][j] == "S" || PlayerTwoBoard[i][j] == "P"))
        Output.insert(Output.size(), 3, (char)178);
      else if (PlayerTwoBoard[i][j] == "Hit")
        Output.insert(Output.size(), 3, (char)176);
      else if (PlayerTwoBoard[i][j] == "Miss")
      {
        Output.insert(Output.size(), " ");
        Output.insert(Output.size(), 1, (char)250);
        Output.insert(Output.size(), " ");
      }
      else
        Output.insert(Output.size(), "   ");
      Output.insert(Output.size(), 1, (char)179);
    }
    Output.insert(Output.size(), "   ");
    Output.insert(Output.size(), 1, (char)186);
  }

  // Bottom row of both boards
  Output.insert(Output.size(), "\n");
  Output.insert(Output.size(), 1, (char)186);
  Output.insert(Output.size(), "   ");
  for (unsigned int i = 0; i < 2; i++)
  {
    Output.insert(Output.size(), 1, (char)192);
    Output.insert(Output.size(), 3, (char)196);
    for (unsigned int j = 0; j < 10; j++)
    {
      Output.insert(Output.size(), 1, (char)193);
      Output.insert(Output.size(), 3, (char)196);
    }
    Output.insert(Output.size(), 1, (char)217);

    if (i == 0)
      Output.insert(Output.size(), "                                                   ");
  }
  Output.insert(Output.size(), "   ");
  Output.insert(Output.size(), 1, (char)186);

  Output.insert(Output.size(), Battleships_Empty_Line());

  return Output;
}

std::string Battleships_Empty_Line(void)
{
  std::string Output;
  Output.insert(Output.size(), "\n");
  Output.insert(Output.size(), 1, (char)186);
  Output.insert(Output.size(), "                                                                                                                                                   ");
  Output.insert(Output.size(), 1, (char)186);

  return Output;
}

std::string Battleships_New_Line(const std::string &Input)
{
  std::string Output;
  Output.insert(Output.size(), "\n");
  Output.insert(Output.size(), 1, (char)186);
  Output.insert(Output.size(), Input);
  Output.insert(Output.size(), 1, (char)186);

  return Output;
}

std::string Battleships_Top_Line(void)
{
  std::string Output;
  Output.insert(Output.size(), "\n");
  Output.insert(Output.size(), 1, (char)201);
  Output.insert(Output.size(), 147, (char)205);
  Output.insert(Output.size(), 1, (char)187);

  return Output;
}

std::string Battleships_Bottom_Line(void)
{
  std::string Output;
  Output.insert(Output.size(), "\n");
  Output.insert(Output.size(), 1, (char)200);
  Output.insert(Output.size(), 147, (char)205);
  Output.insert(Output.size(), 1, (char)188);

  return Output;
}

std::string Battleships_Bottom_Bar(void)
{
  std::string Output;
  Output.append(Battleships_Top_Line());
  Output.append(Battleships_New_Line(RED + "                                                                    Battleships                                                                    " + WHITE));
  Output.append(Battleships_Bottom_Line());

  return Output;
}

bool Winning_Conditions_Met(const std::vector<std::vector<std::string>> &PlayerOneBoard,
                            const std::vector<std::vector<std::string>> &PlayerTwoBoard)
{
  bool PlayerOneShipsPresent = false;
  for (unsigned int i = 0; i < 10; i++)
    for (unsigned int j = 0; j < 10; j++)
      if (PlayerOneBoard[i][j] == "C" || PlayerOneBoard[i][j] == "B" || PlayerOneBoard[i][j] == "D" || PlayerOneBoard[i][j] == "S" || PlayerOneBoard[i][j] == "P")
        PlayerOneShipsPresent = true;

  bool PlayerTwoShipsPresent = false;
  for (unsigned int i = 0; i < 10; i++)
    for (unsigned int j = 0; j < 10; j++)
      if (PlayerTwoBoard[i][j] == "C" || PlayerTwoBoard[i][j] == "B" || PlayerTwoBoard[i][j] == "D" || PlayerTwoBoard[i][j] == "S" || PlayerTwoBoard[i][j] == "P")
        PlayerTwoShipsPresent = true;

  if (!PlayerOneShipsPresent || !PlayerTwoShipsPresent)
    return true;
  else
    return false;
}

unsigned int Get_Next_User_Command(const std::vector<std::vector<std::string>> &PlayerOneBoard,
                                   const std::vector<std::vector<std::string>> &PlayerTwoBoard,
                                   const std::map<std::string, unsigned int> &PlayerOneShipsRemaining,
                                   const std::map<std::string, unsigned int> &PlayerTwoShipsRemaining,
                                   std::vector<unsigned int> &ValidMovesRemaining,
                                   const unsigned int &NumberOfPlayers,
                                   const std::string &AIDifficulty,
                                   const HANDLE &ConsoleHandle)
{
  bool InputInvalid = true;
  unsigned int UserCommand, Row = ValidMovesRemaining[0] / 10, Column = ValidMovesRemaining[0] % 10;
  unsigned char KeyPress = 0;

  std::string Output = Battleships_Game_Display(PlayerOneBoard, PlayerTwoBoard, PlayerOneShipsRemaining, PlayerTwoShipsRemaining, std::to_string(NumberOfPlayers), AIDifficulty, false);
  Output.append(Battleships_New_Line(" Player One, please enter your next command!                                                                                                       "));
  Output.append(Battleships_Empty_Line());
  Output.append(Battleships_Empty_Line());
  Output.append(Battleships_Empty_Line());
  Output.append(Battleships_Empty_Line());
  Output.append(Battleships_Bottom_Line());
  Output.append(Battleships_Bottom_Bar());

  while (InputInvalid)
  {
    while (KeyPress != '\r')
    {
      switch (KeyPress)
      {
      case 72: // up arrow key
        if (Row == 0)
          Row = 9;
        else
          Row--;
        break;

      case 80: // down arrow key
        if (Row == 9)
          Row = 0;
        else
          Row++;
        break;

      case 75: // left arrow key
        if (Column == 0)
          Column = 9;
        else
          Column--;
        break;

      case 77: // right arrow key
        if (Column == 9)
          Column = 0;
        else
          Column++;
        break;

      default:
        break;
      }

      Clear_Terminal();

      std::cout << Output;

      COORD CursorPosition;
      CursorPosition.X = 106 + Column * 4;
      CursorPosition.Y = 8 + Row * 2;
      SetConsoleCursorPosition(ConsoleHandle, CursorPosition);

      KeyPress = _getch();
    }

    UserCommand = Row * 10 + Column;
    auto CommandPosition = std::find(ValidMovesRemaining.begin(), ValidMovesRemaining.end(), UserCommand);

    if (CommandPosition != ValidMovesRemaining.end())
    {
      InputInvalid = false;
      ValidMovesRemaining.erase(CommandPosition);
    }
    else
      KeyPress = 0;
  }

  return UserCommand;
}

unsigned int Get_Next_AI_Command(const std::vector<std::vector<std::string>> &PlayerOneBoard,
                                 const std::vector<std::vector<std::string>> &PlayerTwoBoard,
                                 const std::map<std::string, unsigned int> &PlayerOneShipsRemaining,
                                 const std::map<std::string, unsigned int> &PlayerTwoShipsRemaining,
                                 std::vector<unsigned int> &PlayerOneValidMovesRemaining,
                                 std::vector<unsigned int> &PlayerTwoValidMovesRemaining,
                                 const unsigned int &NumberOfPlayers,
                                 const std::string &AIDifficulty,
                                 const std::string &CurrentPlayer)
{
  std::vector<unsigned int> ValidMovesRemaining;

  if (CurrentPlayer == "PLAYER ONE")
    ValidMovesRemaining = PlayerOneValidMovesRemaining;
  else
    ValidMovesRemaining = PlayerTwoValidMovesRemaining;

  unsigned int AICommand = ValidMovesRemaining[std::rand() % ValidMovesRemaining.size()];
  auto CommandPosition = std::find(ValidMovesRemaining.begin(), ValidMovesRemaining.end(), AICommand);
  ValidMovesRemaining.erase(CommandPosition);

  if (CurrentPlayer == "PLAYER ONE")
    PlayerOneValidMovesRemaining = ValidMovesRemaining;
  else
    PlayerTwoValidMovesRemaining = ValidMovesRemaining;

  return AICommand;
}

void Execute_Next_Turn(std::vector<std::vector<std::string>> &PlayerOneBoard,
                       std::vector<std::vector<std::string>> &PlayerTwoBoard,
                       std::map<std::string, unsigned int> &PlayerOneShipsRemaining,
                       std::map<std::string, unsigned int> &PlayerTwoShipsRemaining,
                       const std::string &CurrentPlayer,
                       const unsigned int &Command)
{
  unsigned int Row = Command / 10;
  unsigned int Column = Command % 10;

  if (CurrentPlayer == "PLAYER ONE")
  {
    if (PlayerTwoBoard[Row][Column] == "C" || PlayerTwoBoard[Row][Column] == "B" || PlayerTwoBoard[Row][Column] == "D" || PlayerTwoBoard[Row][Column] == "S" || PlayerTwoBoard[Row][Column] == "P")
    {
      PlayerTwoShipsRemaining[PlayerTwoBoard[Row][Column]]--;
      PlayerTwoBoard[Row][Column] = "Hit";
    }
    else
      PlayerTwoBoard[Row][Column] = "Miss";
  }

  else
  {
    if (PlayerOneBoard[Row][Column] == "C" || PlayerOneBoard[Row][Column] == "B" || PlayerOneBoard[Row][Column] == "D" || PlayerOneBoard[Row][Column] == "S" || PlayerOneBoard[Row][Column] == "P")
    {
      PlayerOneShipsRemaining[PlayerOneBoard[Row][Column]]--;
      PlayerOneBoard[Row][Column] = "Hit";
    }
    else
      PlayerOneBoard[Row][Column] = "Miss";
  }
}

void Display_Game_Over_Message(const std::vector<std::vector<std::string>> &PlayerOneBoard,
                               const std::vector<std::vector<std::string>> &PlayerTwoBoard,
                               const std::map<std::string, unsigned int> &PlayerOneShipsRemaining,
                               const std::map<std::string, unsigned int> &PlayerTwoShipsRemaining,
                               const unsigned int &NumberOfPlayers,
                               const std::string &AIDifficulty,
                               const std::string &CurrentPlayer,
                               const unsigned int &NumberOfTurns,
                               bool &GameIsRunning)
{
  std::string Output = Battleships_Game_Display(PlayerOneBoard, PlayerTwoBoard, PlayerOneShipsRemaining, PlayerTwoShipsRemaining, std::to_string(NumberOfPlayers), AIDifficulty, true);
  Output.append(Battleships_New_Line("                                                                     GAME OVER                                                                     "));
  Output.append(Battleships_Empty_Line());

  if (CurrentPlayer == "PLAYER ONE")
    Output.append(Battleships_New_Line("                                                  Player One has won! The game lasted " + std::to_string(NumberOfTurns) + " turns.                                                   "));
  else
    Output.append(Battleships_New_Line("                                                  Player Two has won! The game lasted " + std::to_string(NumberOfTurns) + " turns.                                                   "));

  Output.append(Battleships_Empty_Line());
  Output.append(Battleships_New_Line("                                                Press 'Q' to quit OR any other key to play again...                                                "));
  Output.append(Battleships_Bottom_Line());
  Output.append(Battleships_Bottom_Bar());

  std::cout << Output;

  if (_getch() == 'q')
  {
    GameIsRunning = false;
    Clear_Terminal();
  }
}