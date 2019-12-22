//
//  Battleships.cpp
//  Battleships
//
//  Created by Main on 17/12/2019.
//  Copyright © 2019 Junaid Afzal. All rights reserved.
//
//  The file contains the implementation of the Battleships game
//

#include "Battleships.hpp"
#include <iostream>
#include <vector>
#include <iomanip>



void Play_Battleships(void)
{
    // Variables needed for the game
    std::vector< std::vector<char> > AIBoard, AIOpponentBoard, UserBoard, UserOpponentBoard;
    std::string CurrentPlayer;
    unsigned int NumberOfTurns = 0;
    
    // Setups all the varibales so that game can be played
    Setup_Game(AIBoard, AIOpponentBoard, UserBoard, UserOpponentBoard, CurrentPlayer);
    
    // This only displays the boards of the human user
    // Display before while loop for the sake of visual consistency
    Display_Game(UserOpponentBoard, UserBoard);
    
    // Loop until a winning condition on either board exists
    while (!Winning_Conditions_Met_For_AIBoard(AIBoard) && !Winning_Conditions_Met_For_UserBoard(UserBoard))
    {
        // Change to the other player
        Toggle_Player(CurrentPlayer);
        
        // If player is the computer
        if (CurrentPlayer == "AI")
        {
            // Ask computer for a grid position that they want to attack
            unsigned int Command = Ask_AI_For_Next_Command(AIOpponentBoard);
            
            // Carry out the attack and update the corresponding boards
            Execute_Next_Turn(AIBoard, AIOpponentBoard, UserBoard, UserOpponentBoard, CurrentPlayer, Command);
        }
        
        // Else the player will be human user
        else
        {
            // Display the current state of the game so human user can determine their next move
            Display_Game(UserOpponentBoard, UserBoard);
            
            // Ask human user for a grid position that they want to attack
            unsigned int Command = Ask_User_For_Next_Command(UserOpponentBoard);
            
            // Carry out the attack and update the corresponding boards
            Execute_Next_Turn(AIBoard, AIOpponentBoard, UserBoard, UserOpponentBoard, CurrentPlayer, Command);
            
            // Immediately display the result of the attack
            Display_Game(UserOpponentBoard, UserBoard);
        }

        // Increment the number of turns
        NumberOfTurns++;
    }

    // Display the winning message as game is now over
    Display_Winning_Message(CurrentPlayer, NumberOfTurns);
}



void Setup_Game(std::vector< std::vector<char> >& AIBoard, std::vector< std::vector<char> >& AIOpponentBoard, std::vector< std::vector<char> >& UserBoard, std::vector< std::vector<char> >& UserOpponentBoard, std::string& CurrentPlayer)
{
    // Board size is a standard 10 x 10
    unsigned int NumberOfRows = 10, NumberOfColumns = 10;
    
    // The AIBoard and UserBoard will be filled with spaces while the opponent boards will be filled
    // with incrementing numbers from 0 - 99, left to right and then top to bottom
    for (unsigned int i = 0, CurrentPosition = 0; i < NumberOfRows; i++)
    {
        std::vector<char> Row;
        
        AIBoard.push_back(Row);
        AIOpponentBoard.push_back(Row);
        UserBoard.push_back(Row);
        UserOpponentBoard.push_back(Row);
        
        for (unsigned int j = 0; j < NumberOfColumns; j++, CurrentPosition++)
        {
            AIBoard[i].push_back(' ');
            AIOpponentBoard[i].push_back(CurrentPosition);
            UserBoard[i].push_back(' ');
            UserOpponentBoard[i].push_back(CurrentPosition);
        }
    }
    
    // Set seed for std::rand() to system time at 0
    std::srand(std::time(0));
    
    // Ask AI for the ship positions and update AI board
    Ask_AI_For_Ship_Positions(AIBoard);
    
    // Asks user for the ship positions and update UserBoard
    Ask_User_For_Ship_Positions(UserOpponentBoard, UserBoard);
    
    // Use std::rand() to randomly choose the player to start
    if ((std::rand() % 2) == 0)
        CurrentPlayer = "USER";
    else
        CurrentPlayer = "AI";
}



