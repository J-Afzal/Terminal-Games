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

void Setup_Game(std::vector<std::vector<std::string>> &PlayerOneBoard,
                std::vector<std::vector<std::string>> &PlayerTwoBoard,
                std::vector<unsigned int> &PlayerOneValidMovesRemaining,
                std::vector<unsigned int> &PlayerTwoValidMovesRemaining,
                std::map<std::string, unsigned int> &PlayerOneShipsRemaining,
                std::map<std::string, unsigned int> &PlayerTwoShipsRemaining,
                unsigned int &NumberOfPlayers,
                std::string &AIDifficulty,
                std::string &CurrentPlayer)
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

  // Get number of players
  do
  {
    Display_Game(PlayerOneBoard, PlayerTwoBoard, PlayerOneShipsRemaining, PlayerTwoShipsRemaining, "N/A", "N/A", false);
    std::cout << "Please enter the number of human players: ";
  }
  while(!Get_Number_Of_Players(NumberOfPlayers, 0, 1));

  do
  {
    Display_Game(PlayerOneBoard, PlayerTwoBoard, PlayerOneShipsRemaining, PlayerTwoShipsRemaining, std::to_string(NumberOfPlayers), "N/A", false);
    std::cout << "Please enter the AI difficulty (EASY or HARD): ";
  }
  while(!Get_AI_Difficulty(AIDifficulty));

  if (NumberOfPlayers == 1)
    Get_User_Ship_Positions(PlayerOneBoard, PlayerTwoBoard, PlayerOneShipsRemaining, PlayerTwoShipsRemaining, NumberOfPlayers, AIDifficulty);

  else
    Get_AI_Ship_Positions(PlayerOneBoard);

  // Player two will always be AI controlled
  Get_AI_Ship_Positions(PlayerTwoBoard);

  if ((std::rand() % 2) == 0)
    CurrentPlayer = "PLAYER ONE";
  else
    CurrentPlayer = "PLAYER TWO";
}

