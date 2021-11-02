//
//  @File: Hangman.cpp
//  @Author: Junaid Afzal
//

// to prevent max error with windows.h redefining it
// https://stackoverflow.com/questions/7035023/stdmax-expected-an-identifier/7035078
#define NOMINMAX
#include <windows.h>

#include "Hangman.hpp"
#include "Functions.hpp"
#include <iostream>
#include <ctime>
#include <limits>
#include <fstream>
#include <conio.h>
#include <iomanip>

void Setup_Game(std::string &WordToBeGuessed,
                std::string &CurrentGuessOfWord,
                unsigned int &NumberOfPlayers,
                std::string &PlayerThatIsGuessing,
                std::vector<unsigned char> &IncorrectGuesses,
                std::string &AIDifficulty)
{
  // Set seed of srand to time(0) so pseudo random
  std::srand((unsigned int)std::time(0));

  NumberOfPlayers = Get_Number_Of_Players(IncorrectGuesses);

  switch (NumberOfPlayers)
  {
  case 0:
    AIDifficulty = Get_AI_Difficulty(NumberOfPlayers, IncorrectGuesses);
    PlayerThatIsGuessing = "COMPUTER";
    WordToBeGuessed = Get_Word_To_Be_Guessed_From_Computer(IncorrectGuesses);
    break;

  case 1:
    AIDifficulty = Get_AI_Difficulty(NumberOfPlayers, IncorrectGuesses);
    PlayerThatIsGuessing = Get_Who_Is_Guessing(NumberOfPlayers, IncorrectGuesses, AIDifficulty);
    if (PlayerThatIsGuessing == "COMPUTER")
      WordToBeGuessed = Get_Word_To_Be_Guessed_From_User(NumberOfPlayers, PlayerThatIsGuessing, IncorrectGuesses, AIDifficulty);
    else
      WordToBeGuessed = Get_Word_To_Be_Guessed_From_Computer(IncorrectGuesses);
    break;

  case 2:
    PlayerThatIsGuessing = "HUMAN";
    WordToBeGuessed = Get_Word_To_Be_Guessed_From_User(NumberOfPlayers, PlayerThatIsGuessing, IncorrectGuesses, AIDifficulty);
    break;

  default:
    break;
  }

  // Create the current guess to be the same size as the word to be guessed but only containing underscores
  for (unsigned int i = 0; i < WordToBeGuessed.size(); i++)
    CurrentGuessOfWord.push_back('_');
}

unsigned int Get_Number_Of_Players(const std::vector<unsigned char> &IncorrectGuesses)
{
  bool IsValueCorrect = false; // Flag for if input value is valid
  std::string Input;

  while (!IsValueCorrect)
  {
    Display_Game(0, "", IncorrectGuesses, "N/A", "N/A");
    std::cout << "\n\n\n\n\nEnter the number of players: ";

    std::getline(std::cin, Input);

    // Only 0, 1 and 2 players allowed
    if (Input == "0" || Input == "1" || Input == "2")
      IsValueCorrect = true;
  }

  return std::stoi(Input, nullptr, 10);
}

std::string Get_AI_Difficulty(const unsigned int &NumberOfPlayers,
                              const std::vector<unsigned char> &IncorrectGuesses)
{
  bool IsValueCorrect = false; // Flag for if input value is valid
  std::string Input;

  while (!IsValueCorrect)
  {
    Display_Game(0, "", IncorrectGuesses, std::to_string(NumberOfPlayers), "N/A");
    std::cout << "\n\n\n\n\nEnter the AI difficulty (EASY or HARD) ";

    std::getline(std::cin, Input);

    Capitalise_Word(Input);

    if (Input == "EASY" || Input == "HARD")
      IsValueCorrect = true;
  }

  return Input;
}

