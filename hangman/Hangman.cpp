//
//  @File: Hangman.cpp
//  @Author: Junaid Afzal
//

#include "Hangman.hpp"
#include <iostream>
#include <ctime>
#include <limits>
#include <fstream>
#include <conio.h>

void Setup_Game(std::string &WordToBeGuessed,
                std::string &CurrentGuessOfWord,
                unsigned int &NumberOfPlayers,
                std::string &PlayerThatIsGuessing)
{
  // Set seed of srand to time(0) so pseudo random
  std::srand((unsigned int)std::time(0));

  NumberOfPlayers = Get_Number_Of_Players();

  if (NumberOfPlayers == 2)
  {
    // Prompt the user for the word to be guessed
    WordToBeGuessed = Ask_User_For_Word_To_Be_Guessed(NumberOfPlayers, PlayerThatIsGuessing);

    // All players are humans so no need to ask
    PlayerThatIsGuessing = "HUMAN";
  }

  else if (NumberOfPlayers == 1)
  {
    // Prompts the user for who is guessing the word (human or computer)
    PlayerThatIsGuessing = Ask_User_For_Who_Is_Guessing(NumberOfPlayers);

    if (PlayerThatIsGuessing == "HUMAN")
      // Prompt the computer for the word to be guessed
      WordToBeGuessed = Ask_Computer_For_Word_To_Be_Guessed();

    else
      WordToBeGuessed = Ask_User_For_Word_To_Be_Guessed(NumberOfPlayers, PlayerThatIsGuessing);
  }

  else if (NumberOfPlayers == 0)
  {
    // Prompt the computer for the word to be guessed
    WordToBeGuessed = Ask_Computer_For_Word_To_Be_Guessed();

    // All players are computers so no need to ask
    PlayerThatIsGuessing = "COMPUTER";
  }

  // Create the current guess to be the same size as the word to be guessed but only containing underscores
  for (unsigned int i = 0; i < WordToBeGuessed.size(); i++)
    CurrentGuessOfWord.push_back('_');
}

