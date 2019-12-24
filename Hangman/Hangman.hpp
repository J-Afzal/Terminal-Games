//
//  Hangman.hpp
//  Hangman
//
//  Created by Main on 11/12/2019.
//  Copyright © 2019 Junaid Afzal. All rights reserved.
//
//  The classic Hangman game where no hyphens or spaces are allowed in
//  the word to be guessed. Also guessing a word will not replace any letters
//  but just compare it with the word to be guessed. With each incorrect guess the
//  hangman is drawn more until it is complete (after 10 incorrect guesses) or when the
//  word has been guessed.
//
//  Important Points
//      - 2 users represents two human players, with one creating the word and the other guessing the word
//      - 1 user represents one human player and one computer player, the human player is then asked who
//        is guessing the word, and so all combinations of human and computer variants are possible
//      - 0 users represents zero human players and two computer players
//      - The AI is dumb and both randomly picks a word from Words.txt and a random letter when guessing
//      - The The game is played through the function `Play_Hangman()`
//

#ifndef Hangman_hpp
#define Hangman_hpp

#include <iostream>
#include <vector>

// Single function to run whole game
void Play_Hangman(void);

// Sets up the variables required by prompting user for the word to be guessed and the number of players
void Setup_Game(std::vector<std::string>& HangmanStates, std::string& WordToBeGuessed, std::string& CurrentGuessOfWord, unsigned int& NumberOfPlayers, std::string& PlayerThatIsGuessing);

// Creates all the states the hangman drawing can be in
std::vector<std::string> Create_Hangman_States(void);

// Prompts the user for the number of human players in the game
unsigned int Ask_User_For_Number_Of_Players(void);

// Prompts the user for the word to be guessed
std::string Ask_User_For_Word_To_Be_Guessed(void);

// Takes in a string and modifies it so that all letters at capitalised
void Capitalise_Word(std::string& aWord);

// Prompts the AI for the word to be guessed
std::string Ask_AI_For_Word_To_Be_Guessed(void);

// Prompts the user for who is guessing the word (human or computer)
std::string Ask_User_For_Who_Is_Guessing(void);

// Checks if the current guess of word and word to be guessed are the same
bool Winning_Conditions_Met(const std::string& WordToBeGuessed, const std::string& CurrentGuessOfWord);

// Checks if the hangman drawing has reached its final stage
bool Game_Over(const unsigned int& NumberOfErrors);

// Displays the current hangman state, the current guess of word and all incorrect guesses
void Display_Game(const std::vector<std::string>& HangmanStates, const unsigned int& NumberOfErrors, const std::string& CurrentGuessOfWord, const std::vector<std::string>& IncorrectGuesses);

// Prompts the user for a guess of the word
std::string Ask_User_For_Next_Guess(const std::vector<std::string>& IncorrectGuesses, const std::vector<std::string>& CorrectGuesses);

// Prompts the AI for a guess of the word
std::string Ask_AI_For_Next_Guess(const std::vector<std::string>& IncorrectGuesses, const std::vector<std::string>& CorrectGuesses);

// Check if guess is correct against the word to be guessed
bool Check_Guess_Against_Word(const std::string& Guess, const std::string& WordToBeGuessed, std::string& CurrentGuessOfWord);

// Displays the winning or losing message
void Display_Winner(const std::vector<std::string>& HangmanStates, const unsigned int& NumberOfErrors, const std::string& CurrentGuessOfWord, const std::vector<std::string>& IncorrectGuesses, const unsigned int& NumberOfTurns, const std::string& WordToBeGuessed);

#endif /* Hangman_hpp */