void Ask_AI_For_Ship_Positions(std::vector< std::vector<char> >& AIBoard)
{
    // Will count how many ships have been assigned
    unsigned int CurrentShip = 0;
    
    // When ship count has reached 5 then all ships have been assigned a position
    while(CurrentShip < 5)
    {
        std::vector<int> CurrentShipPositions_ints;
        std::string CurrentShipPositionsOrientation;
        std::string IncreasingOrDecreasing;
        
        switch (CurrentShip)
        {
            case 0:
            {
                // Carrier of size 5
                unsigned int ShipSize = 5;
                
                // Ask computer for ship position
                Get_AI_Ship_Coordinates(AIBoard, CurrentShipPositionsOrientation, CurrentShipPositions_ints, ShipSize);
                
                // If error checking returns false then continue to next iteration
                if (!Error_Checking_On_AI_Ship_Coordinates(AIBoard, CurrentShipPositions_ints))
                    continue;
                
                // Place ship on AIBoard using the CurrentShipPositions_ints positions and marking with 'C' for carrier
                Place_Ship(AIBoard, CurrentShipPositions_ints, 'C');
                
                // Increment the ship count
                CurrentShip++;
                
                break;
            }
                
            case 1:
            {
                // Battleship of size 4
                unsigned int ShipSize = 4;

                // Ask computer for ship position
                Get_AI_Ship_Coordinates(AIBoard, CurrentShipPositionsOrientation, CurrentShipPositions_ints, ShipSize);
                
                // If error checking returns false then continue to next iteration
                if (!Error_Checking_On_AI_Ship_Coordinates(AIBoard, CurrentShipPositions_ints))
                    continue;

                // Place ship on AIBoard using the CurrentShipPositions_ints positions and marking with 'B' for battleship
                Place_Ship(AIBoard, CurrentShipPositions_ints, 'B');

                // Increment the ship count
                CurrentShip++;

                break;
            }

            case 2:
            {
                // Destroyer of size 3
                unsigned int ShipSize = 3;

                // Ask computer for ship position
                Get_AI_Ship_Coordinates(AIBoard, CurrentShipPositionsOrientation, CurrentShipPositions_ints, ShipSize);
                
                // If error checking returns false then continue to next iteration
                if (!Error_Checking_On_AI_Ship_Coordinates(AIBoard, CurrentShipPositions_ints))
                    continue;

                // Place ship on AIBoard using the CurrentShipPositions_ints positions and marking with 'D' for destroyer
                Place_Ship(AIBoard, CurrentShipPositions_ints, 'D');

                // Increment the ship count
                CurrentShip++;

                break;
            }

            case 3:
            {
                // Submarine of size 3
                unsigned int ShipSize = 3;

                // Ask computer for ship position
                Get_AI_Ship_Coordinates(AIBoard, CurrentShipPositionsOrientation, CurrentShipPositions_ints, ShipSize);
                
                // If error checking returns false then continue to next iteration
                if (!Error_Checking_On_AI_Ship_Coordinates(AIBoard, CurrentShipPositions_ints))
                    continue;

                // Place ship on AIBoard using the CurrentShipPositions_ints positions and marking with 'S' for submarine
                Place_Ship(AIBoard, CurrentShipPositions_ints, 'S');

                // Increment the ship count
                CurrentShip++;

                break;
            }

            case 4:
            {
                // Patrol Boat of size 2
                unsigned int ShipSize = 2;

                // Ask computer for ship position
                Get_AI_Ship_Coordinates(AIBoard, CurrentShipPositionsOrientation, CurrentShipPositions_ints, ShipSize);
                
                // If error checking returns false then continue to next iteration
                if (!Error_Checking_On_AI_Ship_Coordinates(AIBoard, CurrentShipPositions_ints))
                    continue;

                // Place ship on AIBoard using the CurrentShipPositions_ints positions and marking with 'P' for patrol boat
                Place_Ship(AIBoard, CurrentShipPositions_ints, 'P');

                // Increment the ship count
                CurrentShip++;

                break;
            }

            default:
                // Error message stating where it has occured
                std::cout << "Ask_AI_For_Ship_Positions() switch statement error" << std::endl;
                break;
       }
   }
}



