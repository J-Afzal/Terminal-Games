//
//  Hangman.hpp
//  Hangman
//
//  Created by Main on 11/12/2019.
//  Copyright © 2019 Junaid Afzal. All rights reserved.
//
//  Hangman game where no hyphens or spaces allowed in the
//  word to be guessed. The programs first asks the user for a word, then
//  for the number of players, with one meaning an AI user will guess the word
//  and 2 meaning a human user will guess the word. The user guessing the
//  word is prompted for a guess and can handle a word or a letter guess. Note
//  a word guess will not replace any letters but just compare the guess with
//  the word to be guessed and the AI is dumb and randomly chooses a letter.
//  With each incorrect guess the hangman is drawn more until it is complete
//  (after 10 incorrect guesses) or the word has been guessed.
//

#ifndef Hangman_hpp
#define Hangman_hpp

#include <iostream>



// Single function to run whole game
void Play_Hangman(void);

// Sets up the variables required by prompting user for the word to be guessed and the number of players
void Setup_Game(std::vector<std::string>& HangmanStates, std::string& WordToBeGuessed, std::string& CurrentGuessOfWord, unsigned int& NumberOfPlayers);

// Creates all the states the hangman drawing can be in
std::vector<std::string> Create_Hangman_States(void);

// Prompts the user for the word to be guessed
std::string Ask_User_For_Word_To_Be_Guessed(void);

// Takes in a string and modifies it so that all letters at capitalised
void Capitalise_Word(std::string& aWord);

// Prompts the user for the number of human players in the game
unsigned int Ask_User_For_Number_Of_Players(void);

// Checks if the current guess of word and word to be guessed are the same
bool Winning_Conditions_Met(std::string& WordToBeGuessed, std::string& CurrentGuessOfWord);

// Checks if the hangman drawing has reached its final stage
bool Game_Over(unsigned int& NumberOfErrors);

// Displays the current hangman state, the current guess of word and all incorrect guesses
void Display_Game(std::vector<std::string>& HangmanStates, unsigned int& NumberOfErrors, std::string& CurrentGuessOfWord, std::vector<std::string>& IncorrectGuesses);

// Prompts the user for a guess of the word
std::string Ask_User_For_Next_Guess(std::vector<std::string>& IncorrectGuesses, std::vector<std::string>& CorrectGuesses);

// Prompts the AI for a guess of the word
std::string Ask_AI_For_Next_Guess(std::vector<std::string>& IncorrectGuesses, std::vector<std::string>& CorrectGuesses);

// Check if guess is correct against the word to be guessed
bool Check_Guess_Against_Word(std::string& Guess, std::string& WordToBeGuessed, std::string& CurrentGuessOfWord);

// Displays the winning or losing message
void Display_Winner(std::vector<std::string>& HangmanStates, unsigned int& NumberOfErrors, std::string& CurrentGuessOfWord, std::vector<std::string>& IncorrectGuesses, unsigned int& NumberOfTurns, std::string& WordToBeGuessed);



#endif /* Hangman_hpp */
