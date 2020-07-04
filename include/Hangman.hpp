//
//  The classic Hangman game 
//
//  Important Points
//  - 2 players represents two human players
//  - 1 player represents one human player and one computer player. The human
//  player is then asked who is guessing the word and so who is creating the word
//  - 0 players represents computer vs computer
//  - The computer is dumb and both randomly picks a word from Words.txt and a random letter when guessing
//  - No hyphens or spaces are allowed in the word to be guessed
//  - Guessing with a word will not replace any letters but just compare it with the word to be guessed.
//  - system("cls") is used to clear console
//

#ifndef Hangman_hpp
#define Hangman_hpp

#include <iostream>
#include <vector>

void Play_Hangman(void);

// Test code uses computer vs computer option
void Test_Hangman(void);

// Sets up the variables required by prompting user for the word to be guessed and the number of players
void Setup_Game(std::string& WordToBeGuessed,
                std::string& CurrentGuessOfWord,
                unsigned int& NumberOfPlayers,
                std::string& PlayerThatIsGuessing);

unsigned int Ask_User_For_Number_Of_Players(void);

std::string Ask_User_For_Word_To_Be_Guessed(void);

void Capitalise_Word(std::string& aWord);

std::string Ask_Computer_For_Word_To_Be_Guessed(void);

std::string Ask_User_For_Who_Is_Guessing(void);

// Checks if the hangman drawing has reached its final stage
bool Game_Over(const unsigned int& NumberOfErrors);

// Checks if the current guess of word and word to be guessed are the same
bool Winning_Conditions_Met(const std::string& WordToBeGuessed,
                            const std::string& CurrentGuessOfWord);

// Displays the current hangman state, the current guess of word and all incorrect guesses
// Note that system("cls") is used to clear console
void Display_Game(const unsigned int& NumberOfErrors,
                  const std::string& CurrentGuessOfWord,
                  const std::vector<std::string>& IncorrectGuesses);

std::string Ask_User_For_Next_Guess(const std::vector<std::string>& IncorrectGuesses,
                                    const std::vector<std::string>& CorrectGuesses);

std::string Ask_Computer_For_Next_Guess(const std::vector<std::string>& IncorrectGuesses,
                                        const std::vector<std::string>& CorrectGuesses);

// Checks if guess is correct against the word to be guessed and updates current guess in correct
bool Check_Guess_Against_Word(const std::string& Guess,
                              const std::string& WordToBeGuessed,
                              std::string& CurrentGuessOfWord);

// Displays the winning player and how many turns it took
void Display_Game_Over_Message(const unsigned int& NumberOfErrors,
                               const std::string& CurrentGuessOfWord,
                               const std::vector<std::string>& IncorrectGuesses,
                               const unsigned int& NumberOfTurns,
                               const std::string& WordToBeGuessed,
                               bool& GameIsRunning);

#endif