void Get_AI_Ship_Coordinates(const std::vector< std::vector<char> >& AIBoard, std::string& CurrentShipPositionsOrientation, std::vector<int>& CurrentShipPositions_ints, const unsigned int& ShipSize)
{
    // Singles represents the column number; Tens the row number; and the FirstValue is the first value of the gird positions when ordered in ascending order
    unsigned int Singles, Tens, FirstValue;
    
    // Use std::rand() to randomly choose between a vertical or horizontal orientation
    if ((std::rand() % 2) == 0)
    {
        CurrentShipPositionsOrientation = "Horizontal";
        
        // A max column number exists, as ship is horizontal, which is linked with the size of the ship
        // with the assumption being this value will be the first and smallest of the positions
        Singles = std::rand() % (AIBoard.size() - ShipSize + 1);
        
        // Any row number allowed as ship is horizontal
        Tens = std::rand() % AIBoard.size();
        
        // Create the first value and add to the CurrentShipPositions_ints
        FirstValue = Tens*AIBoard.size() + Singles;
        CurrentShipPositions_ints.push_back(FirstValue);
        
        // Horizontal positions have a difference of 1 between positions
        for (unsigned int i = 1; i < ShipSize; i++)
            CurrentShipPositions_ints.push_back(FirstValue+i);
    }
    
    else
    {
        CurrentShipPositionsOrientation = "Vertical";
        
        // Any column number allowed as ship is horizontal
        Singles = std::rand() % AIBoard.size();
        
        // A max row number exists, as ship is vertical, which is linked with the size of the ship
        // with the assumption being this value will be the first and smallest of the positions
        Tens = std::rand() % (AIBoard.size() - ShipSize + 1);
        
        // Create the first value and add to the CurrentShipPositions_ints
        FirstValue = Tens*AIBoard.size() + Singles;
        CurrentShipPositions_ints.push_back(FirstValue);
        
        // Vertical positions have a difference of AIBoard.size(), which is 10, between positions
        for (unsigned int i = 1; i < ShipSize; i++)
            CurrentShipPositions_ints.push_back(FirstValue+(i*AIBoard.size()));
    }
}



bool Error_Checking_On_AI_Ship_Coordinates(const std::vector< std::vector<char> >& AIBoard, const std::vector<int>& CurrentShipPositions_ints)
{
    // Only check required is if any of the ship positions are already occupied by another ship
    // Cylce through all ship positions
    for (unsigned int i = 0; i < CurrentShipPositions_ints.size(); i++)
    {
        // The next two for loops go to the position on the grid of the current ship position that is being checked and then checks
        // if that positions contains any of the ship letters
        for (unsigned int j = 0, CurrentPosition = 0; j < AIBoard.size(); j++)
            for (unsigned int k = 0; k < AIBoard.size(); k++, CurrentPosition++)
                if (CurrentPosition == CurrentShipPositions_ints[i])
                    if (AIBoard[j][k] == 'C' || AIBoard[j][k] == 'B' || AIBoard[j][k] == 'D' || AIBoard[j][k] == 'S' || AIBoard[j][k] == 'P')
                        return false;
    }
    
    // If none of the positions are occupied then return true
    return true;
}



