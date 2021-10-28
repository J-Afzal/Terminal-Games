//
//  @File: TicTacToe.cpp
//  @Author: Junaid Afzal
//

#include "TicTacToe.hpp"
#include <iostream>
#include <ctime>
#include <limits>
#include <conio.h>

void Setup_Game(unsigned int &NumberOfTurns,
                unsigned int &CurrentPlayer,
                unsigned int &NumberOfPlayers,
                unsigned int &UserXO,
                std::vector<std::vector<std::string>> &GameData)
{
  // Set seed to system time at 0 to create pseudo random numbers
  std::srand((unsigned int)std::time(0));

  // Assign CurrentPlayer, and thus player to play first, randomly
  if (std::rand() % 2 == 0)
    CurrentPlayer = 'X';
  else
    CurrentPlayer = 'O';

  // The for loops add the 3 rows and columns to the grid and the the appropriate grid values
  for (unsigned int i = 0, GridNumber = 0; i < 3; i++)
  {
    std::vector<std::string> Rows;
    GameData.push_back(Rows);

    for (int j = 0; j < 3; j++, GridNumber++)
      GameData[i].push_back(std::to_string(GridNumber));
  }

  // Ask user for number of players
  NumberOfPlayers = Get_Number_Of_Players();

  // If only one human user then ask them for which player they want to be (X or O)
  if (NumberOfPlayers == 1)
    UserXO = Get_User_X_O_Choice(NumberOfPlayers);
}

int Get_Number_Of_Players(void)
{
  bool IsValueCorrect = false; // Flag for if input value is valid
  int NumberOfPlayers = 0;

  while (!IsValueCorrect)
  {
    Clear_Terminal();
    std::cout << "--------------------TicTacToe--------------------";
    std::cout << "\n\nEnter the number of human players ";

    std::cin >> NumberOfPlayers;

    if (std::cin.fail()) // Check if cin failed
    {
      // Clear buffer and retry
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      continue;
    }

    else if (NumberOfPlayers < 0 || NumberOfPlayers > 2) // Only 0, 1 and 2 players allowed
    {
      // Clear buffer and retry
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      continue;
    }

    else
      IsValueCorrect = true;
  }

  // Clear buffer
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  return NumberOfPlayers;
}

int Get_User_X_O_Choice(const unsigned int &NumberOfPlayers)
{
  bool IsValueCorrect = false; // Flag for if input value is valid
  char UserXOChoice = 0;

  while (!IsValueCorrect)
  {
    Clear_Terminal();
    std::cout << "--------------------TicTacToe--------------------";
    std::cout << "\n\nEnter the number of human players " << NumberOfPlayers;
    std::cout << "\n\nEnter you player counter (X or O) ";

    std::cin >> UserXOChoice;
    // Check if cin failed
    if (std::cin.fail())
    {
      // Clear buffer and retry
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      continue;
    }
    // Only X and O inputs allowed
    else if (UserXOChoice != 'X' && UserXOChoice != 'x' && UserXOChoice != 'O' && UserXOChoice != 'o')
    {
      // Clear buffer and retry
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      continue;
    }

    else // all tests passed then input so is valid
      IsValueCorrect = true;
  }

  // Clear buffer
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  // Capitalise to simplify proceeding code
  if (UserXOChoice == 'o')
    UserXOChoice = 'O';

  if (UserXOChoice == 'x')
    UserXOChoice = 'X';

  return UserXOChoice;
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
  if (GameData[0][0] == GameData[0][1] && GameData[0][1] == GameData[0][2])
    return true;

  else if (GameData[1][0] == GameData[1][1] && GameData[1][1] == GameData[1][2])
    return true;

  else if (GameData[2][0] == GameData[2][1] && GameData[2][1] == GameData[2][2])
    return true;

  // Check verticals
  else if (GameData[0][0] == GameData[1][0] && GameData[1][0] == GameData[2][0])
    return true;

  else if (GameData[0][1] == GameData[1][1] && GameData[1][1] == GameData[2][1])
    return true;

  else if (GameData[0][2] == GameData[1][2] && GameData[1][2] == GameData[2][2])
    return true;

  // Check diagonals
  else if (GameData[0][0] == GameData[1][1] && GameData[1][1] == GameData[2][2])
    return true;

  else if (GameData[2][0] == GameData[1][1] && GameData[1][1] == GameData[0][2])
    return true;

  else
    return false;
}

