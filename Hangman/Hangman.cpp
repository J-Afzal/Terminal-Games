//
//  Hangman.cpp
//  Hangman
//
//  Created by Main on 11/12/2019.
//  Copyright © 2019 Junaid Afzal. All rights reserved.
//

#include "Hangman.hpp"
#include <iostream>
#include <vector>



void Play_Hangman(void)
{
    std::vector<std::string> HangmanStates, IncorrectGuesses, CorrectGuesses;
    std::string WordToBeGuessed, CurrentGuessOfWord;
    unsigned int NumberOfPlayers, NumberOfErrors = 0, NumberOfTurns = 0;

    Setup_Game(HangmanStates, WordToBeGuessed, CurrentGuessOfWord, NumberOfPlayers);

    while (!Winning_Conditions_Met(WordToBeGuessed, CurrentGuessOfWord) && !Game_Over(NumberOfErrors))
    {
        Display_Game(HangmanStates, NumberOfErrors, CurrentGuessOfWord, IncorrectGuesses);
        
        std::string Guess;

        if (NumberOfPlayers == 2)
            Guess = Ask_User_For_Next_Guess(IncorrectGuesses, CorrectGuesses);

        else if(NumberOfPlayers == 1)
            Guess = Ask_AI_For_Next_Guess(IncorrectGuesses, CorrectGuesses);

        if (!Check_Guess_Against_Word(Guess, WordToBeGuessed, CurrentGuessOfWord))
        {
            IncorrectGuesses.push_back(Guess);
            NumberOfErrors++;
        }
        
        else
            CorrectGuesses.push_back(Guess);

        NumberOfTurns++;
    }
    
    Display_Winner(HangmanStates, NumberOfErrors, CurrentGuessOfWord, IncorrectGuesses, NumberOfTurns, WordToBeGuessed);
}



void Setup_Game(std::vector<std::string>& HangmanStates, std::string& WordToBeGuessed, std::string& CurrentGuessOfWord, unsigned int& NumberOfPlayers)
{
    HangmanStates = Create_Hangman_States();
    
    WordToBeGuessed = Ask_User_For_Word_To_Be_Guessed();
    
    for (int i = 0; i < WordToBeGuessed.size(); i++)
        CurrentGuessOfWord.push_back('_');
    
    NumberOfPlayers = Ask_User_For_Number_Of_Players();
    std::srand(std::time(0));
}



std::vector<std::string> Create_Hangman_States(void)
{
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
    
        for (int i = 0; i < WordToBeGuessed.size(); i++)
        {
            if(WordToBeGuessed[i] < 'A')
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                IsValueCorrect = false;
                break;
            }
            
            else if(WordToBeGuessed[i] > 'z')
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                IsValueCorrect = false;
                break;
            }
            
            // [ \ ] ^ _ `
            else if(WordToBeGuessed[i] >= 91 && WordToBeGuessed[i] <= 96)
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                IsValueCorrect = false;
                break;
            }
        }
    }
    
    Capitalise_Word(WordToBeGuessed);
    
    return WordToBeGuessed;
}



void Capitalise_Word(std::string& aWord)
{
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
    for (int i = 0; i < WordToBeGuessed.size(); i++)
        if (WordToBeGuessed[i] != CurrentGuessOfWord[i])
            return false;
    
    return true;
}



bool Game_Over(unsigned int& NumberOfErrors)
{
    if(NumberOfErrors >= 10)
        return true;
    
    else
        return false;
}



void Display_Game(std::vector<std::string>& HangmanStates, unsigned int& NumberOfErrors, std::string& CurrentGuessOfWord, std::vector<std::string>& IncorrectGuesses)
{
    system("clear");
    
    std::cout << "Hangman V1.0 by Junaid Afzal\n" << std::endl;
    
    std::cout << HangmanStates[NumberOfErrors] << "\n" << std::endl;
    
    for (int i = 0; i < CurrentGuessOfWord.size(); i++)
        std::cout << CurrentGuessOfWord[i] << " ";
    
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
    
        for (int i = 0; i < Guess.size(); i++)
        {
            if(Guess[i] < 'A')
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                IsValueCorrect = false;
                break;
            }
            
            else if(Guess[i] > 'z')
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                IsValueCorrect = false;
                break;
            }
            
            // [ \ ] ^ _ `
            else if(Guess[i] >= 91 && Guess[i] <= 96)
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                IsValueCorrect = false;
                break;
            }
        }
        
        Capitalise_Word(Guess);
        
        //Check if this value has already been guessed
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
        IsValueCorrect = true;
        
        Guess[0] = (std::rand() % 26) + 65;
        
        //Check if this value has already been guessed
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
    
    std::cout << "AI guessed " << Guess << "\n\n\n" << std::endl;
    
    return Guess;
}



bool Check_Guess_Against_Word(std::string& Guess, std::string& WordToBeGuessed, std::string& CurrentGuessOfWord)
{
    bool IsGuessCorrect = false;
    
    if (Guess.size() == 1) // letter
    {
        for (int i = 0; i < WordToBeGuessed.size(); i++) {
            if (WordToBeGuessed[i] == Guess[0])
            {
                IsGuessCorrect = true;
                CurrentGuessOfWord[i] = Guess[0];
            }
        }
    }
    
    else if (Guess == WordToBeGuessed)
    {
        CurrentGuessOfWord = Guess;
        IsGuessCorrect = true;
    }
    
    return IsGuessCorrect;
}



void Display_Winner(std::vector<std::string>& HangmanStates, unsigned int& NumberOfErrors, std::string& CurrentGuessOfWord, std::vector<std::string>& IncorrectGuesses, unsigned int& NumberOfTurns, std::string& WordToBeGuessed)
{
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