void Ask_User_For_Ship_Positions(const std::vector< std::vector<char> >& UserOpponentBoard, std::vector< std::vector<char> >& UserBoard)
{
    unsigned int CurrentShip = 0;

    while(CurrentShip < 5)
    {
        Display_Game(UserOpponentBoard, UserBoard);
        std::string CurrentShipPositions_string;
        std::vector<int> CurrentShipPositions_ints;
        std::string CurrentShipPositionsOrientation;

        switch (CurrentShip)
        {
            case 0:
            {
                // Carrier of size 5
                unsigned int ShipSize = 5;
                
                // User prompt for ship locations
                std::cout << "Enter the " << ShipSize << " grid locations for the Carrier of size " << ShipSize << ": ";

                // Using std::getline so string with spaces is read in
                std::getline(std::cin, CurrentShipPositions_string);

                // If error checking returns false then continue to next iteration
                if(!Error_Checking_Ordering_Orientation_On_User_Input(UserBoard, CurrentShipPositions_string, CurrentShipPositions_ints, ShipSize, CurrentShipPositionsOrientation))
                    continue;

                // If ship can't be placed then continue to next iteration
                if (!Can_Ship_Be_Placed(CurrentShipPositionsOrientation, UserBoard, CurrentShipPositions_ints, ShipSize))
                    continue;

                // Place ship on UserBoard using the CurrentShipPositions_ints positions and marking with 'C' for carrier
                Place_Ship(UserBoard, CurrentShipPositions_ints, 'C');

                // Increment the ship count
                CurrentShip++;

                break;
            }



            case 1:
            {
                // Battleship of size 4
                unsigned int ShipSize = 4;

                // User prompt for ship locations
                std::cout << "Enter the " << ShipSize << " grid locations for the Battleship of size " << ShipSize << ": ";

                // Using std::getline so string with spaces is read in
                std::getline(std::cin, CurrentShipPositions_string);

                // If error checking returns false then continue to next iteration
                if(!Error_Checking_Ordering_Orientation_On_User_Input(UserBoard, CurrentShipPositions_string, CurrentShipPositions_ints, ShipSize, CurrentShipPositionsOrientation))
                    continue;

                // If ship can't be placed then continue to next iteration
                if (!Can_Ship_Be_Placed(CurrentShipPositionsOrientation, UserBoard, CurrentShipPositions_ints, ShipSize))
                    continue;

                // Place ship on UserBoard using the CurrentShipPositions_ints positions and marking with 'B' for battleship
                Place_Ship(UserBoard, CurrentShipPositions_ints, 'B');

                // Increment the ship count
                CurrentShip++;

                break;
            }



            case 2:
            {
                // Destroyer of size 3
                unsigned int ShipSize = 3;

                // User prompt for ship locations
                std::cout << "Enter the " << ShipSize << " grid locations for the Destroyer of size " << ShipSize << ": ";

                // Using std::getline so string with spaces is read in
                std::getline(std::cin, CurrentShipPositions_string);

                // If error checking returns false then continue to next iteration
                if(!Error_Checking_Ordering_Orientation_On_User_Input(UserBoard, CurrentShipPositions_string, CurrentShipPositions_ints, ShipSize, CurrentShipPositionsOrientation))
                    continue;

                // If ship can't be placed then continue to next iteration
                if (!Can_Ship_Be_Placed(CurrentShipPositionsOrientation, UserBoard, CurrentShipPositions_ints, ShipSize))
                    continue;

                // Place ship on UserBoard using the CurrentShipPositions_ints positions and marking with 'D' for destroyer
                Place_Ship(UserBoard, CurrentShipPositions_ints, 'D');

                // Increment the ship count
                CurrentShip++;

                break;
            }



            case 3:
            {
                // Submarine of size 3
                unsigned int ShipSize = 3;

                // User prompt for ship locations
                std::cout << "Enter the " << ShipSize << " grid locations for the Submarine of size " << ShipSize << ": ";

                // Using std::getline so string with spaces is read in
                std::getline(std::cin, CurrentShipPositions_string);

                // If error checking returns false then continue to next iteration
                if(!Error_Checking_Ordering_Orientation_On_User_Input(UserBoard, CurrentShipPositions_string, CurrentShipPositions_ints, ShipSize, CurrentShipPositionsOrientation))
                    continue;

                // If ship can't be placed then continue to next iteration
                if (!Can_Ship_Be_Placed(CurrentShipPositionsOrientation, UserBoard, CurrentShipPositions_ints, ShipSize))
                    continue;

                // Place ship on UserBoard using the CurrentShipPositions_ints positions and marking with 'S' for submarine
                Place_Ship(UserBoard, CurrentShipPositions_ints, 'S');

                // Increment the ship count
                CurrentShip++;

                break;
            }



            case 4:
            {
                // Patrol Boat of size 2
                unsigned int ShipSize = 2;

                // User prompt for ship locations
                std::cout << "Enter the " << ShipSize << " grid locations for the Patrol Boat of size " << ShipSize << ": ";

                // Using std::getline so string with spaces is read in
                std::getline(std::cin, CurrentShipPositions_string);

                // If error checking returns false then continue to next iteration
                if(!Error_Checking_Ordering_Orientation_On_User_Input(UserBoard, CurrentShipPositions_string, CurrentShipPositions_ints, ShipSize, CurrentShipPositionsOrientation))
                    continue;

                // If ship can't be placed then continue to next iteration
                if (!Can_Ship_Be_Placed(CurrentShipPositionsOrientation, UserBoard, CurrentShipPositions_ints, ShipSize))
                    continue;

                // Place ship on UserBoard using the CurrentShipPositions_ints positions and marking with 'P' for patrol boat
                Place_Ship(UserBoard, CurrentShipPositions_ints, 'P');

                // Increment the ship count
                CurrentShip++;

                break;
            }
            
                
                
            default:
                // Error message stating where it has occured
                std::cout << "Ask_User_For_Ship_Positions() switch statement error" << std::endl;
                break;
        }
    }
}



