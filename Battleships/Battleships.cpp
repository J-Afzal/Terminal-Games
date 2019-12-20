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



void Setup_Game(std::vector< std::vector<char> >& AIBoard, std::vector< std::vector<char> >& AIOpponentBoard, std::vector< std::vector<char> >& UserBoard, std::vector< std::vector<char> >& UserOpponentBoard, std::string& CurrentPlayer)
{
    int NumberOfRows = 10, NumberOfColumns = 10;
    
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
    
    std::srand(std::time(0));
    
    Ask_AI_For_Battleship_Positions(AIBoard);
        
    Ask_User_For_Battleship_Positions(UserOpponentBoard, UserBoard);
    
    
    if ((std::rand() % 2) == 0)
        CurrentPlayer = "USER";
    else
        CurrentPlayer = "AI";
}



void Ask_AI_For_Battleship_Positions(std::vector< std::vector<char> >& AIBoard)
{
    int CurrentShip = 0;
    
    while(CurrentShip < 5)
    {
        std::vector<int> CurrentShipPositions_ints;
        std::string CurrentShipPositionsOrientation;
        std::string IncreasingOrDecreasing;
        
        switch (CurrentShip)
        {
            case 0: // Carrier 5
            {
                int ShipSize = 5;
                
                Get_Ship_Coordinates(AIBoard, CurrentShipPositionsOrientation, CurrentShipPositions_ints, ShipSize);
                
                if (!Error_Checking_On_AI_Input(AIBoard, CurrentShipPositions_ints))
                    continue;
                
                Place_Ship(AIBoard, CurrentShipPositions_ints, 'C');
                
                CurrentShip++;
                
                break;
            }
                
                
                
            case 1: // Battleship 4
            {
                int ShipSize = 4;

                Get_Ship_Coordinates(AIBoard, CurrentShipPositionsOrientation, CurrentShipPositions_ints, ShipSize);
                
                if (!Error_Checking_On_AI_Input(AIBoard, CurrentShipPositions_ints))
                    continue;

                Place_Ship(AIBoard, CurrentShipPositions_ints, 'B');

                CurrentShip++;

                break;
            }



            case 2: // Destroyer 3
            {
                int ShipSize = 3;

                Get_Ship_Coordinates(AIBoard, CurrentShipPositionsOrientation, CurrentShipPositions_ints, ShipSize);
                
                if (!Error_Checking_On_AI_Input(AIBoard, CurrentShipPositions_ints))
                    continue;

                Place_Ship(AIBoard, CurrentShipPositions_ints, 'D');

                CurrentShip++;

                break;
            }



            case 3: // Submarine 3
            {
                int ShipSize = 3;

                Get_Ship_Coordinates(AIBoard, CurrentShipPositionsOrientation, CurrentShipPositions_ints, ShipSize);
                
                if (!Error_Checking_On_AI_Input(AIBoard, CurrentShipPositions_ints))
                    continue;

                Place_Ship(AIBoard, CurrentShipPositions_ints, 'S');

                CurrentShip++;

                break;
            }



            case 4: // Patrol Boat 2
            {
                int ShipSize = 2;

                Get_Ship_Coordinates(AIBoard, CurrentShipPositionsOrientation, CurrentShipPositions_ints, ShipSize);
                
                if (!Error_Checking_On_AI_Input(AIBoard, CurrentShipPositions_ints))
                    continue;

                Place_Ship(AIBoard, CurrentShipPositions_ints, 'P');

                CurrentShip++;

                break;
            }



            default:
                std::cout << "Ask_AI_For_Battleship_Positions() switch statement error" << std::endl;
                break;
       }
   }
}

bool Error_Checking_On_AI_Input(const std::vector< std::vector<char> >& AIBoard, const std::vector<int>& CurrentShipPositions_ints)
{
    //check if number already in use
    for (int i = 0; i < CurrentShipPositions_ints.size(); i++)
    {
        //each co ord
        //find grid position
        for (int j = 0, CurrentPosition = 0; j < AIBoard.size(); j++) {
            for (int k = 0; k < AIBoard.size(); k++, CurrentPosition++) {
                if (CurrentPosition == CurrentShipPositions_ints[i]) {
                    if (AIBoard[j][k] == 'C' || AIBoard[j][k] == 'B' || AIBoard[j][k] == 'D' || AIBoard[j][k] == 'S' || AIBoard[j][k] == 'P')
                        return false;
                }
            }
        }
    }
    
    return true;
}

