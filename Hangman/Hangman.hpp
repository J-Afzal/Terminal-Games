//
//  Hangman.hpp
//  Hangman
//
//  Created by Main on 11/12/2019.
//  Copyright © 2019 Junaid Afzal. All rights reserved.
//

#ifndef Hangman_hpp
#define Hangman_hpp

#include <iostream>



void Play_Hangman(void);

void Setup_Game(std::vector<std::string>& HangmanStates, std::string& WordToBeGuessed, std::string& CurrentGuessOfWord, unsigned int& NumberOfPlayers);

std::vector<std::string> Create_Hangman_States(void);

std::string Ask_User_For_Word_To_Be_Guessed(void);

void Capitalise_Word(std::string& aWord);

unsigned int Ask_User_For_Number_Of_Players(void);

bool Winning_Conditions_Met(std::string& WordToBeGuessed, std::string& CurrentGuessOfWord);

bool Game_Over(unsigned int& NumberOfErrors);

void Display_Game(std::vector<std::string>& HangmanStates, unsigned int& NumberOfErrors, std::string& CurrentGuessOfWord, std::vector<std::string>& IncorrectGuesses);

std::string Ask_User_For_Next_Guess(std::vector<std::string>& IncorrectGuesses, std::vector<std::string>& CorrectGuesses);

std::string Ask_AI_For_Next_Guess(std::vector<std::string>& IncorrectGuesses, std::vector<std::string>& CorrectGuesses);

bool Check_Guess_Against_Word(std::string& Guess, std::string& WordToBeGuessed, std::string& CurrentGuessOfWord);

void Display_Winner(std::vector<std::string>& HangmanStates, unsigned int& NumberOfErrors, std::string& CurrentGuessOfWord, std::vector<std::string>& IncorrectGuesses, unsigned int& NumberOfTurns, std::string& WordToBeGuessed);



#endif /* Hangman_hpp */