std::string Get_Word_To_Be_Guessed_From_User(const unsigned int &NumberOfPlayers,
                                             const std::string &PlayerThatIsGuessing,
                                             const std::vector<unsigned char> &IncorrectGuesses,
                                             const std::string &AIDifficulty)
{
  bool IsValueCorrect = false; // Flag for if input value is valid
  std::string Input; // No spaces or - allowed

  while (!IsValueCorrect)
  {
    // Set flag to true by default as difficult to continue to to next iteration of while loop
    // within a nested if statements within nested for loops
    IsValueCorrect = true;

    Display_Game(0, "", IncorrectGuesses, std::to_string(NumberOfPlayers), AIDifficulty);
    std::cout << "\n\n\n\n\nEnter the word to be guessed: ";

    std::getline(std::cin, Input);

    // Capitalise all letters so that only capital letter need to be dealt with
    Capitalise_Word(Input);

    // Only accept chars that are either capital or lowercase letters
    for (unsigned int i = 0; i < Input.size(); i++)
    {
      if (Input[i] < 'A' || Input[i] > 'Z')
      {
        IsValueCorrect = false;
        break;
      }
    }
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

std::string Get_Who_Is_Guessing(const unsigned int &NumberOfPlayers,
                                const std::vector<unsigned char> &IncorrectGuesses,
                                const std::string &AIDifficulty)
{
  bool IsValueCorrect = false; // Flag for if input value is valid
  std::string Input;

  while (!IsValueCorrect)
  {
    // Set flag to true by default as difficult to continue to to next iteration of while loop
    // within a nested if statements within nested for loops

    Display_Game(0, "", IncorrectGuesses, std::to_string(NumberOfPlayers), AIDifficulty);
    std::cout << "\n\n\n\n\nEnter player that will be guessing (HUMAN or COMPUTER): ";

    std::getline(std::cin, Input);

    Capitalise_Word(Input);

    if (Input == "HUMAN" || Input == "COMPUTER")
      IsValueCorrect = true;
  }

  return Input;
}

std::string Get_Word_To_Be_Guessed_From_Computer(const std::vector<unsigned char> &IncorrectGuesses)
{
  std::vector<std::string> Words = Create_Word_List();
  return Words[std::rand() % Words.size()];
}

bool Game_Over(const unsigned int &NumberOfErrors)
{
  // 10 errors mean that the final state of the
  // hangman drawing has been reached
  if (NumberOfErrors == 10)
    return true;

  else
    return false;
}

bool Winning_Conditions_Met(const std::string &WordToBeGuessed,
                            const std::string &CurrentGuessOfWord)
{
  // If there is any difference then winning condition not met
  for (unsigned int i = 0; i < WordToBeGuessed.size(); i++)
    if (WordToBeGuessed[i] != CurrentGuessOfWord[i])
      return false;

  return true;
}

void Display_Game(const unsigned int &NumberOfErrors,
                  const std::string &CurrentGuessOfWord,
                  const std::vector<unsigned char> &IncorrectGuesses,
                  const std::string &NumberOfPlayers,
                  const std::string &AIDifficulty)
{
  // Start from blank terminal
  Clear_Terminal();

  // Draw the hangman drawing
  switch (NumberOfErrors)
  {
  case 0:
    std::cout << "\n\t\t\t\t\t       Hangman"
              << "\n\n\t\t\t\t\t   # of Players = " << NumberOfPlayers
              << "\n\n\t\t\t\t\t AI Difficulty = " << AIDifficulty
              << "\n\n\n";
    break;

  case 1:
    std::cout << "\n\t\t   Incorrect Guesses\t       Hangman"
              << "\n\n\t\t   " << IncorrectGuesses[0] << "\t\t\t   # of Players = " << NumberOfPlayers
              << "\n\n\t\t\t\t\t AI Difficulty = " << AIDifficulty
              << "\n" << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196
              << "\n\n";
    break;

  case 2:
    std::cout << "\n    " << (char)179 << "\t\t   Incorrect Guesses\t       Hangman"
              << "\n    " << (char)179
              << "\n    " << (char)179 << "\t\t   " << IncorrectGuesses[0] << "   " << IncorrectGuesses[1] << "\t\t   # of Players = " << NumberOfPlayers
              << "\n    " << (char)179
              << "\n    " << (char)179 << "\t\t\t\t\t AI Difficulty = " << AIDifficulty
              << "\n" << (char)196 << (char)196 << (char)196 << (char)196 << (char)193 << (char)196 << (char)196 << (char)196 << (char)196 << "\n\n";
    break;

  case 3:
    std::cout << "    " << (char)218 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196
              << "\n    " << (char)179 << "\t\t   Incorrect Guesses\t       Hangman"
              << "\n    " << (char)179
              << "\n    " << (char)179 << "\t\t   " << IncorrectGuesses[0] << "   " << IncorrectGuesses[1] << "   " << IncorrectGuesses[2] << "\t\t   # of Players = " << NumberOfPlayers
              << "\n    " << (char)179
              << "\n    " << (char)179 << "\t\t\t\t\t AI Difficulty = " << AIDifficulty
              << "\n" << (char)196 << (char)196 << (char)196 << (char)196 << (char)193 << (char)196 << (char)196 << (char)196 << (char)196 << "\n\n";
    break;

  case 4:
    std::cout << "    " << (char)218 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)191
              << "\n    " << (char)179 << "       " << (char)179 << "\t   Incorrect Guesses\t       Hangman"
              << "\n    " << (char)179
              << "\n    " << (char)179 << "\t\t   " << IncorrectGuesses[0] << "   " << IncorrectGuesses[1] << "   " << IncorrectGuesses[2] << "   " << IncorrectGuesses[3] << "\t   # of Players = " << NumberOfPlayers
              << "\n    " << (char)179
              << "\n    " << (char)179 << "\t\t\t\t\t AI Difficulty = " << AIDifficulty
              << "\n" << (char)196 << (char)196 << (char)196 << (char)196 << (char)193 << (char)196 << (char)196 << (char)196 << (char)196 << "\n\n";
    break;

  case 5:
    std::cout << "    " << (char)218 << (char)196 << (char)196 << (char)196  << (char)196 << (char)196 << (char)196 << (char)196 << (char)191
              << "\n    " << (char)179 << "       " << (char)179 << "\t   Incorrect Guesses\t       Hangman"
              << "\n    " << (char)179 << "       O"
              << "\n    " << (char)179 << "\t\t   " << IncorrectGuesses[0] << "   " << IncorrectGuesses[1] << "   " << IncorrectGuesses[2] << "   " << IncorrectGuesses[3] << "   " << IncorrectGuesses[4] << "\t   # of Players = " << NumberOfPlayers
              << "\n    " << (char)179
              << "\n    " << (char)179 << "\t\t\t\t\t AI Difficulty = " << AIDifficulty
              << "\n" << (char)196 << (char)196 << (char)196 << (char)196 << (char)193 << (char)196 << (char)196 << (char)196 << (char)196 << "\n\n";
    break;

  case 6:
    std::cout << "    " << (char)218 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)191
              << "\n    " << (char)179 << "       " << (char)179 << "\t   Incorrect Guesses\t       Hangman"
              << "\n    " << (char)179 << "       O"
              << "\n    " << (char)179 << "       " << (char)179 << "\t   " << IncorrectGuesses[0] << "   " << IncorrectGuesses[1] << "   " << IncorrectGuesses[2] << "   " << IncorrectGuesses[3] << "   " << IncorrectGuesses[4] << "\t   # of Players = " << NumberOfPlayers
              << "\n    " << (char)179
              << "\n    " << (char)179 << "\t\t   " << IncorrectGuesses[5] << "\t\t\t AI Difficulty = " << AIDifficulty
              << "\n" << (char)196 << (char)196 << (char)196 << (char)196 << (char)193 << (char)196 << (char)196 << (char)196 << (char)196 << "\n\n";
    break;

  case 7:
    std::cout << "    " << (char)218 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)191
              << "\n    " << (char)179 << "       " << (char)179 << "\t   Incorrect Guesses\t       Hangman"
              << "\n    " << (char)179 << "       O"
              << "\n    " << (char)179 << "       " << (char)179 << "\t   " << IncorrectGuesses[0] << "   " << IncorrectGuesses[1] << "   " << IncorrectGuesses[2] << "   " << IncorrectGuesses[3] << "   " << IncorrectGuesses[4] << "\t   # of Players = " << NumberOfPlayers
              << "\n    " << (char)179 << "      /"
              << "\n    " << (char)179 << "\t\t   " << IncorrectGuesses[5] << "   " << IncorrectGuesses[6] << "\t\t AI Difficulty = " << AIDifficulty
              << "\n" << (char)196 << (char)196 << (char)196 << (char)196 << (char)193 << (char)196 << (char)196 << (char)196 << (char)196 << "\n\n";
    break;

  case 8:
    std::cout << "    " << (char)218 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)191
              << "\n    " << (char)179 << "       " << (char)179 << "\t   Incorrect Guesses\t       Hangman"
              << "\n    " << (char)179 << "       O"
              << "\n    " << (char)179 << "       " << (char)179 << "\t   " << IncorrectGuesses[0] << "   " << IncorrectGuesses[1] << "   " << IncorrectGuesses[2] << "   " << IncorrectGuesses[3] << "   " << IncorrectGuesses[4] << "\t   # of Players = " << NumberOfPlayers
              << "\n    " << (char)179 << "      / \\"
              << "\n    " << (char)179 << "\t\t   " << IncorrectGuesses[5] << "   " << IncorrectGuesses[6] << "   " << IncorrectGuesses[7] << "\t\t AI Difficulty = " << AIDifficulty
              << "\n" << (char)196 << (char)196 << (char)196 << (char)196 << (char)193 << (char)196 << (char)196 << (char)196 << (char)196 << "\n\n";
    break;

  case 9:
    std::cout << "    " << (char)218 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)191
              << "\n    " << (char)179 << "       " << (char)179 << "\t   Incorrect Guesses\t       Hangman"
              << "\n    " << (char)179 << "       O"
              << "\n    " << (char)179 << "      /" << (char)179 << "\t   " << IncorrectGuesses[0] << "   " << IncorrectGuesses[1] << "   " << IncorrectGuesses[2] << "   " << IncorrectGuesses[3] << "   " << IncorrectGuesses[4] << "\t   # of Players = " << NumberOfPlayers
              << "\n    " << (char)179 << "      / \\"
              << "\n    " << (char)179 << "\t\t   " << IncorrectGuesses[5] << "   " << IncorrectGuesses[6] << "   " << IncorrectGuesses[7] << "   " << IncorrectGuesses[8] << "\t AI Difficulty = " << AIDifficulty
              << "\n" << (char)196 << (char)196 << (char)196 << (char)196 << (char)193 << (char)196 << (char)196 << (char)196 << (char)196 << "\n\n";
    break;

  case 10:
    std::cout << "    " << (char)218 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)191
              << "\n    " << (char)179 << "       " << (char)179 << "\t   Incorrect Guesses\t       Hangman"
              << "\n    " << (char)179 << "       O"
              << "\n    " << (char)179 << "      /" << (char)179 << "\\" << "\t   " << IncorrectGuesses[0] << "   " << IncorrectGuesses[1] << "   " << IncorrectGuesses[2] << "   " << IncorrectGuesses[3] << "   " << IncorrectGuesses[4] << "\t   # of Players = " << NumberOfPlayers
              << "\n    " << (char)179 << "      / \\"
              << "\n    " << (char)179 << "\t\t   " << IncorrectGuesses[5] << "   " << IncorrectGuesses[6] << "   " << IncorrectGuesses[7] << "   " << IncorrectGuesses[8] << "   " << IncorrectGuesses[9] << "\t AI Difficulty = " << AIDifficulty
              << "\n" << (char)196 << (char)196 << (char)196 << (char)196 << (char)193 << (char)196 << (char)196 << (char)196 << (char)196 << "\n\n";
    break;

  default:
    std::cout << "Error in Display_Game() switch statement\n";
    break;
  }

  // Current guess of word
  for (unsigned int i = 0; i < CurrentGuessOfWord.size(); i++)
    std::cout << CurrentGuessOfWord[i] << " ";
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

