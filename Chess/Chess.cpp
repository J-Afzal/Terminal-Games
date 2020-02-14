//
//  Chess.cpp
//  Chess
//
//  Created by Main on 07/01/2020.
//  Copyright © 2020 Junaid Afzal. All rights reserved.
//

#include "Chess.hpp"

void Setup_Game(std::vector< std::vector<std::string> >& Board, unsigned int& NumberOfPlayers, std::string& HumanPlayer, std::string& CurrentPlayer)
{
    for (unsigned int i = 0; i < 8; i++)
    {
        std::vector<std::string> Rows;
        Board.push_back(Rows);
        
        for (unsigned int j = 0; j < 8; j++)
        {
            Board[i].push_back(".");
            
            if (i == 0)
                switch (j)
                {
                    case 0:
                        Board[i][j] = "BR";
                        break;
                    
                    case 1:
                        Board[i][j] = "BN";
                        break;
                    
                    case 2:
                        Board[i][j] = "BB";
                        break;
                        
                    case 3:
                        Board[i][j] = "BQ";
                        break;
                        
                    case 4:
                        Board[i][j] = "BK";
                        break;
                        
                    case 5:
                        Board[i][j] = "BB";
                        break;
                        
                    case 6:
                        Board[i][j] = "BN";
                        break;
                        
                    case 7:
                        Board[i][j] = "BR";
                        break;
                        
                    default:
                        std::cout << "Error in black pieces setup in Setup_Game()" << std::endl;
                        break;
                }
            
            else if (i == 1)
                switch (j)
                {
                    case 0:
                        Board[i][j] = "BP1";
                        break;
                    
                    case 1:
                        Board[i][j] = "BP2";
                        break;
                    
                    case 2:
                        Board[i][j] = "BP3";
                        break;
                        
                    case 3:
                        Board[i][j] = "BP4";
                        break;
                        
                    case 4:
                        Board[i][j] = "BP5";
                        break;
                        
                    case 5:
                        Board[i][j] = "BP6";
                        break;
                        
                    case 6:
                        Board[i][j] = "BP7";
                        break;
                        
                    case 7:
                        Board[i][j] = "BP8";
                        break;
                        
                    default:
                        std::cout << "Error in black pawn setup in Setup_Game()" << std::endl;
                        break;
                }
            
            else if (i == 6)
                switch (j)
                {
                    case 0:
                        Board[i][j] = "WP1";
                        break;
                    
                    case 1:
                        Board[i][j] = "WP2";
                        break;
                    
                    case 2:
                        Board[i][j] = "WP3";
                        break;
                        
                    case 3:
                        Board[i][j] = "WP4";
                        break;
                        
                    case 4:
                        Board[i][j] = "WP5";
                        break;
                        
                    case 5:
                        Board[i][j] = "WP6";
                        break;
                        
                    case 6:
                        Board[i][j] = "WP7";
                        break;
                        
                    case 7:
                        Board[i][j] = "WP8";
                        break;
                        
                    default:
                        std::cout << "Error in white pawn setup in Setup_Game()" << std::endl;
                        break;
                }
            
            else if (i == 7)
                switch (j)
                {
                    case 0:
                        Board[i][j] = "WR";
                        break;
                    
                    case 1:
                        Board[i][j] = "WN";
                        break;
                    
                    case 2:
                        Board[i][j] = "WB";
                        break;
                        
                    case 3:
                        Board[i][j] = "WQ";
                        break;
                        
                    case 4:
                        Board[i][j] = "WK";
                        break;
                        
                    case 5:
                        Board[i][j] = "WB";
                        break;
                        
                    case 6:
                        Board[i][j] = "WN";
                        break;
                        
                    case 7:
                        Board[i][j] = "WR";
                        break;
                        
                    default:
                        std::cout << "Error in white pieces setup in Setup_Game()" << std::endl;
                        break;
                }
        }
    }
    
    
    NumberOfPlayers = Ask_User_For_Number_Of_Players();
    
    std::srand((unsigned int)std::time(0));
    
    if (NumberOfPlayers == 1)
    {
        if ((std::rand() % 2) == 0)
            HumanPlayer = "WHITE";
        else
            HumanPlayer = "BLACK";
    }
    
    if ((std::rand() % 2) == 0)
        CurrentPlayer = "WHITE";
    else
        CurrentPlayer = "BLACK";
}

int Ask_User_For_Number_Of_Players(void)
{
    bool isValueCorrect = false; // Flag for if input value in invalid
    unsigned int NumberOfPlayers = 0;
    
    while (!isValueCorrect)
    {
        // Prompt user for next command that will be the next grid position to attack
        std::cout << "Enter the number of human player: ";
        
        std::cin >> NumberOfPlayers;
        
        // Check if cin failed
        if (std::cin.fail())
        {
            // Clear buffer and retry
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            isValueCorrect = false;
            continue;
        }
        
        // Check if value is 0, 1 or 2
        if (NumberOfPlayers != 0 && NumberOfPlayers != 1 && NumberOfPlayers != 2)
            continue;
        
        // If all checks passed then value is valid
        else
            isValueCorrect = true;
    }
    
    // This is to clear .22222 in a value 5.22222 as value would assume to be 5
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    return NumberOfPlayers;
}

bool Game_Over()
{
    
    
    //*******************************************************
    // Check if WK/BK are in check
    // and all possible moves result in check
    //*******************************************************
    
    
    
    return false;
}

