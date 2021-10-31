//
//  @File: TicTacToe.cpp
//  @Author: Junaid Afzal
//

#include "TicTacToe.hpp"

#include <iostream>
#include <ctime>
#include <limits>
#include <algorithm>
#include <conio.h>
// to prevent max error with windows.h redefining it
// https://stackoverflow.com/questions/7035023/stdmax-expected-an-identifier/7035078
#define NOMINMAX
#include <windows.h>

void Setup_Game(unsigned int &NumberOfTurns,
                unsigned int &CurrentPlayer,
                unsigned int &NumberOfPlayers,
                unsigned int &UserXO,
                std::string &AIDifficulty,
                std::vector<std::vector<std::string>> &GameData,
                std::vector<int> &ValidMovesRemaining)
{
  // The for loops add the 3 rows and columns to the grid and the the appropriate grid values
  for (unsigned int i = 0, GridNumber = 0; i < 3; i++)
  {
    std::vector<std::string> Rows;
    GameData.push_back(Rows);

    for (int j = 0; j < 3; j++, GridNumber++)
    {
      GameData[i].push_back(std::to_string(GridNumber));
      ValidMovesRemaining.push_back(GridNumber);
    }
  }

  // Ask user for number of players
  NumberOfPlayers = Get_Number_Of_Players(GameData, NumberOfPlayers);

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

int Get_Number_Of_Players(const std::vector<std::vector<std::string>> &GameData,
                          unsigned int &NumberOfPlayers)
{
  bool IsValueCorrect = false; // Flag for if input value is valid

  while (!IsValueCorrect)
  {
    Display_Game(GameData, -1, "N/A");
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

int Get_User_X_O_Choice(const std::vector<std::vector<std::string>> &GameData,
                        const unsigned int &NumberOfPlayers)
{
  bool IsValueCorrect = false; // Flag for if input value is valid
  char UserXOChoice = 0;

  while (!IsValueCorrect)
  {
    Display_Game(GameData, NumberOfPlayers, "N/A");
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

std::string Get_AI_Difficulty(const std::vector<std::vector<std::string>> &GameData,
                              const unsigned int &NumberOfPlayers)
{
  bool IsValueCorrect = false; // Flag for if input value is valid
  std::string AIDifficulty;

  while (!IsValueCorrect)
  {
    Display_Game(GameData, NumberOfPlayers, "N/A");
    std::cout << "\n\nEnter the AI difficulty (EASY or HARD) ";

    std::cin >> AIDifficulty;
    // Check if cin failed
    if (std::cin.fail())
    {
      // Clear buffer and retry
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      continue;
    }

        // Only accept chars that are either capital or lowercase letters
    for (unsigned int i = 0; i < AIDifficulty.size(); i++)
    {
      if (AIDifficulty[i] < 'A')
      {
        // Clear buffer and retry
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        IsValueCorrect = false;
        break;
      }

      else if (AIDifficulty[i] > 'z')
      {
        // Clear buffer and retry
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        IsValueCorrect = false;
        break;
      }

      // Check for [ \ ] ^ _ ` as they occur in between the uppercase and lowercase letters blocks
      else if (AIDifficulty[i] >= 91 && AIDifficulty[i] <= 96)
      {
        // Clear buffer and retry
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        IsValueCorrect = false;
        break;
      }
    }

    Capitalise_Word(AIDifficulty);

    // Only X and O inputs allowed
    if ((AIDifficulty != "EASY") && (AIDifficulty != "HARD"))
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

  return AIDifficulty;
}

void Capitalise_Word(std::string &aWord)
{
  // Assuming aWord contains only letters of unkown capitalisation, if
  // a letter is lower case (>=97) then minus 32 to capitalise it
  for (unsigned int i = 0; i < aWord.size(); i++)
  {
    if (aWord[i] >= 97)
      aWord[i] -= 32;
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

void Display_Game(const std::vector<std::vector<std::string>> &GameData,
                  const unsigned int &NumberOfPlayers,
                  const std::string &AIDifficulty)
{
  // Start from blank terminal
  Clear_Terminal();

  // Iterate across whole grid and output its value
  for (unsigned int i = 0; i < 3; i++)
  {
    for (unsigned int j = 0; j < 3; j++)
    {
      if ((GameData[i][j] == "X") || (GameData[i][j] == "O"))
        std::cout << std::left << " " << GameData[i][j] << " ";
      else
        std::cout << std::left << "   ";

      // Vertical bars
      if (j == 0 || j == 1)
        std::cout << (char)179;
    }

    std::cout << '\t';

    switch (i)
    {
    case 0:
      std::cout << "    Tic Tac Toe    ";
    break;

    case 1:
      if (NumberOfPlayers == -1)
        std::cout << "# of Players  = N/A";
      else
        std::cout << "# of Players  = " << NumberOfPlayers;
      break;

    case 2:
      std::cout << "AI Difficulty = " << AIDifficulty;
      break;

    default:
      std::cout << "\n\nError in Display_Game() switch statement\n\n";
      exit(1);
      break;
    }

    std::cout << '\t';

    for (unsigned int j = 0; j < 3; j++)
    {
      std::cout << std::left << " " << j+i*3 << " ";

      // Vertical bars
      if (j == 0 || j == 1)
        std::cout << (char)179;
    }

    // Horizontal bars
    if (i == 0 || i == 1)
    {
      std::cout << '\n';

      for (unsigned int j = 0; j <= 10; j++)
      {
        if (j == 3 || j == 7)
          std::cout << (char)197;

        else
          std::cout << (char)196;
      }

      std::cout << "\t\t\t\t";

      for (unsigned int j = 0; j <= 10; j++)
      {
        if (j == 3 || j == 7)
          std::cout << (char)197;

        else
          std::cout << (char)196;
      }

      std::cout << '\n';
    }
  }
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

void Toggle_Player(unsigned int &CurrentPlayer)
{
  if (CurrentPlayer == 'X')
    CurrentPlayer = 'O';

  else
    CurrentPlayer = 'X';
}

void Ask_User_For_Next_Input(std::vector<std::vector<std::string>> &GameData,
                             const unsigned int &NumberOfPlayers,
                             const std::string &AIDifficulty,
                             const unsigned int &CurrentPlayer,
                             std::vector<int> &ValidMovesRemaining)
{
  bool IsValueCorrect = false; // Flag for if input value is valid
  int UserCommand, Row, Column;

  while (!IsValueCorrect)
  {
    Display_Game(GameData, NumberOfPlayers, AIDifficulty);
    std::cout << "\n\nPlayer " << (char)CurrentPlayer << ", please enter your command ";

    std::cin >> UserCommand;

    if (std::cin.fail()) // Check if cin failed
    {
      // Clear buffer, set flag to false and retry
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      continue;
    }

    auto CommandPosition = std::find(ValidMovesRemaining.begin(), ValidMovesRemaining.end(), UserCommand);

    if (CommandPosition != ValidMovesRemaining.end())
    {
      IsValueCorrect = true;

      Column = UserCommand % 3;
      Row = UserCommand / 3;
      GameData[Row][Column] = CurrentPlayer;

      ValidMovesRemaining.erase(CommandPosition);

      // Clear buffer
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    else
    {
      // Clear buffer, set flag to false and retry
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      continue;
    }
  }
}

void Ask_Computer_For_Next_Input(std::vector<std::vector<std::string>> &GameData,
                                 const unsigned int &NumberOfPlayers,
                                 const std::string &AIDifficulty,
                                 const unsigned int &CurrentPlayer,
                                 std::vector<int> &ValidMovesRemaining)
{

  if (AIDifficulty == "EASY")
  {
    bool IsValueCorrect = false; // Flag for if input value is valid
    unsigned int ComputerCommand, Row, Column;

    Display_Game(GameData, NumberOfPlayers, AIDifficulty);

    // Computer is dumb and picks a pseudo random number as command
    ComputerCommand = ValidMovesRemaining[std::rand() % ValidMovesRemaining.size()];

    Column = ComputerCommand % 3;
    Row = ComputerCommand / 3;

    // Go to the command position in the grid and overwrite with the current player
    GameData[Row][Column] = CurrentPlayer;

    auto CommandPosition = std::find(ValidMovesRemaining.begin(), ValidMovesRemaining.end(), ComputerCommand);
    ValidMovesRemaining.erase(CommandPosition);
  }

  else
    MiniMax_Algorithm();
}

void MiniMax_Algorithm(void)
{

}

void Display_Game_Over_Message(const std::vector<std::vector<std::string>> &GameData,
                               const unsigned int &NumberOfPlayers,
                               const std::string &AIDifficulty,
                               const unsigned int &CurrentPlayer,
                               const unsigned int &NumberOfTurns,
                               bool &GameIsRunning)
{
  Display_Game(GameData, NumberOfPlayers, AIDifficulty);

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
    // Start from blank terminal
    Clear_Terminal();
}
