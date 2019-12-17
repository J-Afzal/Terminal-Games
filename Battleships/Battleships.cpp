//
//  Battleships.cpp
//  Battleships
//
//  Created by Main on 17/12/2019.
//  Copyright © 2019 Junaid Afzal. All rights reserved.
//

#include "Battleships.hpp"
#include <iostream>



void Setup_Game(std::vector< std::vector<int> >& AIBoard, std::vector< std::vector<int> >& UserBoardAsSeenFromAI, std::vector< std::vector<int> >& UserBoard, std::vector< std::vector<int> >& AIBoardAsSeenFromUser, std::string& CurrentPlayer)
{
    std::cout << "--------------------Battleships V1.0 By Junaid Afzal--------------------" << std::endl;
    
    for (unsigned int i = 0, CurrentPosition = 0; i < 10; i++)
    {
        std::vector<int> Row;
        
        AIBoard.push_back(Row);
        UserBoardAsSeenFromAI.push_back(Row);
        UserBoard.push_back(Row);
        AIBoardAsSeenFromUser.push_back(Row);
        
        for (unsigned int j = 0; j < 10; j++, CurrentPosition++)
        {
            AIBoard[i].push_back(CurrentPosition);
            UserBoardAsSeenFromAI[i].push_back(CurrentPosition);
            UserBoard[i].push_back(CurrentPosition);
            AIBoardAsSeenFromUser[i].push_back(CurrentPosition);
        }
    }
    
    
    Ask_AI_For_Battleship_Positions(AIBoard);
    
    Ask_User_For_Battleship_Positions(UserBoard);
    
    
    std::srand(std::time(0));
    
    if ((std::rand() % 2) == 0)
        CurrentPlayer = "USER";
    else
        CurrentPlayer = "AI";
}



void Ask_AI_For_Battleship_Positions(std::vector< std::vector<int> >& AIBoard)
{
    std::cout << "Not coded ai" << std::endl;
    
    
    
}



void Ask_User_For_Battleship_Positions(std::vector< std::vector<int> >& UserBoard)
{
    //Display_Game();
         
    int CurrentShip = 0; // 1 - 5
    std::string CurrentShipPositions;
    
    
    while(CurrentShip < 5)
    {
        bool ExitSwitchStatement = false;
        
        switch (CurrentShip)
        {
            case 0:
            {
                std::cout << "Enter the 5 grid locations for the Carrier of size 5 ";
                
                std::getline(std::cin, CurrentShipPositions);
                
                if (std::cin.fail()) // Check if cin failed
                {
                    // Clear buffer and retry
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    continue;
                }
                
                //check for just numbers
                for (int i = 0; i < CurrentShipPositions.size(); i++)
                {
                    if (CurrentShipPositions[i] < 48 && CurrentShipPositions[i] != 32)
                    {
                        // Clear buffer and retry
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        ExitSwitchStatement = true;
                        break;
                    }

                    if (CurrentShipPositions[i] > 57)
                    {
                        // Clear buffer and retry
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        ExitSwitchStatement = true;
                        break;
                    }
                }
                
                if (ExitSwitchStatement)
                    continue;
                
                if(CurrentShipPositions.back() != ' ')
                    CurrentShipPositions.push_back(' ');
                
                //read in numbers
                std::vector<int> Positions;
                std::string Temp;
                for (int i = 0; i < CurrentShipPositions.size(); i++)
                {
                    if (CurrentShipPositions[i] != ' ')
                        Temp.push_back(CurrentShipPositions[i]);
                    
                    else if (Temp.size() == 0)
                        continue;
                        
                    else
                    {
                        Positions.push_back(std::stoi(Temp, nullptr, 10));
                        Temp.clear();
                    }
                }
                
                //check for just 5 nunbers
                if (Positions.size() > 5)
                    continue;
                
                //check for duplicates
                
                
                //check if numbers exist
                
                
                //check if number already in use
                
                std::cout << "next command" << std::endl;
                
                
                
                //CurrentShip++;
                break;
            }
                
                
                
            case 1:
            {
                std::cout << "Enter the 4 grid locations for the Battleship of size 4 ";
                
                std::cin >> CurrentShipPositions;
                
                
                CurrentShip++;
                break;
            }
                
                
            
            case 2:
            {
                std::cout << "Enter the 3 grid locations for the Destroyer of size 3 ";
                    
                std::cin >> CurrentShipPositions;
                    
                    
                CurrentShip++;
                break;
            }
                
                
                
            case 3:
            {
                std::cout << "Enter the 3 grid locations for the Submarine of size 3 ";
                
                std::cin >> CurrentShipPositions;
                
                
                CurrentShip++;
                break;
            }
            
                
                
            case 4:
            {
                std::cout << "Enter the 2 grid locations for the Patrol Boat of size 2 ";
                
                std::cin >> CurrentShipPositions;
                
                
                CurrentShip++;
                break;
            }
            
                
                
            default:
                std::cout << "Ask_User_For_Battleship_Positions() switch statement error" << std::endl;
                break;
        }
        
        std::cout << "End of while loop" << std::endl;
    }
     
//    // The for loops add the appropriate ammount of rows and columns to the grid and the
//    // the appropriate grid value
//    for (unsigned int i = 0, GridNumber = 0; i < SizeOfGrid; i++)
//    {
//        std::vector<int> Rows;
//        GameData.push_back(Rows);
//
//        for (int j = 0; j < SizeOfGrid; j++, GridNumber++)
//            GameData[i].push_back(GridNumber);
//    }
//
//    // This is to clear .22222 in a value 5.22222 as value would assume to be 5
//    std::cin.clear();
//    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
