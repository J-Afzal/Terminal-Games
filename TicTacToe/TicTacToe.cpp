//
//  TicTacToe.cpp
//  TicTacToe
//
//  Created by Main on 09/12/2019.
//  Copyright © 2019 Junaid Afzal. All rights reserved.
//
//  The file contains the implementation of the TicTacToe game
//

#include "TicTacToe.hpp"
#include <iomanip>



void Play_TicTacToe(void)
{
    // Variables for the TicTacToe game
    //  - UserXOChoice is used when there is only one player and contains the 'X' or 'O' that the user has chosen to be
    //  - GameData contains the game info of the TicTacToe grid
    unsigned int NumberOfTurns = 0, CurrentPlayer = 0, NumberOfPlayers = 0, UserXOChoice = 0;
    std::vector< std::vector<int> > GameData;

    // The current player (and thus the player that starts) is assigned pseudo randomly; user is asked for the size of the
    // TicTacToe grid and is created; user is asked for the number of players; if players is 1 then human user asked if they
    // want to be X or O
    Setup_Game(NumberOfTurns, CurrentPlayer, NumberOfPlayers, UserXOChoice, GameData);
    
    // Loop until a winning condition is met or no more moves are possible and game is over
    while (!Winning_Conditions_Met(GameData) && !Game_Over(GameData))
    {
        // Displays the current TicTacToe grid
        Display_Current_Game(GameData);
        
        CurrentPlayer = Toggle_Player(CurrentPlayer);
        
        // Check if user input is required
        if(NumberOfPlayers == 2 || CurrentPlayer == UserXOChoice)
            GameData = Ask_User_For_Next_Input(GameData, CurrentPlayer);
        
        else
            GameData = Ask_AI_For_Next_Input(GameData, CurrentPlayer);

        NumberOfTurns++;

        std::cout << "\n\n" << std::endl;
     }

    // Determine the winner, if there is one, and display winning message
    Display_Winner(NumberOfTurns, GameData, CurrentPlayer);
}



void Setup_Game(unsigned int& NumberOfTurns, unsigned int& CurrentPlayer, unsigned int& NumberOfPlayers, unsigned int& UserXO, std::vector< std::vector<int> >& GameData)
{
    std::cout << "--------------------TicTacToe by Junaid Afzal--------------------" << std::endl;
    
    // Set seed to system time at 0 to create pseudo random numbers
    std::srand((unsigned int)std::time(0));
    
    // Assign currentplayer, and thus player to play first, randomly
    if (std::rand() % 2 == 0)
        CurrentPlayer = 'X'; // It will be converted to 88
    else
        CurrentPlayer = 'O'; // It will be converted to 79
    
    // The for loops add the 3 rows and columns to the grid and the the appropriate grid values
    for (unsigned int i = 0, GridNumber = 0; i < 3; i++)
    {
        std::vector<int> Rows;
        GameData.push_back(Rows);
        
        for (int j = 0; j < 3; j++, GridNumber++)
            GameData[i].push_back(GridNumber);
    }
    
    // Ask user for number of players
    NumberOfPlayers = Get_Number_Of_Players();
    
    // If only one human user then ask them for which player they want to be (X or O)
    if(NumberOfPlayers == 1)
        UserXO = Get_User_X_O_Choice();
}