void Ask_User_For_Next_Guess(std::vector<unsigned char> &IncorrectGuesses,
                             std::vector<unsigned char> &CorrectGuesses,
                             unsigned int &NumberOfErrors,
                             std::string &CurrentGuessOfWord,
                             const std::string &AIDifficulty,
                             const unsigned int &NumberOfPlayers,
                             std::string &WordToBeGuessed)
{
  bool IsValueCorrect = false; // Flag for if input value is valid
  std::string Input;

  while (!IsValueCorrect)
  {
    // Set flag to true by default as difficult to continue to to next iteration of while loop
    // within a nested if statements within nested for loops
    IsValueCorrect = true;

    Display_Game(NumberOfErrors, CurrentGuessOfWord, IncorrectGuesses, std::to_string(NumberOfPlayers), AIDifficulty);
    std::cout << "\n\nEnter your guess: ";

    std::getline(std::cin, Input);

    if (Input.size() != 1)
    {
      IsValueCorrect = false;
      continue;
    }

    Capitalise_Word(Input);

    if (Input[0] < 'A' || Input[0] > 'Z')
    {
      IsValueCorrect = false;
      continue;
    }

    //Check if this string has already been guessed both correctly or incorrectly
    for (unsigned int i = 0; i < IncorrectGuesses.size(); i++)
      if (Input[0] == IncorrectGuesses[i])
      {
        IsValueCorrect = false;
        break;
      }

    for (unsigned int i = 0; i < CorrectGuesses.size(); i++)
      if (Input[0] == CorrectGuesses[i])
      {
        IsValueCorrect = false;
        break;
      }
  }

  if (!Check_Guess_Against_Word(Input[0], WordToBeGuessed, CurrentGuessOfWord))
  {
    IncorrectGuesses.push_back(Input[0]);
    NumberOfErrors++;
  }
  else
    CorrectGuesses.push_back(Input[0]);

}