void Get_Ship_Coordinates(const std::vector< std::vector<char> >& AIBoard, std::string& CurrentShipPositionsOrientation, std::vector<int>& CurrentShipPositions_ints, const int& ShipSize)
{
    int Singles, Tens, FirstValue;
    
    if ((std::rand() % 2) == 0)
    {
        CurrentShipPositionsOrientation = "Horizontal";
        
        Singles = std::rand() % (AIBoard.size() - ShipSize + 1);
        Tens = std::rand() % AIBoard.size();
        
        FirstValue = Tens*AIBoard.size() + Singles;
        CurrentShipPositions_ints.push_back(FirstValue);
        
        for (int i = 1; i < ShipSize; i++)
            CurrentShipPositions_ints.push_back(FirstValue+i);
    }
    
    else
    {
        CurrentShipPositionsOrientation = "Vertical";
        
        Singles = std::rand() % AIBoard.size();
        Tens = std::rand() % (AIBoard.size() - ShipSize + 1);
        
        FirstValue = Tens*AIBoard.size() + Singles;
        CurrentShipPositions_ints.push_back(FirstValue);
        
        for (int i = 1; i < ShipSize; i++)
            CurrentShipPositions_ints.push_back(FirstValue+(i*AIBoard.size()));
    }
}

void Ask_User_For_Battleship_Positions(const std::vector< std::vector<char> >& UserOpponentBoard, std::vector< std::vector<char> >& UserBoard)
{
    int CurrentShip = 0;

    while(CurrentShip < 5)
    {
        Display_Game(UserOpponentBoard, UserBoard);
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
    }
}

void Display_Game(const std::vector< std::vector<char> >& UserOpponentBoard, const std::vector< std::vector<char> >& UserBoard)
{
    // ***Better alternative needed***
    // Clears terminal window
    system("clear");
    
    std::cout << "--------------------Battleships V1.0 By Junaid Afzal--------------------\n" << std::endl;
    
    std::cout << "---Opponent's Board---" << std::endl;
    for (int i = 0; i < UserOpponentBoard.size(); i++) {
        for (int j = 0; j < UserOpponentBoard.size(); j++)
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
    
    std::cout << "\n---Your Board---" << std::endl;
    for (int i = 0; i < UserBoard.size(); i++) {
        for (int j = 0; j < UserBoard.size(); j++)
            std::cout << std::setw(2) << UserBoard[i][j] << " ";

        std::cout << "\n";
    }
    
    std::cout << "\n";
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
    
    //check for just shipsize numbers nunbers
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
        CurrentShipPositionsOrientation = "Vertical";
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
        CurrentShipPositionsOrientation = "Horizontal";
        return true;
    }
    
    return false;
}

