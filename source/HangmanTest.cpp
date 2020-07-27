#include "Hangman.hpp"

int main(void)
{
  //Variables for the Hangman game
  // - Hangman states representing the different states the hangman drawing can be in
  std::vector<std::string> IncorrectGuesses, CorrectGuesses;
  std::string WordToBeGuessed, CurrentGuessOfWord, PlayerThatIsGuessing;
  unsigned int NumberOfPlayers = 0, NumberOfErrors = 0, NumberOfTurns = 0;

  // Set seed of srand to time(0) so pseudo random
  std::srand((unsigned int)std::time(0));

  // Prompt the computer for the word to be guessed
  WordToBeGuessed = Ask_Computer_For_Word_To_Be_Guessed();

  // All players are computers so no need to ask
  PlayerThatIsGuessing = "COMPUTER";

  // Create the current guess to be the same size as the word to be guessed but only containing underscores
  for (unsigned int i = 0; i < WordToBeGuessed.size(); i++)
    CurrentGuessOfWord.push_back('_');

  // while the current guess of word and word to be guessed are not the same and the hangman drawing
  // has not reached its final stage continue playing game
  while (!Game_Over(NumberOfErrors) && !Winning_Conditions_Met(WordToBeGuessed, CurrentGuessOfWord))
  {
    std::string Guess;

    // Prompt the computer user for a guess
    Guess = Ask_Computer_For_Next_Guess(IncorrectGuesses, CorrectGuesses);

    // If the guess is incorrect then add to incorrect list and increment errors
    if (!Check_Guess_Against_Word(Guess, WordToBeGuessed, CurrentGuessOfWord))
    {
      IncorrectGuesses.push_back(Guess);
      NumberOfErrors++;
    }

    // Else add guess to correct list
    else
      CorrectGuesses.push_back(Guess);

    // Increment
    NumberOfTurns++;
  }
  
  return 0;
}