void Display_Game(const std::vector< std::vector<char> >& UserOpponentBoard, const std::vector< std::vector<char> >& UserBoard)
{
    // ***Better alternative needed***
    // Clears terminal window
    system("clear");
    
    std::cout << "--------------------Battleships V1.0 By Junaid Afzal--------------------\n" << std::endl;
    
    // First display the opponent's board with hits = X, misses = . and empty spots = grid position
    // See Execute_Next_Turn() for why 'x' and 'o' are used instead of 'X' and '.'
    std::cout << "---Opponent's Board---" << std::endl;
    for (unsigned int i = 0; i < UserOpponentBoard.size(); i++)
    {
        for (unsigned int j = 0; j < UserOpponentBoard.size(); j++)
        {
            if (UserOpponentBoard[i][j] == 'x')
                std::cout << std::setw(2) << 'X' << " ";
            
            else if (UserOpponentBoard[i][j] == 'o')
                std::cout << std::setw(2) << '.' << " ";
                
            else
                std::cout << std::setw(2) << (int)UserOpponentBoard[i][j] << " ";
        }
            
        std::cout << "\n";
    }
    
    // Display the user's board with hits = 'X', misses = '.' and empty spots = ' '
    std::cout << "\n---Your Board---" << std::endl;
    for (unsigned int i = 0; i < UserBoard.size(); i++)
    {
        for (unsigned int j = 0; j < UserBoard.size(); j++)
            std::cout << std::setw(2) << UserBoard[i][j] << " ";

        std::cout << "\n";
    }
    
    std::cout << "\n";
}



