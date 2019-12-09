//
//  TicTacToe.cpp
//  TicTacToe
//
//  Created by Main on 09/12/2019.
//  Copyright © 2019 Junaid Afzal. All rights reserved.
//

#include "TicTacToe.hpp"

//Constructors and destructor
TicTacToe::TicTacToe()
{
    GameData.push_back('0');
    GameData.push_back('1');
    GameData.push_back('2');
    GameData.push_back('3');
    GameData.push_back('4');
    GameData.push_back('5');
    GameData.push_back('6');
    GameData.push_back('7');
    GameData.push_back('8');
        
    if (rand() % 2 == 0)
        CurrentPlayer = 'X';
    
    else
        CurrentPlayer = 'O';
    
    NumberOfTurns = 0;
}

TicTacToe::TicTacToe(const TicTacToe& aTicTacToe) { *this = aTicTacToe; }

TicTacToe::~TicTacToe() { }



//Custom cout function
std::ostream& operator<< (std::ostream& Output, const TicTacToe& aTicTacToe)
{
    Output << aTicTacToe.GameData[0] << " " << aTicTacToe.GameData[1] << " " << aTicTacToe.GameData[2] << std::endl;
    Output << aTicTacToe.GameData[3] << " " << aTicTacToe.GameData[4] << " " << aTicTacToe.GameData[5] << std::endl;
    Output << aTicTacToe.GameData[6] << " " << aTicTacToe.GameData[7] << " " << aTicTacToe.GameData[8] << std::endl;
    
    return Output;
}
    
//Custom operator function
TicTacToe& TicTacToe::operator = (const TicTacToe& aTicTacToe)
{
    if (&aTicTacToe == this)
        return *this;
    
    else
    {
        GameData = aTicTacToe.GameData;
        CurrentPlayer = aTicTacToe.CurrentPlayer;
        NumberOfTurns = aTicTacToe.NumberOfTurns;
    }
    
    return *this;
}

//TicTacToe specific functions
void TicTacToe::Play_Game(void)
{
   while (!Game_Over())
   {
        std::cout << "TicTacToe V1.0 by Junaid Afzal\n" << std::endl;
                
        std::cout << *this << std::endl;
       
        Toggle_Player();
       
        Input();
        
        std::cout << "\n\n" << std::endl;
    }
    
    if (Game_Winner())
        std::cout << "Congratulations on Player " << CurrentPlayer << " for winning!\nOnly took you " << NumberOfTurns << " turns" << std::endl;
    
    else
        std::cout << "Game is a draw\nOnly took you " << NumberOfTurns << " turns" << std::endl;
}
    

//Private member functions
bool TicTacToe::Game_Over(void)
{
    if(Game_Winner())
        return true;
    
    for (int i = 0; i < 9; i++)
        if(GameData[i] != 'X' || GameData[i] != 'O')
            return false;
    
    return true;
}

bool TicTacToe::Game_Winner(void)
{
    if(GameData[0] == 'X' && GameData[1] == 'X' && GameData[2] == 'X')
        return true;
    
    else if(GameData[3] == 'X' && GameData[4] == 'X' && GameData[5] == 'X')
        return true;
    
    else if(GameData[6] == 'X' && GameData[7] == 'X' && GameData[8] == 'X')
        return true;
    
    else if(GameData[0] == 'X' && GameData[3] == 'X' && GameData[6] == 'X')
        return true;
    
    else if(GameData[1] == 'X' && GameData[4] == 'X' && GameData[7] == 'X')
        return true;
    
    else if(GameData[2] == 'X' && GameData[5] == 'X' && GameData[8] == 'X')
        return true;
    
    else if(GameData[0] == 'X' && GameData[4] == 'X' && GameData[8] == 'X')
        return true;
    
    else if(GameData[6] == 'X' && GameData[4] == 'X' && GameData[2] == 'X')
        return true;
    
    
    
    else if(GameData[0] == 'O' && GameData[1] == 'O' && GameData[2] == 'O')
        return true;
    
    else if(GameData[3] == 'O' && GameData[4] == 'O' && GameData[5] == 'O')
        return true;
    
    else if(GameData[6] == 'O' && GameData[7] == 'O' && GameData[8] == 'O')
        return true;

    else if(GameData[0] == 'O' && GameData[3] == 'O' && GameData[6] == 'O')
        return true;
    
    else if(GameData[1] == 'O' && GameData[4] == 'O' && GameData[7] == 'O')
        return true;
    
    else if(GameData[2] == 'O' && GameData[5] == 'O' && GameData[8] == 'O')
        return true;
    
    else if(GameData[0] == 'O' && GameData[4] == 'O' && GameData[8] == 'O')
        return true;
    
    else if(GameData[6] == 'O' && GameData[4] == 'O' && GameData[2] == 'O')
        return true;
    
    
    
    else
        return false;
}

void TicTacToe::Input(void)
{
    bool IsValueCorrect = false;
    int PlayerCommand = 0;
    
    while(!IsValueCorrect)
    {
        std::cout << "Player " << CurrentPlayer << " enter command ";
        
        std::cin >> PlayerCommand;
    
        if(PlayerCommand < 0 || PlayerCommand > 8)
            continue;
        
        else if(GameData[PlayerCommand] == 'X' || GameData[PlayerCommand] == 'O')
            continue;
    
        else
            IsValueCorrect = true;
    }
    
    GameData[PlayerCommand] = CurrentPlayer;
    
    NumberOfTurns++;
}

void TicTacToe::Toggle_Player(void)
{
    if(CurrentPlayer == 'X')
        CurrentPlayer = 'O';
    
    else
        CurrentPlayer = 'X';
}
