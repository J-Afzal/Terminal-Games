//
//  Battleships.cpp
//  Battleships
//
//  Created by Main on 17/12/2019.
//  Copyright © 2019 Junaid Afzal. All rights reserved.
//

#include "Battleships.hpp"
#include <iostream>
#include <iomanip>



void Setup_Game(std::vector< std::vector<char> >& AIBoard, std::vector< std::vector<int> >& UserBoardAsSeenFromAI, std::vector< std::vector<char> >& UserBoard, std::vector< std::vector<int> >& AIBoardAsSeenFromUser, std::string& CurrentPlayer)
{
    int NumberOfRows = 10, NumberOfColumns = 10;
    
    for (unsigned int i = 0, CurrentPosition = 0; i < NumberOfRows; i++)
    {
        std::vector<int> Row_int;
        std::vector<char> Row_char;
        
        AIBoard.push_back(Row_char);
        UserBoardAsSeenFromAI.push_back(Row_int);
        UserBoard.push_back(Row_char);
        AIBoardAsSeenFromUser.push_back(Row_int);
        
        for (unsigned int j = 0; j < NumberOfColumns; j++, CurrentPosition++)
        {
            AIBoard[i].push_back('.');
            UserBoardAsSeenFromAI[i].push_back(CurrentPosition);
            UserBoard[i].push_back('.');
            AIBoardAsSeenFromUser[i].push_back(CurrentPosition);
        }
    }
    
    
    Ask_AI_For_Battleship_Positions(AIBoard);
    
    Ask_User_For_Battleship_Positions(AIBoardAsSeenFromUser, UserBoard);
    
    
    std::srand(std::time(0));
    
    if ((std::rand() % 2) == 0)
        CurrentPlayer = "USER";
    else
        CurrentPlayer = "AI";
}



void Ask_AI_For_Battleship_Positions(std::vector< std::vector<char> >& AIBoard)
{
    std::cout << "No code for AI positions on board" << std::endl;
}