bool Error_Checking_Ordering_Orientation_On_User_Input(const std::vector< std::vector<char> >& UserBoard, std::string& CurrentShipPositions_string, std::vector<int>& CurrentShipPositions_ints, const unsigned int& ShipSize, std::string& CurrentShipPositionsOrientation)
{
    // Check if cin failed
    if (std::cin.fail())
    {
        // Clear buffer and retry
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }
    
    // Check if string is empty
    if (CurrentShipPositions_string.size() == 0)
    {
        // Clear buffer and retry
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }
    
    //Check if string contains non-number characters with an exception of space character ( = 32)
    for (unsigned int i = 0; i < CurrentShipPositions_string.size(); i++)
    {
        if (CurrentShipPositions_string[i] < 48 && CurrentShipPositions_string[i] != 32)
        {
            // Clear buffer and retry
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return false;
        }

        if (CurrentShipPositions_string[i] > 57)
        {
            // Clear buffer and retry
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return false;
        }
    }
    
    //Add space to the end of string, if there is no space at the end, so last number can be read in easier
    if(CurrentShipPositions_string.back() != ' ')
        CurrentShipPositions_string.push_back(' ');
    
    // Iterate across string; read in value to temp until a space is reached; then convert
    // that value to an int; with a check to see if string is empty
    std::string Temp;
    for (unsigned int i = 0; i < CurrentShipPositions_string.size(); i++)
    {
        if (CurrentShipPositions_string[i] != ' ')
            Temp.push_back(CurrentShipPositions_string[i]);
        
        else if (Temp.size() == 0)
            continue;
            
        else
        {
            CurrentShipPositions_ints.push_back(std::stoi(Temp, nullptr, 10));
            Temp.clear();
        }
    }
    
    // Check if the correct number of positions were given
    if (CurrentShipPositions_ints.size() != ShipSize)
        return false;
    
    // Check for duplicates in the ship positions given
    for (unsigned int i = 0; i < CurrentShipPositions_ints.size(); i++)
        for (unsigned int j = 0; j < CurrentShipPositions_ints.size(); j++)
        {
            if (i == j)
                continue;
            
            if (CurrentShipPositions_ints[i] == CurrentShipPositions_ints[j])
                return false;
        }
    
    // Check if positions are over 99, as 99 is the limit
    for (unsigned int i = 0; i < CurrentShipPositions_ints.size(); i++)
        if (CurrentShipPositions_ints[i] > 99)
            return false;
    
    // Check if any of the ship positions are already occupied by another ship
    // Cylce through all ship positions
    for (unsigned int i = 0; i < CurrentShipPositions_ints.size(); i++)
    {
        // The next two for loops and if statement go to the position on the grid of the current ship position that is being checked
        // and then checks if that positions contains any of the ship letters
        for (unsigned int j = 0, CurrentPosition = 0; j < UserBoard.size(); j++)
            for (unsigned int k = 0; k < UserBoard.size(); k++, CurrentPosition++)
                if (CurrentPosition == CurrentShipPositions_ints[i])
                    if (UserBoard[j][k] == 'C' || UserBoard[j][k] == 'B' || UserBoard[j][k] == 'D' || UserBoard[j][k] == 'S' || UserBoard[j][k] == 'P')
                        return false;
    }
    
    // Sort the positions in ascending order
    std::sort(CurrentShipPositions_ints.begin(), CurrentShipPositions_ints.end());
    
    // Check is ship has an orientation, using the assumption that the ship positions have been ordered in ascending order
    // Ship is vertical if there is a difference of 10 between all values
    bool IsVertical = true;
    for (int i = 0; i < CurrentShipPositions_ints.size() - 1; i++)
        if(CurrentShipPositions_ints[i] != (CurrentShipPositions_ints[i+1] - 10))
        {
            IsVertical = false;
            break;
        }
    
    if (IsVertical)
    {
        CurrentShipPositionsOrientation = "Vertical";
        return true;
    }
    
    // Ship is horizontal if there is a difference of 1 between all values
    bool IsHorizontal = true;
    for (unsigned int i = 0; i < CurrentShipPositions_ints.size() - 1; i++)
        if(CurrentShipPositions_ints[i] != (CurrentShipPositions_ints[i+1] - 1))
        {
            IsHorizontal = false;
            break;
        }
    
    if (IsHorizontal)
    {
        CurrentShipPositionsOrientation = "Horizontal";
        return true;
    }
    
    // If neither vertical or horizontal then invalid ship positions
    return false;
}



bool Can_Ship_Be_Placed(const std::string& CurrentShipPositionsOrientation, const std::vector< std::vector<char> >& UserBoard, const std::vector<int>& CurrentShipPositions_ints, const unsigned int& ShipSize)
{
    // The next two for loops and if statement go to the first grid position
    for (unsigned int i = 0, CurrentBoardPosition = 0; i < UserBoard.size(); i++)
        for (unsigned int j = 0; j <  UserBoard.size(); j++, CurrentBoardPosition++)
            if (CurrentBoardPosition == CurrentShipPositions_ints[0])
            {
                // A max column number (j) exists, as ship is horizontal, which is linked with the size of the ship
                // with the assumption being this value will be the first and smallest of the positions
                if(CurrentShipPositionsOrientation == "Horizontal")
                {
                    if (j > (UserBoard.size() - ShipSize))
                        return false;
                }
                    
                // A max row number (i) exists, as ship is vertical, which is linked with the size of the ship
                // with the assumption being this value will be the first and smallest of the positions
                else if(CurrentShipPositionsOrientation == "Vertical")
                {
                    if (i > (UserBoard.size() - ShipSize))
                        return false;
                }
            }
    
    // If test is passed then return true
    return true;
}