void Toggle_Player(std::string& CurrentPlayer)
{
    if (CurrentPlayer == "BLACK")
        CurrentPlayer = "WHITE";
    else
        CurrentPlayer = "BLACK";
}

void Display_Game(const std::vector< std::vector<std::string> >& Board)
{
    for (unsigned int i = 0; i < 8; i++)
    {
        if (i == 0)
            std::cout << "    A B C D E F G H" << std::endl << std::endl;
        
        for (unsigned int j = 0; j < 8; j++)
        {
            if (j == 0)
                std::cout << 8 - i << "   ";
            
            
            if (Board[i][j] == "BR")
                std::cout << "\u2656 ";
            
            else if (Board[i][j] == "BN")
                std::cout << "\u2658 ";
            
            else if (Board[i][j] == "BB")
                std::cout << "\u2657 ";
            
            else if (Board[i][j] == "BQ")
                std::cout << "\u2655 ";
            
            else if (Board[i][j] == "BK")
                std::cout << "\u2654 ";
            
            else if (Board[i][j] == "BP1")
                std::cout << "\u2659 ";
            
            else if (Board[i][j] == "BP2")
                std::cout << "\u2659 ";
            
            else if (Board[i][j] == "BP3")
                std::cout << "\u2659 ";
            
            else if (Board[i][j] == "BP4")
                std::cout << "\u2659 ";
            
            else if (Board[i][j] == "BP5")
                std::cout << "\u2659 ";
            
            else if (Board[i][j] == "BP6")
                std::cout << "\u2659 ";
            
            else if (Board[i][j] == "BP7")
                std::cout << "\u2659 ";
            
            else if (Board[i][j] == "BP8")
                std::cout << "\u2659 ";
            
            else if (Board[i][j] == "WR")
                std::cout << "\u265C ";
            
            else if (Board[i][j] == "WN")
                std::cout << "\u265E ";
            
            else if (Board[i][j] == "WB")
                std::cout << "\u265D ";
            
            else if (Board[i][j] == "WQ")
                std::cout << "\u265B ";
            
            else if (Board[i][j] == "WK")
                std::cout << "\u265A ";
            
            else if (Board[i][j] == "WP1")
                std::cout << "\u265F ";
            
            else if (Board[i][j] == "WP2")
                std::cout << "\u265F ";
            
            else if (Board[i][j] == "WP3")
                std::cout << "\u265F ";
            
            else if (Board[i][j] == "WP4")
                std::cout << "\u265F ";
            
            else if (Board[i][j] == "WP5")
                std::cout << "\u265F ";
            
            else if (Board[i][j] == "WP6")
                std::cout << "\u265F ";
            
            else if (Board[i][j] == "WP7")
                std::cout << "\u265F ";
            
            else if (Board[i][j] == "WP8")
                std::cout << "\u265F ";
            
            else
                std::cout << ". ";
            
            
            if (j == 7)
                std::cout << "   " << 8 - i;
        }
        
        std::cout << std::endl;
        
        if (i == 7)
            std::cout << std::endl << "    A B C D E F G H" << std::endl << std::endl;
    }
}

std::string Ask_AI_For_Next_Move(void)
{
    std::string temp;
    
    return temp;
}

std::string Ask_User_For_Next_Move(void)
{
    bool isValueCorrect = false; // Flag for if input value in invalid
    std::string NextMove;
    
    while (!isValueCorrect)
    {
        isValueCorrect = true;
        
        // Prompt user for next command that will be the next grid position to attack
        std::cout << "Enter your next move: ";
        
        getline(std::cin, NextMove);
        
        // Check if cin failed
        if (std::cin.fail())
        {
            // Clear buffer and retry
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            isValueCorrect = false;
            continue;
        }
        
        Capitalise_Word(NextMove);
        
        std::string FirstWord, SecondWord;
        
        for (unsigned int currentPosition = 0, spaceCount = 0; currentPosition < NextMove.size(); currentPosition++) //Iterate across the line
        {
            if (NextMove[currentPosition] == ' ') //If a space is reached then whatever is in 'Placeholder' must be read in
                spaceCount++; //Increment space count
            
            else if (spaceCount == 0)
                FirstWord.push_back(NextMove[currentPosition]); //If current position in current line is NOT a space then read in the value
            
            else
                SecondWord.push_back(NextMove[currentPosition]);
        }
        
        if (FirstWord != "KING" && FirstWord != "QUEEN" && FirstWord != "BISHOP" && FirstWord != "KNIGHT" && FirstWord != "ROOK" && FirstWord != "PAWN")
        {
            isValueCorrect = false;
            continue;
        }
        
        if (SecondWord.size() != 2)
        {
            isValueCorrect = false;
            continue;
        }
        
        if (SecondWord[0] >= 97 && SecondWord[0] <= 104)
        {
            isValueCorrect = false;
            continue;
        }
            
            
        if (SecondWord[1] >= 49 && SecondWord[1] <= 56)
        {
            isValueCorrect = false;
            continue;
        }
        
        //*******************************************************
        // code to check if command is legal
        //*******************************************************
        
        
    }
    
    return NextMove;
}

void Capitalise_Word(std::string& aWord)
{
    // Takes a string and replaces every lowercase occurrence of a letter
    // and replaces it with its corresponding uppercase letter
    for (unsigned int i = 0; i < aWord.size(); i++)
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

void Execute_Next_Move()
{
    
}

void Display_Winning_Message()
{
    
}
