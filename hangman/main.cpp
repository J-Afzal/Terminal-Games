/**
 * @file main.cpp
 * @author Junaid Afzal
 * @brief Game loop for Hangman
 * @version 1.0
 * @date 07-11-2021
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "hangman.hpp"
#include "functions.hpp"

int main(void)
{
  bool GameIsRunning = true;

  while (GameIsRunning)
  {
    unsigned int NumberOfPlayers, NumberOfErrors = 0, NumberOfTurns = 0;
    std::string WordToBeGuessed, CurrentGuessOfWord, PlayerThatIsGuessing, AIDifficulty;
    std::vector<std::string> CorrectGuesses, IncorrectGuesses, ValidMovesRemaining;

    Setup_Game(NumberOfPlayers, PlayerThatIsGuessing, AIDifficulty, WordToBeGuessed, CurrentGuessOfWord, ValidMovesRemaining, IncorrectGuesses);

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

  return 0;
}