void Ask_User_For_Battleship_Positions(const std::vector< std::vector<int> >& AIBoardAsSeenFromUser, std::vector< std::vector<char> >& UserBoard)
{
    int CurrentShip = 0;
    
    while(CurrentShip < 5)
    {
        Display_Game(AIBoardAsSeenFromUser, UserBoard);
        std::string CurrentShipPositions_string;
        std::vector<int> CurrentShipPositions_ints;
        std::string CurrentShipPositionsOrientation;
        
        switch (CurrentShip)
        {
            case 0: // Carrier 5
            {
                int ShipSize = 5;
                
                std::cout << "Enter the " << ShipSize << " grid locations for the Carrier of size " << ShipSize << ": ";
                
                std::getline(std::cin, CurrentShipPositions_string);
                
                if(!Error_Checking_Ordering_Orientation_On_User_Input(UserBoard, CurrentShipPositions_string, CurrentShipPositions_ints, ShipSize, CurrentShipPositionsOrientation))
                    continue;
                
                if (!Can_Ship_Be_Placed(CurrentShipPositionsOrientation, UserBoard, CurrentShipPositions_ints, ShipSize))
                    continue;
                
                Place_Ship(UserBoard, CurrentShipPositions_ints, 'C');
                
                CurrentShip++;
                
                break;
            }
                
                
                
            case 1: // Battleship 4
            {
                int ShipSize = 4;
                
                std::cout << "Enter the " << ShipSize << " grid locations for the Battleship of size " << ShipSize << ": ";
                
                std::getline(std::cin, CurrentShipPositions_string);
                
                if(!Error_Checking_Ordering_Orientation_On_User_Input(UserBoard, CurrentShipPositions_string, CurrentShipPositions_ints, ShipSize, CurrentShipPositionsOrientation))
                    continue;
                
                if (!Can_Ship_Be_Placed(CurrentShipPositionsOrientation, UserBoard, CurrentShipPositions_ints, ShipSize))
                    continue;
                
                Place_Ship(UserBoard, CurrentShipPositions_ints, 'B');
                
                CurrentShip++;
                
                break;
            }
                
                
            
            case 2: // Destroyer 3
            {
                int ShipSize = 3;
                
                std::cout << "Enter the " << ShipSize << " grid locations for the Destroyer of size " << ShipSize << ": ";
                
                std::getline(std::cin, CurrentShipPositions_string);
                
                if(!Error_Checking_Ordering_Orientation_On_User_Input(UserBoard, CurrentShipPositions_string, CurrentShipPositions_ints, ShipSize, CurrentShipPositionsOrientation))
                    continue;
                
                if (!Can_Ship_Be_Placed(CurrentShipPositionsOrientation, UserBoard, CurrentShipPositions_ints, ShipSize))
                    continue;
                
                Place_Ship(UserBoard, CurrentShipPositions_ints, 'D');
                
                CurrentShip++;
                
                break;
            }
                
                
                
            case 3: // Submarine 3
            {
                int ShipSize = 3;
                
                std::cout << "Enter the " << ShipSize << " grid locations for the Submarine of size " << ShipSize << ": ";
                
                std::getline(std::cin, CurrentShipPositions_string);
                
                if(!Error_Checking_Ordering_Orientation_On_User_Input(UserBoard, CurrentShipPositions_string, CurrentShipPositions_ints, ShipSize, CurrentShipPositionsOrientation))
                    continue;
                
                if (!Can_Ship_Be_Placed(CurrentShipPositionsOrientation, UserBoard, CurrentShipPositions_ints, ShipSize))
                    continue;
                
                Place_Ship(UserBoard, CurrentShipPositions_ints, 'S');
                
                CurrentShip++;
                
                break;
            }
            
                
                
            case 4: // Patrol Boat 2
            {
                int ShipSize = 2;
                
                std::cout << "Enter the " << ShipSize << " grid locations for the Patrol Boat of size " << ShipSize << ": ";
                
                std::getline(std::cin, CurrentShipPositions_string);
                
                if(!Error_Checking_Ordering_Orientation_On_User_Input(UserBoard, CurrentShipPositions_string, CurrentShipPositions_ints, ShipSize, CurrentShipPositionsOrientation))
                    continue;
                
                if (!Can_Ship_Be_Placed(CurrentShipPositionsOrientation, UserBoard, CurrentShipPositions_ints, ShipSize))
                    continue;
                
                Place_Ship(UserBoard, CurrentShipPositions_ints, 'P');
                
                CurrentShip++;
                
                break;
            }
            
                
                
            default:
                std::cout << "Ask_User_For_Battleship_Positions() switch statement error" << std::endl;
                break;
        }
        
        std::cout << "End of while loop" << std::endl;
    }
}

void Display_Game(const std::vector< std::vector<int> >& AIBoardAsSeenFromUser, const std::vector< std::vector<char> >& UserBoard)
{
    // ***Better alternative needed***
    // Clears terminal window
    system("clear");
    
    std::cout << "--------------------Battleships V1.0 By Junaid Afzal--------------------\n" << std::endl;
    
    std::cout << "Opponent's Board" << std::endl;
    for (int i = 0; i < AIBoardAsSeenFromUser.size(); i++) {
        for (int j = 0; j < AIBoardAsSeenFromUser.size(); j++)
            std::cout << std::setw(2) << AIBoardAsSeenFromUser[i][j] << " ";

        std::cout << "\n";
    }
    
    std::cout << "\nYour Board" << std::endl;
    for (int i = 0; i < UserBoard.size(); i++) {
        for (int j = 0; j < UserBoard.size(); j++)
            std::cout << std::setw(2) << UserBoard[i][j] << " ";

        std::cout << "\n";
    }
}

