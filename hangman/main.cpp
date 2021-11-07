//
//  @File: main.cpp for Hangman
//  @Author: Junaid Afzal
//

#include "hangman.hpp"
#include "functions.hpp"

int main(void)
{
  bool GameIsRunning = true;

  while (GameIsRunning)
  {
    // Hangman states represents the different states the hangman drawing can be in
    unsigned int NumberOfPlayers, NumberOfErrors = 0, NumberOfTurns = 0;
    std::string WordToBeGuessed, CurrentGuessOfWord, PlayerThatIsGuessing, AIDifficulty = "N/A";
    std::vector<std::string> CorrectGuesses, IncorrectGuesses, ValidMovesRemaining;

    // Sets up the variables required by game
    Setup_Game(NumberOfPlayers, PlayerThatIsGuessing, AIDifficulty, WordToBeGuessed, CurrentGuessOfWord, ValidMovesRemaining, IncorrectGuesses);

    // While the current guess of word and word to be guessed are not the same AND while the hangman drawing
    // has not reached its final stage, continue playing the game
    while (!Winning_Conditions_Met(NumberOfErrors, WordToBeGuessed, CurrentGuessOfWord))
    {
      // Prompt the human or AI user for a guess depending upon how many human players there are
      // The display is updated before asking for a guess with the current hangman state, the current guess
      // of word and all incorrect guesses (including words)
      if (PlayerThatIsGuessing == "HUMAN")
        Get_Next_User_Guess(NumberOfErrors, NumberOfPlayers, AIDifficulty, IncorrectGuesses, CorrectGuesses, ValidMovesRemaining, CurrentGuessOfWord, WordToBeGuessed);
      else
        Get_Next_AI_Guess(NumberOfErrors, NumberOfPlayers, AIDifficulty, IncorrectGuesses, CorrectGuesses, ValidMovesRemaining, CurrentGuessOfWord, WordToBeGuessed);

      NumberOfTurns++;
    }

    // Displays the winning or losing message
    Display_Game_Over_Message(NumberOfErrors, NumberOfPlayers, AIDifficulty, IncorrectGuesses, CurrentGuessOfWord, WordToBeGuessed, NumberOfTurns, GameIsRunning);
  }

  Clear_Terminal();

  return 0;
}
