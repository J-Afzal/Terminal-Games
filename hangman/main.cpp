//
//  @File: main.cpp for Hangman
//  @Author: Junaid Afzal
//

#include "Hangman.hpp"

int main(void)
{
  bool GameIsRunning = true;

  while (GameIsRunning)
  {
    // Hangman states represents the different states the hangman drawing can be in
    std::vector<std::string> IncorrectGuesses, CorrectGuesses;
    std::string WordToBeGuessed, CurrentGuessOfWord, PlayerThatIsGuessing;
    unsigned int NumberOfPlayers, NumberOfErrors = 0, NumberOfTurns = 0;

    // Sets up the variables required by game
    Setup_Game(WordToBeGuessed, CurrentGuessOfWord, NumberOfPlayers, PlayerThatIsGuessing);

    // While the current guess of word and word to be guessed are not the same AND while the hangman drawing
    // has not reached its final stage, continue playing the game
    while (!Game_Over(NumberOfErrors) && !Winning_Conditions_Met(WordToBeGuessed, CurrentGuessOfWord))
    {
      // Display_Game(NumberOfErrors, CurrentGuessOfWord, IncorrectGuesses);

      std::string Guess;

      // Prompt the human or computer user for a guess depending upon how many human players there are
      // The display is updated before asking for a guess with the current hangman state, the current guess
      // of word and all incorrect guesses (including words)
      if (PlayerThatIsGuessing == "HUMAN")
        Guess = Ask_User_For_Next_Guess(IncorrectGuesses, CorrectGuesses, NumberOfErrors, CurrentGuessOfWord);
      else
        Guess = Ask_Computer_For_Next_Guess(IncorrectGuesses, CorrectGuesses, NumberOfErrors, CurrentGuessOfWord);

      if (!Check_Guess_Against_Word(Guess, WordToBeGuessed, CurrentGuessOfWord))
      {
        IncorrectGuesses.push_back(Guess);
        NumberOfErrors++;
      }
      else
        CorrectGuesses.push_back(Guess);

      NumberOfTurns++;
    }

    // Displays the winning or losing message
    Display_Game_Over_Message(NumberOfErrors, CurrentGuessOfWord, IncorrectGuesses, NumberOfTurns, WordToBeGuessed, GameIsRunning);
  }

  return 0;
}
