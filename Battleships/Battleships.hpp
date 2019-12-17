//
//  Battleships.hpp
//  Battleships
//
//  Created by Main on 17/12/2019.
//  Copyright © 2019 Junaid Afzal. All rights reserved.
//

#ifndef Battleships_hpp
#define Battleships_hpp

#include <vector>



void Setup_Game(std::vector< std::vector<int> >& AIBoard, std::vector< std::vector<int> >& UserBoardAsSeenFromAI, std::vector< std::vector<int> >& UserBoard, std::vector< std::vector<int> >& AIBoardAsSeenFromUser, std::string& CurrentPlayer);

void Ask_AI_For_Battleship_Positions(std::vector< std::vector<int> >& AIBoard);

void Ask_User_For_Battleship_Positions(std::vector< std::vector<int> >& UserBoard);



#endif /* Battleships_hpp */
