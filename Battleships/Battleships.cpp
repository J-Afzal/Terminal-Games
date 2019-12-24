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
    std::vector< std::vector<char> > PlayerOneBoard, PlayerOneOpponentBoard, PlayerTwoBoard, PlayerTwoOpponentBoard;
    std::string CurrentPlayer;
    unsigned int NumberOfPlayers, NumberOfTurns = 0;
    
    // Setups all the varibales so that game can be played
    Setup_Game(PlayerOneBoard, PlayerOneOpponentBoard, PlayerTwoBoard, PlayerTwoOpponentBoard, NumberOfPlayers, CurrentPlayer);
    
    //Loop until a winning condition on either board exists
    while (!Winning_Conditions_Met_For_Player_One_Board(PlayerOneBoard) && !Winning_Conditions_Met_For_Player_Two_Board(PlayerTwoBoard))
    {
        // Change to the other player
        Toggle_Player(CurrentPlayer);

        // One human player and one computer player
        if (NumberOfPlayers == 1)
        {
            // Human player is PLAYER_ONE by default
            if (CurrentPlayer == "PLAYER_ONE")
            {
                //Display the current state of the game so human user can determine their next move
                Display_Game_For_User(PlayerOneBoard, PlayerOneOpponentBoard);
                
                // Ask human user for a grid position that they want to attack
                unsigned int Command = Ask_User_For_Next_Command(PlayerOneOpponentBoard);
                
                // Carry out the attack and update the corresponding boards
                Execute_Next_Turn(PlayerOneBoard, PlayerOneOpponentBoard, PlayerTwoBoard, PlayerTwoOpponentBoard, CurrentPlayer, Command);
    
                // Immediately display the result of the attack
                Display_Game_For_User(PlayerOneBoard, PlayerOneOpponentBoard);
            }

            // Player is the computer
            else
            {
                //Ask computer for a grid position that they want to attack
                unsigned int Command = Ask_AI_For_Next_Command(PlayerTwoOpponentBoard);
                
                // Carry out the attack and update the corresponding boards
                Execute_Next_Turn(PlayerOneBoard, PlayerOneOpponentBoard, PlayerTwoBoard, PlayerTwoOpponentBoard, CurrentPlayer, Command);
            }
        }

        // computer vs computer
        else
        {
            // Player is the computer
            if (CurrentPlayer == "PLAYER_ONE")
            {
                //Ask computer for a grid position that they want to attack
                unsigned int Command = Ask_AI_For_Next_Command(PlayerOneOpponentBoard);
                
                // Carry out the attack and update the corresponding boards
                Execute_Next_Turn(PlayerOneBoard, PlayerOneOpponentBoard, PlayerTwoBoard, PlayerTwoOpponentBoard, CurrentPlayer, Command);
            }

            // Player is the computer
            else
            {
                //Ask computer for a grid position that they want to attack
                unsigned int Command = Ask_AI_For_Next_Command(PlayerTwoOpponentBoard);
                
                // Carry out the attack and update the corresponding boards
                Execute_Next_Turn(PlayerOneBoard, PlayerOneOpponentBoard, PlayerTwoBoard, PlayerTwoOpponentBoard, CurrentPlayer, Command);
            }
            
            Display_Game_For_AIs(PlayerOneBoard, PlayerTwoBoard);
        }
        
        // Increment the number of turns
        NumberOfTurns++;
    }
    
    // Display the winning message as game is now over
    Display_Winning_Message(CurrentPlayer, NumberOfTurns);
}