void Display_Game(const std::vector<std::vector<std::string>> &GameData)
{
  // Start from blank console
  Clear_Terminal();

  std::cout << "--------------------TicTacToe--------------------\n\n";
  // Iterate across whole grid and output its value
  for (unsigned int i = 0; i < 3; i++)
  {
    for (unsigned int j = 0; j < 3; j++)
    {
      std::cout << std::left << " " << GameData[i][j] << " ";

      // Vertical bars
      if (j == 0 || j == 1)
        std::cout << "│";
    }

    // Horizontal bars
    if (i == 0 || i == 1)
    {
      std::cout << '\n';

      for (unsigned int k = 0; k <= 10; k++)
      {
        if (k == 3 || k == 7)
          std::cout << "┼";

        else
          std::cout << "─";
      }

      std::cout << '\n';
    }
  }
}

void Clear_Terminal(void)
{
  // ***Better alternative needed***
  // 100 new lines to clear console
  std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}

void Toggle_Player(unsigned int &CurrentPlayer)
{
  if (CurrentPlayer == 'X')
    CurrentPlayer = 'O';

  else
    CurrentPlayer = 'X';
}

void Ask_User_For_Next_Input(std::vector<std::vector<std::string>> &GameData,
                             const unsigned int &CurrentPlayer)
{
  bool IsValueCorrect = false; // Flag for if input value is valid
  int UserCommand, Row, Column;

  while (!IsValueCorrect)
  {
    Display_Game(GameData);
    std::cout << "\n\nPlayer " << (char)CurrentPlayer << " enter command ";

    std::cin >> UserCommand;

    if (std::cin.fail()) // Check if cin failed
    {
      // Clear buffer, set flag to false and retry
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      continue;
    }

    else if (UserCommand < 0 || UserCommand > 8) // Check if command is within range of grid
    {
      // Clear buffer, set flag to false and retry
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      continue;
    }

    Column = UserCommand % 3;
    Row = UserCommand / 3;

    // Check if command has already been called by a player previously as it will contain and X or O
    if (GameData[Row][Column] != "X" && GameData[Row][Column] != "O")
      IsValueCorrect = true;
  }

  // Go to the command position in the grid and overwrite with the current player
  GameData[Row][Column] = CurrentPlayer;

  // Clear buffer
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void Ask_Computer_For_Next_Input(std::vector<std::vector<std::string>> &GameData,
                                 const unsigned int &CurrentPlayer)
{
  bool IsValueCorrect = false; // Flag for if input value is valid
  unsigned int ComputerCommand, Row, Column;

  while (!IsValueCorrect)
  {
    // Computer is dumb and picks a pseudo random number as command
    ComputerCommand = std::rand() % 9;

    Column = ComputerCommand % 3;
    Row = ComputerCommand / 3;

    // Check if command has already been called by a player previously as it will contain and X or O
    if (GameData[Row][Column] != "X" && GameData[Row][Column] != "O")
      IsValueCorrect = true;
  }

  Display_Game(GameData);
  // Output a message which is similar to a human player command message
  std::cout << "\n\nComputer " << (char)CurrentPlayer << " entered command " << ComputerCommand << '\n';

  // Go to the command position in the grid and overwrite with the current player
  GameData[Row][Column] = CurrentPlayer;
}

void Display_Game_Over_Message(const unsigned int &NumberOfTurns,
                               const std::vector<std::vector<std::string>> &GameData,
                               const unsigned int &CurrentPlayer,
                               bool &GameIsRunning)
{
  Display_Game(GameData);

  // Winner will be current player as Toggle_Player() function has not been called
  // from receiving input and determining winner
  if (Winning_Conditions_Met(GameData))
    std::cout << "\n\nGAME OVER\n\n" << (char)CurrentPlayer << " has won! The game lasted " << NumberOfTurns << " turns.";

  // No winner so a draw
  else
    std::cout << "\n\nGAME OVER\n\nIt is a draw! The game lasted " << NumberOfTurns << " turns.";

  std::cout << "\n\nPress 'Q' to quit the game OR press any other key to play again...";

  // Gets key pressed and then checks and clears terminal window if replaying
  char Decision = _getch();

  if (Decision == 'q')
    GameIsRunning = false;

  else
    // Start from blank console
    Clear_Terminal();
}
