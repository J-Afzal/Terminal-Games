#include "Hangman.hpp"

int main(void)
{
  bool GameIsRunning = true;

  while (GameIsRunning)
  {
    //Variables for the Hangman game
    //Hangman states representing the different states the hangman drawing can be in
    std::vector<std::string> IncorrectGuesses, CorrectGuesses;
    std::string WordToBeGuessed, CurrentGuessOfWord, PlayerThatIsGuessing;
    unsigned int NumberOfPlayers, NumberOfErrors = 0, NumberOfTurns = 0;

    // Sets up the variables required by game
    Setup_Game(WordToBeGuessed, CurrentGuessOfWord, NumberOfPlayers, PlayerThatIsGuessing);

    // while the current guess of word and word to be guessed are not the same and the hangman drawing
    // has not reached its final stage continue playing game
    while (!Game_Over(NumberOfErrors) && !Winning_Conditions_Met(WordToBeGuessed, CurrentGuessOfWord))
    {
      // Displays the current hangman state, the current guess of word and all incorrect guesses
      Display_Game(NumberOfErrors, CurrentGuessOfWord, IncorrectGuesses);

      std::string Guess;

      // Prompt the human or computer user for a guess depending upon how many human players there are
      if (PlayerThatIsGuessing == "HUMAN")
        Guess = Ask_User_For_Next_Guess(IncorrectGuesses, CorrectGuesses);

      else
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

    // Displays the winning or losing message
    Display_Game_Over_Message(NumberOfErrors, CurrentGuessOfWord, IncorrectGuesses, NumberOfTurns, WordToBeGuessed, GameIsRunning);
  }
  
  return 0;
}
