//
//  TicTacToe.cpp
//  TicTacToe
//
//  Created by Main on 09/12/2019.
//  Copyright © 2019 Junaid Afzal. All rights reserved.
//

#include "TicTacToe.hpp"
#include <iostream>
#include <vector>
#include <iomanip>

void Play_TicTacToe(void)
{
    unsigned int NumberOfTurns = 0, CurrentPlayer = 0, NumberOfPlayers = 0, UserXO = 0;
    std::vector< std::vector<int> > GameData;

    Setup_Game(NumberOfTurns, CurrentPlayer, NumberOfPlayers, UserXO, GameData);
    
    while (!Winning_Conditions_Met(GameData) && !Game_Over(GameData))
    {
        Display_Current_Game(GameData);

        CurrentPlayer = Toggle_Player(CurrentPlayer);
        
        if(NumberOfPlayers == 2 || CurrentPlayer == UserXO)
            GameData = Ask_User_For_Next_Input(GameData, CurrentPlayer);
        
        else
            GameData = Ask_AI_For_Next_Input(GameData, CurrentPlayer);

        NumberOfTurns++;

        std::cout << "\n\n" << std::endl;
     }

    Display_Winner(NumberOfTurns, GameData, CurrentPlayer);
}

void Setup_Game(unsigned int& NumberOfTurns, unsigned int& CurrentPlayer, unsigned int& NumberOfPlayers, unsigned int& UserXO, std::vector< std::vector<int> >& GameData)
{
    std::cout << "--------------------TicTacToe V1.0 by Junaid Afzal--------------------" << std::endl;
    
    std::srand(std::time(0));
    if (std::rand() % 2 == 0)
        CurrentPlayer = 'X'; //88
    else
        CurrentPlayer = 'O'; //79
        
    GameData = Get_Size_Of_Grid();
    
    NumberOfPlayers = Get_Number_Of_Players();
        
    if(NumberOfPlayers == 1)
        UserXO = Get_User_X_O();
}

std::vector< std::vector<int> > Get_Size_Of_Grid(void)
{
    std::vector< std::vector<int> > GameData;
    
    bool IsValueCorrect = false;
    int SizeOfGrid = 0;
    
    while(!IsValueCorrect)
    {
        std::cout << "Enter the size of the grid ";
        
        std::cin >> SizeOfGrid;
        
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        
        else if(SizeOfGrid <= 2)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        
        else
            IsValueCorrect = true;
    }
    
    for (unsigned int i = 0, GridNumber = 0; i < SizeOfGrid; i++)
    {
        std::vector<int> Rows;
        GameData.push_back(Rows);
        
        for (int j = 0; j < SizeOfGrid; j++, GridNumber++)
            GameData[i].push_back(GridNumber);
    }
    
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    return GameData;
}

int Get_Number_Of_Players(void)
{
    bool IsValueCorrect = false;
    int NumberOfPlayers = 0;
    
    while(!IsValueCorrect)
    {
        std::cout << "Enter the number of players ";
        
        std::cin >> NumberOfPlayers;
        
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        
        else if(NumberOfPlayers < 0 || NumberOfPlayers > 2)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
    
        else
            IsValueCorrect = true;
    }
    
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    return NumberOfPlayers;
}

int Get_User_X_O(void)
{
    bool IsValueCorrect = false;
    char UserXO = 0;
    
    while(!IsValueCorrect)
    {
        std::cout << "Enter user counter (X or O) ";
        
        std::cin >> UserXO;
        
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        
        else if(UserXO != 'X' && UserXO != 'O')
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
    
        else
            IsValueCorrect = true;
    }
    
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    return UserXO;
}


bool Game_Over(const std::vector< std::vector<int> >& GameData)
{
    for(unsigned int i = 0; i < GameData.size(); i++)
        for(unsigned int j = 0; j < GameData.size(); j++)
            if(GameData[i][j] != 'X' && GameData[i][j] != 'O')
                return false;

    return true;
}

bool Winning_Conditions_Met(const std::vector< std::vector<int> >& GameData)
{
    for(unsigned int i = 0; i < GameData.size(); i++)
    {
        for(unsigned int j = 0, HowManyX = 0, HowManyO = 0; j < GameData.size(); j++)
        {
            if(GameData[i][j] == 'X')
                 HowManyX++;
            
            if(GameData[i][j] == 'O')
                HowManyO++;
            
            if(HowManyX == GameData.size())
                return true;
            
            if(HowManyO == GameData.size())
                return true;
        }
    }
    
    for(unsigned int i = 0; i < GameData.size(); i++)
    {
        for(unsigned int j = 0, HowManyX = 0, HowManyO = 0; j < GameData.size(); j++)
        {
            if(GameData[j][i] == 'X')
                 HowManyX++;
            
            if(GameData[j][i] == 'O')
                HowManyO++;
            
            if(HowManyX == GameData.size())
                return true;
            
            if(HowManyO == GameData.size())
                return true;
        }
    }
    
    for(unsigned int i = 0, HowManyX = 0, HowManyO = 0; i < GameData.size(); i++)
    {
        if(GameData[i][i] == 'X')
             HowManyX++;
        
        if(GameData[i][i] == 'O')
            HowManyO++;
        
        if(HowManyX == GameData.size())
            return true;
        
        if(HowManyO == GameData.size())
            return true;
    }
    
    for(unsigned long i = GameData.size() - 1, j = 0, HowManyX = 0, HowManyO = 0; j < GameData.size(); i--, j++)
    {
        if(GameData[i][j] == 'X')
             HowManyX++;
        
        if(GameData[i][j] == 'O')
            HowManyO++;
        
        if(HowManyX == GameData.size())
            return true;
        
        if(HowManyO == GameData.size())
            return true;
    }
    
    return false;
}

