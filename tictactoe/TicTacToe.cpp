//
//  @File: TicTacToe.cpp
//  @Author: Junaid Afzal
//



// to prevent max error with windows.h redefining it
// https://stackoverflow.com/questions/7035023/stdmax-expected-an-identifier/7035078
#define NOMINMAX
#include <windows.h>

#include "TicTacToe.hpp"
#include <iostream>
#include <ctime>
#include <limits>
#include <algorithm>
#include <conio.h>
#include <iomanip>
#include <string>



void Setup_Game(unsigned int &NumberOfTurns,
                unsigned char &CurrentPlayer,
                unsigned int &NumberOfPlayers,
                unsigned char &UserXO,
                std::string &AIDifficulty,
                std::vector<std::vector<std::string>> &GameData,
                std::vector<unsigned int> &ValidMovesRemaining)
{
  // The for loops add the 3 rows and columns to the grid and the the appropriate grid values
  for (unsigned int i = 0, GridNumber = 0; i < 3; i++)
  {
    std::vector<std::string> Rows;
    GameData.push_back(Rows);

    for (int j = 0; j < 3; j++, GridNumber++)
    {
      GameData[i].push_back(" ");
      ValidMovesRemaining.push_back(GridNumber);
    }
  }

  // Ask user for number of players
  NumberOfPlayers = Get_Number_Of_Players(GameData);

  // If only one human user then ask them for which player they want to be (X or O)
  if (NumberOfPlayers == 1)
    UserXO = Get_User_X_O_Choice(GameData, NumberOfPlayers);

  if (NumberOfPlayers < 2)
    AIDifficulty = Get_AI_Difficulty(GameData, NumberOfPlayers);

  // Set seed to system time at 0 to create pseudo random numbers
  std::srand((unsigned int)std::time(0));

  // Assign CurrentPlayer, and thus player to play first, randomly
  if (std::rand() % 2 == 0)
    CurrentPlayer = 'X';
  else
    CurrentPlayer = 'O';
}

unsigned int Get_Number_Of_Players(const std::vector<std::vector<std::string>> &GameData)
{
  bool IsValueCorrect = false; // Flag for if input value is valid
  std::string Input;

  while (!IsValueCorrect)
  {
    Display_Game(GameData, "N/A", "N/A");
    std::cout << "\n\nEnter the number of human players ";

    std::getline(std::cin, Input);

    // Only 0, 1 and 2 players allowed
    if (Input == "0" || Input == "1" || Input == "2")
      IsValueCorrect = true;
  }

  return std::stoi(Input, nullptr, 10);
}

unsigned char Get_User_X_O_Choice(const std::vector<std::vector<std::string>> &GameData,
                                  const unsigned int &NumberOfPlayers)
{
  bool IsValueCorrect = false; // Flag for if input value is valid
  std::string Input;

  while (!IsValueCorrect)
  {
    Display_Game(GameData, std::to_string(NumberOfPlayers), "N/A");
    std::cout << "\n\nWhat player would you like to be (X or O) ";

    std::getline(std::cin, Input);

    Capitalise_Word(Input);

    // Only X and O allowed
    if (Input == "X" || Input == "O")
      IsValueCorrect = true;
  }

  return Input[0];
}

std::string Get_AI_Difficulty(const std::vector<std::vector<std::string>> &GameData,
                              const unsigned int &NumberOfPlayers)
{
  bool IsValueCorrect = false; // Flag for if input value is valid
  std::string Input;

  while (!IsValueCorrect)
  {
    Display_Game(GameData, std::to_string(NumberOfPlayers), "N/A");
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

void Toggle_Player(unsigned char &CurrentPlayer)
{
  if (CurrentPlayer == 'X')
    CurrentPlayer = 'O';

  else
    CurrentPlayer = 'X';
}

void Ask_User_For_Next_Input(std::vector<std::vector<std::string>> &GameData,
                             const unsigned int &NumberOfPlayers,
                             const std::string &AIDifficulty,
                             const unsigned char &CurrentPlayer,
                             std::vector<unsigned int> &ValidMovesRemaining)
{
  bool IsValueCorrect = false; // Flag for if input value is valid
  std::string Input;
  unsigned int UserCommand, Row, Column;

  while (!IsValueCorrect)
  {
    Display_Game(GameData, std::to_string(NumberOfPlayers), AIDifficulty);
    std::cout << "\n\nPlayer " << CurrentPlayer << ", please enter your command ";

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
      GameData[Row][Column] = CurrentPlayer;

      ValidMovesRemaining.erase(CommandPosition);
    }
  }
}

void Ask_Computer_For_Next_Input(std::vector<std::vector<std::string>> &GameData,
                                 const unsigned int &NumberOfPlayers,
                                 const std::string &AIDifficulty,
                                 const unsigned char &CurrentPlayer,
                                 std::vector<unsigned int> &ValidMovesRemaining)
{
  unsigned int ComputerCommand, Row, Column;

  Display_Game(GameData, std::to_string(NumberOfPlayers), AIDifficulty);

  if (AIDifficulty == "EASY")
  {
    ComputerCommand = ValidMovesRemaining[std::rand() % ValidMovesRemaining.size()];
    auto CommandPosition = std::find(ValidMovesRemaining.begin(), ValidMovesRemaining.end(), ComputerCommand);
    ValidMovesRemaining.erase(CommandPosition);
  }
  else // Hard
    ComputerCommand = MiniMax_Algorithm();

  Column = ComputerCommand % 3;
  Row = ComputerCommand / 3;

  // Go to the command position in the grid and overwrite with the current player
  GameData[Row][Column] = CurrentPlayer;
}

unsigned int MiniMax_Algorithm(void)
{
  return 0;
}

void Display_Game_Over_Message(const std::vector<std::vector<std::string>> &GameData,
                               const unsigned int &NumberOfPlayers,
                               const std::string &AIDifficulty,
                               const unsigned char &CurrentPlayer,
                               const unsigned int &NumberOfTurns,
                               bool &GameIsRunning)
{
  Display_Game(GameData, std::to_string(NumberOfPlayers), AIDifficulty);

  // Winner will be current player as Toggle_Player() function has not been called
  // from receiving input and determining winner
  if (Winning_Conditions_Met(GameData))
    std::cout << "\n\n\t\t     GAME OVER\n\n\t" << CurrentPlayer << " has won! The game lasted " << NumberOfTurns << " turns.";

  // No winner so a draw
  else
    std::cout << "\n\n\t\t     GAME OVER\n\n      It is a draw! The game lasted " << NumberOfTurns << " turns.";

  std::cout << "\n\nPress 'Q' to quit OR any other key to play again...";

  // Gets key pressed and then checks and clears terminal window if replaying
  char Decision = _getch();

  if (Decision == 'q')
    GameIsRunning = false;

  else
    // Start from blank terminal
    Clear_Terminal();
}