bool Can_Ship_Be_Placed(const std::string& CurrentShipPositionsOrientation, const std::vector< std::vector<char> >& UserBoard, const std::vector<int>& CurrentShipPositions_ints, const int& ShipSize)
{
    for (int i = 0, CurrentBoardPosition = 0; i < UserBoard.size(); i++)
    {
        for (int j = 0; j <  UserBoard.size(); j++, CurrentBoardPosition++)
        {
            if (CurrentBoardPosition == CurrentShipPositions_ints[0])
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

bool Winning_Conditions_Met_For_UserBoard(const std::vector< std::vector<char> >& UserBoard)
{
    for (int i = 0; i < UserBoard.size(); i++)
        for (int j = 0; j < UserBoard.size(); j++)
            if (UserBoard[i][j] == 'C' || UserBoard[i][j] == 'B' || UserBoard[i][j] == 'D' || UserBoard[i][j] == 'S' || UserBoard[i][j] == 'P')
                return false;
    
    return true;
}

bool Winning_Conditions_Met_For_AIBoard(const std::vector< std::vector<char> >& AIBoard)
{
    for (int i = 0; i < AIBoard.size(); i++)
        for (int j = 0; j < AIBoard.size(); j++)
            if (AIBoard[i][j] == 'C' || AIBoard[i][j] == 'B' || AIBoard[i][j] == 'D' || AIBoard[i][j] == 'S' || AIBoard[i][j] == 'P')
                return false;
    
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
    int Command = 0;
    
    while (!isValueCorrect)
    {
        isValueCorrect = true;
        
        Command = std::rand() % 100;
        
        for (int i = 0, CurrentPosition = 0; i < AIOpponentBoard.size(); i++) {
            for (int j = 0; j < AIOpponentBoard.size(); j++, CurrentPosition++) {
                if (CurrentPosition == Command) {
                    if (AIOpponentBoard[i][j] == 79 || AIOpponentBoard[i][j] == 88) // X 88 or O 79
                    {
                        isValueCorrect = false;
                        i = j = AIOpponentBoard.size();
                        break;
                    }
                }
            }
        }
    }
    
    return Command;
}

void Execute_Next_Turn(std::vector< std::vector<char> >& AIBoard, std::vector< std::vector<char> >& AIOpponentBoard, std::vector< std::vector<char> >& UserBoard, std::vector< std::vector<char> >& UserOpponentBoard, const std::string& CurrentPlayer, const int& Command)
{
    if (CurrentPlayer == "USER")
    {
        for (int i = 0, CurrentPosition = 0; i < AIOpponentBoard.size(); i++) {
            for (int j = 0; j < AIOpponentBoard.size(); j++, CurrentPosition++) {
                if (CurrentPosition == Command) {
                    if (AIBoard[i][j] == 'C' || AIBoard[i][j] == 'B' || AIBoard[i][j] == 'D' || AIBoard[i][j] == 'S' || AIBoard[i][j] == 'P')
                    {
                        AIBoard[i][j] = 'X';
                        UserOpponentBoard[i][j] = 'x'; //120
                    }
                    
                    else
                    {
                        AIBoard[i][j] = '.';
                        UserOpponentBoard[i][j] = 'o'; //111
                    }
                }
            }
        }
    }
    
    else
    {
        for (int i = 0, CurrentPosition = 0; i < AIOpponentBoard.size(); i++) {
            for (int j = 0; j < AIOpponentBoard.size(); j++, CurrentPosition++) {
                if (CurrentPosition == Command) {
                    if (UserBoard[i][j] == 'C' || UserBoard[i][j] == 'B' || UserBoard[i][j] == 'D' || UserBoard[i][j] == 'S' || UserBoard[i][j] == 'P')
                    {
                        UserBoard[i][j] = 'X';
                        AIOpponentBoard[i][j] = 'x'; //120
                    }
                    
                    else
                    {
                        UserBoard[i][j] = '.';
                        AIOpponentBoard[i][j] = 'o'; //111
                    }
                }
            }
        }
    }
}

int Ask_User_For_Next_Command(const std::vector< std::vector<char> >& UserOpponentBoard)
{
    bool isValueCorrect = false;
    int Command = 0;
    
    while (!isValueCorrect)
    {
        isValueCorrect = true;
        
        std::cout << "Enter your next command ";
        
        std::cin >> Command;
        
        if (std::cin.fail()) // Check if cin failed
        {
            // Clear buffer and retry
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            isValueCorrect = false;
            continue;
        }
        
        if (Command < 0 || Command > 99)
        {
            isValueCorrect = false;
            continue;
        }
            
        for (int i = 0, CurrentPosition = 0; i < UserOpponentBoard.size(); i++) {
            for (int j = 0; j < UserOpponentBoard.size(); j++, CurrentPosition++) {
                if (CurrentPosition == Command) {
                    if (UserOpponentBoard[i][j] == 'x' || UserOpponentBoard[i][j] == 'o')
                    {
                        isValueCorrect = false;
                        i = j = UserOpponentBoard.size();
                        break;
                    }
                }
            }
        }
    }
    
    // This is to clear .22222 in a value 5.22222 as value would assume to be 5
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    return Command;
}

void Display_Winning_Message(const std::string& CurrentPlayer, const unsigned int& NumberOfTurns)
{
    if (CurrentPlayer == "USER")
        std::cout << "Congratulations, you won!\nOnly took " << NumberOfTurns << " turns" << std::endl;
    
    else
        std::cout << "Commiserations, you lost!\nOnly took " << NumberOfTurns << " turns" << std::endl;
}
