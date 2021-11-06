//
//  @File: Battleships.cpp
//  @Author: Junaid Afzal
//

// to prevent max error with windows.h redefining it
// https://stackoverflow.com/questions/7035023/stdmax-expected-an-identifier/7035078
#define NOMINMAX
#include <windows.h>

#include "Battleships.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <conio.h>

void Setup_Game(std::vector<std::vector<std::string>> &PlayerOneBoard,
                std::vector<std::vector<std::string>> &PlayerTwoBoard,
                unsigned int &NumberOfPlayers,
                std::string &CurrentPlayer,
                std::string &AIDifficulty,
                std::vector<unsigned int> &PlayerOneValidMovesRemaining,
                std::vector<unsigned int> &PlayerTwoValidMovesRemaining,
                std::map<std::string, unsigned int> &PlayerOneShipsRemaining,
                std::map<std::string, unsigned int> &PlayerTwoShipsRemaining)
{
  // Board size is a standard 10 x 10
  unsigned int NumberOfRows = 10, NumberOfColumns = 10;

  // The ComputerBoard and UserBoard will be filled with spaces while the opponent boards will be filled
  // with incrementing numbers from 0 - 99, left to right and then top to bottom
  for (unsigned int i = 0, GridNumber = 0; i < NumberOfRows; i++)
  {
    std::vector<std::string> Row;

    PlayerOneBoard.push_back(Row);
    PlayerTwoBoard.push_back(Row);

    for (unsigned int j = 0; j < NumberOfColumns; j++, GridNumber++)
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

  // Set seed for std::rand() to system time at 0
  std::srand((unsigned int)std::time(0));

  // Get number of players
  NumberOfPlayers = Ask_User_For_Number_Of_Players(PlayerOneBoard, PlayerTwoBoard, PlayerOneShipsRemaining, PlayerTwoShipsRemaining);

  AIDifficulty = Get_AI_Difficulty(PlayerOneBoard, PlayerTwoBoard, NumberOfPlayers, PlayerOneShipsRemaining, PlayerTwoShipsRemaining);

  // If 1 then 1 human player and one computer player
  if (NumberOfPlayers == 1)
    Ask_User_For_Ship_Positions(PlayerOneBoard, PlayerTwoBoard, NumberOfPlayers, AIDifficulty, PlayerOneShipsRemaining, PlayerTwoShipsRemaining);

  else // then zero human players and two computer players
    Ask_Computer_For_Ship_Positions(PlayerOneBoard);

  // Ask computer for the ship positions and update computer board
  Ask_Computer_For_Ship_Positions(PlayerTwoBoard);

  // Use std::rand() to randomly choose the player to start
  if ((std::rand() % 2) == 0)
    CurrentPlayer = "PLAYER ONE";
  else
    CurrentPlayer = "PLAYER TWO";
}

int Ask_User_For_Number_Of_Players(const std::vector<std::vector<std::string>> &PlayerOneBoard,
                                   const std::vector<std::vector<std::string>> &PlayerTwoBoard,
                                   const std::map<std::string, unsigned int> &PlayerOneShipsRemaining,
                                   const std::map<std::string, unsigned int> &PlayerTwoShipsRemaining)
{
  bool IsValueCorrect = false; // Flag for if input value is valid
  std::string Input;

  while (!IsValueCorrect)
  {
    Display_Game(PlayerOneBoard, PlayerTwoBoard, PlayerOneShipsRemaining, PlayerTwoShipsRemaining, "N/A", "N/A", false);
    std::cout << "\n\nEnter the number of human players ";

    std::getline(std::cin, Input);

    // Only 0 and players allowed
    if (Input == "0" || Input == "1")
      IsValueCorrect = true;
  }

  return std::stoi(Input, nullptr, 10);
}

std::string Get_AI_Difficulty(const std::vector<std::vector<std::string>> &PlayerOneBoard,
                              const std::vector<std::vector<std::string>> &PlayerTwoBoard,
                              const unsigned int &NumberOfPlayers,
                              const std::map<std::string, unsigned int> &PlayerOneShipsRemaining,
                              const std::map<std::string, unsigned int> &PlayerTwoShipsRemaining)
{
  bool IsValueCorrect = false; // Flag for if input value is valid
  std::string Input;

  while (!IsValueCorrect)
  {
    Display_Game(PlayerOneBoard, PlayerTwoBoard, PlayerOneShipsRemaining, PlayerTwoShipsRemaining, std::to_string(NumberOfPlayers), "N/A", false);
    std::cout << "\n\nEnter the AI difficulty (EASY or HARD) ";

    std::getline(std::cin, Input);

    Capitalise_Word(Input);

    if (Input == "EASY" || Input == "HARD")
      IsValueCorrect = true;
  }

  return Input;
}

void Capitalise_Word(std::string &Input)
{
  // Assuming Input contains only letters of unkown capitalisation, if
  // a letter is lower case (>=97) then minus 32 to capitalise it
  for (unsigned int i = 0; i < Input.size(); i++)
  {
    if (Input[i] >= 'a' && Input[i] <= 'z')
      Input[i] -= 32;
  }
}

void Ask_User_For_Ship_Positions(std::vector<std::vector<std::string>> &PlayerOneBoard,
                                 const std::vector<std::vector<std::string>> &PlayerTwoBoard,
                                 const unsigned int &NumberOfPlayers,
                                 const std::string &AIDifficulty,
                                 const std::map<std::string, unsigned int> &PlayerOneShipsRemaining,
                                 const std::map<std::string, unsigned int> &PlayerTwoShipsRemaining)
{
  for (unsigned int CurrentShip = 0; CurrentShip < 5; CurrentShip++)
  {
    bool isValueCorrect = false;
    std::string Input;
    std::vector<unsigned int> ShipPositionRows, ShipPositionColumns;

    switch (CurrentShip)
    {
    case 0:
    {
      while (!isValueCorrect)
      {
        // Carrier of size 5
        unsigned int ShipSize = 5;

        Display_Game(PlayerOneBoard, PlayerTwoBoard, PlayerOneShipsRemaining, PlayerTwoShipsRemaining, std::to_string(NumberOfPlayers), AIDifficulty, false);

        // User prompt for ship locations
        std::cout << "\n\nEnter the " << ShipSize << " grid locations for the Carrier: ";

        // Using std::getline so string with spaces is read in
        std::getline(std::cin, Input);

        // If error checking returns false then continue to next iteration
        if (!Error_Checking_Ordering_Orientation_On_User_Ship_Positions(PlayerOneBoard, Input, ShipPositionRows, ShipPositionColumns, ShipSize))
          continue;

        isValueCorrect = true;

        // Place ship on UserBoard using the CurrentShipPositions_ints positions and marking with 'C' for carrier
        Place_Ship(PlayerOneBoard, ShipPositionRows, ShipPositionColumns, "C");
      }

      break;
    }

    case 1:
    {
      while (!isValueCorrect)
      {
        // Battleship of size 4
        unsigned int ShipSize = 4;

        Display_Game(PlayerOneBoard, PlayerTwoBoard, PlayerOneShipsRemaining, PlayerTwoShipsRemaining, std::to_string(NumberOfPlayers), AIDifficulty, false);

        // User prompt for ship locations
        std::cout << "\n\nEnter the " << ShipSize << " grid locations for the Battleship: ";

        // Using std::getline so string with spaces is read in
        std::getline(std::cin, Input);

        // If error checking returns false then continue to next iteration
        if (!Error_Checking_Ordering_Orientation_On_User_Ship_Positions(PlayerOneBoard, Input, ShipPositionRows, ShipPositionColumns, ShipSize))
          continue;

        isValueCorrect = true;

        // Place ship on UserBoard using the CurrentShipPositions_ints positions and marking with 'B' for battleship
        Place_Ship(PlayerOneBoard, ShipPositionRows, ShipPositionColumns, "B");
      }
      break;
    }

    case 2:
    {
      while (!isValueCorrect)
      {
        // Destroyer of size 3
        unsigned int ShipSize = 3;

        Display_Game(PlayerOneBoard, PlayerTwoBoard, PlayerOneShipsRemaining, PlayerTwoShipsRemaining, std::to_string(NumberOfPlayers), AIDifficulty, false);

        // User prompt for ship locations
        std::cout << "\n\nEnter the " << ShipSize << " grid locations for the Destroyer: ";

        // Using std::getline so string with spaces is read in
        std::getline(std::cin, Input);

        // If error checking returns false then continue to next iteration
        if (!Error_Checking_Ordering_Orientation_On_User_Ship_Positions(PlayerOneBoard, Input, ShipPositionRows, ShipPositionColumns, ShipSize))
          continue;

        isValueCorrect = true;

        // Place ship on UserBoard using the CurrentShipPositions_ints positions and marking with 'D' for destroyer
        Place_Ship(PlayerOneBoard, ShipPositionRows, ShipPositionColumns, "D");
      }

      break;
    }

    case 3:
    {
      while (!isValueCorrect)
      {
        // Submarine of size 3
        unsigned int ShipSize = 3;

        Display_Game(PlayerOneBoard, PlayerTwoBoard, PlayerOneShipsRemaining, PlayerTwoShipsRemaining, std::to_string(NumberOfPlayers), AIDifficulty, false);

        // User prompt for ship locations
        std::cout << "\n\nEnter the " << ShipSize << " grid locations for the Submarine: ";

        // Using std::getline so string with spaces is read in
        std::getline(std::cin, Input);

        // If error checking returns false then continue to next iteration
        if (!Error_Checking_Ordering_Orientation_On_User_Ship_Positions(PlayerOneBoard, Input, ShipPositionRows, ShipPositionColumns, ShipSize))
          continue;

        isValueCorrect = true;

        // Place ship on UserBoard using the CurrentShipPositions_ints positions and marking with 'S' for submarine
        Place_Ship(PlayerOneBoard, ShipPositionRows, ShipPositionColumns, "S");
      }

      break;
    }

    case 4:
    {
      while (!isValueCorrect)
      {
        // Patrol Boat of size 2
        unsigned int ShipSize = 2;

        Display_Game(PlayerOneBoard, PlayerTwoBoard, PlayerOneShipsRemaining, PlayerTwoShipsRemaining, std::to_string(NumberOfPlayers), AIDifficulty, false);

        // User prompt for ship locations
        std::cout << "\n\nEnter the " << ShipSize << " grid locations for the Patrol Boat: ";

        // Using std::getline so string with spaces is read in
        std::getline(std::cin, Input);

        // If error checking returns false then continue to next iteration
        if (!Error_Checking_Ordering_Orientation_On_User_Ship_Positions(PlayerOneBoard, Input, ShipPositionRows, ShipPositionColumns, ShipSize))
          continue;

        isValueCorrect = true;

        // Place ship on UserBoard using the CurrentShipPositions_ints positions and marking with 'P' for patrol boat
        Place_Ship(PlayerOneBoard, ShipPositionRows, ShipPositionColumns, "P");
      }

      break;
    }

    default:
      // Error message stating where it has occurred
      std::cout << "Ask_User_For_Ship_Positions() switch statement error\n";
      break;
    }
  }
}

void Display_Game(const std::vector<std::vector<std::string>> &PlayerOneBoard,
                  const std::vector<std::vector<std::string>> &PlayerTwoBoard,
                  const std::map<std::string, unsigned int> &PlayerOneShipsRemaining,
                  const std::map<std::string, unsigned int> &PlayerTwoShipsRemaining,
                  const std::string &NumberOfPlayers,
                  const std::string &AIDifficulty,
                  const bool &GameOver)
{
  // Start from blank terminal
  Clear_Terminal();

  // Top Row of both boards
  std::cout << "\t\t  PLAYER ONE\t\t\t\t\t\t                                          PLAYER TWO\n";

  std::cout << (char)218 << (char)196 << (char)196 << (char)196;

  for (unsigned int i = 0; i < 10; i++)
    std::cout << (char)194 << (char)196 << (char)196 << (char)196;

  std::cout << (char)191 << "\t\t\t\t\t\t\t" << (char)218 << (char)196 << (char)196 << (char)196;

  for (unsigned int i = 0; i < 10; i++)
    std::cout << (char)194 << (char)196 << (char)196 << (char)196;

  std::cout << (char)191 << '\n';

  std::cout << (char)179 << "   " << (char)179 << " A " << (char)179  << " B " << (char)179 << " C " << (char)179 << " D " << (char)179 << " E "
            << (char)179 << " F " << (char)179 << " G " << (char)179 << " H " << (char)179 << " I " << (char)179 << " J " << (char)179
            << "\t\t\t BATTLESHIPS\t\t\t"
            << (char)179 << "   " << (char)179 << " A " << (char)179  << " B " << (char)179 << " C " << (char)179 << " D " << (char)179 << " E "
            << (char)179 << " F " << (char)179 << " G " << (char)179 << " H " << (char)179 << " I " << (char)179 << " J " << (char)179 << '\n';

  // Main parts of both boards and centre information
  for (unsigned int i = 0; i < 10; i++)
  {
    // Player One Board horizontal dividers
    std::cout << (char)195 << (char)196 << (char)196 << (char)196;

    for (unsigned int j = 0; j < 10; j++)
      std::cout << (char)197 << (char)196 << (char)196 << (char)196;

    std::cout << (char)180;

    // Centre information Part 1
    switch (i)
    {
    case 3:
      std::cout << "\tCarrier\t\t\t\t      Carrier\t";
    break;

    case 5: // Battleship
      std::cout << '\t';
      for (unsigned int j = 0; j < 4; j++)
      {
        if (j < PlayerOneShipsRemaining.at("B"))
          std::cout << (char)178 << (char)178 << (char)178 << ' ';
        else
          std::cout << (char)176 << (char)176 << (char)176 << ' ';
      }
      std::cout << "\t      ";
      for (unsigned int j = 0; j < 4; j++)
      {
        if (j < (4-PlayerTwoShipsRemaining.at("B")))
          std::cout << (char)176 << (char)176 << (char)176 << ' ';
        else
          std::cout << (char)178 << (char)178 << (char)178 << ' ';
      }
      std::cout << '\t';
    break;

    case 6:
      std::cout << "\tDestroyer\t\t\t    Destroyer\t";
    break;

    case 8: // Submarine
      std::cout << '\t';
      for (unsigned int j = 0; j < 3; j++)
      {
        if (j < PlayerOneShipsRemaining.at("S"))
          std::cout << (char)178 << (char)178 << (char)178 << ' ';
        else
          std::cout << (char)176 << (char)176 << (char)176 << ' ';
      }
      std::cout << "\t\t\t  ";
      for (unsigned int j = 0; j < 3; j++)
      {
        if (j < (3-PlayerTwoShipsRemaining.at("S")))
          std::cout << (char)176 << (char)176 << (char)176 << ' ';
        else
          std::cout << (char)178 << (char)178 << (char)178 << ' ';
      }
      std::cout << '\t';
    break;

    case 9:
      std::cout << "\tPatrol Boat\t\t\t  Patrol Boat\t";
    break;

    default:
      std::cout << "\t\t\t\t\t\t\t";
    break;
    }

    // Player Two Board horizontal dividers
    std::cout << (char)195 << (char)196 << (char)196 << (char)196;

    for (unsigned int j = 0; j < 10; j++)
      std::cout << (char)197 << (char)196 << (char)196 << (char)196;

    std::cout << (char)180 << '\n';

    // Player One Board
    std::cout << (char)179 << ' ' << i << ' ' << (char)179;
    for (unsigned int j = 0; j < 10; j++)
    {
      if (PlayerOneBoard[i][j] == "C" || PlayerOneBoard[i][j] == "B" || PlayerOneBoard[i][j] == "D" || PlayerOneBoard[i][j] == "S" || PlayerOneBoard[i][j] == "P")
        std::cout << (char)178 << (char)178 << (char)178 << (char)179;
      else if (PlayerOneBoard[i][j] == "Hit")
        std::cout << (char)176 << (char)176 << (char)176 << (char)179;
      else if (PlayerOneBoard[i][j] == "Miss")
        std::cout << ' ' << (char)250 << ' ' << (char)179;
      else
        std::cout << "   " << (char)179;
    }

    // Centre Information Part 2
    switch (i)
    {
    case 0:
      if (NumberOfPlayers == "N/A")
        std::cout << "\t\t     # of Players = " << NumberOfPlayers << "\t\t\t";
      else
        std::cout << "\t\t       # of Players = " << NumberOfPlayers << "\t\t\t";
    break;

    case 1:
        std::cout << "\t\t     AI Difficulty = " << AIDifficulty << "\t\t";
    break;

    case 3: // Carrier
      std::cout << '\t';
      for (unsigned int j = 0; j < 5; j++)
      {
        if (j < PlayerOneShipsRemaining.at("C"))
          std::cout << (char)178 << (char)178 << (char)178 << ' ';
        else
          std::cout << (char)176 << (char)176 << (char)176 << ' ';
      }
      std::cout << "\t  ";
      for (unsigned int j = 0; j < 5; j++)
      {
        if (j < (5-PlayerTwoShipsRemaining.at("C")))
          std::cout << (char)176 << (char)176 << (char)176 << ' ';
        else
          std::cout << (char)178 << (char)178 << (char)178 << ' ';
      }
      std::cout << '\t';
    break;

    case 4:
      std::cout << "\tBattleship\t\t\t   Battleship\t";
    break;

    case 6: // Destroyer
      std::cout << '\t';
      for (unsigned int j = 0; j < 3; j++)
      {
        if (j < PlayerOneShipsRemaining.at("D"))
          std::cout << (char)178 << (char)178 << (char)178 << ' ';
        else
          std::cout << (char)176 << (char)176 << (char)176 << ' ';
      }
      std::cout << "\t\t\t  ";
      for (unsigned int j = 0; j < 3; j++)
      {
        if (j < (3-PlayerTwoShipsRemaining.at("D")))
          std::cout << (char)176 << (char)176 << (char)176 << ' ';
        else
          std::cout << (char)178 << (char)178 << (char)178 << ' ';
      }
      std::cout << '\t';
    break;

    case 7:
      std::cout << "\tSubmarine\t\t\t    Submarine\t";
    break;

    case 9: // Patrol Boat
      std::cout << '\t';
      for (unsigned int j = 0; j < 2; j++)
      {
        if (j < PlayerOneShipsRemaining.at("P"))
          std::cout << (char)178 << (char)178 << (char)178 << ' ';
        else
          std::cout << (char)176 << (char)176 << (char)176 << ' ';
      }
      std::cout << "\t\t\t      ";
      for (unsigned int j = 0; j < 2; j++)
      {
        if (j < (2-PlayerTwoShipsRemaining.at("P")))
          std::cout << (char)176 << (char)176 << (char)176 << ' ';
        else
          std::cout << (char)178 << (char)178 << (char)178 << ' ';
      }
      std::cout << '\t';
    break;

    default:
      std::cout << "\t\t\t\t\t\t\t";
    break;
    }

    // Player Two Board
    std::cout << (char)179 << ' ' << i << ' ' << (char)179;
    for (unsigned int j = 0; j < 10; j++)
    {
      if ((GameOver || NumberOfPlayers == "0") && (PlayerTwoBoard[i][j] == "C" || PlayerTwoBoard[i][j] == "B" || PlayerTwoBoard[i][j] == "D" || PlayerTwoBoard[i][j] == "S" || PlayerTwoBoard[i][j] == "P"))
        std::cout << (char)178 << (char)178 << (char)178 << (char)179;
      else if (PlayerTwoBoard[i][j] == "Hit")
        std::cout << (char)176 << (char)176 << (char)176 << (char)179;
      else if (PlayerTwoBoard[i][j] == "Miss")
        std::cout << ' ' << (char)250 << ' ' << (char)179;
      else
        std::cout << "   " << (char)179;
    }
    std::cout << '\n';
  }

  // Bottom row of both boards
  std::cout << (char)192 << (char)196 << (char)196 << (char)196;

  for (unsigned int j = 0; j < 10; j++)
    std::cout << (char)193 << (char)196 << (char)196 << (char)196;

  std::cout << (char)217 << "\t\t\t\t\t\t\t" << (char)192 << (char)196 << (char)196 << (char)196;

  for (unsigned int j = 0; j < 10; j++)
    std::cout << (char)193 << (char)196 << (char)196 << (char)196;

  std::cout << (char)217;
}

void Clear_Terminal(void)
{
  // Windows API method taken from https://www.cplusplus.com/articles/4z18T05o

  HANDLE                     hStdOut;
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  DWORD                      count;
  DWORD                      cellCount;
  COORD                      homeCoords = { 0, 0 };

  hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
  if (hStdOut == INVALID_HANDLE_VALUE) return;

  // Get the number of cells in the current buffer
  if (!GetConsoleScreenBufferInfo( hStdOut, &csbi )) return;
  cellCount = csbi.dwSize.X *csbi.dwSize.Y;

  // Fill the entire buffer with spaces
  if (!FillConsoleOutputCharacter(
    hStdOut,
    (TCHAR) ' ',
    cellCount,
    homeCoords,
    &count
    )) return;

  // Fill the entire buffer with the current colors and attributes
  if (!FillConsoleOutputAttribute(
    hStdOut,
    csbi.wAttributes,
    cellCount,
    homeCoords,
    &count
    )) return;

  // Move the cursor home
  SetConsoleCursorPosition( hStdOut, homeCoords );
}

bool Error_Checking_Ordering_Orientation_On_User_Ship_Positions(std::vector<std::vector<std::string>> &PlayerOneBoard,
                                                                std::string &Input,
                                                                std::vector<unsigned int> &ShipPositionRows,
                                                                std::vector<unsigned int> &ShipPositionColumns,
                                                                const unsigned int &ShipSize)
{
  // capitalise and separate single string in to command strings
  Capitalise_Word(Input);

  if (Input.back() != ' ')
    Input.push_back(' ');

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

  // check right number of commands
  if (IndividualCoordinates.size() != ShipSize)
    return false;

  // check first character is letter and second is number and each command is size of 2
  for (unsigned int i = 0; i < IndividualCoordinates.size(); i++)
  {
    if (IndividualCoordinates[i].size() != 2)
      return false;

    if (IndividualCoordinates[i][0] < 'A' || IndividualCoordinates[i][0] > 'J')
      return false;

    if (IndividualCoordinates[i][1] < '0' || IndividualCoordinates[i][1] > '9')
      return false;
  }

  // check whether letters or numbers of all commands are identical
  bool LettersIdentical = true, NumbersIdentical = true;

  for (unsigned int i = 1; i < IndividualCoordinates.size(); i++)
  {
    if (IndividualCoordinates[i][0] != IndividualCoordinates[0][0])
      LettersIdentical = false;

    if (IndividualCoordinates[i][1] != IndividualCoordinates[0][1])
      NumbersIdentical = false;
  }

  if (LettersIdentical && !NumbersIdentical)
  {
    // check that number is increment by one each time
    for (unsigned int i = 1; i < IndividualCoordinates.size(); i++)
      if (IndividualCoordinates[i][1] != (IndividualCoordinates[i-1][1] + 1))
        return false;

    // thus ShipOrientation = "Vertical";
  }

  else if (NumbersIdentical && !LettersIdentical)
  {
    // check that letter is increment by one each time
    for (unsigned int i = 1; i < IndividualCoordinates.size(); i++)
      if (IndividualCoordinates[i][0] != (IndividualCoordinates[i-1][0] + 1))
        return false;

    // thus ShipOrientation = "Horizontal";
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
    // Check if CurrentShipPositions_ints position is already occupied by another ship
    if (PlayerOneBoard[ShipPositionRows[i]][ShipPositionColumns[i]] == "C" ||
        PlayerOneBoard[ShipPositionRows[i]][ShipPositionColumns[i]] == "B" ||
        PlayerOneBoard[ShipPositionRows[i]][ShipPositionColumns[i]] == "D" ||
        PlayerOneBoard[ShipPositionRows[i]][ShipPositionColumns[i]] == "S" ||
        PlayerOneBoard[ShipPositionRows[i]][ShipPositionColumns[i]] == "P")
      return false;
  }

  return true;
}

void Place_Ship(std::vector<std::vector<std::string>> &anyBoard,
                const std::vector<unsigned int> &ShipPositionRows,
                const std::vector<unsigned int> &ShipPositionColumns,
                const std::string ShipName)
{
  // Go through all CurrentShipPositions positions and overwrite its value with the ship name
  for (unsigned int i = 0; i < ShipPositionRows.size(); i++)
    anyBoard[ShipPositionRows[i]][ShipPositionColumns[i]] = ShipName;
}

void Ask_Computer_For_Ship_Positions(std::vector<std::vector<std::string>> &ComputerBoard)
{
  for (unsigned int i = 0; i < 5; i++)
  {
    bool isValueCorrect = false;

    switch (i)
    {
    case 0:
    {
      while (!isValueCorrect)
      {
        std::vector<unsigned int> ShipPositionRows, ShipPositionColumns;
        // Carrier of size 5
        unsigned int ShipSize = 5;

        // Ask computer for ship position
        Get_Computer_Ship_Positions(ShipPositionRows, ShipPositionColumns, ShipSize);

        // If error checking returns false then continue to next iteration
        if (!Error_Checking_On_Computer_Ship_Positions(ComputerBoard, ShipPositionRows, ShipPositionColumns))
          continue;

        isValueCorrect = true;

        // Place ship on ComputerBoard using the CurrentShipPositions_ints positions and marking with 'C' for carrier
        Place_Ship(ComputerBoard, ShipPositionRows, ShipPositionColumns, "C");
      }

      break;
    }

    case 1:
    {
      while (!isValueCorrect)
      {
        std::vector<unsigned int> ShipPositionRows, ShipPositionColumns;

        // Battleship of size 4
        unsigned int ShipSize = 4;

        // Ask computer for ship position
        Get_Computer_Ship_Positions(ShipPositionRows, ShipPositionColumns, ShipSize);

        // If error checking returns false then continue to next iteration
        if (!Error_Checking_On_Computer_Ship_Positions(ComputerBoard, ShipPositionRows, ShipPositionColumns))
          continue;

        isValueCorrect = true;


        // Place ship on ComputerBoard using the CurrentShipPositions_ints positions and marking with 'B' for battleship
        Place_Ship(ComputerBoard, ShipPositionRows, ShipPositionColumns, "B");
      }

      break;
    }

    case 2:
    {
      while (!isValueCorrect)
      {
        std::vector<unsigned int> ShipPositionRows, ShipPositionColumns;

        // Destroyer of size 3
        unsigned int ShipSize = 3;

        // Ask computer for ship position
        Get_Computer_Ship_Positions(ShipPositionRows, ShipPositionColumns, ShipSize);

        // If error checking returns false then continue to next iteration
        if (!Error_Checking_On_Computer_Ship_Positions(ComputerBoard, ShipPositionRows, ShipPositionColumns))
          continue;

        isValueCorrect = true;

        // Place ship on ComputerBoard using the CurrentShipPositions_ints positions and marking with 'D' for destroyer
        Place_Ship(ComputerBoard, ShipPositionRows, ShipPositionColumns, "D");
      }

      break;
    }

    case 3:
    {
      while (!isValueCorrect)
      {
        std::vector<unsigned int> ShipPositionRows, ShipPositionColumns;

        // Submarine of size 3
        unsigned int ShipSize = 3;

        // Ask computer for ship position
        Get_Computer_Ship_Positions(ShipPositionRows, ShipPositionColumns, ShipSize);

        // If error checking returns false then continue to next iteration
        if (!Error_Checking_On_Computer_Ship_Positions(ComputerBoard, ShipPositionRows, ShipPositionColumns))
          continue;

        isValueCorrect = true;

        // Place ship on ComputerBoard using the CurrentShipPositions_ints positions and marking with 'S' for submarine
        Place_Ship(ComputerBoard, ShipPositionRows, ShipPositionColumns, "S");
      }

      break;
    }

    case 4:
    {
      while (!isValueCorrect)
      {
        std::vector<unsigned int> ShipPositionRows, ShipPositionColumns;

        // Patrol Boat of size 2
        unsigned int ShipSize = 2;

        // Ask computer for ship position
        Get_Computer_Ship_Positions(ShipPositionRows, ShipPositionColumns, ShipSize);

        // If error checking returns false then continue to next iteration
        if (!Error_Checking_On_Computer_Ship_Positions(ComputerBoard, ShipPositionRows, ShipPositionColumns))
          continue;

        isValueCorrect = true;

        // Place ship on ComputerBoard using the CurrentShipPositions_ints positions and marking with 'P' for patrol boat
        Place_Ship(ComputerBoard, ShipPositionRows, ShipPositionColumns, "P");
      }

      break;
    }

    default:
      // Error message stating where it has occurred
      std::cout << "Ask_Computer_For_Ship_Positions() switch statement error\n";
      break;
    }
  }
}

void Get_Computer_Ship_Positions(std::vector<unsigned int> &ShipPositionRows,
                                 std::vector<unsigned int> &ShipPositionColumns,
                                 const unsigned int &ShipSize)
{
  // Singles represents the column number; Tens the row number; and the FirstValue
  // is the first value of the gird positions when ordered in ascending order
  unsigned int Column, Row;

  // Use std::rand() to randomly choose between a vertical or horizontal orientation
  if ((std::rand() % 2) == 0)
  {
    //ShipOrientation = "Horizontal";

    // A max column number exists, as ship is horizontal, which is linked with the size of the ship
    // with the assumption being this value will be the first and smallest of the positions
    Column = std::rand() % (11 - ShipSize);

    // Any row number allowed as ship is horizontal
    Row = std::rand() % 10;

    // Horizontal positions have a difference in columns of 1 between positions
    for (unsigned int i = 0; i < ShipSize; i++)
    {
      ShipPositionRows.push_back(Row);
      ShipPositionColumns.push_back(Column+i);
    }
  }

  else
  {
    //ShipOrientation = "Vertical";

    // Any column number allowed as ship is vertical
    Column = std::rand() % 10;

    // A max row number exists, as ship is vertical, which is linked with the size of the ship
    // with the assumption being this value will be the first and smallest of the positions
    Row = std::rand() % (11 - ShipSize);

    // Vertical positions have a difference of ComputerBoard.size(), which is 10, between positions
    for (unsigned int i = 0; i < ShipSize; i++)
    {
      ShipPositionRows.push_back(Row+i);
      ShipPositionColumns.push_back(Column);
    }
  }
}

bool Error_Checking_On_Computer_Ship_Positions(const std::vector<std::vector<std::string>> &ComputerBoard,
                                               const std::vector<unsigned int> &ShipPositionRows,
                                               const std::vector<unsigned int> &ShipPositionColumns)
{
  // Only check required is if any of the ship positions are already occupied by another ship
  for (unsigned int i = 0; i < ShipPositionRows.size(); i++)
  {
    // Check if CurrentShipPositions_ints position is already occupied by another ship
    if (ComputerBoard[ShipPositionRows[i]][ShipPositionColumns[i]] == "C" ||
        ComputerBoard[ShipPositionRows[i]][ShipPositionColumns[i]] == "B" ||
        ComputerBoard[ShipPositionRows[i]][ShipPositionColumns[i]] == "D" ||
        ComputerBoard[ShipPositionRows[i]][ShipPositionColumns[i]] == "S" ||
        ComputerBoard[ShipPositionRows[i]][ShipPositionColumns[i]] == "P")
      return false;
  }

  return true;
}

bool Winning_Conditions_Met(const std::vector<std::vector<std::string>> &PlayerOneBoard,
                            const std::vector<std::vector<std::string>> &PlayerTwoBoard)
{
  bool ArePlayerOneShipsPresent = false;
  // If there are any ship letter on the board then winning condition is not met
  for (unsigned int i = 0; i < 10; i++)
    for (unsigned int j = 0; j < 10; j++)
      if (PlayerOneBoard[i][j] == "C" || PlayerOneBoard[i][j] == "B" || PlayerOneBoard[i][j] == "D" || PlayerOneBoard[i][j] == "S" || PlayerOneBoard[i][j] == "P")
        ArePlayerOneShipsPresent = true;

  bool ArePlayerTwoShipsPresent = false;
  for (unsigned int i = 0; i < 10; i++)
    for (unsigned int j = 0; j < 10; j++)
      if (PlayerTwoBoard[i][j] == "C" || PlayerTwoBoard[i][j] == "B" || PlayerTwoBoard[i][j] == "D" || PlayerTwoBoard[i][j] == "S" || PlayerTwoBoard[i][j] == "P")
        ArePlayerTwoShipsPresent = true;

  // Then there are no ships left and winning condition as been met
  if (!ArePlayerOneShipsPresent || !ArePlayerTwoShipsPresent)
    return true;
  else
    return false;
}

void Toggle_Player(std::string &CurrentPlayer)
{
  if (CurrentPlayer == "PLAYER ONE")
    CurrentPlayer = "PLAYER TWO";

  else
    CurrentPlayer = "PLAYER ONE";
}

int Ask_User_For_Next_Command(const std::vector<std::vector<std::string>> &PlayerOneBoard,
                              const std::vector<std::vector<std::string>> &PlayerTwoBoard,
                              const unsigned int &NumberOfPlayers,
                              const std::string &AIDifficulty,
                              const std::map<std::string, unsigned int> &PlayerOneShipsRemaining,
                              const std::map<std::string, unsigned int> &PlayerTwoShipsRemaining)
{
  bool IsValueCorrect = false; // Flag for if input value is valid
  std::string Input;
  unsigned int Row, Column;

  while (!IsValueCorrect)
  {
    Display_Game(PlayerOneBoard, PlayerTwoBoard, PlayerOneShipsRemaining, PlayerTwoShipsRemaining, std::to_string(NumberOfPlayers), AIDifficulty, false);
    // Prompt user for next command that will be the next grid position to attack
    std::cout << "\n\nPlayer One, please enter your next command ";

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
  // to get a value from 0 to 99 representing all values on the board
  return Row*10 + Column;
}

int Ask_Computer_For_Next_Command(const std::vector<std::vector<std::string>> &PlayerOneBoard,
                                  const std::vector<std::vector<std::string>> &PlayerTwoBoard,
                                  std::vector<unsigned int> &PlayerOneValidMovesRemaining,
                                  std::vector<unsigned int> &PlayerTwoValidMovesRemaining,
                                  const unsigned int &NumberOfPlayers,
                                  const std::string &CurrentPlayer,
                                  const std::string &AIDifficulty,
                                  const std::map<std::string, unsigned int> &PlayerOneShipsRemaining,
                                  const std::map<std::string, unsigned int> &PlayerTwoShipsRemaining)
{
  std::vector<unsigned int> ValidMovesRemaining;

  if (CurrentPlayer == "PLAYER ONE")
    ValidMovesRemaining = PlayerOneValidMovesRemaining;
  else
    ValidMovesRemaining = PlayerTwoValidMovesRemaining;

  Display_Game(PlayerOneBoard, PlayerTwoBoard, PlayerOneShipsRemaining, PlayerTwoShipsRemaining, std::to_string(NumberOfPlayers), AIDifficulty, false);
  // Computer randomly chooses a value from 0 to 99

  unsigned int ComputerCommand = ValidMovesRemaining[std::rand() % ValidMovesRemaining.size()];
  auto CommandPosition = std::find(ValidMovesRemaining.begin(), ValidMovesRemaining.end(), ComputerCommand);
  ValidMovesRemaining.erase(CommandPosition);

  if (CurrentPlayer == "PLAYER ONE")
    PlayerOneValidMovesRemaining = ValidMovesRemaining;
  else
    PlayerTwoValidMovesRemaining = ValidMovesRemaining;

  return ComputerCommand;
}

void Execute_Next_Turn(std::vector<std::vector<std::string>> &PlayerOneBoard,
                       std::vector<std::vector<std::string>> &PlayerTwoBoard,
                       std::map<std::string, unsigned int> &PlayerOneShipsRemaining,
                       std::map<std::string, unsigned int> &PlayerTwoShipsRemaining,
                       const std::string &CurrentPlayer,
                       const unsigned int &Command)
{
  // Row and column number for Command on the board
  unsigned int Row = Command / 10;
  unsigned int Column = Command % 10;

  // Check which player is attacking and therefore is being attacked
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

void Display_Game_Over_Message(const std::string &CurrentPlayer,
                               const unsigned int &NumberOfTurns,
                               bool &GameIsRunning,
                               const std::vector<std::vector<std::string>> &PlayerOneBoard,
                               const std::vector<std::vector<std::string>> &PlayerTwoBoard,
                               const unsigned int &NumberOfPlayers,
                               const std::string &AIDifficulty,
                               const std::map<std::string, unsigned int> &PlayerOneShipsRemaining,
                               const std::map<std::string, unsigned int> &PlayerTwoShipsRemaining)
{
  Display_Game(PlayerOneBoard, PlayerTwoBoard, PlayerOneShipsRemaining, PlayerTwoShipsRemaining, std::to_string(NumberOfPlayers), AIDifficulty, true);

  // CurrentPlayer is the winner of the game as player toggle as not been
  // triggered since last attack and gamer over check
  if (CurrentPlayer == "PLAYER ONE")
    std::cout << "\n\n\t\t\t\t\t\t\t\t  GAME OVER\n\n\t\t\t\t\t       Player One has won! The game lasted " << NumberOfTurns << " turns.";

  else
    std::cout << "\n\n\t\t\t\t\t\t\t\t  GAME OVER\n\n\t\t\t\t\t       Player Two has won! The game lasted " << NumberOfTurns << " turns.";

  std::cout << "\n\n\t\t\t\t\t     Press 'Q' to quit OR any other key to play again...";

  // Gets key pressed and then checks and clears terminal window if replaying
  char Decision = _getch();

  if (Decision == 'q')
    GameIsRunning = false;

  else
    // Start from blank terminal
    Clear_Terminal();
}
