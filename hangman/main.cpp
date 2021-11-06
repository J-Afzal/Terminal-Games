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
    std::vector<unsigned char> IncorrectGuesses, CorrectGuesses, ValidMovesRemaining;
    std::string WordToBeGuessed, CurrentGuessOfWord, PlayerThatIsGuessing, AIDifficulty = "N/A";
    unsigned int NumberOfPlayers, NumberOfErrors = 0, NumberOfTurns = 0;

    // Sets up the variables required by game
    Setup_Game(WordToBeGuessed, CurrentGuessOfWord, NumberOfPlayers, PlayerThatIsGuessing, IncorrectGuesses, AIDifficulty, ValidMovesRemaining);

    // While the current guess of word and word to be guessed are not the same AND while the hangman drawing
    // has not reached its final stage, continue playing the game
    while (!Winning_Conditions_Met(WordToBeGuessed, CurrentGuessOfWord, NumberOfErrors))
    {
      // Prompt the human or computer user for a guess depending upon how many human players there are
      // The display is updated before asking for a guess with the current hangman state, the current guess
      // of word and all incorrect guesses (including words)
      if (PlayerThatIsGuessing == "HUMAN")
        Ask_User_For_Next_Guess(IncorrectGuesses, CorrectGuesses, NumberOfErrors, CurrentGuessOfWord, AIDifficulty, NumberOfPlayers, WordToBeGuessed, ValidMovesRemaining);
      else
        Ask_Computer_For_Next_Guess(IncorrectGuesses, CorrectGuesses, NumberOfErrors, CurrentGuessOfWord, AIDifficulty, NumberOfPlayers, WordToBeGuessed, ValidMovesRemaining);

      NumberOfTurns++;
    }

    // Displays the winning or losing message
    Display_Game_Over_Message(NumberOfErrors, CurrentGuessOfWord, IncorrectGuesses, NumberOfTurns, WordToBeGuessed, GameIsRunning, AIDifficulty, NumberOfPlayers);
  }

  Clear_Terminal();

  return 0;
}
