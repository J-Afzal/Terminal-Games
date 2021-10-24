//
//  @File: Hangman.hpp
//  @Author: Junaid Afzal
//

#ifndef Hangman_hpp
#define Hangman_hpp

#include <vector>
#include <string>

// Sets up the variables required
void Setup_Game(std::string& WordToBeGuessed,
                std::string& CurrentGuessOfWord,
                unsigned int& NumberOfPlayers,
                std::string& PlayerThatIsGuessing);

unsigned int Get_Number_Of_Players(void);

std::string Ask_User_For_Word_To_Be_Guessed(const unsigned int& NumberOfPlayers,
                                            const std::string& PlayerThatIsGuessing);

void Capitalise_Word(std::string& aWord);

std::string Ask_User_For_Who_Is_Guessing(const unsigned int& NumberOfPlayers);

std::string Ask_Computer_For_Word_To_Be_Guessed(void);

// Checks if the hangman drawing has reached its final stage
bool Game_Over(const unsigned int& NumberOfErrors);

// Checks if the current guess of word and word to be guessed are the same
bool Winning_Conditions_Met(const std::string& WordToBeGuessed,
                            const std::string& CurrentGuessOfWord);

// Displays the current hangman state, the current guess of word and all incorrect guesses
void Display_Game(const unsigned int& NumberOfErrors,
                  const std::string& CurrentGuessOfWord,
                  const std::vector<std::string>& IncorrectGuesses);

void Clear_Terminal(void);

std::string Ask_User_For_Next_Guess(const std::vector<std::string>& IncorrectGuesses,
                                    const std::vector<std::string>& CorrectGuesses,
                                    const unsigned int& NumberOfErrors,
                                    const std::string& CurrentGuessOfWord);

std::string Ask_Computer_For_Next_Guess(const std::vector<std::string>& IncorrectGuesses,
                                        const std::vector<std::string>& CorrectGuesses,
                                        const unsigned int& NumberOfErrors,
                                        const std::string& CurrentGuessOfWord);

// Checks if guess is correct against the word to be guessed and updates current guess in correct
bool Check_Guess_Against_Word(const std::string& Guess,
                              const std::string& WordToBeGuessed,
                              std::string& CurrentGuessOfWord);

// Displays whether the guesser won or lost, how many turns it took and the word that was to be guessed
void Display_Game_Over_Message(const unsigned int& NumberOfErrors,
                               const std::string& CurrentGuessOfWord,
                               const std::vector<std::string>& IncorrectGuesses,
                               const unsigned int& NumberOfTurns,
                               const std::string& WordToBeGuessed,
                               bool& GameIsRunning);

#endif
