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
            {
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
            }
            
            else if (i == 1)
                Board[i][j] = "BP";
            
            else if (i == 6)
                Board[i][j] = "WP";
            
            else if (i == 7)
            {
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

bool Game_Over();

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
        for (unsigned int j = 0; j < 8; j++)
        {
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
            
            else if (Board[i][j] == "BP")
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
            
            else if (Board[i][j] == "WP")
                std::cout << "\u265F ";
        }
        
        std::cout << std::endl;
    }
}

std::string Ask_AI_For_Next_Move();

std::string Ask_User_For_Next_Move();

void Execute_Next_Move();

void Display_Winning_Message();