bool Error_Checking_Ordering_Orientation_On_User_Input(const std::vector< std::vector<char> >& UserBoard, std::string& CurrentShipPositions_string, std::vector<int>& CurrentShipPositions_ints, const int& ShipSize, std::string& CurrentShipPositionsOrientation)
{
    if (std::cin.fail()) // Check if cin failed
    {
        // Clear buffer and retry
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }
    
    if (CurrentShipPositions_string.size() == 0)
    {
        // Clear buffer and retry
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }
    
    //check for just numbers
    for (int i = 0; i < CurrentShipPositions_string.size(); i++)
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
    
    //to make sure last number is read in
    if(CurrentShipPositions_string.back() != ' ')
        CurrentShipPositions_string.push_back(' ');
    
    //read in numbers
    std::string Temp;
    for (int i = 0; i < CurrentShipPositions_string.size(); i++)
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
    
    //check for just 5 nunbers
    if (CurrentShipPositions_ints.size() != ShipSize)
        return false;
    
    //check for duplicates
    for (int i = 0; i < CurrentShipPositions_ints.size(); i++)
        for (int j = 0; j < CurrentShipPositions_ints.size(); j++)
        {
            if (i == j)
                continue;
            
            if (CurrentShipPositions_ints[i] == CurrentShipPositions_ints[j])
                return false;
        }
    
    //check if numbers exist
    for (int i = 0; i < CurrentShipPositions_ints.size(); i++)
        if (CurrentShipPositions_ints[i] > 99)
            return false;
    
    
    //check if number already in use
    for (int i = 0; i < CurrentShipPositions_ints.size(); i++)
    {
        //each co ord
        //find grid position
        for (int j = 0, CurrentPosition = 0; j < UserBoard.size(); j++) {
            for (int k = 0; k < UserBoard.size(); k++, CurrentPosition++) {
                if (CurrentPosition == CurrentShipPositions_ints[i]) {
                    if (UserBoard[j][k] == 'C' || UserBoard[j][k] == 'B' || UserBoard[j][k] == 'D' || UserBoard[j][k] == 'S' || UserBoard[j][k] == 'P')
                        return false;
                }
            }
        }
    }
    
    //sort the numbers
    std::sort(CurrentShipPositions_ints.begin(), CurrentShipPositions_ints.end());
    
    //determine orientation
    // vertical if 10 difference between all values
    bool IsVertical = true;
    for (int i = 0; i < CurrentShipPositions_ints.size() - 1; i++) {
        if(CurrentShipPositions_ints[i] != (CurrentShipPositions_ints[i+1] - 10))
        {
            IsVertical = false;
            break;
        }
    }
    
    if (IsVertical) {
        CurrentShipPositionsOrientation = "Horizontal";
        return true;
    }
    
    // horizontal if +1 difference between all values
    bool IsHorizontal = true;
    for (int i = 0; i < CurrentShipPositions_ints.size() - 1; i++) {
        if(CurrentShipPositions_ints[i] != (CurrentShipPositions_ints[i+1] - 1))
        {
            IsHorizontal = false;
            break;
        }
    }
    
    if (IsHorizontal) {
        CurrentShipPositionsOrientation = "Vetical";
        return true;
    }
    
    return false;
}

bool Can_Ship_Be_Placed(const std::string& CurrentShipPositionsOrientation, const std::vector< std::vector<char> >& UserBoard, const std::vector<int>& CurrentShipPositions_ints, const int& ShipSize)
{
    for (int i = 0; i < UserBoard.size(); i++)
    {
        for (int j = 0; j <  UserBoard.size(); j++)
        {
            if (UserBoard[i][j] == CurrentShipPositions_ints[0])
            {
                if(CurrentShipPositionsOrientation == "Horizontal")
                {
                    if (j > (UserBoard.size() - ShipSize))
                        return false;
                }
                    
                else if(CurrentShipPositionsOrientation == "Vertical")
                {
                    if (i > (UserBoard.size() - ShipSize))
                        return false;
                }
            }
        }
    }
    
    return true;
}

void Place_Ship(std::vector< std::vector<char> >& UserBoard, const std::vector<int>& CurrentShipPositions_ints, const char& ShipName)
{
    for (int i = 0; i < CurrentShipPositions_ints.size(); i++)
    {
        //each co ord
        //find grid position
        for (int j = 0, CurrentPosition = 0; j < UserBoard.size(); j++) {
            for (int k = 0; k < UserBoard.size(); k++, CurrentPosition++) {
                if (CurrentPosition == CurrentShipPositions_ints[i]) {
                    UserBoard[j][k] = ShipName;
                }
            }
        }
    }
}