int Get_Number_Of_Players(void)
{
    bool IsValueCorrect = false; // Flag for if input value in invalid
    int NumberOfPlayers = 0;
    
    while(!IsValueCorrect)
    {
        std::cout << "Enter the number of human players ";
        
        std::cin >> NumberOfPlayers;
        
        if (std::cin.fail()) // Check if cin failed
        {
            // Clear buffer and retry
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        
        else if(NumberOfPlayers < 0 || NumberOfPlayers > 2) // Only 0, 1 and 2 players allowed
        {
            // Clear buffer and retry
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
    
        else // If passed all tests then input is valid
            IsValueCorrect = true;
    }
    
    // This is to clear .22222 in a value 5.22222 as value would assume to be 5
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    return NumberOfPlayers;
}



int Get_User_X_O_Choice(void)
{
    bool IsValueCorrect = false; // Flag for if input value in invalid
    char UserXOChoice = 0;
    
    while(!IsValueCorrect)
    {
        std::cout << "Enter you player counter (X or O) ";
        
        std::cin >> UserXOChoice;
        
        if (std::cin.fail()) // Check if cin failed
        {
            // Clear buffer and retry
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        
        else if(UserXOChoice != 'X' && UserXOChoice != 'O') // Only X and O inputs allowed
        {
            // Clear buffer and retry
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
    
        else // If passed all tests then input is valid
            IsValueCorrect = true;
    }
    
    // This is to clear .22222 in a value 5.22222 as value would assume to be 5
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    return UserXOChoice;
}



bool Game_Over(const std::vector< std::vector<int> >& GameData)
{
    // Go through all positions on the grid and if it is not occupied by an X or O
    // then game is not over. Otherwise if all positions are occupied then game is over
    for(unsigned int i = 0; i < 3; i++)
        for(unsigned int j = 0; j < 3; j++)
            if(GameData[i][j] != 'X' && GameData[i][j] != 'O')
                return false;

    return true;
}



bool Winning_Conditions_Met(const std::vector< std::vector<int> >& GameData)
{
    if (GameData[0][0] == 'X' && GameData[0][1] == 'X' && GameData[0][2] == 'X')
        return true;
    
    else if (GameData[1][0] == 'X' && GameData[1][1] == 'X' && GameData[1][2] == 'X')
        return true;
    
    else if (GameData[2][0] == 'X' && GameData[2][1] == 'X' && GameData[2][2] == 'X')
        return true;
    

    else if (GameData[0][0] == 'X' && GameData[1][0] == 'X' && GameData[2][0] == 'X')
        return true;
    
    else if (GameData[0][1] == 'X' && GameData[1][1] == 'X' && GameData[2][1] == 'X')
        return true;
    
    else if (GameData[0][2] == 'X' && GameData[1][2] == 'X' && GameData[2][2] == 'X')
        return true;
    
    
    else if (GameData[0][0] == 'X' && GameData[1][1] == 'X' && GameData[2][2] == 'X')
        return true;
    
    else if (GameData[2][0] == 'X' && GameData[1][1] == 'X' && GameData[0][2] == 'X')
        return true;
    
    
    
    else if (GameData[0][0] =='O' && GameData[0][1] == 'O' && GameData[0][2] == 'O')
        return true;
    
    else if (GameData[1][0] == 'O' && GameData[1][1] == 'O' && GameData[1][2] == 'O')
        return true;
    
    else if (GameData[2][0] == 'O' && GameData[2][1] == 'O' && GameData[2][2] == 'O')
        return true;
    

    else if (GameData[0][0] == 'O' && GameData[1][0] == 'O' && GameData[2][0] == 'O')
        return true;
    
    else if (GameData[0][1] == 'O' && GameData[1][1] == 'O' && GameData[2][1] == 'O')
        return true;
    
    else if (GameData[0][2] == 'O' && GameData[1][2] == 'O' && GameData[2][2] == 'O')
        return true;
    
    
    else if (GameData[0][0] == 'O' && GameData[1][1] == 'O' && GameData[2][2] == 'O')
        return true;
    
    else if (GameData[2][0] == 'O' && GameData[1][1] == 'O' && GameData[0][2] == 'O')
        return true;
    
    
    
    else
        return false;
}



void Display_Current_Game(const std::vector< std::vector<int> >& GameData)
{
    // ***Better alternative needed***
    // Clears terminal window
    std::system("clear");

    // Solution to print errors = https://www.rapidtables.com/code/text/ascii-table.html
    
    std::cout << "--------------------TicTacToe by Junaid Afzal--------------------" << std::endl;
    // Iterate across whole grid and output its value
    for(unsigned int i = 0; i < 3; i++)
    {
        for (unsigned int  j = 0; j < 3; j++)
        {
            // X and O are stored as 88 and 79 respectively and so display them as char
            if (GameData[i][j] == 88 || GameData[i][j] == 79)
                std::cout  << std::left << (char)GameData[i][j] << " ";
                
            else
                std::cout << std::left << GameData[i][j] << " ";
            
            if (j == 0 || j == 1)
                std::cout << "\u2502 ";
        }
        
        if (i == 0 || i == 1)
        {
            std::cout << std::endl;
            
            for (int i = 0; i < 10; i++)
                std::cout << "\u2501";
            
            std::cout << std::endl;
        }
    }
    
    std::cout << std::endl << std::endl;
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
    bool IsValueCorrect = false; // Flag for if input value in invalid
    int UserCommand = 0;
    
    while(!IsValueCorrect)
    {
        // Set flag to true by default as difficult to continue to to next iteration of while loop
        // within a nested if statements within nested for loops
        IsValueCorrect = true;
        
        std::cout << "Player " << (char)CurrentPlayer << " enter command ";
        
        std::cin >> UserCommand;
        
        if (std::cin.fail()) // Check if cin failed
        {
            // Clear buffer, set flag to false and retry
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            IsValueCorrect = false;
            continue;
        }
        
        else if(UserCommand < 0 || UserCommand > 8) // Check if command is within range of grid
        {
            // Clear buffer, set flag to false and retry
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            IsValueCorrect = false;
            continue;
        }
        
        int Column = UserCommand % 3;
        int Row = UserCommand / 3;
        
        // Check if command has already been called by a player previously as it will contain and X or O
        if (GameData[Row][Column] == 'X' || GameData[Row][Column] == 'O')
            IsValueCorrect = false;
    }
    
    int Column = UserCommand % 3;
    int Row = UserCommand / 3;
    
    // Go to the command position in the grid and overwrite with the current player
    GameData[Row][Column] = CurrentPlayer;
    
    // This is to clear .22222 in a value 5.22222 as value would assume to be 5
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    return GameData;
}



std::vector< std::vector<int> > Ask_AI_For_Next_Input(std::vector< std::vector<int> >& GameData, const unsigned int& CurrentPlayer)
{
    bool IsValueCorrect = false; // Flag for if input value in invalid
    unsigned int AICommand = 0;
    
    while(!IsValueCorrect)
    {
        // Set flag to true by default as difficult to continue to to next iteration of while loop
        // within a nested if statements within nested for loops
        IsValueCorrect = true;
        
        // AI is dumb and picks a pseudo random number as command
        AICommand = std::rand() % 9;
        
        int Column = AICommand % 3;
        int Row = AICommand / 3;
        
        // Check if command has already been called by a player previously as it will contain and X or O
        if (GameData[Row][Column] == 'X' || GameData[Row][Column]== 'O')
            IsValueCorrect = false;
    }
    
    // Output a message which is similar to human player command message
    std::cout << "AI " << (char)CurrentPlayer << " entering command " << AICommand << std::endl;
    
    int Column = AICommand % 3;
    int Row = AICommand / 3;
    
    // Go to the command position in the grid and overwrite with the current player
    GameData[Row][Column] = CurrentPlayer;
    
    return GameData;
}



void Display_Winner(const unsigned int& NumberOfTurns, const std::vector< std::vector<int> >& GameData, const unsigned int& CurrentPlayer)
{
    // Winner will be current player as Toggle_Player() function has not been called from receiving input and determining winner
    if (Winning_Conditions_Met(GameData))
    {
       Display_Current_Game(GameData);
       std::cout << "Congratulations on Player " << (char)CurrentPlayer << " for winning!\nOnly took you " << NumberOfTurns << " turns\n\n\n" << std::endl;
    }

    // No winner so a draw
    else
    {
       Display_Current_Game(GameData);
       std::cout << "Game is a draw\nOnly took you " << NumberOfTurns << " turns\n\n\n" << std::endl;
    }
}
