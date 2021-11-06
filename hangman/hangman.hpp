//
//  @File: Hangman.hpp
//  @Author: Junaid Afzal
//

#ifndef hangman_hpp
#define hangman_hpp

#include <vector>
#include <string>

// Sets up the variables required
void Setup_Game(std::string &WordToBeGuessed,
                std::string &CurrentGuessOfWord,
                unsigned int &NumberOfPlayers,
                std::string &PlayerThatIsGuessing,
                std::vector<unsigned char> &IncorrectGuesses,
                std::string &AIDifficulty,
                std::vector<unsigned char> &ValidMovesRemaining);

std::string Get_Word_To_Be_Guessed_From_User(const unsigned int &NumberOfPlayers,
                                             const std::vector<unsigned char> &IncorrectGuesses,
                                             const std::string &AIDifficulty);

std::string Get_Word_To_Be_Guessed_From_Computer(void);

// Checks if the hangman drawing has reached its final stage and
// checks if the current guess of word and word to be guessed are the same
bool Winning_Conditions_Met(const std::string &WordToBeGuessed,
                            const std::string &CurrentGuessOfWord,
                            const unsigned int &NumberOfErrors);

// Displays the current hangman state, the current guess of word and all incorrect guesses
void Display_Game(const unsigned int &NumberOfErrors,
                  const std::string &CurrentGuessOfWord,
                  const std::vector<unsigned char> &IncorrectGuesses,
                  const std::string &NumberOfPlayers,
                  const std::string &AIDifficulty);

void Ask_User_For_Next_Guess(std::vector<unsigned char> &IncorrectGuesses,
                             std::vector<unsigned char> &CorrectGuesses,
                             unsigned int &NumberOfErrors,
                             std::string &CurrentGuessOfWord,
                             const std::string &AIDifficulty,
                             const unsigned int &NumberOfPlayers,
                             std::string &WordToBeGuessed,
                             std::vector<unsigned char> &ValidMovesRemaining);

void Ask_Computer_For_Next_Guess(std::vector<unsigned char> &IncorrectGuesses,
                                 std::vector<unsigned char> &CorrectGuesses,
                                 unsigned int &NumberOfErrors,
                                 std::string &CurrentGuessOfWord,
                                 const std::string &AIDifficulty,
                                 const unsigned int &NumberOfPlayers,
                                 std::string &WordToBeGuessed,
                                 std::vector<unsigned char> &ValidMovesRemaining);

// Checks if guess is correct against the word to be guessed and updates current guess in correct
bool Check_Guess_Against_Word(const unsigned char &Guess,
                              const std::string &WordToBeGuessed,
                              std::string &CurrentGuessOfWord);

// Displays whether the guesser won or lost, how many turns it took and the word that was to be guessed
void Display_Game_Over_Message(const unsigned int &NumberOfErrors,
                               const std::string &CurrentGuessOfWord,
                               const std::vector<unsigned char> &IncorrectGuesses,
                               const unsigned int &NumberOfTurns,
                               const std::string &WordToBeGuessed,
                               bool &GameIsRunning,
                               const std::string &AIDifficulty,
                               const unsigned int &NumberOfPlayers);

#endif
