//
//  @File: Hangman.hpp
//  @Author: Junaid Afzal
//

#ifndef hangman_hpp
#define hangman_hpp

#include <vector>
#include <string>

// Sets up the variables required
void Setup_Game(unsigned int &NumberOfPlayers,
                std::string &PlayerThatIsGuessing,
                std::string &AIDifficulty,
                std::string &WordToBeGuessed,
                std::string &CurrentGuessOfWord,
                std::vector<unsigned char> &ValidMovesRemaining,
                const std::vector<unsigned char> &IncorrectGuesses);

std::string Get_Word_To_Be_Guessed_From_User(const std::vector<unsigned char> &IncorrectGuesses,
                                             const unsigned int &NumberOfPlayers,
                                             const std::string &AIDifficulty);

std::string Get_Word_To_Be_Guessed_From_AI(void);

// Displays the current hangman state, the current guess of word and all incorrect guesses
void Display_Game(const unsigned int &NumberOfErrors,
                  const std::string &NumberOfPlayers,
                  const std::string &AIDifficulty,
                  const std::vector<unsigned char> &IncorrectGuesses,
                  const std::string &CurrentGuessOfWord);

// Checks if the hangman drawing has reached its final stage and
// checks if the current guess of word and word to be guessed are the same
bool Winning_Conditions_Met(const unsigned int &NumberOfErrors,
                            const std::string &WordToBeGuessed,
                            const std::string &CurrentGuessOfWord);



void Get_Next_User_Guess(unsigned int &NumberOfErrors,
                         const unsigned int &NumberOfPlayers,
                         const std::string &AIDifficulty,
                         std::vector<unsigned char> &IncorrectGuesses,
                         std::vector<unsigned char> &CorrectGuesses,
                         std::vector<unsigned char> &ValidMovesRemaining,
                         std::string &CurrentGuessOfWord,
                         const std::string &WordToBeGuessed);

void Get_Next_AI_Guess(unsigned int &NumberOfErrors,
                       const unsigned int &NumberOfPlayers,
                       const std::string &AIDifficulty,
                       std::vector<unsigned char> &IncorrectGuesses,
                       std::vector<unsigned char> &CorrectGuesses,
                       std::vector<unsigned char> &ValidMovesRemaining,
                       std::string &CurrentGuessOfWord,
                       const std::string &WordToBeGuessed);

// Checks if guess is correct against the word to be guessed and updates current guess in correct
bool Check_Guess_Against_Word_To_Be_Guessed(const std::string &WordToBeGuessed,
                                            const unsigned char &Guess,
                                            std::string &CurrentGuessOfWord);

// Displays whether the guesser won or lost, how many turns it took and the word that was to be guessed
void Display_Game_Over_Message(const unsigned int &NumberOfErrors,
                               const unsigned int &NumberOfPlayers,
                               const std::string &AIDifficulty,
                               const std::vector<unsigned char> &IncorrectGuesses,
                               const std::string &CurrentGuessOfWord,
                               const std::string &WordToBeGuessed,
                               const unsigned int &NumberOfTurns,
                               bool &GameIsRunning);

#endif