void Place_Ship(std::vector< std::vector<char> >& UserBoard, const std::vector<int>& CurrentShipPositions_ints, const unsigned char& ShipName)
{
    for (unsigned int i = 0; i < CurrentShipPositions_ints.size(); i++)
    {
        // The next two for loops and if statement go to the current grid position
        for (unsigned int j = 0, CurrentPosition = 0; j < UserBoard.size(); j++)
            for (unsigned int k = 0; k < UserBoard.size(); k++, CurrentPosition++)
                if (CurrentPosition == CurrentShipPositions_ints[i])
                    // Overwrite the UserBoard with the ship name
                    UserBoard[j][k] = ShipName;
    }
}



bool Winning_Conditions_Met_For_UserBoard(const std::vector< std::vector<char> >& UserBoard)
{
    // If there are any ship letter on the board then winning condition is not met
    for (unsigned int i = 0; i < UserBoard.size(); i++)
        for (unsigned int j = 0; j < UserBoard.size(); j++)
            if (UserBoard[i][j] == 'C' || UserBoard[i][j] == 'B' || UserBoard[i][j] == 'D' || UserBoard[i][j] == 'S' || UserBoard[i][j] == 'P')
                return false;
    
    // Otherwise there are no ships left and winning condtion as been met
    return true;
}



bool Winning_Conditions_Met_For_AIBoard(const std::vector< std::vector<char> >& AIBoard)
{
    // If there are any ship letter on the board then winning condition is not met
    for (unsigned int i = 0; i < AIBoard.size(); i++)
        for (unsigned int j = 0; j < AIBoard.size(); j++)
            if (AIBoard[i][j] == 'C' || AIBoard[i][j] == 'B' || AIBoard[i][j] == 'D' || AIBoard[i][j] == 'S' || AIBoard[i][j] == 'P')
                return false;
    
    // Otherwise there are no ships left and winning condtion as been met
    return true;
}



void Toggle_Player(std::string& CurrentPlayer)
{
    if (CurrentPlayer == "USER")
          CurrentPlayer = "AI";
    
    else
        CurrentPlayer = "USER";
}



int Ask_AI_For_Next_Command(const std::vector< std::vector<char> >& AIOpponentBoard)
{
    bool isValueCorrect = false;
    unsigned int Command = 0;
    
    while (!isValueCorrect)
    {
        // Set flag to true by default as difficult to continue to to next iteration of while loop
        // within a nested if statements within nested for loops
        isValueCorrect = true;
        
        // Computer randomly chooses a value from 0 to 99
        Command = std::rand() % 100;
        
        // The next two for loops and if statement go to the position on the grid of the command
        // and check if the grid position has already been attacked
        for (unsigned int i = 0, CurrentPosition = 0; i < AIOpponentBoard.size(); i++)
            for (unsigned int j = 0; j < AIOpponentBoard.size(); j++, CurrentPosition++)
                if (CurrentPosition == Command)
                    if (AIOpponentBoard[i][j] == 'x' || AIOpponentBoard[i][j] == 'o')
                    {
                        // Set flag to false; i and j to terminating values and then break
                        isValueCorrect = false;
                        i = j = AIOpponentBoard.size();
                        break;
                    }
    }
    
    return Command;
}



