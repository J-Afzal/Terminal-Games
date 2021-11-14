/**
 * @file hangman.cpp
 * @author Junaid Afzal
 * @brief Implementation of hangman.hpp
 * @version 1.0
 * @date 07-11-2021
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "hangman.hpp"
#include "functions.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <conio.h>

void Play_Hangman(const HANDLE &ConsoleHandle)
{
  bool GameIsRunning = true;

  while (GameIsRunning)
  {
    unsigned int NumberOfPlayers, NumberOfErrors = 0, NumberOfTurns = 0;
    std::string WordToBeGuessed, CurrentGuessOfWord, PlayerThatIsGuessing, AIDifficulty = "N/A";
    std::vector<std::string> CorrectGuesses, IncorrectGuesses, ValidMovesRemaining;

    Setup_Game(NumberOfPlayers, PlayerThatIsGuessing, AIDifficulty, WordToBeGuessed, CurrentGuessOfWord, ValidMovesRemaining, IncorrectGuesses, ConsoleHandle);

    while (!Winning_Conditions_Met(NumberOfErrors, WordToBeGuessed, CurrentGuessOfWord))
    {
      // Display_Game() called before either user or AI are asked for an input
      if (PlayerThatIsGuessing == "HUMAN")
        Get_Next_User_Guess(NumberOfErrors, NumberOfPlayers, AIDifficulty, IncorrectGuesses, CorrectGuesses, ValidMovesRemaining, CurrentGuessOfWord, WordToBeGuessed);
      else
        Get_Next_AI_Guess(NumberOfErrors, NumberOfPlayers, AIDifficulty, IncorrectGuesses, CorrectGuesses, ValidMovesRemaining, CurrentGuessOfWord, WordToBeGuessed);

      NumberOfTurns++;
    }

    Display_Game_Over_Message(NumberOfErrors, NumberOfPlayers, AIDifficulty, IncorrectGuesses, CurrentGuessOfWord, WordToBeGuessed, NumberOfTurns, GameIsRunning);
  }
}

void Setup_Game(unsigned int &NumberOfPlayers,
                std::string &PlayerThatIsGuessing,
                std::string &AIDifficulty,
                std::string &WordToBeGuessed,
                std::string &CurrentGuessOfWord,
                std::vector<std::string> &ValidMovesRemaining,
                const std::vector<std::string> &IncorrectGuesses,
                const HANDLE &ConsoleHandle)
{
  std::srand((unsigned int)std::time(0));

  NumberOfPlayers = Get_Number_Of_Players(IncorrectGuesses);

  switch (NumberOfPlayers)
  {
  case 0:
    PlayerThatIsGuessing = "AI";
    AIDifficulty = Get_AI_Difficulty(NumberOfPlayers, IncorrectGuesses);
    WordToBeGuessed = Get_Word_To_Be_Guessed_From_AI();
  break;

  case 1:
    PlayerThatIsGuessing = Get_User_Player_Choice(NumberOfPlayers, IncorrectGuesses);
    AIDifficulty = Get_AI_Difficulty(NumberOfPlayers, IncorrectGuesses);

    if (PlayerThatIsGuessing == "PLAYER ONE")
    {
      PlayerThatIsGuessing = "HUMAN";
      WordToBeGuessed = Get_Word_To_Be_Guessed_From_AI();
    }
    else
    {
      PlayerThatIsGuessing = "AI";
      WordToBeGuessed = Get_Word_To_Be_Guessed_From_User(IncorrectGuesses, NumberOfPlayers, AIDifficulty, ConsoleHandle);
    }
  break;

  case 2:
    PlayerThatIsGuessing = "HUMAN";
    WordToBeGuessed = Get_Word_To_Be_Guessed_From_User(IncorrectGuesses, NumberOfPlayers, AIDifficulty, ConsoleHandle);
    AIDifficulty = "N/A";
  break;

  default:
  break;
  }

  for (unsigned int i = 0; i < WordToBeGuessed.size(); i++)
    CurrentGuessOfWord.push_back('_');

  ValidMovesRemaining = {"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"};
}

unsigned int Get_Number_Of_Players(const std::vector<std::string> &IncorrectGuesses)
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

    Display_Game(0, "N/A", "N/A", IncorrectGuesses, "", "", false);

    std::string Output;
    Output.insert(Output.size(), 1, (char)186);
    Output.append(" Please select the number of human players:\t\t       ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");

    switch (CurrentSelection)
    {
    case 0:
      Output.insert(Output.size(), 1, (char)186);
      Output.append(BLUE);
      Output.append(" > 0\t\t\t\t\t\t\t       ");
      Output.append(WHITE);
      Output.insert(Output.size(), 1, (char)186);

      Output.append("\n");
      Output.insert(Output.size(), 1, (char)186);
      Output.append("   1\t\t\t\t\t\t\t       ");
      Output.insert(Output.size(), 1, (char)186);

      Output.append("\n");
      Output.insert(Output.size(), 1, (char)186);
      Output.append("   2\t\t\t\t\t\t\t       ");
      Output.insert(Output.size(), 1, (char)186);
    break;

    case 1:
      Output.insert(Output.size(), 1, (char)186);
      Output.append("   0\t\t\t\t\t\t\t       ");
      Output.insert(Output.size(), 1, (char)186);

      Output.append("\n");
      Output.insert(Output.size(), 1, (char)186);
      Output.append(BLUE);
      Output.append(" > 1\t\t\t\t\t\t\t       ");
      Output.append(WHITE);
      Output.insert(Output.size(), 1, (char)186);

      Output.append("\n");
      Output.insert(Output.size(), 1, (char)186);
      Output.append("   2\t\t\t\t\t\t\t       ");
      Output.insert(Output.size(), 1, (char)186);
    break;

    case 2:
      Output.insert(Output.size(), 1, (char)186);
      Output.append("   0\t\t\t\t\t\t\t       ");
      Output.insert(Output.size(), 1, (char)186);

      Output.append("\n");
      Output.insert(Output.size(), 1, (char)186);
      Output.append("   1\t\t\t\t\t\t\t       ");
      Output.insert(Output.size(), 1, (char)186);

      Output.append("\n");
      Output.insert(Output.size(), 1, (char)186);
      Output.append(BLUE);
      Output.append(" > 2\t\t\t\t\t\t\t       ");
      Output.append(WHITE);
      Output.insert(Output.size(), 1, (char)186);
    break;

    default:
    break;
    }

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append("\t\t\t\t\t\t\t       ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)200);
    Output.insert(Output.size(), 62, (char)205);
    Output.insert(Output.size(), 1, (char)188);

    // Bottom bar
    Output.append("\n");
    Output.insert(Output.size(), 1, (char)201);
    Output.insert(Output.size(), 62, (char)205);
    Output.insert(Output.size(), 1, (char)187);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append(RED);
    Output.append("\t\t\t    Hangman\t\t\t       ");
    Output.append(WHITE);
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)200);
    Output.insert(Output.size(), 62, (char)205);
    Output.insert(Output.size(), 1, (char)188);

    std::cout << Output;

    KeyPress = _getch();
  }

  return CurrentSelection;
}

std::string Get_User_Player_Choice(const unsigned int &NumberOfPlayers,
                                   const std::vector<std::string> &IncorrectGuesses)
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

    Display_Game(0, std::to_string(NumberOfPlayers), "N/A", IncorrectGuesses, "", "", false);

    std::string Output;
    Output.insert(Output.size(), 1, (char)186);
    Output.append(" Please select what player you would like to be:\t       ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");

    switch (CurrentSelection)
    {
    case 0:
      Output.insert(Output.size(), 1, (char)186);
      Output.append(BLUE);
      Output.append(" > GUESSER\t\t\t\t\t\t       ");
      Output.append(WHITE);
      Output.insert(Output.size(), 1, (char)186);

      Output.append("\n");
      Output.insert(Output.size(), 1, (char)186);
      Output.append("   WORD SETTER\t\t\t\t\t\t       ");
      Output.insert(Output.size(), 1, (char)186);
    break;

    case 1:
      Output.insert(Output.size(), 1, (char)186);
      Output.append("   GUESSER\t\t\t\t\t\t       ");
      Output.insert(Output.size(), 1, (char)186);

      Output.append("\n");
      Output.insert(Output.size(), 1, (char)186);
      Output.append(BLUE);
      Output.append(" > WORD SETTER\t\t\t\t\t\t       ");
      Output.append(WHITE);
      Output.insert(Output.size(), 1, (char)186);
    break;

    default:
    break;
    }

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append("\t\t\t\t\t\t\t       ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append("\t\t\t\t\t\t\t       ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)200);
    Output.insert(Output.size(), 62, (char)205);
    Output.insert(Output.size(), 1, (char)188);

    // Bottom bar
    Output.append("\n");
    Output.insert(Output.size(), 1, (char)201);
    Output.insert(Output.size(), 62, (char)205);
    Output.insert(Output.size(), 1, (char)187);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append(RED);
    Output.append("\t\t\t    Hangman\t\t\t       ");
    Output.append(WHITE);
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)200);
    Output.insert(Output.size(), 62, (char)205);
    Output.insert(Output.size(), 1, (char)188);

    std::cout << Output;

    KeyPress = _getch();
  }

  return CurrentSelection == 0 ? "PLAYER ONE" : "PLAYER TWO";
}

std::string Get_AI_Difficulty(const unsigned int &NumberOfPlayers,
                              const std::vector<std::string> &IncorrectGuesses)
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

    Display_Game(0, std::to_string(NumberOfPlayers), "N/A", IncorrectGuesses, "", "", false);

    std::string Output;
    Output.insert(Output.size(), 1, (char)186);
    Output.append(" Please select the AI difficulty:\t\t\t       ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");

    switch (CurrentSelection)
    {
    case 0:
      Output.insert(Output.size(), 1, (char)186);
      Output.append(BLUE);
      Output.append(" > EASY\t\t\t\t\t\t       ");
      Output.append(WHITE);
      Output.insert(Output.size(), 1, (char)186);

      Output.append("\n");
      Output.insert(Output.size(), 1, (char)186);
      Output.append("   HARD (Coming Soon!)\t\t\t\t\t       ");
      Output.insert(Output.size(), 1, (char)186);
    break;

    case 1:
      Output.insert(Output.size(), 1, (char)186);
      Output.append("   EASY\t\t\t\t\t\t       ");
      Output.insert(Output.size(), 1, (char)186);

      Output.append("\n");
      Output.insert(Output.size(), 1, (char)186);
      Output.append(BLUE);
      Output.append(" > HARD (Coming Soon!)\t\t\t\t\t       ");
      Output.append(WHITE);
      Output.insert(Output.size(), 1, (char)186);
    break;

    default:
    break;
    }

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append("\t\t\t\t\t\t\t       ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append("\t\t\t\t\t\t\t       ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)200);
    Output.insert(Output.size(), 62, (char)205);
    Output.insert(Output.size(), 1, (char)188);

    // Bottom bar
    Output.append("\n");
    Output.insert(Output.size(), 1, (char)201);
    Output.insert(Output.size(), 62, (char)205);
    Output.insert(Output.size(), 1, (char)187);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append(RED);
    Output.append("\t\t\t    Hangman\t\t\t       ");
    Output.append(WHITE);
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)200);
    Output.insert(Output.size(), 62, (char)205);
    Output.insert(Output.size(), 1, (char)188);

    std::cout << Output;

    KeyPress = _getch();
  }

  return CurrentSelection == 0 ? "EASY" : "HARD";
}

std::string Get_Word_To_Be_Guessed_From_User(const std::vector<std::string> &IncorrectGuesses,
                                             const unsigned int &NumberOfPlayers,
                                             const std::string &AIDifficulty,
                                             const HANDLE ConsoleHandle)
{
  bool InputValid = false;
  std::string Input;

  std::string Output;
  Output.insert(Output.size(), 1, (char)186);
  Output.append(" Please enter the word to be guessed: \t\t\t       ");
  Output.insert(Output.size(), 1, (char)186);

  Output.append("\n");
  Output.insert(Output.size(), 1, (char)186);
  Output.append("\t\t\t\t\t\t\t       ");
  Output.insert(Output.size(), 1, (char)186);

  Output.append("\n");
  Output.insert(Output.size(), 1, (char)186);
  Output.append("\t\t\t\t\t\t\t       ");
  Output.insert(Output.size(), 1, (char)186);

  Output.append("\n");
  Output.insert(Output.size(), 1, (char)186);
  Output.append("\t\t\t\t\t\t\t       ");
  Output.insert(Output.size(), 1, (char)186);

  Output.append("\n");
  Output.insert(Output.size(), 1, (char)186);
  Output.append("\t\t\t\t\t\t\t       ");
  Output.insert(Output.size(), 1, (char)186);

  Output.append("\n");
  Output.insert(Output.size(), 1, (char)200);
  Output.insert(Output.size(), 62, (char)205);
  Output.insert(Output.size(), 1, (char)188);

  // Bottom bar
  Output.append("\n");
  Output.insert(Output.size(), 1, (char)201);
  Output.insert(Output.size(), 62, (char)205);
  Output.insert(Output.size(), 1, (char)187);

  Output.append("\n");
  Output.insert(Output.size(), 1, (char)186);
  Output.append(RED);
  Output.append("\t\t\t    Hangman\t\t\t       ");
  Output.append(WHITE);
  Output.insert(Output.size(), 1, (char)186);

  Output.append("\n");
  Output.insert(Output.size(), 1, (char)200);
  Output.insert(Output.size(), 62, (char)205);
  Output.insert(Output.size(), 1, (char)188);

  while (!InputValid)
  {
    InputValid = true;

    Display_Game(0, std::to_string(NumberOfPlayers), AIDifficulty, IncorrectGuesses, "", "", false);
    std::cout << Output;

    SetConsoleCursorPosition( ConsoleHandle, { 39, 13 } );

    std::getline(std::cin, Input);

    if (Input.size() < 3 || Input.size() > 14)
    {
      InputValid = false;
      continue;
    }

    Capitalise_Word(Input);

    for (unsigned int i = 0; i < Input.size(); i++)
    {
      if (Input[i] < 'A' || Input[i] > 'Z')
      {
        InputValid = false;
        break;
      }
    }
  }

  return Input;
}

std::string Get_Word_To_Be_Guessed_From_AI(void)
{
  std::vector<std::string> Words = Generate_Word_List();
  return Words[std::rand() % Words.size()];
}

void Display_Game(const unsigned int &NumberOfErrors,
                  const std::string &NumberOfPlayers,
                  const std::string &AIDifficulty,
                  const std::vector<std::string> &IncorrectGuesses,
                  const std::string &CurrentGuessOfWord,
                  const std::string &WordToBeGuessed,
                  const bool &GameOver)
{
  Clear_Terminal();

  std::string Output;

  // Top bar
  Output.append(WHITE);
  Output.insert(Output.size(), 1, (char)201);
  Output.insert(Output.size(), 62, (char)205);
  Output.insert(Output.size(), 1, (char)187);

  Output.append("\n");
  Output.insert(Output.size(), 1, (char)186);
  Output.append(RED);
  Output.append("\t\t\t Terminal-Games\t\t\t       ");
  Output.append(WHITE);
  Output.insert(Output.size(), 1, (char)186);

  Output.append("\n");
  Output.insert(Output.size(), 1, (char)200);
  Output.insert(Output.size(), 62, (char)205);
  Output.insert(Output.size(), 1, (char)188);

  // Centre information
  Output.append("\n");
  Output.insert(Output.size(), 1, (char)201);
  Output.insert(Output.size(), 62, (char)205);
  Output.insert(Output.size(), 1, (char)187);
  Output.append("\n");

  switch (NumberOfErrors)
  {
  case 0:
    Output.insert(Output.size(), 1, (char)186);
    Output.append("\t\t\t\t\t\t\t       ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append("\t\t\t\t\t\t\t       ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    if (NumberOfPlayers == "N/A")
      Output.append("\t\t    # of Players = " + NumberOfPlayers + "\t\t\t       ");
    else
      Output.append("\t\t     # of Players = " + NumberOfPlayers + "\t\t\t       ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append("\t\t\t\t\t\t\t       ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    if (AIDifficulty == "N/A")
      Output.append("\t\t    AI Difficulty = " + AIDifficulty + "\t\t\t       ");
    else
      Output.append("\t\t   AI Difficulty = " + AIDifficulty + "\t\t\t       ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append("\t\t\t\t\t\t\t       ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append("\t\t\t\t\t\t\t       ");
    Output.insert(Output.size(), 1, (char)186);
    break;

  case 1:
    Output.insert(Output.size(), 1, (char)186);
    Output.append("\t\t\t\t\t\t\t       ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append("\t\t\t\t\t   Incorrect Guesses   ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append("\t\t     # of Players = " + NumberOfPlayers + "\t\t\t       ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append("\t\t\t\t\t   " + IncorrectGuesses[0] + "\t\t       ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    if (AIDifficulty == "N/A")
      Output.append("\t\t    AI Difficulty = " + AIDifficulty + "\t\t\t       ");
    else
      Output.append("\t\t   AI Difficulty = " + AIDifficulty + "\t\t\t       ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append("\t\t\t\t\t\t\t       ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append(" ");
    Output.insert(Output.size(), 9, (char)196);
    Output.append("\t\t\t\t\t\t       ");
    Output.insert(Output.size(), 1, (char)186);
    break;

  case 2:
    Output.insert(Output.size(), 1, (char)186);
    Output.append("\t\t\t\t\t\t\t       ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append("     ");
    Output.insert(Output.size(), 1, (char)179);
    Output.append("\t\t\t\t\t   Incorrect Guesses   ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append("     ");
    Output.insert(Output.size(), 1, (char)179);
    Output.append("\t\t     # of Players = " + NumberOfPlayers + "\t\t\t       ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append("     ");
    Output.insert(Output.size(), 1, (char)179);
    Output.append("\t\t\t\t\t   " + IncorrectGuesses[0] + "   " + IncorrectGuesses[1] + "\t       ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append("     ");
    Output.insert(Output.size(), 1, (char)179);
    if (AIDifficulty == "N/A")
      Output.append("\t\t    AI Difficulty = " + AIDifficulty + "\t\t\t       ");
    else
      Output.append("\t\t   AI Difficulty = " + AIDifficulty + "\t\t\t       ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append("     ");
    Output.insert(Output.size(), 1, (char)179);
    Output.append("\t\t\t\t\t\t\t       ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append(" ");
    Output.insert(Output.size(), 4, (char)196);
    Output.insert(Output.size(), 1, (char)193);
    Output.insert(Output.size(), 4, (char)196);
    Output.append("\t\t\t\t\t\t       ");
    Output.insert(Output.size(), 1, (char)186);
    break;

  case 3:
    Output.insert(Output.size(), 1, (char)186);
    Output.append("     ");
    Output.insert(Output.size(), 1, (char)218);
    Output.insert(Output.size(), 8, (char)196);
    Output.append("\t\t\t\t\t\t       ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append("     ");
    Output.insert(Output.size(), 1, (char)179);
    Output.append("\t\t\t\t\t   Incorrect Guesses   ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append("     ");
    Output.insert(Output.size(), 1, (char)179);
    Output.append("\t\t     # of Players = " + NumberOfPlayers + "\t\t\t       ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append("     ");
    Output.insert(Output.size(), 1, (char)179);
    Output.append("\t\t\t\t\t   " + IncorrectGuesses[0] + "   " + IncorrectGuesses[1] + "   " + IncorrectGuesses[2] + "\t       ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append("     ");
    Output.insert(Output.size(), 1, (char)179);
    if (AIDifficulty == "N/A")
      Output.append("\t\t    AI Difficulty = " + AIDifficulty + "\t\t\t       ");
    else
      Output.append("\t\t   AI Difficulty = " + AIDifficulty + "\t\t\t       ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append("     ");
    Output.insert(Output.size(), 1, (char)179);
    Output.append("\t\t\t\t\t\t\t       ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append(" ");
    Output.insert(Output.size(), 4, (char)196);
    Output.insert(Output.size(), 1, (char)193);
    Output.insert(Output.size(), 4, (char)196);
    Output.append("\t\t\t\t\t\t       ");
    Output.insert(Output.size(), 1, (char)186);
    break;

  case 4:
    Output.insert(Output.size(), 1, (char)186);
    Output.append("     ");
    Output.insert(Output.size(), 1, (char)218);
    Output.insert(Output.size(), 7, (char)196);
    Output.insert(Output.size(), 1, (char)191);
    Output.append("\t\t\t\t\t\t       ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append("     ");
    Output.insert(Output.size(), 1, (char)179);
    Output.append("       ");
    Output.insert(Output.size(), 1, (char)179);
    Output.append("\t\t\t\t   Incorrect Guesses   ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append("     ");
    Output.insert(Output.size(), 1, (char)179);
    Output.append("\t\t     # of Players = " + NumberOfPlayers + "\t\t\t       ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append("     ");
    Output.insert(Output.size(), 1, (char)179);
    Output.append("\t\t\t\t\t   " + IncorrectGuesses[0] + "   " + IncorrectGuesses[1] + "   " + IncorrectGuesses[2] + "   " + IncorrectGuesses[3] + "       ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append("     ");
    Output.insert(Output.size(), 1, (char)179);
    if (AIDifficulty == "N/A")
      Output.append("\t\t    AI Difficulty = " + AIDifficulty + "\t\t\t       ");
    else
      Output.append("\t\t   AI Difficulty = " + AIDifficulty + "\t\t\t       ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append("     ");
    Output.insert(Output.size(), 1, (char)179);
    Output.append("\t\t\t\t\t\t\t       ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append(" ");
    Output.insert(Output.size(), 4, (char)196);
    Output.insert(Output.size(), 1, (char)193);
    Output.insert(Output.size(), 4, (char)196);
    Output.append("\t\t\t\t\t\t       ");
    Output.insert(Output.size(), 1, (char)186);
    break;

  case 5:
    Output.insert(Output.size(), 1, (char)186);
    Output.append("     ");
    Output.insert(Output.size(), 1, (char)218);
    Output.insert(Output.size(), 7, (char)196);
    Output.insert(Output.size(), 1, (char)191);
    Output.append("\t\t\t\t\t\t       ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append("     ");
    Output.insert(Output.size(), 1, (char)179);
    Output.append("       ");
    Output.insert(Output.size(), 1, (char)179);
    Output.append("\t\t\t\t   Incorrect Guesses   ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append("     ");
    Output.insert(Output.size(), 1, (char)179);
    Output.append("       O      # of Players = " + NumberOfPlayers + "\t\t\t       ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append("     ");
    Output.insert(Output.size(), 1, (char)179);
    Output.append("\t\t\t\t\t   " + IncorrectGuesses[0] + "   " + IncorrectGuesses[1] + "   " + IncorrectGuesses[2] + "   " + IncorrectGuesses[3] + "   " + IncorrectGuesses[4] + "   ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append("     ");
    Output.insert(Output.size(), 1, (char)179);
    if (AIDifficulty == "N/A")
      Output.append("\t\t    AI Difficulty = " + AIDifficulty + "\t\t\t       ");
    else
      Output.append("\t\t   AI Difficulty = " + AIDifficulty + "\t\t\t       ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append("     ");
    Output.insert(Output.size(), 1, (char)179);
    Output.append("\t\t\t\t\t\t\t       ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append(" ");
    Output.insert(Output.size(), 4, (char)196);
    Output.insert(Output.size(), 1, (char)193);
    Output.insert(Output.size(), 4, (char)196);
    Output.append("\t\t\t\t\t\t       ");
    Output.insert(Output.size(), 1, (char)186);
    break;

  case 6:
    Output.insert(Output.size(), 1, (char)186);
    Output.append("     ");
    Output.insert(Output.size(), 1, (char)218);
    Output.insert(Output.size(), 7, (char)196);
    Output.insert(Output.size(), 1, (char)191);
    Output.append("\t\t\t\t\t\t       ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append("     ");
    Output.insert(Output.size(), 1, (char)179);
    Output.append("       ");
    Output.insert(Output.size(), 1, (char)179);
    Output.append("\t\t\t\t   Incorrect Guesses   ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append("     ");
    Output.insert(Output.size(), 1, (char)179);
    Output.append("       O      # of Players = " + NumberOfPlayers + "\t\t\t       ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append("     ");
    Output.insert(Output.size(), 1, (char)179);
    Output.append("       ");
    Output.insert(Output.size(), 1, (char)179);
    Output.append("\t\t\t\t   " + IncorrectGuesses[0] + "   " + IncorrectGuesses[1] + "   " + IncorrectGuesses[2] + "   " + IncorrectGuesses[3] + "   " + IncorrectGuesses[4] + "   ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append("     ");
    Output.insert(Output.size(), 1, (char)179);
    if (AIDifficulty == "N/A")
      Output.append("\t\t    AI Difficulty = " + AIDifficulty + "\t\t\t       ");
    else
      Output.append("\t\t   AI Difficulty = " + AIDifficulty + "\t\t\t       ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append("     ");
    Output.insert(Output.size(), 1, (char)179);
    Output.append("\t\t\t\t\t   " + IncorrectGuesses[5] + "\t\t       ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append(" ");
    Output.insert(Output.size(), 4, (char)196);
    Output.insert(Output.size(), 1, (char)193);
    Output.insert(Output.size(), 4, (char)196);
    Output.append("\t\t\t\t\t\t       ");
    Output.insert(Output.size(), 1, (char)186);
    break;

  case 7:
    Output.insert(Output.size(), 1, (char)186);
    Output.append("     ");
    Output.insert(Output.size(), 1, (char)218);
    Output.insert(Output.size(), 7, (char)196);
    Output.insert(Output.size(), 1, (char)191);
    Output.append("\t\t\t\t\t\t       ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append("     ");
    Output.insert(Output.size(), 1, (char)179);
    Output.append("       ");
    Output.insert(Output.size(), 1, (char)179);
    Output.append("\t\t\t\t   Incorrect Guesses   ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append("     ");
    Output.insert(Output.size(), 1, (char)179);
    Output.append("       O      # of Players = " + NumberOfPlayers + "\t\t\t       ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append("     ");
    Output.insert(Output.size(), 1, (char)179);
    Output.append("       ");
    Output.insert(Output.size(), 1, (char)179);
    Output.append("\t\t\t\t   " + IncorrectGuesses[0] + "   " + IncorrectGuesses[1] + "   " + IncorrectGuesses[2] + "   " + IncorrectGuesses[3] + "   " + IncorrectGuesses[4] + "   ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append("     ");
    Output.insert(Output.size(), 1, (char)179);
    if (AIDifficulty == "N/A")
      Output.append("      /\t    AI Difficulty = " + AIDifficulty + "\t\t\t       ");
    else
      Output.append("      /\t   AI Difficulty = " + AIDifficulty + "\t\t\t       ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append("     ");
    Output.insert(Output.size(), 1, (char)179);
    Output.append("\t\t\t\t\t   " + IncorrectGuesses[5] + "   " + IncorrectGuesses[6] + "\t       ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append(" ");
    Output.insert(Output.size(), 4, (char)196);
    Output.insert(Output.size(), 1, (char)193);
    Output.insert(Output.size(), 4, (char)196);
    Output.append("\t\t\t\t\t\t       ");
    Output.insert(Output.size(), 1, (char)186);
    break;

  case 8:
   Output.insert(Output.size(), 1, (char)186);
    Output.append("     ");
    Output.insert(Output.size(), 1, (char)218);
    Output.insert(Output.size(), 7, (char)196);
    Output.insert(Output.size(), 1, (char)191);
    Output.append("\t\t\t\t\t\t       ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append("     ");
    Output.insert(Output.size(), 1, (char)179);
    Output.append("       ");
    Output.insert(Output.size(), 1, (char)179);
    Output.append("\t\t\t\t   Incorrect Guesses   ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append("     ");
    Output.insert(Output.size(), 1, (char)179);
    Output.append("       O      # of Players = " + NumberOfPlayers + "\t\t\t       ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append("     ");
    Output.insert(Output.size(), 1, (char)179);
    Output.append("       ");
    Output.insert(Output.size(), 1, (char)179);
    Output.append("\t\t\t\t   " + IncorrectGuesses[0] + "   " + IncorrectGuesses[1] + "   " + IncorrectGuesses[2] + "   " + IncorrectGuesses[3] + "   " + IncorrectGuesses[4] + "   ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append("     ");
    Output.insert(Output.size(), 1, (char)179);
    if (AIDifficulty == "N/A")
      Output.append("      / \\    AI Difficulty = " + AIDifficulty + "\t\t\t       ");
    else
      Output.append("      / \\   AI Difficulty = " + AIDifficulty + "\t\t\t       ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append("     ");
    Output.insert(Output.size(), 1, (char)179);
    Output.append("\t\t\t\t\t   " + IncorrectGuesses[5] + "   " + IncorrectGuesses[6] + "   " + IncorrectGuesses[7] + "\t       ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append(" ");
    Output.insert(Output.size(), 4, (char)196);
    Output.insert(Output.size(), 1, (char)193);
    Output.insert(Output.size(), 4, (char)196);
    Output.append("\t\t\t\t\t\t       ");
    Output.insert(Output.size(), 1, (char)186);
    break;

  case 9:
    Output.insert(Output.size(), 1, (char)186);
    Output.append("     ");
    Output.insert(Output.size(), 1, (char)218);
    Output.insert(Output.size(), 7, (char)196);
    Output.insert(Output.size(), 1, (char)191);
    Output.append("\t\t\t\t\t\t       ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append("     ");
    Output.insert(Output.size(), 1, (char)179);
    Output.append("       ");
    Output.insert(Output.size(), 1, (char)179);
    Output.append("\t\t\t\t   Incorrect Guesses   ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append("     ");
    Output.insert(Output.size(), 1, (char)179);
    Output.append("       O      # of Players = " + NumberOfPlayers + "\t\t\t       ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append("     ");
    Output.insert(Output.size(), 1, (char)179);
    Output.append("      /");
    Output.insert(Output.size(), 1, (char)179);
    Output.append("\t\t\t\t   " + IncorrectGuesses[0] + "   " + IncorrectGuesses[1] + "   " + IncorrectGuesses[2] + "   " + IncorrectGuesses[3] + "   " + IncorrectGuesses[4] + "   ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append("     ");
    Output.insert(Output.size(), 1, (char)179);
    if (AIDifficulty == "N/A")
      Output.append("      / \\    AI Difficulty = " + AIDifficulty + "\t\t\t       ");
    else
      Output.append("      / \\   AI Difficulty = " + AIDifficulty + "\t\t\t       ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append("     ");
    Output.insert(Output.size(), 1, (char)179);
    Output.append("\t\t\t\t\t   " + IncorrectGuesses[5] + "   " + IncorrectGuesses[6] + "   " + IncorrectGuesses[7] + "   " + IncorrectGuesses[8] + "       ");

    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append(" ");
    Output.insert(Output.size(), 4, (char)196);
    Output.insert(Output.size(), 1, (char)193);
    Output.insert(Output.size(), 4, (char)196);
    Output.append("\t\t\t\t\t\t       ");
    Output.insert(Output.size(), 1, (char)186);
    break;

  case 10:
    Output.insert(Output.size(), 1, (char)186);
    Output.append("     ");
    Output.insert(Output.size(), 1, (char)218);
    Output.insert(Output.size(), 7, (char)196);
    Output.insert(Output.size(), 1, (char)191);
    Output.append("\t\t\t\t\t\t       ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append("     ");
    Output.insert(Output.size(), 1, (char)179);
    Output.append("       ");
    Output.insert(Output.size(), 1, (char)179);
    Output.append("\t\t\t\t   Incorrect Guesses   ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append("     ");
    Output.insert(Output.size(), 1, (char)179);
    Output.append("       O      # of Players = " + NumberOfPlayers + "\t\t\t       ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append("     ");
    Output.insert(Output.size(), 1, (char)179);
    Output.append("      /");
    Output.insert(Output.size(), 1, (char)179);
    Output.append("\\\t\t\t   " + IncorrectGuesses[0] + "   " + IncorrectGuesses[1] + "   " + IncorrectGuesses[2] + "   " + IncorrectGuesses[3] + "   " + IncorrectGuesses[4] + "   ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append("     ");
    Output.insert(Output.size(), 1, (char)179);
    if (AIDifficulty == "N/A")
      Output.append("      / \\    AI Difficulty = " + AIDifficulty + "\t\t\t       ");
    else
      Output.append("      / \\   AI Difficulty = " + AIDifficulty + "\t\t\t       ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append("     ");
    Output.insert(Output.size(), 1, (char)179);
    Output.append("\t\t\t\t\t   " + IncorrectGuesses[5] + "   " + IncorrectGuesses[6] + "   " + IncorrectGuesses[7] + "   " + IncorrectGuesses[8] + "   " + IncorrectGuesses[9] + "   ");
    Output.insert(Output.size(), 1, (char)186);
    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append(" ");
    Output.insert(Output.size(), 4, (char)196);
    Output.insert(Output.size(), 1, (char)193);
    Output.insert(Output.size(), 4, (char)196);
    Output.append("\t\t\t\t\t\t       ");
    Output.insert(Output.size(), 1, (char)186);
    break;

  default:
  break;
  }

  // Word to be guessed, and thus current guess of word, are limited to a size in between 3 and 14
  Output.append("\n");
  Output.insert(Output.size(), 1, (char)186);
  for (unsigned int i = 0; i < CurrentGuessOfWord.size(); i++)
  {
    Output.append(" ");
    Output.insert(Output.size(), 1, CurrentGuessOfWord[i]);
  }
  if (GameOver && NumberOfErrors == 10)
  {
    Output.append("   (The word was " + WordToBeGuessed + ")");
    for (unsigned int i = 0; i < (62 - WordToBeGuessed.size()*3 - 18); i++)
      Output.append(" ");
  }
  else
    for (unsigned int i = 0; i < (62 - WordToBeGuessed.size()*2); i++)
      Output.append(" ");

  Output.insert(Output.size(), 1, (char)186);
  Output.append("\n");
  Output.insert(Output.size(), 1, (char)186);
  Output.append("\t\t\t\t\t\t\t       ");
  Output.insert(Output.size(), 1, (char)186);

  Output.append("\n");

  std::cout << Output;
}

bool Winning_Conditions_Met(const unsigned int &NumberOfErrors,
                            const std::string &WordToBeGuessed,
                            const std::string &CurrentGuessOfWord)
{
  if (NumberOfErrors == 10)
    return true;

  else
  {
    for (unsigned int i = 0; i < WordToBeGuessed.size(); i++)
      if (WordToBeGuessed[i] != CurrentGuessOfWord[i])
        return false;

    return true;
  }
}

void Get_Next_User_Guess(unsigned int &NumberOfErrors,
                         const unsigned int &NumberOfPlayers,
                         const std::string &AIDifficulty,
                         std::vector<std::string> &IncorrectGuesses,
                         std::vector<std::string> &CorrectGuesses,
                         std::vector<std::string> &ValidMovesRemaining,
                         std::string &CurrentGuessOfWord,
                         const std::string &WordToBeGuessed)
{
  std::string UserGuess;
  unsigned int CurrentSelection = 0;
  unsigned char KeyPress = 0;

  while (KeyPress != '\r')
  {
    switch (KeyPress)
    {
    case 72: // up arrow key
      if (CurrentSelection == 0)
        CurrentSelection = ValidMovesRemaining.size() - 1;
      else
        CurrentSelection--;

    break;

    case 80: // down arrow key
      if (CurrentSelection == ValidMovesRemaining.size() - 1)
        CurrentSelection = 0;
      else
        CurrentSelection++;
    break;

    default:
    break;
    }

    Display_Game(NumberOfErrors, std::to_string(NumberOfPlayers), AIDifficulty, IncorrectGuesses, CurrentGuessOfWord, WordToBeGuessed, false);

    std::string Output;
    Output.insert(Output.size(), 1, (char)186);
    Output.append("\t\t\t\t\t\t\t       ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append("Guesser, please enter your next guess: ");
    Output.append(BLUE);
    Output.append(ValidMovesRemaining[CurrentSelection]);
    Output.append(WHITE);
    Output.append("\t\t       ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append("\t\t\t\t\t\t\t       ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append("\t\t\t\t\t\t\t       ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append("\t\t\t\t\t\t\t       ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append("\t\t\t\t\t\t\t       ");
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)200);
    Output.insert(Output.size(), 62, (char)205);
    Output.insert(Output.size(), 1, (char)188);

    // Bottom bar
    Output.append("\n");
    Output.insert(Output.size(), 1, (char)201);
    Output.insert(Output.size(), 62, (char)205);
    Output.insert(Output.size(), 1, (char)187);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.append(RED);
    Output.append("\t\t\t    Hangman\t\t\t       ");
    Output.append(WHITE);
    Output.insert(Output.size(), 1, (char)186);

    Output.append("\n");
    Output.insert(Output.size(), 1, (char)200);
    Output.insert(Output.size(), 62, (char)205);
    Output.insert(Output.size(), 1, (char)188);

    std::cout << Output;

    KeyPress = _getch();
  }

  UserGuess = ValidMovesRemaining[CurrentSelection];
  auto CommandPosition = std::find(ValidMovesRemaining.begin(), ValidMovesRemaining.end(), UserGuess);
  ValidMovesRemaining.erase(CommandPosition);

  if (!Check_Guess_Against_Word_To_Be_Guessed(WordToBeGuessed, UserGuess[0], CurrentGuessOfWord))
  {
    IncorrectGuesses.push_back(UserGuess);
    NumberOfErrors++;
  }
  else
    CorrectGuesses.push_back(UserGuess);
}

void Get_Next_AI_Guess(unsigned int &NumberOfErrors,
                       const unsigned int &NumberOfPlayers,
                       const std::string &AIDifficulty,
                       std::vector<std::string> &IncorrectGuesses,
                       std::vector<std::string> &CorrectGuesses,
                       std::vector<std::string> &ValidMovesRemaining,
                       std::string &CurrentGuessOfWord,
                       const std::string &WordToBeGuessed)
{
  std::string Guess = ValidMovesRemaining[std::rand() % ValidMovesRemaining.size()];
  auto CommandPosition = std::find(ValidMovesRemaining.begin(), ValidMovesRemaining.end(), Guess);
  ValidMovesRemaining.erase(CommandPosition);

  if (!Check_Guess_Against_Word_To_Be_Guessed(WordToBeGuessed, Guess[0], CurrentGuessOfWord))
  {
    IncorrectGuesses.push_back(Guess);
    NumberOfErrors++;
  }
  else
    CorrectGuesses.push_back(Guess);
}

bool Check_Guess_Against_Word_To_Be_Guessed(const std::string &WordToBeGuessed,
                                            const unsigned char &Guess,
                                            std::string &CurrentGuessOfWord)
{
  bool IsGuessCorrect = false;

  for (unsigned int i = 0; i < WordToBeGuessed.size(); i++)
    if (WordToBeGuessed[i] == Guess)
    {
      IsGuessCorrect = true;
      CurrentGuessOfWord[i] = Guess;
    }

  return IsGuessCorrect;
}

void Display_Game_Over_Message(const unsigned int &NumberOfErrors,
                               const unsigned int &NumberOfPlayers,
                               const std::string &AIDifficulty,
                               const std::vector<std::string> &IncorrectGuesses,
                               const std::string &CurrentGuessOfWord,
                               const std::string &WordToBeGuessed,
                               const unsigned int &NumberOfTurns,
                               bool &GameIsRunning)
{
  Display_Game(NumberOfErrors, std::to_string(NumberOfPlayers), AIDifficulty, IncorrectGuesses, CurrentGuessOfWord, WordToBeGuessed, true);

  std::string Output;
  Output.insert(Output.size(), 1, (char)186);
  Output.append("\t\t\t\t\t\t\t       ");
  Output.insert(Output.size(), 1, (char)186);

  Output.append("\n");
  Output.insert(Output.size(), 1, (char)186);
  Output.append("\t\t\t   GAME OVER\t\t\t       ");
  Output.insert(Output.size(), 1, (char)186);

  Output.append("\n");
  Output.insert(Output.size(), 1, (char)186);
  Output.append("\t\t\t\t\t\t\t       ");
  Output.insert(Output.size(), 1, (char)186);

  Output.append("\n");
  Output.insert(Output.size(), 1, (char)186);
  if (NumberOfErrors == 10)
    Output.append("    The word setter has won! The game lasted for " + std::to_string(NumberOfTurns) + " turns!    ");
  else
    Output.append("\t The guesser has won! The game lasted " + std::to_string(NumberOfTurns) + " turns.\t       ");
  Output.insert(Output.size(), 1, (char)186);

  Output.append("\n");
  Output.insert(Output.size(), 1, (char)186);
  Output.append("\t\t\t\t\t\t\t       ");
  Output.insert(Output.size(), 1, (char)186);

  Output.append("\n");
  Output.insert(Output.size(), 1, (char)186);
  Output.append("     Press 'Q' to quit OR any other key to play again...      ");
  Output.insert(Output.size(), 1, (char)186);

  Output.append("\n");
  Output.insert(Output.size(), 1, (char)200);
  Output.insert(Output.size(), 62, (char)205);
  Output.insert(Output.size(), 1, (char)188);

  // Bottom bar
  Output.append("\n");
  Output.insert(Output.size(), 1, (char)201);
  Output.insert(Output.size(), 62, (char)205);
  Output.insert(Output.size(), 1, (char)187);

  Output.append("\n");
  Output.insert(Output.size(), 1, (char)186);
  Output.append(RED);
  Output.append("\t\t\t    Hangman\t\t\t       ");
  Output.append(WHITE);
  Output.insert(Output.size(), 1, (char)186);

  Output.append("\n");
  Output.insert(Output.size(), 1, (char)200);
  Output.insert(Output.size(), 62, (char)205);
  Output.insert(Output.size(), 1, (char)188);

  std::cout << Output;

  if (_getch() == 'q')
  {
    GameIsRunning = false;
    Clear_Terminal();
  }
}
