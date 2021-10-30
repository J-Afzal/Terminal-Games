//
//  @File: Battleships.hpp
//  @Author: Junaid Afzal
//

#ifndef Battleships_hpp
#define Battleships_hpp

#include <vector>
#include <string>

// Setups all the variables so that game can be played
void Setup_Game(std::vector<std::vector<std::string>> &PlayerOneBoard,
                std::vector<std::vector<std::string>> &PlayerOneOpponentBoard,
                std::vector<std::vector<std::string>> &PlayerTwoBoard,
                std::vector<std::vector<std::string>> &PlayerTwoOpponentBoard,
                unsigned int &NumberOfPlayers,
                std::string &CurrentPlayer);

int Ask_User_For_Number_Of_Players(void);

// Gets the user to give ships positions for each ship, error checks, and then places the ships on the board
void Ask_User_For_Ship_Positions(std::vector<std::vector<std::string>> &PlayerOneBoard,
                                 const std::vector<std::vector<std::string>> &PlayerOneOpponentBoard);

// This only displays the boards of the user and the user's perspective of the computers board
void Display_Game_For_User(const std::vector<std::vector<std::string>> &PlayerOneBoard,
                           const std::vector<std::vector<std::string>> &PlayerOneOpponentBoard);

// Windows API method taken from https://www.cplusplus.com/articles/4z18T05o
void Clear_Terminal(void);

// Displays the two computer boards (used when in 0 player mode)
void Display_Game_For_Computers(const std::vector<std::vector<std::string>> &PlayerOneBoard,
                                const std::vector<std::vector<std::string>> &PlayerTwoBoard);

bool Error_Checking_Ordering_Orientation_On_User_Ship_Positions(std::vector<std::vector<std::string>> &PlayerOneBoard,
                                                                std::string &CurrentShipPositions_string,
                                                                std::vector<int> &CurrentShipPositions_ints,
                                                                const unsigned int &ShipSize,
                                                                std::string &CurrentShipPositionsOrientation);

bool Can_Ship_Be_Placed(const std::string &CurrentShipPositionsOrientation,
                        const std::vector<int> &CurrentShipPositions_ints,
                        const unsigned int &ShipSize);

// Overwrites anyBoard with the ship name at the CurrentShipPositions_ints positions
void Place_Ship(std::vector<std::vector<std::string>> &anyBoard,
                const std::vector<int> &CurrentShipPositions_ints,
                const std::string ShipName);

// Gets the computer to give ships positions for each ship, error checks, and then places ship on the board
void Ask_Computer_For_Ship_Positions(std::vector<std::vector<std::string>> &ComputerBoard);

// Prompts computer to generate ship positions
void Get_Computer_Ship_Positions(std::string &CurrentShipPositionsOrientation,
                                 std::vector<int> &CurrentShipPositions_ints,
                                 const unsigned int &ShipSize);

// Checking whether the computer generated ship postions have ships occupying them
bool Error_Checking_On_Computer_Ship_Positions(const std::vector<std::vector<std::string>> &ComputerBoard,
                                               const std::vector<int> &CurrentShipPositions_ints);

// If there are no ship letters left on either board, then true
bool Winning_Conditions_Met(const std::vector<std::vector<std::string>> &PlayerOneBoard,
                            const std::vector<std::vector<std::string>> &PlayerTwoBoard);

void Toggle_Player(std::string &CurrentPlayer);

// Asks the user for the grid position to attack
int Ask_User_For_Next_Command(const std::vector<std::vector<std::string>> &PlayerOneBoard,
                              const std::vector<std::vector<std::string>> &PlayerOneOpponentBoard);

// Asks the computer for the grid position to attack
int Ask_Computer_For_Next_Command(const std::vector<std::vector<std::string>> &ComputerOpponentBoard);

// Carry out the attack and update the corresponding boards
void Execute_Next_Turn(std::vector<std::vector<std::string>> &PlayerOneBoard,
                       std::vector<std::vector<std::string>> &PlayerOneOpponentBoard,
                       std::vector<std::vector<std::string>> &PlayerTwoBoard,
                       std::vector<std::vector<std::string>> &PlayerTwoOpponentBoard,
                       const std::string &CurrentPlayer,
                       const unsigned int &Command);

// Displays the winning player and how many turns it took
void Display_Game_Over_Message(const std::string &CurrentPlayer,
                               const unsigned int &NumberOfTurns,
                               bool &GameIsRunning);

#endif