void Setup_Game(std::vector< std::vector<char> >& PlayerOneBoard, std::vector< std::vector<char> >& PlayerOneOpponentBoard, std::vector< std::vector<char> >& PlayerTwoBoard, std::vector< std::vector<char> >& PlayerTwoOpponentBoard, unsigned int& NumberOfPlayers, std::string& CurrentPlayer)
{
    // Board size is a standard 10 x 10
    unsigned int NumberOfRows = 10, NumberOfColumns = 10;
    
    // The AIBoard and UserBoard will be filled with spaces while the opponent boards will be filled
    // with incrementing numbers from 0 - 99, left to right and then top to bottom
    for (unsigned int i = 0, CurrentPosition = 0; i < NumberOfRows; i++)
    {
        std::vector<char> Row;
        
        PlayerOneBoard.push_back(Row);
        PlayerOneOpponentBoard.push_back(Row);
        PlayerTwoBoard.push_back(Row);
        PlayerTwoOpponentBoard.push_back(Row);
        
        for (unsigned int j = 0; j < NumberOfColumns; j++, CurrentPosition++)
        {
            PlayerOneBoard[i].push_back('.');
            PlayerOneOpponentBoard[i].push_back(CurrentPosition);
            PlayerTwoBoard[i].push_back('.');
            PlayerTwoOpponentBoard[i].push_back(CurrentPosition);
        }
    }
    
    // Set seed for std::rand() to system time at 0
    std::srand((unsigned int)std::time(0));
    
    std::cout << "--------------------Battleships By Junaid Afzal--------------------" << std::endl;
    
    // Get number of players
    NumberOfPlayers = Ask_User_For_Number_Of_Players();
    
    // If 1 then 1 human player and one computer player
    if (NumberOfPlayers == 1)
    {
        // Asks user for the ship positions and update UserBoard
        Ask_User_For_Ship_Positions(PlayerOneBoard, PlayerOneOpponentBoard);
        
        // Ask AI for the ship positions and update AI board
        Ask_AI_For_Ship_Positions(PlayerTwoBoard);
    }
    
    // If 0 then zero human players and two computer players
    else
    {
        // Ask AI for the ship positions and update AI board
        Ask_AI_For_Ship_Positions(PlayerOneBoard);
        
        // Ask AI for the ship positions and update AI board
        Ask_AI_For_Ship_Positions(PlayerTwoBoard);
    }
    
    // Use std::rand() to randomly choose the player to start
    if ((std::rand() % 2) == 0)
        CurrentPlayer = "PLAYER_ONE";
    else
        CurrentPlayer = "PLAYER_TWO";
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
        
        // Check if value is not between 0 and 99
        if (NumberOfPlayers != 0 && NumberOfPlayers != 1)
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



void Ask_User_For_Ship_Positions(std::vector< std::vector<char> >& PlayerOneBoard, const std::vector< std::vector<char> >& PlayerOneOpponentBoard)
{
    unsigned int CurrentShip = 0;

    while(CurrentShip < 5)
    {
        Display_Game_For_User(PlayerOneBoard, PlayerOneOpponentBoard);
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
                if(!Error_Checking_Ordering_Orientation_On_User_Ship_Positions(PlayerOneBoard, CurrentShipPositions_string, CurrentShipPositions_ints, ShipSize, CurrentShipPositionsOrientation))
                    continue;

                // If ship can't be placed then continue to next iteration
                if (!Can_Ship_Be_Placed(CurrentShipPositionsOrientation, CurrentShipPositions_ints, ShipSize))
                    continue;

                // Place ship on UserBoard using the CurrentShipPositions_ints positions and marking with 'C' for carrier
                Place_Ship(PlayerOneBoard, CurrentShipPositions_ints, 'C');

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
                if(!Error_Checking_Ordering_Orientation_On_User_Ship_Positions(PlayerOneBoard, CurrentShipPositions_string, CurrentShipPositions_ints, ShipSize, CurrentShipPositionsOrientation))
                    continue;

                // If ship can't be placed then continue to next iteration
                if (!Can_Ship_Be_Placed(CurrentShipPositionsOrientation, CurrentShipPositions_ints, ShipSize))
                    continue;

                // Place ship on UserBoard using the CurrentShipPositions_ints positions and marking with 'B' for battleship
                Place_Ship(PlayerOneBoard, CurrentShipPositions_ints, 'B');

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
                if(!Error_Checking_Ordering_Orientation_On_User_Ship_Positions(PlayerOneBoard, CurrentShipPositions_string, CurrentShipPositions_ints, ShipSize, CurrentShipPositionsOrientation))
                    continue;

                // If ship can't be placed then continue to next iteration
                if (!Can_Ship_Be_Placed(CurrentShipPositionsOrientation, CurrentShipPositions_ints, ShipSize))
                    continue;

                // Place ship on UserBoard using the CurrentShipPositions_ints positions and marking with 'D' for destroyer
                Place_Ship(PlayerOneBoard, CurrentShipPositions_ints, 'D');

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
                if(!Error_Checking_Ordering_Orientation_On_User_Ship_Positions(PlayerOneBoard, CurrentShipPositions_string, CurrentShipPositions_ints, ShipSize, CurrentShipPositionsOrientation))
                    continue;

                // If ship can't be placed then continue to next iteration
                if (!Can_Ship_Be_Placed(CurrentShipPositionsOrientation, CurrentShipPositions_ints, ShipSize))
                    continue;

                // Place ship on UserBoard using the CurrentShipPositions_ints positions and marking with 'S' for submarine
                Place_Ship(PlayerOneBoard, CurrentShipPositions_ints, 'S');

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
                if(!Error_Checking_Ordering_Orientation_On_User_Ship_Positions(PlayerOneBoard, CurrentShipPositions_string, CurrentShipPositions_ints, ShipSize, CurrentShipPositionsOrientation))
                    continue;

                // If ship can't be placed then continue to next iteration
                if (!Can_Ship_Be_Placed(CurrentShipPositionsOrientation, CurrentShipPositions_ints, ShipSize))
                    continue;

                // Place ship on UserBoard using the CurrentShipPositions_ints positions and marking with 'P' for patrol boat
                Place_Ship(PlayerOneBoard, CurrentShipPositions_ints, 'P');

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
    
    Display_Game_For_User(PlayerOneBoard, PlayerOneOpponentBoard);
}



void Display_Game_For_User(std::vector< std::vector<char> >& PlayerOneBoard, const std::vector< std::vector<char> >& PlayerOneOpponentBoard)
{
    // ***Better alternative needed***
    // Clears terminal window
    system("clear");
    
    std::cout << "--------------------Battleships By Junaid Afzal--------------------\n" << std::endl;
    
    // First display the opponent's board with hits = '✶', misses = ' ' and empty spots = grid position
    // See Execute_Next_Turn() for why 'x' and 'o' are used instead of 'X' and 'O'
    std::cout << "---Opponent's Board---" << std::endl;
    for (unsigned int i = 0; i < 10; i++)
    {
        for (unsigned int j = 0; j < 10; j++)
        {
            if (PlayerOneOpponentBoard[i][j] == 'x')
                std::cout << std::left << std::setw(3) << "\u2736  ";
            
            else if (PlayerOneOpponentBoard[i][j] == 'o')
                std::cout << std::left << std::setw(3) << " ";
                
            else
                std::cout << std::left << std::setw(3) << (int)PlayerOneOpponentBoard[i][j];
        }
            
        std::cout << "\n";
    }
    
    // Display the user's board with hits = '✶', misses = ' ' and empty spots = '.'
    std::cout << "\n---Your Board---" << std::endl;
    for (unsigned int i = 0; i < 10; i++)
    {
        for (unsigned int j = 0; j < 10; j++)
        {
            if (PlayerOneBoard[i][j] == 'X')
                std::cout << std::left << std::setw(3) << "\u2736  ";
            
            else if (PlayerOneBoard[i][j] == 'O')
                std::cout << std::left << std::setw(3) << " ";
                
            else
                std::cout << std::left << std::setw(3) << PlayerOneBoard[i][j];
        }
        std::cout << "\n";
    }
    
    std::cout << "\n";
}



void Display_Game_For_AIs(std::vector< std::vector<char> >& PlayerOneBoard, std::vector< std::vector<char> >& PlayerTwoBoard)
{
    // ***Better alternative needed***
    // Clears terminal window
    system("clear");
    
    std::cout << "--------------------Battleships By Junaid Afzal--------------------\n" << std::endl;
    
    // Display the user's board with hits = '✶', misses = ' ' and empty spots = '.'
    std::cout << "---Player One Board---" << std::endl;
    for (unsigned int i = 0; i < 10; i++)
    {
        for (unsigned int j = 0; j < 10; j++)
        {
            if (PlayerOneBoard[i][j] == 'X')
                std::cout << std::left << std::setw(3) << "\u2736  ";
            
            else if (PlayerOneBoard[i][j] == 'O')
                std::cout << std::left << std::setw(3) << " ";
                
            else
                std::cout << std::left << std::setw(3) << PlayerOneBoard[i][j];
        }
        std::cout << "\n";
    }
    
    // Display the user's board with hits = '✶', misses = ' ' and empty spots = '.'
    std::cout << "\n---Player Two Board---" << std::endl;
    for (unsigned int i = 0; i < 10; i++)
    {
        for (unsigned int j = 0; j < 10; j++)
        {
            if (PlayerTwoBoard[i][j] == 'X')
                std::cout << std::left << std::setw(3) << "\u2736  ";
            
            else if (PlayerTwoBoard[i][j] == 'O')
                std::cout << std::left << std::setw(3) << " ";
                
            else
                std::cout << std::left << std::setw(3) << PlayerTwoBoard[i][j];
        }
        
        std::cout << "\n";
    }
    
    std::cout << "\n\n";
}



bool Error_Checking_Ordering_Orientation_On_User_Ship_Positions(const std::vector< std::vector<char> >& PlayerOneBoard, std::string& CurrentShipPositions_string, std::vector<int>& CurrentShipPositions_ints, const unsigned int& ShipSize, std::string& CurrentShipPositionsOrientation)
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
        // Row and column number for CurrentShipPositions_ints on the board
        unsigned int Row = CurrentShipPositions_ints[i] / 10;
        unsigned int Column = CurrentShipPositions_ints[i] % 10;
        
        // Check if CurrentShipPositions_ints position is already occupied by another ship
        if (PlayerOneBoard[Row][Column] == 'C' || PlayerOneBoard[Row][Column] == 'B' || PlayerOneBoard[Row][Column] == 'D' || PlayerOneBoard[Row][Column] == 'S' || PlayerOneBoard[Row][Column] == 'P')
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



bool Can_Ship_Be_Placed(const std::string& CurrentShipPositionsOrientation, const std::vector<int>& CurrentShipPositions_ints, const unsigned int& ShipSize)
{
    // Row and column number for CurrentShipPositions_ints on the board
    unsigned int Row = CurrentShipPositions_ints[0] / 10;
    unsigned int Column = CurrentShipPositions_ints[0] % 10;
    
    // A max row number (i) exists, as ship is vertical, which is linked with the size of the ship
    // with the assumption being this value will be the first and smallest of the positions
    if(CurrentShipPositionsOrientation == "Vertical")
    {
        if (Row > (10 - ShipSize))
            return false;
    }

    // A max column number (j) exists, as ship is horizontal, which is linked with the size of the ship
    // with the assumption being this value will be the first and smallest of the positions
    else if(CurrentShipPositionsOrientation == "Horizontal")
    {
        if (Column > (10 - ShipSize))
            return false;
    }
    
    // If test is passed then return true
    return true;
}



void Place_Ship(std::vector< std::vector<char> >& SomeBoard, const std::vector<int>& CurrentShipPositions_ints, const unsigned char& ShipName)
{
    // Go through all CurrentShipPositions_ints positions and overwrite its value with the ship name
    for (unsigned int i = 0; i < CurrentShipPositions_ints.size(); i++)
    {
        // Row and column number for CurrentShipPositions_ints on the board
        unsigned int Row = CurrentShipPositions_ints[i] / 10;
        unsigned int Column = CurrentShipPositions_ints[i] % 10;
        
        SomeBoard[Row][Column] = ShipName;
    }
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
                Get_AI_Ship_Positions(AIBoard, CurrentShipPositionsOrientation, CurrentShipPositions_ints, ShipSize);
                
                // If error checking returns false then continue to next iteration
                if (!Error_Checking_On_AI_Ship_Positions(AIBoard, CurrentShipPositions_ints))
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
                Get_AI_Ship_Positions(AIBoard, CurrentShipPositionsOrientation, CurrentShipPositions_ints, ShipSize);
                
                // If error checking returns false then continue to next iteration
                if (!Error_Checking_On_AI_Ship_Positions(AIBoard, CurrentShipPositions_ints))
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
                Get_AI_Ship_Positions(AIBoard, CurrentShipPositionsOrientation, CurrentShipPositions_ints, ShipSize);
                
                // If error checking returns false then continue to next iteration
                if (!Error_Checking_On_AI_Ship_Positions(AIBoard, CurrentShipPositions_ints))
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
                Get_AI_Ship_Positions(AIBoard, CurrentShipPositionsOrientation, CurrentShipPositions_ints, ShipSize);
                
                // If error checking returns false then continue to next iteration
                if (!Error_Checking_On_AI_Ship_Positions(AIBoard, CurrentShipPositions_ints))
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
                Get_AI_Ship_Positions(AIBoard, CurrentShipPositionsOrientation, CurrentShipPositions_ints, ShipSize);
                
                // If error checking returns false then continue to next iteration
                if (!Error_Checking_On_AI_Ship_Positions(AIBoard, CurrentShipPositions_ints))
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



void Get_AI_Ship_Positions(const std::vector< std::vector<char> >& AIBoard, std::string& CurrentShipPositionsOrientation, std::vector<int>& CurrentShipPositions_ints, const unsigned int& ShipSize)
{
    // Singles represents the column number; Tens the row number; and the FirstValue is the first value of the gird positions when ordered in ascending order
    unsigned int Singles, Tens, FirstValue;
    
    // Use std::rand() to randomly choose between a vertical or horizontal orientation
    if ((std::rand() % 2) == 0)
    {
        CurrentShipPositionsOrientation = "Horizontal";
        
        // A max column number exists, as ship is horizontal, which is linked with the size of the ship
        // with the assumption being this value will be the first and smallest of the positions
        Singles = std::rand() % (11 - ShipSize);
        
        // Any row number allowed as ship is horizontal
        Tens = std::rand() % 10;
        
        // Create the first value and add to the CurrentShipPositions_ints
        FirstValue = Tens*10 + Singles;
        CurrentShipPositions_ints.push_back(FirstValue);
        
        // Horizontal positions have a difference of 1 between positions
        for (unsigned int i = 1; i < ShipSize; i++)
            CurrentShipPositions_ints.push_back(FirstValue+i);
    }
    
    else
    {
        CurrentShipPositionsOrientation = "Vertical";
        
        // Any column number allowed as ship is horizontal
        Singles = std::rand() % 10;
        
        // A max row number exists, as ship is vertical, which is linked with the size of the ship
        // with the assumption being this value will be the first and smallest of the positions
        Tens = std::rand() % (11 - ShipSize);
        
        // Create the first value and add to the CurrentShipPositions_ints
        FirstValue = Tens*10 + Singles;
        CurrentShipPositions_ints.push_back(FirstValue);
        
        // Vertical positions have a difference of AIBoard.size(), which is 10, between positions
        for (unsigned int i = 1; i < ShipSize; i++)
            CurrentShipPositions_ints.push_back(FirstValue+(i*10));
    }
}



bool Error_Checking_On_AI_Ship_Positions(const std::vector< std::vector<char> >& AIBoard, const std::vector<int>& CurrentShipPositions_ints)
{
    // Only check required is if any of the ship positions are already occupied by another ship
    // Cylce through all ship positions
    for (unsigned int i = 0; i < CurrentShipPositions_ints.size(); i++)
    {
        // Row and column number for CurrentShipPositions_ints on the board
        unsigned int Row = CurrentShipPositions_ints[i] / 10;
        unsigned int Column = CurrentShipPositions_ints[i] % 10;
        
        // Check if CurrentShipPositions_ints position is already occupied by another ship
        if (AIBoard[Row][Column] == 'C' || AIBoard[Row][Column] == 'B' || AIBoard[Row][Column] == 'D' || AIBoard[Row][Column] == 'S' || AIBoard[Row][Column] == 'P')
            return false;
    }
    
    // If none of the positions are occupied then return true
    return true;
}



bool Winning_Conditions_Met_For_Player_One_Board(const std::vector< std::vector<char> >& PlayerOneBoard)
{
    // If there are any ship letter on the board then winning condition is not met
    for (unsigned int i = 0; i < 10; i++)
        for (unsigned int j = 0; j < 10; j++)
            if (PlayerOneBoard[i][j] == 'C' || PlayerOneBoard[i][j] == 'B' || PlayerOneBoard[i][j] == 'D' || PlayerOneBoard[i][j] == 'S' || PlayerOneBoard[i][j] == 'P')
                return false;
    
    // Otherwise there are no ships left and winning condtion as been met
    return true;
}



bool Winning_Conditions_Met_For_Player_Two_Board(const std::vector< std::vector<char> >& PlayerTwoBoard)
{
    // If there are any ship letter on the board then winning condition is not met
    for (unsigned int i = 0; i < 10; i++)
        for (unsigned int j = 0; j < 10; j++)
            if (PlayerTwoBoard[i][j] == 'C' || PlayerTwoBoard[i][j] == 'B' || PlayerTwoBoard[i][j] == 'D' || PlayerTwoBoard[i][j] == 'S' || PlayerTwoBoard[i][j] == 'P')
                return false;
    
    // Otherwise there are no ships left and winning condtion as been met
    return true;
}



void Toggle_Player(std::string& CurrentPlayer)
{
    if (CurrentPlayer == "PLAYER_ONE")
          CurrentPlayer = "PLAYER_TWO";
    
    else
        CurrentPlayer = "PLAYER_ONE";
}



int Ask_AI_For_Next_Command(const std::vector< std::vector<char> >& AIOpponentBoard)
{
    bool isValueCorrect = false; // Flag for if input value in invalid
    unsigned int Command = 0;
    
    while (!isValueCorrect)
    {
        // Computer randomly chooses a value from 0 to 99
        Command = std::rand() % 100;
        
        // Row and column number for Command on the board
        unsigned int Row = Command / 10;
        unsigned int Column = Command % 10;
        
        // Check if the position has already been used
        if (AIOpponentBoard[Row][Column] == 'x' || AIOpponentBoard[Row][Column] == 'o')
            continue;
        
        // If all checks passed then value is valid
        else
            isValueCorrect = true;
    }
    
    return Command;
}



void Execute_Next_Turn(std::vector< std::vector<char> >& PlayerOneBoard, std::vector< std::vector<char> >& PlayerOneOpponentBoard, std::vector< std::vector<char> >& PlayerTwoBoard, std::vector< std::vector<char> >& PlayerTwoOpponentBoard, const std::string& CurrentPlayer, const unsigned int& Command)
{
    // Row and column number for Command on the board
    unsigned int Row = Command / 10;
    unsigned int Column = Command % 10;
    
    // Check which use is attacking and therefore is being attacked
    if (CurrentPlayer == "PLAYER_ONE")
    {
        // If it is a ship letter then it is a hit
        if (PlayerTwoBoard[Row][Column] == 'C' || PlayerTwoBoard[Row][Column] == 'B' || PlayerTwoBoard[Row][Column] == 'D' || PlayerTwoBoard[Row][Column] == 'S' || PlayerTwoBoard[Row][Column] == 'P')
        {
            // Update the AI board
            PlayerTwoBoard[Row][Column] = 'X';
            
            // Lower case 'x' is used as it has a value of 120 while upper case 'X' has a value
            // inside the 0-99 range and so conflicts with the grid position labels
            PlayerOneOpponentBoard[Row][Column] = 'x';
        }
                    
        // Otherwise it is a miss
        else
        {
            // Update the AI board
            PlayerTwoBoard[Row][Column] = 'O';
            
            // A lower case 'o' is used as it has a value of 111 while the full stop ',' has a value
            // inside the 0-99 range and so conflicts with the grid position labels
            PlayerOneOpponentBoard[Row][Column] = 'o';
        }
    }
    
    else
    {
        // If it is a ship letter then it is a hit
        if (PlayerOneBoard[Row][Column] == 'C' || PlayerOneBoard[Row][Column] == 'B' || PlayerOneBoard[Row][Column] == 'D' || PlayerOneBoard[Row][Column] == 'S' || PlayerOneBoard[Row][Column] == 'P')
        {
            // Update the User board
            PlayerOneBoard[Row][Column] = 'X';
            
            // Lower case 'x' is used as it has a value of 120 while upper case 'X' has a value
            // inside the 0-99 range and so conflicts with the grid position labels
            PlayerTwoOpponentBoard[Row][Column] = 'x';
        }
        
        // Otherwise it is a miss
        else
        {
            // Update the User board
            PlayerOneBoard[Row][Column] = 'O';
            
            // A lower case 'o' is used as it has a value of 111 while the full stop ',' has a value
            // inside the 0-99 range and so conflicts with the grid position labels
            PlayerTwoOpponentBoard[Row][Column] = 'o';
        }
    }
}



int Ask_User_For_Next_Command(const std::vector< std::vector<char> >& PlayerOneOpponentBoard)
{
    bool isValueCorrect = false; // Flag for if input value in invalid
    unsigned int Command = 0;
    
    while (!isValueCorrect)
    {
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
            continue;
        
        // Row and column number for Command on the board
        unsigned int Row = Command / 10;
        unsigned int Column = Command % 10;
        
        // Check if the position has already been used
        if (PlayerOneOpponentBoard[Row][Column] == 'x' || PlayerOneOpponentBoard[Row][Column] == 'o')
            continue;
        
        // If all checks passed then value is valid
        else
            isValueCorrect = true;
    }
    
    // This is to clear .22222 in a value 5.22222 as value would assume to be 5
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    return Command;
}



void Display_Winning_Message(const std::string& CurrentPlayer, const unsigned int& NumberOfTurns)
{
    // CurrentPlayer is the winner of the game as player toggle as not been triggered since last attack and gamer over check
    if (CurrentPlayer == "PLAYER_ONE")
        std::cout << "Congratulations on Player One for winning!\nOnly took " << NumberOfTurns << " turns" << std::endl;
    
    else
        std::cout << "Congratulations on Player Two for winning!\nOnly took " << NumberOfTurns << " turns" << std::endl;
}
