//
//  Hangman.cpp
//  Hangman
//
//  Created by Main on 11/12/2019.
//  Copyright © 2019 Junaid Afzal. All rights reserved.
//
// Implementation of the game Hangman

#include "Hangman.hpp"
#include <iostream>
#include <vector>



void Play_Hangman(void)
{
    //Variables for the Hangman game
    // - Hangman states representing the different states the hangman drawing can be in
    std::vector<std::string> HangmanStates, IncorrectGuesses, CorrectGuesses;
    std::string WordToBeGuessed, CurrentGuessOfWord;
    unsigned int NumberOfPlayers, NumberOfErrors = 0, NumberOfTurns = 0;

    // Sets up the variables required by game
    Setup_Game(HangmanStates, WordToBeGuessed, CurrentGuessOfWord, NumberOfPlayers);

    // while the current guess of word and word to be guessed are not the same and the hangman drawing
    // has not reached its final stage continue playing game
    while (!Winning_Conditions_Met(WordToBeGuessed, CurrentGuessOfWord) && !Game_Over(NumberOfErrors))
    {
        // Displays the current hangman state, the current guess of word and all incorrect guesses
        Display_Game(HangmanStates, NumberOfErrors, CurrentGuessOfWord, IncorrectGuesses);
        
        std::string Guess;

        // Prompt the human or AI user for a guess depending upon how many human players there are
        if (NumberOfPlayers == 2)
            Guess = Ask_User_For_Next_Guess(IncorrectGuesses, CorrectGuesses);

        else if(NumberOfPlayers == 1)
            Guess = Ask_AI_For_Next_Guess(IncorrectGuesses, CorrectGuesses);
            
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
    Display_Winner(HangmanStates, NumberOfErrors, CurrentGuessOfWord, IncorrectGuesses, NumberOfTurns, WordToBeGuessed);
}



void Setup_Game(std::vector<std::string>& HangmanStates, std::string& WordToBeGuessed, std::string& CurrentGuessOfWord, unsigned int& NumberOfPlayers)
{
    // Creates the hangman states of the drawing
    HangmanStates = Create_Hangman_States();
    
    // Prompt the user for the word to be guessed
    WordToBeGuessed = Ask_User_For_Word_To_Be_Guessed();
    
    // Create the current guess to be the same size as the word to be guessed but only containing underscores
    for (int i = 0; i < WordToBeGuessed.size(); i++)
        CurrentGuessOfWord.push_back('_');
    
    // Prompt the user for the number of players if one the AI will guess and if two then human user will guess
    NumberOfPlayers = Ask_User_For_Number_Of_Players();
    
    // If one the AI will guess so set seed of srand to time(0) so pseudo random
    if (NumberOfPlayers == 1)
        std::srand(std::time(0));
}



std::vector<std::string> Create_Hangman_States(void)
{
    // Hard coded strings that represent the different hangman state drawings
    std::vector<std::string> HangmanStates;
    HangmanStates.push_back("\n\n\n\n\n\n \n\n");
    HangmanStates.push_back("\n\n\n\n\n\n+---+---+ \n\n");
    HangmanStates.push_back("\n    |\n    |\n    |\n    |\n    |\n+---+---+ \n\n");
    HangmanStates.push_back("    +-------+\n    |\n    |\n    |\n    |\n    |\n+---+---+ \n\n");
    HangmanStates.push_back("    +-------+\n    |       |\n    |\n    |\n    |\n    |\n+---+---+ \n\n");
    HangmanStates.push_back("    +-------+\n    |       |\n    |       O\n    |\n    |\n    |\n+---+---+ \n\n");
    HangmanStates.push_back("    +-------+\n    |       |\n    |       O\n    |       |\n    |\n    |\n+---+---+ \n\n");
    HangmanStates.push_back("    +-------+\n    |       |\n    |       O\n    |       |\n    |      /\n    |\n+---+---+ \n\n");
    HangmanStates.push_back("    +-------+\n    |       |\n    |       O\n    |       |\n    |      / \\\n    |\n+---+---+ \n\n");
    HangmanStates.push_back("    +-------+\n    |       |\n    |       O\n    |      /|\n    |      / \\\n    |\n+---+---+ \n\n");
    HangmanStates.push_back("    +-------+\n    |       |\n    |       O\n    |      /|\\\n    |      / \\\n    |\n+---+---+ \n\n");
    
    return HangmanStates;
}



std::string Ask_User_For_Word_To_Be_Guessed(void) //spaces or -
{
    bool IsValueCorrect = false; // Flag for if input value in invalid
    std::string WordToBeGuessed;
    
    while(!IsValueCorrect)
    {
        // Set flag to true by default as difficult to continue to to next iteration of while loop
        // within a nested if statements within nested for loops
        IsValueCorrect = true;
        
        std::cout << "Enter the word to be guessed ";
        
        std::cin >> WordToBeGuessed;
        
        if (std::cin.fail()) // Check if cin failed
        {
            // Clear buffer and retry
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            IsValueCorrect = false;
            continue;
        }
    
        // Only accept chars that are either captial or lowercase letters
        for (int i = 0; i < WordToBeGuessed.size(); i++)
        {
            if(WordToBeGuessed[i] < 'A')
            {
                // Clear buffer and retry
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                IsValueCorrect = false;
                break;
            }
            
            else if(WordToBeGuessed[i] > 'z')
            {
                // Clear buffer and retry
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                IsValueCorrect = false;
                break;
            }
            
            // Check for [ \ ] ^ _ ` as they occur inbetween the uppercase and lowercase letters blocks
            else if(WordToBeGuessed[i] >= 91 && WordToBeGuessed[i] <= 96)
            {
                // Clear buffer and retry
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                IsValueCorrect = false;
                break;
            }
        }
    }
    
    // Capitalise all letters so that only capital letter need to be dealt with
    Capitalise_Word(WordToBeGuessed);
    
    return WordToBeGuessed;
}



void Capitalise_Word(std::string& aWord)
{
    // Takes a string and replaces every lowercase occurrence of a letter
    // and replaces it with its corresponding uppercase letter
    for (int i = 0; i < aWord.size(); i++)
    {
        switch (aWord[i]) {
            case 'a':
                aWord[i] = 'A';
                break;
                    
            case 'b':
                aWord[i] = 'B';
                break;
            
            case 'c':
                aWord[i] = 'C';
                break;
                
            case 'd':
                aWord[i] = 'D';
                break;
               
            case 'e':
                aWord[i] = 'E';
                break;
                
            case 'f':
                aWord[i] = 'F';
                break;
             
            case 'g':
                aWord[i] = 'G';
                break;
                
            case 'h':
                aWord[i] = 'H';
                break;
                
            case 'i':
                aWord[i] = 'I';
                break;
                
            case 'j':
                aWord[i] = 'J';
                break;
                
            case 'k':
                aWord[i] = 'K';
                break;
            
            case 'l':
                aWord[i] = 'L';
                break;
                
            case 'm':
                aWord[i] = 'M';
                break;
                
            case 'n':
                aWord[i] = 'N';
                break;
                
            case 'o':
                aWord[i] = 'O';
                break;
                
            case 'p':
                aWord[i] = 'P';
                break;
                
            case 'q':
                aWord[i] = 'Q';
                break;
            
            case 'r':
                aWord[i] = 'R';
                break;
                
            case 's':
                aWord[i] = 'S';
                break;
                
            case 't':
                aWord[i] = 'T';
                break;
                
            case 'u':
                aWord[i] = 'U';
                break;
                
            case 'v':
                aWord[i] = 'V';
                break;
                
            case 'w':
                aWord[i] = 'W';
                break;
                
            case 'x':
                aWord[i] = 'X';
                break;
                
            case 'y':
                aWord[i] = 'Y';
                break;
                
            case 'z':
                aWord[i] = 'Z';
                break;
                
            default:
                break;
        }
    }
}



unsigned int Ask_User_For_Number_Of_Players(void)
{
    bool IsValueCorrect = false; // Flag for if input value in invalid
    unsigned int NumberOfPlayers = 0;

    while(!IsValueCorrect)
    {
        std::cout << "Enter the number of players ";
        
        std::cin >> NumberOfPlayers;
        
        if (std::cin.fail()) // Check if cin failed
        {
            // Clear buffer and retry
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        
        // Only one or two players allowed, as one player represents the human user choosing
        // the word to be gueesed and the AI guessing, and two players representing two human players
        else if (NumberOfPlayers != 1 && NumberOfPlayers != 2)
        {
            // Clear buffer and retry
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        
        else
            IsValueCorrect = true;
    }
    
    return NumberOfPlayers;
}



bool Winning_Conditions_Met(std::string& WordToBeGuessed, std::string& CurrentGuessOfWord)
{
    // If there is any difference then winning condition not met
    for (int i = 0; i < WordToBeGuessed.size(); i++)
        if (WordToBeGuessed[i] != CurrentGuessOfWord[i])
            return false;
    
    return true;
}



bool Game_Over(unsigned int& NumberOfErrors)
{
    // 10 or more errors mean that the final state of the
    // hangman drawing has been reached
    if(NumberOfErrors >= 10)
        return true;
    
    else
        return false;
}



void Display_Game(std::vector<std::string>& HangmanStates, unsigned int& NumberOfErrors, std::string& CurrentGuessOfWord, std::vector<std::string>& IncorrectGuesses)
{
    // ***Better alternative needed***
    // Clears terminal window
    system("clear");
    
    std::cout << "Hangman V1.0 by Junaid Afzal\n" << std::endl;
    
    // Draw the hangman drawing
    std::cout << HangmanStates[NumberOfErrors] << "\n" << std::endl;
    
    // Current guess of word
    for (int i = 0; i < CurrentGuessOfWord.size(); i++)
        std::cout << CurrentGuessOfWord[i] << " ";
    
    //Incorrect guesses
    std::cout << "\n\nIncorrect Guesses" << std::endl;
    for (int i = 0; i < IncorrectGuesses.size(); i++)
        std::cout << IncorrectGuesses[i] << "   ";
    
    std::cout << "\n" << std::endl;
}



std::string Ask_User_For_Next_Guess(std::vector<std::string>& IncorrectGuesses, std::vector<std::string>& CorrectGuesses)
{
    bool IsValueCorrect = false; // Flag for if input value in invalid
    std::string Guess;
    
    while(!IsValueCorrect)
    {
        // Set flag to true by default as difficult to continue to to next iteration of while loop
        // within a nested if statements within nested for loops
        IsValueCorrect = true;
        
        std::cout << "Enter your guess ";
        
        std::cin >> Guess;
        
        if (std::cin.fail()) // Check if cin failed
        {
            // Clear buffer and retry
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            IsValueCorrect = false;
            continue;
        }
    
        // Only accept chars that are either captial or lowercase letters
        for (int i = 0; i < Guess.size(); i++)
        {
            if(Guess[i] < 'A')
            {
                // Clear buffer and retry
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                IsValueCorrect = false;
                break;
            }
            
            else if(Guess[i] > 'z')
            {
                // Clear buffer and retry
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                IsValueCorrect = false;
                break;
            }
            
            // Check for [ \ ] ^ _ ` as they occur inbetween the uppercase and lowercase letters blocks
            else if(Guess[i] >= 91 && Guess[i] <= 96)
            {
                // Clear buffer and retry
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                IsValueCorrect = false;
                break;
            }
        }
        
        // Capitalise all letters so that only capital letter need to be dealt with
        // and the word to be guessed has already been capitalised
        Capitalise_Word(Guess);
        
        //Check if this string has already been guessed both correctly or incorrectly
        for (int i = 0; i < IncorrectGuesses.size(); i++)
            if(Guess == IncorrectGuesses[i])
            {
                IsValueCorrect = false;
                break;
            }
        
        for (int i = 0; i < CorrectGuesses.size(); i++)
            if(Guess == CorrectGuesses[i])
            {
                IsValueCorrect = false;
                break;
            }
    }
    
    return Guess;
}



std::string Ask_AI_For_Next_Guess(std::vector<std::string>& IncorrectGuesses, std::vector<std::string>& CorrectGuesses)
{
    bool IsValueCorrect = false; // Flag for if input value in invalid
    std::string Guess = " ";
    
    while(!IsValueCorrect)
    {
        // Set flag to true by default as difficult to continue to to next iteration of while loop
        // within a nested if statements within nested for loops
        IsValueCorrect = true;
        
        // AI will guess a random letter from A to Z
        Guess[0] = (std::rand() % 26) + 65;
        
        //Check if this string has already been guessed both correctly or incorrectly
        for (int i = 0; i < IncorrectGuesses.size(); i++)
            if(Guess == IncorrectGuesses[i])
            {
                IsValueCorrect = false;
                break;
            }
        
        for (int i = 0; i < CorrectGuesses.size(); i++)
            if(Guess == CorrectGuesses[i])
            {
                IsValueCorrect = false;
                break;
            }
    }
    
    // Output a message which is similar to human player guess
    std::cout << "AI guessed " << Guess << "\n\n\n" << std::endl;
    
    return Guess;
}



bool Check_Guess_Against_Word(std::string& Guess, std::string& WordToBeGuessed, std::string& CurrentGuessOfWord)
{
    bool IsGuessCorrect = false;
    
    // If below is true then guess is a letter and every occurence of this letter
    // needs to be deposited is the current guess of word
    if (Guess.size() == 1)
    {
        for (int i = 0; i < WordToBeGuessed.size(); i++) {
            if (WordToBeGuessed[i] == Guess[0])
            {
                IsGuessCorrect = true;
                CurrentGuessOfWord[i] = Guess[0];
            }
        }
    }
    
    // If not then guess is a word and a simple check to see if they are the
    // same and if so return true and overwrite current guess
    else if (Guess == WordToBeGuessed)
    {
        CurrentGuessOfWord = Guess;
        IsGuessCorrect = true;
    }
    
    return IsGuessCorrect;
}



void Display_Winner(std::vector<std::string>& HangmanStates, unsigned int& NumberOfErrors, std::string& CurrentGuessOfWord, std::vector<std::string>& IncorrectGuesses, unsigned int& NumberOfTurns, std::string& WordToBeGuessed)
{
    // If the below is true then hangman has reached its final state and thus user has lost
    if(NumberOfErrors >= 10)
    {
        Display_Game(HangmanStates, NumberOfErrors, CurrentGuessOfWord, IncorrectGuesses);
        std::cout << "You lost!\nOnly took " << NumberOfTurns << " turns\nThe word was " << WordToBeGuessed << std::endl;
    }
    
    else
    {
        Display_Game(HangmanStates, NumberOfErrors, CurrentGuessOfWord, IncorrectGuesses);
        std::cout << "Congratulations you won!\nOnly took " << NumberOfTurns << " turns" << std::endl;
    }
}