void Get_User_Ship_Positions(std::vector<std::vector<std::string>> &PlayerOneBoard,
                             const std::vector<std::vector<std::string>> &PlayerTwoBoard,
                             const std::map<std::string, unsigned int> &PlayerOneShipsRemaining,
                             const std::map<std::string, unsigned int> &PlayerTwoShipsRemaining,
                             const unsigned int &NumberOfPlayers,
                             const std::string &AIDifficulty)
{
  for (unsigned int CurrentShip = 0; CurrentShip < 5; CurrentShip++)
  {
    bool isValueCorrect = false;
    std::string Input;
    std::vector<unsigned int> ShipPositionRows, ShipPositionColumns;

    switch (CurrentShip)
    {
    case 0: // Carrier (C)
    {
      while (!isValueCorrect)
      {
        unsigned int ShipSize = 5;

        Display_Game(PlayerOneBoard, PlayerTwoBoard, PlayerOneShipsRemaining, PlayerTwoShipsRemaining, std::to_string(NumberOfPlayers), AIDifficulty, false);

        std::cout << "Please enter the " << ShipSize << " grid locations for the Carrier: ";

        std::getline(std::cin, Input);

        if (!Error_Checking_On_User_Ship_Positions(PlayerOneBoard, Input, ShipPositionRows, ShipPositionColumns, ShipSize))
          continue;

        isValueCorrect = true;

        Place_Ship(PlayerOneBoard, ShipPositionRows, ShipPositionColumns, "C");
      }

      break;
    }

    case 1: // Battleship (B)
    {
      while (!isValueCorrect)
      {
        unsigned int ShipSize = 4;

        Display_Game(PlayerOneBoard, PlayerTwoBoard, PlayerOneShipsRemaining, PlayerTwoShipsRemaining, std::to_string(NumberOfPlayers), AIDifficulty, false);

        std::cout << "Please enter the " << ShipSize << " grid locations for the Battleship: ";

        std::getline(std::cin, Input);

        if (!Error_Checking_On_User_Ship_Positions(PlayerOneBoard, Input, ShipPositionRows, ShipPositionColumns, ShipSize))
          continue;

        isValueCorrect = true;

        Place_Ship(PlayerOneBoard, ShipPositionRows, ShipPositionColumns, "B");
      }
      break;
    }

    case 2: // Destroyer (D)
    {
      while (!isValueCorrect)
      {
        unsigned int ShipSize = 3;

        Display_Game(PlayerOneBoard, PlayerTwoBoard, PlayerOneShipsRemaining, PlayerTwoShipsRemaining, std::to_string(NumberOfPlayers), AIDifficulty, false);

        std::cout << "Please enter the " << ShipSize << " grid locations for the Destroyer: ";

        std::getline(std::cin, Input);

        if (!Error_Checking_On_User_Ship_Positions(PlayerOneBoard, Input, ShipPositionRows, ShipPositionColumns, ShipSize))
          continue;

        isValueCorrect = true;

        Place_Ship(PlayerOneBoard, ShipPositionRows, ShipPositionColumns, "D");
      }

      break;
    }

    case 3: // Submarine (S)
    {
      while (!isValueCorrect)
      {
        unsigned int ShipSize = 3;

        Display_Game(PlayerOneBoard, PlayerTwoBoard, PlayerOneShipsRemaining, PlayerTwoShipsRemaining, std::to_string(NumberOfPlayers), AIDifficulty, false);

        std::cout << "Please enter the " << ShipSize << " grid locations for the Submarine: ";

        std::getline(std::cin, Input);

        if (!Error_Checking_On_User_Ship_Positions(PlayerOneBoard, Input, ShipPositionRows, ShipPositionColumns, ShipSize))
          continue;

        isValueCorrect = true;

        Place_Ship(PlayerOneBoard, ShipPositionRows, ShipPositionColumns, "S");
      }

      break;
    }

    case 4: // Patrol Boat (P)
    {
      while (!isValueCorrect)
      {
        unsigned int ShipSize = 2;

        Display_Game(PlayerOneBoard, PlayerTwoBoard, PlayerOneShipsRemaining, PlayerTwoShipsRemaining, std::to_string(NumberOfPlayers), AIDifficulty, false);

        std::cout << "Please enter the " << ShipSize << " grid locations for the Patrol Boat: ";

        std::getline(std::cin, Input);

        if (!Error_Checking_On_User_Ship_Positions(PlayerOneBoard, Input, ShipPositionRows, ShipPositionColumns, ShipSize))
          continue;

        isValueCorrect = true;

        Place_Ship(PlayerOneBoard, ShipPositionRows, ShipPositionColumns, "P");
      }

      break;
    }

    default:
      std::cout << "Get_User_Ship_Positions() switch statement error\n";
      break;
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
      if (IndividualCoordinates[i][1] != (IndividualCoordinates[i-1][1] + 1))
        return false;
  }

  else if (NumbersIdentical && !LettersIdentical) // Horizontal
  {
    // Check that letter is increment by one after each co-ordinate
    for (unsigned int i = 1; i < IndividualCoordinates.size(); i++)
      if (IndividualCoordinates[i][0] != (IndividualCoordinates[i-1][0] + 1))
        return false;
  }

  else // No diagonals allowed
    return false;

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
  for (unsigned int i = 0; i < 5; i++)
  {
    bool isValueCorrect = false;

    switch (i)
    {
    case 0: // Carrier (C)
    {
      while (!isValueCorrect)
      {
        std::vector<unsigned int> ShipPositionRows, ShipPositionColumns;

        unsigned int ShipSize = 5;

        Generate_AI_Ship_Positions(ShipPositionRows, ShipPositionColumns, ShipSize);

        if (!Error_Checking_On_AI_Ship_Positions(AIBoard, ShipPositionRows, ShipPositionColumns))
          continue;

        isValueCorrect = true;

        Place_Ship(AIBoard, ShipPositionRows, ShipPositionColumns, "C");
      }

      break;
    }

    case 1: // Battleship (B)
    {
      while (!isValueCorrect)
      {
        std::vector<unsigned int> ShipPositionRows, ShipPositionColumns;

        unsigned int ShipSize = 4;

        Generate_AI_Ship_Positions(ShipPositionRows, ShipPositionColumns, ShipSize);

        if (!Error_Checking_On_AI_Ship_Positions(AIBoard, ShipPositionRows, ShipPositionColumns))
          continue;

        isValueCorrect = true;

        Place_Ship(AIBoard, ShipPositionRows, ShipPositionColumns, "B");
      }

      break;
    }

    case 2: // Destroyer (D)
    {
      while (!isValueCorrect)
      {
        std::vector<unsigned int> ShipPositionRows, ShipPositionColumns;

        unsigned int ShipSize = 3;

        Generate_AI_Ship_Positions(ShipPositionRows, ShipPositionColumns, ShipSize);

        if (!Error_Checking_On_AI_Ship_Positions(AIBoard, ShipPositionRows, ShipPositionColumns))
          continue;

        isValueCorrect = true;

        Place_Ship(AIBoard, ShipPositionRows, ShipPositionColumns, "D");
      }

      break;
    }

    case 3: // Submarine (S)
    {
      while (!isValueCorrect)
      {
        std::vector<unsigned int> ShipPositionRows, ShipPositionColumns;

        unsigned int ShipSize = 3;

        Generate_AI_Ship_Positions(ShipPositionRows, ShipPositionColumns, ShipSize);

        if (!Error_Checking_On_AI_Ship_Positions(AIBoard, ShipPositionRows, ShipPositionColumns))
          continue;

        isValueCorrect = true;

        Place_Ship(AIBoard, ShipPositionRows, ShipPositionColumns, "S");
      }

      break;
    }

    case 4: // Patrol Boat (P)
    {
      while (!isValueCorrect)
      {
        std::vector<unsigned int> ShipPositionRows, ShipPositionColumns;

        unsigned int ShipSize = 2;

        Generate_AI_Ship_Positions(ShipPositionRows, ShipPositionColumns, ShipSize);

        if (!Error_Checking_On_AI_Ship_Positions(AIBoard, ShipPositionRows, ShipPositionColumns))
          continue;

        isValueCorrect = true;

        Place_Ship(AIBoard, ShipPositionRows, ShipPositionColumns, "P");
      }

      break;
    }

    default:
      std::cout << "Ask_AI_For_Ship_Positions() switch statement error\n";
      break;
    }
  }
}

void Generate_AI_Ship_Positions(std::vector<unsigned int> &ShipPositionRows,
                                std::vector<unsigned int> &ShipPositionColumns,
                                const unsigned int &ShipSize)

{
  unsigned int Column, Row;

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
      ShipPositionColumns.push_back(Column+i);
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
      ShipPositionRows.push_back(Row+i);
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

void Display_Game(const std::vector<std::vector<std::string>> &PlayerOneBoard,
                  const std::vector<std::vector<std::string>> &PlayerTwoBoard,
                  const std::map<std::string, unsigned int> &PlayerOneShipsRemaining,
                  const std::map<std::string, unsigned int> &PlayerTwoShipsRemaining,
                  const std::string &NumberOfPlayers,
                  const std::string &AIDifficulty,
                  const bool &GameOver)
{
  Clear_Terminal();

  // Top Row of both boards
  std::string Output = "\t\t  PLAYER ONE\t\t\t\t\t\t                                          PLAYER TWO\n";
  Output.insert(Output.size(), 1, (char)218);
  Output.insert(Output.size(), 3, (char)196);

  for (unsigned int i = 0; i < 10; i++)
  {
    Output.insert(Output.size(), 1, (char)194);
    Output.insert(Output.size(), 3, (char)196);
  }

  Output.insert(Output.size(), 1, (char)191);
  Output.append("\t\t\t\t\t\t\t");
  Output.insert(Output.size(), 1, (char)218);
  Output.insert(Output.size(), 3, (char)196);

  for (unsigned int i = 0; i < 10; i++)
  {
    Output.insert(Output.size(), 1, (char)194);
    Output.insert(Output.size(), 3, (char)196);
  }

  Output.insert(Output.size(), 1, (char)191);
  Output.append("\n");

  Output.insert(Output.size(), 1, (char)179);
  Output.append("   ");
  Output.insert(Output.size(), 1, (char)179);
  Output.append(" A ");
  Output.insert(Output.size(), 1, (char)179);
  Output.append(" B ");
  Output.insert(Output.size(), 1, (char)179);
  Output.append(" C ");
  Output.insert(Output.size(), 1, (char)179);
  Output.append(" D ");
  Output.insert(Output.size(), 1, (char)179);
  Output.append(" E ");
  Output.insert(Output.size(), 1, (char)179);
  Output.append(" F ");
  Output.insert(Output.size(), 1, (char)179);
  Output.append(" G ");
  Output.insert(Output.size(), 1, (char)179);
  Output.append(" H ");
  Output.insert(Output.size(), 1, (char)179);
  Output.append(" I ");
  Output.insert(Output.size(), 1, (char)179);
  Output.append(" J ");
  Output.insert(Output.size(), 1, (char)179);
  Output.append("\t\t\t BATTLESHIPS\t\t\t");
  Output.insert(Output.size(), 1, (char)179);
  Output.append("   ");
  Output.insert(Output.size(), 1, (char)179);
  Output.append(" A ");
  Output.insert(Output.size(), 1, (char)179);
  Output.append(" B ");
  Output.insert(Output.size(), 1, (char)179);
  Output.append(" C ");
  Output.insert(Output.size(), 1, (char)179);
  Output.append(" D ");
  Output.insert(Output.size(), 1, (char)179);
  Output.append(" E ");
  Output.insert(Output.size(), 1, (char)179);
  Output.append(" F ");
  Output.insert(Output.size(), 1, (char)179);
  Output.append(" G ");
  Output.insert(Output.size(), 1, (char)179);
  Output.append(" H ");
  Output.insert(Output.size(), 1, (char)179);
  Output.append(" I ");
  Output.insert(Output.size(), 1, (char)179);
  Output.append(" J ");
  Output.insert(Output.size(), 1, (char)179);
  Output.append("\n");

  // Main parts of both boards and centre information
  for (unsigned int i = 0; i < 10; i++)
  {
    // Player One Board horizontal dividers
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
      Output.append("\tCarrier\t\t\t\t      Carrier\t");
    break;

    case 5: // Battleship
      Output.append("\t");
      for (unsigned int j = 0; j < 4; j++)
      {
        if (j < PlayerOneShipsRemaining.at("B"))
          Output.insert(Output.size(), 3, (char)178);
        else
          Output.insert(Output.size(), 3, (char)176);
        Output.append(" ");
      }
      Output.append("\t      ");
      for (unsigned int j = 0; j < 4; j++)
      {
        if (j < (4-PlayerTwoShipsRemaining.at("B")))
          Output.insert(Output.size(), 3, (char)176);
        else
          Output.insert(Output.size(), 3, (char)178);
        Output.append(" ");
      }
      Output.append("\t");
    break;

    case 6:
      Output.append("\tDestroyer\t\t\t    Destroyer\t");
    break;

    case 8: // Submarine
      Output.append("\t");
      for (unsigned int j = 0; j < 3; j++)
      {
        if (j < PlayerOneShipsRemaining.at("S"))
          Output.insert(Output.size(), 3, (char)178);
        else
          Output.insert(Output.size(), 3, (char)176);
        Output.append(" ");
      }
      Output.append("\t\t\t  ");
      for (unsigned int j = 0; j < 3; j++)
      {
        if (j < (3-PlayerTwoShipsRemaining.at("S")))
          Output.insert(Output.size(), 3, (char)176);
        else
          Output.insert(Output.size(), 3, (char)178);
        Output.append(" ");
      }
      Output.append("\t");
    break;

    case 9:
      Output.append("\tPatrol Boat\t\t\t  Patrol Boat\t");
    break;

    default:
      Output.append("\t\t\t\t\t\t\t");
    break;
    }

    // Player Two Board horizontal dividers
    Output.insert(Output.size(), 1, (char)195);
    Output.insert(Output.size(), 3, (char)196);

    for (unsigned int j = 0; j < 10; j++)
    {
      Output.insert(Output.size(), 1, (char)197);
      Output.insert(Output.size(), 3, (char)196);
    }

    Output.insert(Output.size(), 1, (char)180);
    Output.append("\n");

    // Player One Board
    Output.insert(Output.size(), 1, (char)179);
    Output.append(" ");
    Output.insert(Output.size(), 1, i+48);
    Output.append(" ");
    Output.insert(Output.size(), 1, (char)179);

    for (unsigned int j = 0; j < 10; j++)
    {
      if (PlayerOneBoard[i][j] == "C" || PlayerOneBoard[i][j] == "B" || PlayerOneBoard[i][j] == "D" || PlayerOneBoard[i][j] == "S" || PlayerOneBoard[i][j] == "P")
        Output.insert(Output.size(), 3, (char)178);
      else if (PlayerOneBoard[i][j] == "Hit")
        Output.insert(Output.size(), 3, (char)176);
      else if (PlayerOneBoard[i][j] == "Miss")
      {
        Output.append(" ");
        Output.insert(Output.size(), 1, (char)250);
        Output.append(" ");
      }
      else
        Output.append("   ");
      Output.insert(Output.size(), 1, (char)179);
    }

    // Centre Information Part 2
    switch (i)
    {
    case 0:
      if (NumberOfPlayers == "N/A")
        Output.append("\t\t     # of Players = " + NumberOfPlayers + "\t\t\t");
      else
        Output.append("\t\t       # of Players = " + NumberOfPlayers + "\t\t\t");
    break;

    case 1:
        Output.append("\t\t     AI Difficulty = " + AIDifficulty + "\t\t");
    break;

    case 3: // Carrier
      Output.append("\t");
      for (unsigned int j = 0; j < 5; j++)
      {
        if (j < PlayerOneShipsRemaining.at("C"))
          Output.insert(Output.size(), 3, (char)178);
        else
          Output.insert(Output.size(), 3, (char)176);
        Output.append(" ");
      }
      Output.append("\t  ");
      for (unsigned int j = 0; j < 5; j++)
      {
        if (j < (5-PlayerTwoShipsRemaining.at("C")))
          Output.insert(Output.size(), 3, (char)176);
        else
          Output.insert(Output.size(), 3, (char)178);
        Output.append(" ");
      }
      Output.append("\t");
    break;

    case 4:
      Output.append("\tBattleship\t\t\t   Battleship\t");
    break;

    case 6: // Destroyer
      Output.append("\t");
      for (unsigned int j = 0; j < 3; j++)
      {
        if (j < PlayerOneShipsRemaining.at("D"))
          Output.insert(Output.size(), 3, (char)178);
        else
          Output.insert(Output.size(), 3, (char)176);
        Output.append(" ");
      }
      Output.append("\t\t\t  ");
      for (unsigned int j = 0; j < 3; j++)
      {
        if (j < (3-PlayerTwoShipsRemaining.at("D")))
          Output.insert(Output.size(), 3, (char)176);
        else
          Output.insert(Output.size(), 3, (char)178);
        Output.append(" ");
      }
      Output.append("\t");
    break;

    case 7:
      Output.append("\tSubmarine\t\t\t    Submarine\t");
    break;

    case 9: // Patrol Boat
      Output.append("\t");
      for (unsigned int j = 0; j < 2; j++)
      {
        if (j < PlayerOneShipsRemaining.at("P"))
          Output.insert(Output.size(), 3, (char)178);
        else
          Output.insert(Output.size(), 3, (char)176);
        Output.append(" ");
      }
      Output.append("\t\t\t      ");
      for (unsigned int j = 0; j < 2; j++)
      {
        if (j < (2-PlayerTwoShipsRemaining.at("P")))
          Output.insert(Output.size(), 3, (char)176);
        else
          Output.insert(Output.size(), 3, (char)178);
        Output.append(" ");
      }
      Output.append("\t");
    break;

    default:
      Output.append("\t\t\t\t\t\t\t");
    break;
    }

    // Player Two Board
    Output.insert(Output.size(), 1, (char)179);
    Output.append(" ");
    Output.insert(Output.size(), 1, i+48);
    Output.append(" ");
    Output.insert(Output.size(), 1, (char)179);
    for (unsigned int j = 0; j < 10; j++)
    {
      if ((GameOver || NumberOfPlayers == "0") && (PlayerTwoBoard[i][j] == "C" || PlayerTwoBoard[i][j] == "B" || PlayerTwoBoard[i][j] == "D" || PlayerTwoBoard[i][j] == "S" || PlayerTwoBoard[i][j] == "P"))
        Output.insert(Output.size(), 3, (char)178);
      else if (PlayerTwoBoard[i][j] == "Hit")
        Output.insert(Output.size(), 3, (char)176);
      else if (PlayerTwoBoard[i][j] == "Miss")
      {
        Output.append(" ");
        Output.insert(Output.size(), 1, (char)250);
        Output.append(" ");
      }
      else
        Output.append("   ");
      Output.insert(Output.size(), 1, (char)179);
    }
    Output.append("\n");
  }

  // Bottom row of both boards
  Output.insert(Output.size(), 1, (char)192);
  Output.insert(Output.size(), 3, (char)196);

  for (unsigned int j = 0; j < 10; j++)
  {
    Output.insert(Output.size(), 1, (char)193);
    Output.insert(Output.size(), 3, (char)196);
  }

  Output.insert(Output.size(), 1, (char)217);
  Output.append("\t\t\t\t\t\t\t");
  Output.insert(Output.size(), 1, (char)192);
  Output.insert(Output.size(), 3, (char)196);

  for (unsigned int j = 0; j < 10; j++)
  {
    Output.insert(Output.size(), 1, (char)193);
    Output.insert(Output.size(), 3, (char)196);
  }

  Output.insert(Output.size(), 1, (char)217);
  Output.append("\n\n");

  std::cout << Output;
}

bool Winning_Conditions_Met(const std::vector<std::vector<std::string>> &PlayerOneBoard,
                            const std::vector<std::vector<std::string>> &PlayerTwoBoard)
{
  bool ArePlayerOneShipsPresent = false;
  for (unsigned int i = 0; i < 10; i++)
    for (unsigned int j = 0; j < 10; j++)
      if (PlayerOneBoard[i][j] == "C" || PlayerOneBoard[i][j] == "B" || PlayerOneBoard[i][j] == "D" || PlayerOneBoard[i][j] == "S" || PlayerOneBoard[i][j] == "P")
        ArePlayerOneShipsPresent = true;

  bool ArePlayerTwoShipsPresent = false;
  for (unsigned int i = 0; i < 10; i++)
    for (unsigned int j = 0; j < 10; j++)
      if (PlayerTwoBoard[i][j] == "C" || PlayerTwoBoard[i][j] == "B" || PlayerTwoBoard[i][j] == "D" || PlayerTwoBoard[i][j] == "S" || PlayerTwoBoard[i][j] == "P")
        ArePlayerTwoShipsPresent = true;

  if (!ArePlayerOneShipsPresent || !ArePlayerTwoShipsPresent)
    return true;
  else
    return false;
}

unsigned int Get_Next_User_Command(const std::vector<std::vector<std::string>> &PlayerOneBoard,
                                   const std::vector<std::vector<std::string>> &PlayerTwoBoard,
                                   const std::map<std::string, unsigned int> &PlayerOneShipsRemaining,
                                   const std::map<std::string, unsigned int> &PlayerTwoShipsRemaining,
                                   const unsigned int &NumberOfPlayers,
                                   const std::string &AIDifficulty)
{
  bool IsValueCorrect = false;
  std::string Input;
  unsigned int Row, Column;

  while (!IsValueCorrect)
  {
    Display_Game(PlayerOneBoard, PlayerTwoBoard, PlayerOneShipsRemaining, PlayerTwoShipsRemaining, std::to_string(NumberOfPlayers), AIDifficulty, false);
    std::cout << "Player One, please enter your next command: ";
    std::getline(std::cin, Input);

    if (Input.size() != 2)
      continue;

    Capitalise_Word(Input);

    if (Input[0] < 'A' || Input[0] > 'J')
      continue;

    if (Input[1] < '0' || Input[1] > '9')
      continue;

    Row = std::stoi(std::to_string(Input[1]-48), nullptr, 10);
    Column = std::stoi(std::to_string(Input[0]-65), nullptr, 10);

    if (PlayerTwoBoard[Row][Column] == "Hit" || PlayerTwoBoard[Row][Column] == "Miss")
      continue;

    IsValueCorrect = true;
  }
  // To get a value from 0 to 99 representing all values on the board
  return Row*10 + Column;
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

  Display_Game(PlayerOneBoard, PlayerTwoBoard, PlayerOneShipsRemaining, PlayerTwoShipsRemaining, std::to_string(NumberOfPlayers), AIDifficulty, false);

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
  Display_Game(PlayerOneBoard, PlayerTwoBoard, PlayerOneShipsRemaining, PlayerTwoShipsRemaining, std::to_string(NumberOfPlayers), AIDifficulty, true);

  if (CurrentPlayer == "PLAYER ONE")
    std::cout << "\t\t\t\t\t\t\t\t  GAME OVER\n\n\t\t\t\t\t       Player One has won! The game lasted " << NumberOfTurns << " turns.";
  else
    std::cout << "\t\t\t\t\t\t\t\t  GAME OVER\n\n\t\t\t\t\t       Player Two has won! The game lasted " << NumberOfTurns << " turns.";

  std::cout << "\n\n\t\t\t\t\t     Press 'Q' to quit OR any other key to play again...";

  if (_getch() == 'q')
  {
    GameIsRunning = false;
    Clear_Terminal();
  }
}