unsigned int Get_Number_Of_Players(void)
{
  bool IsValueCorrect = false; // Flag for if input value is valid
  unsigned int NumberOfPlayers = 0;

  while (!IsValueCorrect)
  {
    Clear_Terminal();
    std::cout << "--------------------Hangman--------------------\n\n";
    std::cout << "Enter the number of players: ";

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

std::string Ask_User_For_Word_To_Be_Guessed(const unsigned int &NumberOfPlayers,
                                            const std::string &PlayerThatIsGuessing)
{
  bool IsValueCorrect = false; // Flag for if input value is valid
  std::string WordToBeGuessed; // No spaces or - allowed

  while (!IsValueCorrect)
  {
    // Set flag to true by default as difficult to continue to to next iteration of while loop
    // within a nested if statements within nested for loops
    IsValueCorrect = true;

    Clear_Terminal();
    std::cout << "--------------------Hangman--------------------";
    std::cout << "\n\nEnter the number of players: " << NumberOfPlayers;
    if (NumberOfPlayers == 1)
      std::cout << "\n\nEnter player that will be guessing (HUMAN or COMPUTER): " << PlayerThatIsGuessing;
    std::cout << "\n\nEnter the word to be guessed: ";

    std::cin >> WordToBeGuessed;

    if (std::cin.fail()) // Check if cin failed
    {
      // Clear buffer and retry
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      IsValueCorrect = false;
      continue;
    }

    // Only accept chars that are either capital or lowercase letters
    for (unsigned int i = 0; i < WordToBeGuessed.size(); i++)
    {
      if (WordToBeGuessed[i] < 'A')
      {
        // Clear buffer and retry
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        IsValueCorrect = false;
        break;
      }

      else if (WordToBeGuessed[i] > 'z')
      {
        // Clear buffer and retry
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        IsValueCorrect = false;
        break;
      }

      // Check for [ \ ] ^ _ ` as they occur in between the uppercase and lowercase letters blocks
      else if (WordToBeGuessed[i] >= 91 && WordToBeGuessed[i] <= 96)
      {
        // Clear buffer and retry
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        IsValueCorrect = false;
        break;
      }
    }
  }

  // Capitalise all letters so that only capital letter need to be dealt with
  Capitalise_Word(WordToBeGuessed);

  return WordToBeGuessed;
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

std::string Ask_User_For_Who_Is_Guessing(const unsigned int &NumberOfPlayers)
{
  bool IsValueCorrect = false; // Flag for if input value is valid
  std::string PlayerThatWillBeGuessing;

  while (!IsValueCorrect)
  {
    // Set flag to true by default as difficult to continue to to next iteration of while loop
    // within a nested if statements within nested for loops
    IsValueCorrect = true;

    Clear_Terminal();
    std::cout << "--------------------Hangman--------------------";
    std::cout << "\n\nEnter the number of players: " << NumberOfPlayers;
    std::cout << "\n\nEnter player that will be guessing (HUMAN or COMPUTER): ";

    std::cin >> PlayerThatWillBeGuessing;

    if (std::cin.fail()) // Check if cin failed
    {
      // Clear buffer and retry
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      IsValueCorrect = false;
      continue;
    }

    // Only accept chars that are either capital or lowercase letters
    for (unsigned int i = 0; i < PlayerThatWillBeGuessing.size(); i++)
    {
      if (PlayerThatWillBeGuessing[i] < 'A')
      {
        // Clear buffer and retry
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        IsValueCorrect = false;
        break;
      }

      else if (PlayerThatWillBeGuessing[i] > 'z')
      {
        // Clear buffer and retry
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        IsValueCorrect = false;
        break;
      }

      // Check for [ \ ] ^ _ ` as they occur in between the uppercase and lowercase letters blocks
      else if (PlayerThatWillBeGuessing[i] >= 91 && PlayerThatWillBeGuessing[i] <= 96)
      {
        // Clear buffer and retry
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        IsValueCorrect = false;
        break;
      }
    }

    // Capitalise all letters so that only capital letter need to be dealt with
    Capitalise_Word(PlayerThatWillBeGuessing);

    if (PlayerThatWillBeGuessing != "HUMAN" && PlayerThatWillBeGuessing != "COMPUTER")
    {
      IsValueCorrect = false;
      continue;
    }
  }

  return PlayerThatWillBeGuessing;
}

std::string Ask_Computer_For_Word_To_Be_Guessed(void)
{
  bool IsValueCorrect = false; // Flag for if input value is valid
  std::string WordToBeGuessed;

  while (!IsValueCorrect)
  {
    // Set flag to true by default as difficult to continue to to next iteration of while loop
    // within a nested if statements within nested for loops
    IsValueCorrect = true;

    std::ifstream WordList("Words.txt");

    if (WordList.is_open())
    {
      unsigned long int LineNumber = (std::rand() % 65189) + 1;
      unsigned long int CurrentLineNumber = 0;

      while (CurrentLineNumber != LineNumber)
      {
        std::getline(WordList, WordToBeGuessed);
        CurrentLineNumber++;
      }

      // Only accept chars that are either capital or lowercase letters
      for (unsigned int i = 0; i < WordToBeGuessed.size(); i++)
      {
        if (WordToBeGuessed[i] < 'A')
        {
          // Clear buffer and retry
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          IsValueCorrect = false;
          break;
        }

        else if (WordToBeGuessed[i] > 'z')
        {
          // Clear buffer and retry
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          IsValueCorrect = false;
          break;
        }

        // Check for [ \ ] ^ _ ` as they occur in between the uppercase and lowercase letters blocks
        else if (WordToBeGuessed[i] >= 91 && WordToBeGuessed[i] <= 96)
        {
          // Clear buffer and retry
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          IsValueCorrect = false;
          break;
        }
      }
    }

    else
    {
      std::cout << "Unable to open Words.txt, make sure it is in the same directory as the .exe or project file\n";
      exit(1);
    }
  }

  // Capitalise all letters so that only capital letter need to be dealt with
  Capitalise_Word(WordToBeGuessed);

  return WordToBeGuessed;
}

bool Game_Over(const unsigned int &NumberOfErrors)
{
  // 10 or more errors mean that the final state of the
  // hangman drawing has been reached
  if (NumberOfErrors >= 10)
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
                  const std::vector<std::string> &IncorrectGuesses)
{
  Clear_Terminal();

  std::cout << "--------------------Hangman--------------------\n\n";

  // Draw the hangman drawing
  switch (NumberOfErrors)
  {
  case 0:
    std::cout << "\n\n\n\n\n\n \n\n";
    break;

  case 1:
    std::cout << "\n\n\n\n\n\n─────────\n\n";
    break;

  case 2:
    std::cout << "\n    │\n    │\n    │\n    │\n    │\n────┴────\n\n";
    break;

  case 3:
    std::cout << "    ┌────────\n    │\n    │\n    │\n    │\n    │\n────┴────\n\n";
    break;

  case 4:
    std::cout << "    ┌───────┐\n    │       │\n    │\n    │\n    │\n    │\n────┴────\n\n";
    break;

  case 5:
    std::cout << "    ┌───────┐\n    │       │\n    │       O\n    │\n    │\n    │\n────┴────\n\n";
    break;

  case 6:
    std::cout << "    ┌───────┐\n    │       │\n    │       O\n    │       |\n    │\n    │\n────┴────\n\n";
    break;

  case 7:
    std::cout << "    ┌───────┐\n    │       │\n    │       O\n    │       |\n    │      /\n    │\n────┴────\n\n";
    break;

  case 8:
    std::cout << "    ┌───────┐\n    │       │\n    │       O\n    │       |\n    │      / \\\n    │\n────┴────\n\n";
    break;

  case 9:
    std::cout << "    ┌───────┐\n    │       │\n    │       O\n    │      /|\n    │      / \\\n    │\n────┴────\n\n";
    break;

  case 10:
    std::cout << "    ┌───────┐\n    │       │\n    │       O\n    │      /|\\\n    │      / \\\n    │\n────┴────\n\n";
    break;

  default:
    std::cout << "Error in Display_Game() switch statement\n";
    break;
  }

  // Current guess of word
  for (unsigned int i = 0; i < CurrentGuessOfWord.size(); i++)
    std::cout << CurrentGuessOfWord[i] << " ";

  // Incorrect guesses
  std::cout << "\n\nIncorrect Guesses:\n";
  for (unsigned int i = 0; i < IncorrectGuesses.size(); i++)
    std::cout << IncorrectGuesses[i] << "   ";
}

void Clear_Terminal(void)
{
  // ***Better alternative needed***
  // 100 new lines to clear console
  std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}

std::string Ask_User_For_Next_Guess(const std::vector<std::string> &IncorrectGuesses,
                                    const std::vector<std::string> &CorrectGuesses,
                                    const unsigned int &NumberOfErrors,
                                    const std::string &CurrentGuessOfWord)
{
  bool IsValueCorrect = false; // Flag for if input value is valid
  std::string Guess;

  while (!IsValueCorrect)
  {
    // Set flag to true by default as difficult to continue to to next iteration of while loop
    // within a nested if statements within nested for loops
    IsValueCorrect = true;

    Display_Game(NumberOfErrors, CurrentGuessOfWord, IncorrectGuesses);
    std::cout << "\n\nEnter your guess: ";

    std::cin >> Guess;

    if (std::cin.fail()) // Check if cin failed
    {
      // Clear buffer and retry
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      IsValueCorrect = false;
      continue;
    }

    // Only accept chars that are either capital or lowercase letters
    for (unsigned int i = 0; i < Guess.size(); i++)
    {
      if (Guess[i] < 'A')
      {
        // Clear buffer and retry
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        IsValueCorrect = false;
        break;
      }

      else if (Guess[i] > 'z')
      {
        // Clear buffer and retry
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        IsValueCorrect = false;
        break;
      }

      // Check for [ \ ] ^ _ ` as they occur in between the uppercase and lowercase letters blocks
      else if (Guess[i] >= 91 && Guess[i] <= 96)
      {
        // Clear buffer and retry
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        IsValueCorrect = false;
        break;
      }
    }

    // Capitalise all letters so that only capital letter need to be dealt with
    // and the word to be guessed has already been capitalised
    Capitalise_Word(Guess);

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

  return Guess;
}

std::string Ask_Computer_For_Next_Guess(const std::vector<std::string> &IncorrectGuesses,
                                        const std::vector<std::string> &CorrectGuesses,
                                        const unsigned int &NumberOfErrors,
                                        const std::string &CurrentGuessOfWord)
{
  bool IsValueCorrect = false; // Flag for if input value is valid
  std::string Guess = " ";

  while (!IsValueCorrect)
  {
    // Set flag to true by default as difficult to continue to to next iteration of while loop
    // within a nested if statements within nested for loops
    IsValueCorrect = true;

    // Computer will guess a random letter from A to Z
    Guess[0] = (std::rand() % 26) + 65;

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

  Display_Game(NumberOfErrors, CurrentGuessOfWord, IncorrectGuesses);
  // Output a message which is similar to human player guess
  std::cout << "\n\nComputer guessed: " << Guess << "\n\n\n\n";

  return Guess;
}

bool Check_Guess_Against_Word(const std::string &Guess,
                              const std::string &WordToBeGuessed,
                              std::string &CurrentGuessOfWord)
{
  bool IsGuessCorrect = false;

  // If below is true then guess is a letter and every occurrence of this letter
  // needs to be deposited is the current guess of word
  if (Guess.size() == 1)
  {
    for (unsigned int i = 0; i < WordToBeGuessed.size(); i++)
    {
      if (WordToBeGuessed[i] == Guess[0])
      {
        IsGuessCorrect = true;
        CurrentGuessOfWord[i] = Guess[0];
      }
    }
  }

  // If not then guess is a word and a simple check to see if they are the
  // same and if so return true and overwrite current guess
  else if (Guess == WordToBeGuessed)
  {
    CurrentGuessOfWord = Guess;
    IsGuessCorrect = true;
  }

  return IsGuessCorrect;
}

void Display_Game_Over_Message(const unsigned int &NumberOfErrors,
                               const std::string &CurrentGuessOfWord,
                               const std::vector<std::string> &IncorrectGuesses,
                               const unsigned int &NumberOfTurns,
                               const std::string &WordToBeGuessed,
                               bool &GameIsRunning)
{
  Display_Game(NumberOfErrors, CurrentGuessOfWord, IncorrectGuesses);
  // If the below is true then hangman has reached its final state and thus user has lost
  if (NumberOfErrors == 10)
    std::cout << "\n\nGAME OVER\n\nThe guessser has lost but lasted for " << NumberOfTurns << " turns!\n\nThe word was " << WordToBeGuessed;

  else
    std::cout << "\n\nGAME OVER\n\nThe guesser has won!\n\nThe game lasted " << NumberOfTurns << " turns";

  std::cout << "\n\nPress 'Q' to quit the game OR press any other key to play again...";

  // Gets key pressed and then checks and clears terminal window if replaying
  char Decision = _getch();

  if (Decision == 'q')
    GameIsRunning = false;

  else
    // Start from blank console
    Clear_Terminal();
}