void Execute_Next_Turn(std::vector< std::vector<char> >& AIBoard, std::vector< std::vector<char> >& AIOpponentBoard, std::vector< std::vector<char> >& UserBoard, std::vector< std::vector<char> >& UserOpponentBoard, const std::string& CurrentPlayer, const unsigned int& Command)
{
    // Check which use is attacking and therefore is being attacked
    if (CurrentPlayer == "USER")
    {
        // The next two for loops and if statement go to the position on the grid of the command
        for (unsigned int i = 0, CurrentPosition = 0; i < AIOpponentBoard.size(); i++)
            for (unsigned int j = 0; j < AIOpponentBoard.size(); j++, CurrentPosition++)
                if (CurrentPosition == Command)
                {
                    // If it is a ship letter then it is a hit
                    if (AIBoard[i][j] == 'C' || AIBoard[i][j] == 'B' || AIBoard[i][j] == 'D' || AIBoard[i][j] == 'S' || AIBoard[i][j] == 'P')
                    {
                        // Update the AI board
                        AIBoard[i][j] = 'X';
                        
                        // Lower case 'x' is used as it has a value of 120 while upper case 'X' has a value
                        // inside the 0-99 range and so conflicts with the grid position labels
                        UserOpponentBoard[i][j] = 'x';
                    }
                    
                    // Otherwise it is a miss
                    else
                    {
                        // Update the AI board
                        AIBoard[i][j] = '.';
                        
                        // A lower case 'o' is used as it has a value of 111 while the full stop ',' has a value
                        // inside the 0-99 range and so conflicts with the grid position labels
                        UserOpponentBoard[i][j] = 'o';
                    }
                }
    }
    
    else
    {
        // The next two for loops and if statement go to the position on the grid of the command
        for (unsigned int i = 0, CurrentPosition = 0; i < AIOpponentBoard.size(); i++)
            for (unsigned int j = 0; j < AIOpponentBoard.size(); j++, CurrentPosition++)
                if (CurrentPosition == Command)
                {
                    // If it is a ship letter then it is a hit
                    if (UserBoard[i][j] == 'C' || UserBoard[i][j] == 'B' || UserBoard[i][j] == 'D' || UserBoard[i][j] == 'S' || UserBoard[i][j] == 'P')
                    {
                        // Update the User board
                        UserBoard[i][j] = 'X';
                        
                        // Lower case 'x' is used as it has a value of 120 while upper case 'X' has a value
                        // inside the 0-99 range and so conflicts with the grid position labels
                        AIOpponentBoard[i][j] = 'x';
                    }
                    
                    // Otherwise it is a miss
                    else
                    {
                        // Update the User board
                        UserBoard[i][j] = '.';
                        
                        // A lower case 'o' is used as it has a value of 111 while the full stop ',' has a value
                        // inside the 0-99 range and so conflicts with the grid position labels
                        AIOpponentBoard[i][j] = 'o';
                    }
                }
    }
}



int Ask_User_For_Next_Command(const std::vector< std::vector<char> >& UserOpponentBoard)
{
    bool isValueCorrect = false; // Flag for if input value in invalid
    unsigned int Command = 0;
    
    while (!isValueCorrect)
    {
        // Set flag to true by default as difficult to continue to to next iteration of while loop
        // within a nested if statements within nested for loops
        isValueCorrect = true;
        
        // Prompt user for next command that will be the next grid position to attack
        std::cout << "Enter your next command ";
        
        std::cin >> Command;
        
        // Check if cin failed
        if (std::cin.fail())
        {
            // Clear buffer and retry
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            isValueCorrect = false;
            continue;
        }
        
        // Check if value is not between 0 and 99
        if (Command < 0 || Command > 99)
        {
            // If so retry
            isValueCorrect = false;
            continue;
        }
        
        // The next two for loops and if statement go to the position on the grid of the command
        // and check if the grid position has already been attacked
        for (unsigned int i = 0, CurrentPosition = 0; i < UserOpponentBoard.size(); i++)
            for (unsigned int j = 0; j < UserOpponentBoard.size(); j++, CurrentPosition++)
                if (CurrentPosition == Command)
                    if (UserOpponentBoard[i][j] == 'x' || UserOpponentBoard[i][j] == 'o')
                    {
                        // Set flag to false; i and j to terminating values and then break
                        isValueCorrect = false;
                        i = j = UserOpponentBoard.size();
                        break;
                    }
    }
    
    // This is to clear .22222 in a value 5.22222 as value would assume to be 5
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    return Command;
}



void Display_Winning_Message(const std::string& CurrentPlayer, const unsigned int& NumberOfTurns)
{
    // CurrentPlayer is the winner of the game as player toggle as not been triggered since last attack and gamer over check
    if (CurrentPlayer == "USER")
        std::cout << "Congratulations, you won!\nOnly took " << NumberOfTurns << " turns" << std::endl;
    
    // Winner will be computer so human user will see a losing message
    else
        std::cout << "Commiserations, you lost!\nOnly took " << NumberOfTurns << " turns" << std::endl;
}