void Ask_Computer_For_Next_Guess(std::vector<unsigned char> &IncorrectGuesses,
                                 std::vector<unsigned char> &CorrectGuesses,
                                 unsigned int &NumberOfErrors,
                                 std::string &CurrentGuessOfWord,
                                 const std::string &AIDifficulty,
                                 const unsigned int &NumberOfPlayers,
                                 std::string &WordToBeGuessed)
{
  bool IsValueCorrect = false; // Flag for if input value is valid
  unsigned char Guess;

  Display_Game(NumberOfErrors, CurrentGuessOfWord, IncorrectGuesses, std::to_string(NumberOfPlayers), AIDifficulty);

  while (!IsValueCorrect)
  {
    // Set flag to true by default as difficult to continue to to next iteration of while loop
    // within a nested if statements within nested for loops
    IsValueCorrect = true;

    // Computer will guess a random letter from A to Z
    Guess = (std::rand() % 26) + 65;

    //Check if this string has already been guessed both correctly or incorrectly
    for (unsigned int i = 0; i < IncorrectGuesses.size(); i++)
      if (Guess == IncorrectGuesses[i])
      {
        IsValueCorrect = false;
        break;
      }

    for (unsigned int i = 0; i < CorrectGuesses.size(); i++)
      if (Guess == CorrectGuesses[i])
      {
        IsValueCorrect = false;
        break;
      }
  }

  if (!Check_Guess_Against_Word(Guess, WordToBeGuessed, CurrentGuessOfWord))
  {
    IncorrectGuesses.push_back(Guess);
    NumberOfErrors++;
  }
  else
    CorrectGuesses.push_back(Guess);
}

