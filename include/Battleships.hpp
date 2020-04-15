//
//  The classic Battleships game
//
//  Important Points
//  - 2 players represents two human players which is not coded
//  for as difficult to keep the board information for each user separate.
//  - 1 player represents one human player and one computer player
//  - 0 players represents computer vs computer
//  - The computer is 'dumb' and picks random locations to place ships and random locations to attack ships
//  - system("cls") is used to clear console


#ifndef Battleships_hpp
#define Battleships_hpp

#include <vector>
#include <string>



void Play_Battleships(void);

// Test code uses computer vs computer option
void Test_Battleships(void);

// Setups all the varibales so that game can be played
void Setup_Game(std::vector< std::vector<char> >& PlayerOneBoard,
                std::vector< std::vector<char> >& PlayerOneOpponentBoard,
                std::vector< std::vector<char> >& PlayerTwoBoard,
                std::vector< std::vector<char> >& PlayerTwoOpponentBoard,
                unsigned int& NumberOfPlayers,
                std::string& CurrentPlayer);

int Ask_User_For_Number_Of_Players(void);

// Gets the user to give ships positions for each ship; error checks; and then places ship on the board
void Ask_User_For_Ship_Positions(std::vector< std::vector<char> >& PlayerOneBoard,
                                 const std::vector< std::vector<char> >& PlayerOneOpponentBoard);

// This only displays the boards of the user and the user's perspective of the computers board
// Note that system("cls") is used to clear console
void Display_Game_For_User(std::vector< std::vector<char> >& PlayerOneBoard,
                           const std::vector< std::vector<char> >& PlayerOneOpponentBoard);

// Displays the two computer boards (used when in 0 player mode)
// Note that system("cls") is used to clear console
void Display_Game_For_Computers(std::vector< std::vector<char> >& PlayerOneBoard,
                                std::vector< std::vector<char> >& PlayerTwoBoard);

// Basic error checking on the user ship positions
bool Error_Checking_Ordering_Orientation_On_User_Ship_Positions(const std::vector< std::vector<char> >& PlayerOneBoard,
                                                                std::string& CurrentShipPositions_string,
                                                                std::vector<int>& CurrentShipPositions_ints,
                                                                const unsigned int& ShipSize,
                                                                std::string& CurrentShipPositionsOrientation);

// Checks if the ship positions given by user can be used to place a ship on the board
bool Can_Ship_Be_Placed(const std::string& CurrentShipPositionsOrientation,
                        const std::vector<int>& CurrentShipPositions_ints,
                        const unsigned int& ShipSize);

// Overwrites anyBoard with the ship name at the CurrentShipPositions_ints positions
void Place_Ship(std::vector< std::vector<char> >& anyBoard,
                const std::vector<int>& CurrentShipPositions_ints,
                const unsigned char& ShipName);

// Gets the computer to give ships positions for each ship; error checks; and then places ship on the board
void Ask_Computer_For_Ship_Positions(std::vector< std::vector<char> >& ComputerBoard);

// Prompts computer to generate ship positions
void Get_Computer_Ship_Positions(const std::vector< std::vector<char> >& ComputerBoard,
                                 std::string& CurrentShipPositionsOrientation,
                                 std::vector<int>& CurrentShipPositions_ints,
                                 const unsigned int& ShipSize);

// Checking whether the computer generated ship postions have ships occupying them
bool Error_Checking_On_Computer_Ship_Positions(const std::vector< std::vector<char> >& ComputerBoard,
                                               const std::vector<int>& CurrentShipPositions_ints);

// If there are any ship letter on the either
bool Winning_Conditions_Met(const std::vector< std::vector<char> >& PlayerOneBoard,
                            const std::vector< std::vector<char> >& PlayerTwoBoard);

void Toggle_Player(std::string& CurrentPlayer);

// Asks the user for the grid position to attack
int Ask_User_For_Next_Command(const std::vector< std::vector<char> >& PlayerOneOpponentBoard);

// Asks the computer for the grid position to attack
int Ask_Computer_For_Next_Command(const std::vector< std::vector<char> >& ComputerOpponentBoard);

// Carry out the attack and update the corresponding boards
void Execute_Next_Turn(std::vector< std::vector<char> >& PlayerOneBoard,
                       std::vector< std::vector<char> >& PlayerOneOpponentBoard,
                       std::vector< std::vector<char> >& PlayerTwoBoard,
                       std::vector< std::vector<char> >& PlayerTwoOpponentBoard,
                       const std::string& CurrentPlayer,
                       const unsigned int& Command);

// Displays the winning player and how many turns it took
void Display_Game_Over_Message(const std::string& CurrentPlayer,
                               const unsigned int& NumberOfTurns);

#endif