void Display_Current_Game(const std::vector< std::vector<int> >& GameData)
{
    for(unsigned int i = 0, GridPosition = 0; i < GameData.size(); i++, GridPosition++)
    {
        for (unsigned int  j = 0; j < GameData.size(); j++, GridPosition++)
        {
            if (GameData[i][j] == 88 || GameData[i][j] == 79)
                std::cout << std::setw(4) << std::left << (char)GameData[i][j] << " ";
                
            else
                std::cout << std::setw(4) << std::left << GameData[i][j] << " ";
        }
        
        std::cout << "\n\n";
    }
}

char Toggle_Player(const int& CurrentPlayer)
{
    if(CurrentPlayer == 'X')
        return 'O';

    else
        return 'X';
}

std::vector< std::vector<int> > Ask_User_For_Next_Input(std::vector< std::vector<int> >& GameData, const unsigned int& CurrentPlayer)
{
    bool IsValueCorrect = false;
    int PlayerCommand = 0;
    
    while(!IsValueCorrect)
    {
        IsValueCorrect = true;
        
        std::cout << "Player " << (char)CurrentPlayer << " enter command ";
        
        std::cin >> PlayerCommand;
        
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            IsValueCorrect = false;
            continue;
        }
        
        else if(PlayerCommand < 0 || PlayerCommand > (GameData.size() * GameData.size() - 1))
        {
            IsValueCorrect = false;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        
        for(unsigned long i = 0, GridPosition = 0; i < GameData.size(); i++)
        {
            for (unsigned int  j = 0; j < GameData.size(); j++, GridPosition++)
            {
                if (GridPosition == PlayerCommand)
                {
                    if (GameData[i][j] == 'X' || GameData[i][j]== 'O')
                        IsValueCorrect = false;
                    
                    i = GameData.size();
                    break;
                }
            }
        }
    }
    
    for(unsigned long i = 0, GridPosition = 0; i < GameData.size(); i++)
    {
        for (unsigned int  j = 0; j < GameData.size(); j++, GridPosition++)
        {
            if (GridPosition == PlayerCommand)
            {
                GameData[i][j] = CurrentPlayer;
                i = GameData.size();
                break;
            }
        }
    }
    
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    return GameData;
}

std::vector< std::vector<int> > Ask_AI_For_Next_Input(std::vector< std::vector<int> >& GameData, const unsigned int& CurrentPlayer)
{
    bool IsValueCorrect = false;
    unsigned int AICommand = 0;
    
    while(!IsValueCorrect)
    {
        IsValueCorrect = true;
        
        AICommand = std::rand() % (GameData.size() * GameData.size());
                
        for(unsigned long i = 0, GridPosition = 0; i < GameData.size(); i++)
        {
            for (unsigned int  j = 0; j < GameData.size(); j++, GridPosition++)
            {
                if (GridPosition == AICommand)
                {
                    if (GameData[i][j] == 'X' || GameData[i][j]== 'O')
                        IsValueCorrect = false;
                    
                    i = GameData.size();
                    break;
                }
            }
        }
    }
    
    std::cout << "AI " << (char)CurrentPlayer << " entering command " << AICommand;
    
    for(unsigned long i = 0, GridPosition = 0; i < GameData.size(); i++)
    {
        for (unsigned int  j = 0; j < GameData.size(); j++, GridPosition++)
        {
            if (GridPosition == AICommand)
            {
                GameData[i][j] = CurrentPlayer;
                i = GameData.size();
                break;
            }
        }
    }
    
    return GameData;
}

void Display_Winner(const unsigned int& NumberOfTurns, const std::vector< std::vector<int> >& GameData, const unsigned int& CurrentPlayer)
{
    if (Winning_Conditions_Met(GameData))
    {
       Display_Current_Game(GameData);
       std::cout << "Congratulations on Player " << (char)CurrentPlayer << " for winning!\nOnly took you " << NumberOfTurns << " turns" << std::endl;
       std::cout << "--------------------TicTacToe V2.0 by Junaid Afzal--------------------\n\n" << std::endl;
    }

    else
    {
       Display_Current_Game(GameData);
       std::cout << "Game is a draw\nOnly took you " << NumberOfTurns << " turns" << std::endl;
       std::cout << "--------------------TicTacToe V2.0 by Junaid Afzal--------------------\n\n" << std::endl;
    }
}