bool Check_Guess_Against_Word(const unsigned char &Guess,
                              const std::string &WordToBeGuessed,
                              std::string &CurrentGuessOfWord)
{
  bool IsGuessCorrect = false;

  // If below is true then guess is a letter and every occurrence of this letter
  // needs to be deposited is the current guess of word
  for (unsigned int i = 0; i < WordToBeGuessed.size(); i++)
  {
    if (WordToBeGuessed[i] == Guess)
    {
      IsGuessCorrect = true;
      CurrentGuessOfWord[i] = Guess;
    }
  }

  return IsGuessCorrect;
}

void Display_Game_Over_Message(const unsigned int &NumberOfErrors,
                               const std::string &CurrentGuessOfWord,
                               const std::vector<unsigned char> &IncorrectGuesses,
                               const unsigned int &NumberOfTurns,
                               const std::string &WordToBeGuessed,
                               bool &GameIsRunning,
                               const std::string &AIDifficulty,
                               const unsigned int &NumberOfPlayers)
{
  Display_Game(NumberOfErrors, CurrentGuessOfWord, IncorrectGuesses, std::to_string(NumberOfPlayers), AIDifficulty);
  // If the below is true then hangman has reached its final state and thus user has lost
  if (NumberOfErrors == 10)
    std::cout << "  (The word was " << WordToBeGuessed << ")\n\n\n\t\t\tGAME OVER\n\n       The guesser has lost but lasted for " << NumberOfTurns << " turns!";

  else
    std::cout << "\n\n\n\t\t\tGAME OVER\n\n       The guesser has won! The game lasted " << NumberOfTurns << " turns.";

  std::cout << "\n\n     Press 'Q' to quit OR any other key to play again...";

  // Gets key pressed and then checks and clears terminal window if replaying
  char Decision = _getch();

  if (Decision == 'q')
    GameIsRunning = false;

  else
    // Start from blank terminal
    Clear_Terminal();
}
