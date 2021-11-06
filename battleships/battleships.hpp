//
//  @File: Battleships.hpp
//  @Author: Junaid Afzal
//

#ifndef battleships_hpp
#define battleships_hpp

#include <vector>
#include <string>
#include <map>

// Setups all the variables so that game can be played
void Setup_Game(std::vector<std::vector<std::string>> &PlayerOneBoard,
                std::vector<std::vector<std::string>> &PlayerTwoBoard,
                unsigned int &NumberOfPlayers,
                std::string &CurrentPlayer,
                std::string &AIDifficulty,
                std::vector<unsigned int> &PlayerOneValidMovesRemaining,
                std::vector<unsigned int> &PlayerTwoValidMovesRemaining,
                std::map<std::string, unsigned int> &PlayerOneShipsRemaining,
                std::map<std::string, unsigned int> &PlayerTwoShipsRemaining);

// Gets the user to give ships positions for each ship, error checks, and then places the ships on the board
void Ask_User_For_Ship_Positions(std::vector<std::vector<std::string>> &PlayerOneBoard,
                                 const std::vector<std::vector<std::string>> &PlayerTwoBoard,
                                 const unsigned int &NumberOfPlayers,
                                 const std::string &AIDifficulty,
                                 const std::map<std::string, unsigned int> &PlayerOneShipsRemaining,
                                 const std::map<std::string, unsigned int> &PlayerTwoShipsRemaining);

// This only displays the boards of the user and the user's perspective of the computers board
void Display_Game(const std::vector<std::vector<std::string>> &PlayerOneBoard,
                  const std::vector<std::vector<std::string>> &PlayerTwoBoard,
                  const std::map<std::string, unsigned int> &PlayerOneShipsRemaining,
                  const std::map<std::string, unsigned int> &PlayerTwoShipsRemaining,
                  const std::string &NumberOfPlayers,
                  const std::string &AIDifficulty,
                  const bool &GameOver);

bool Error_Checking_On_User_Ship_Positions(std::vector<std::vector<std::string>> &PlayerOneBoard,
                                                                std::string &Input,
                                                                std::vector<unsigned int> &ShipPositionRows,
                                                                std::vector<unsigned int> &ShipPositionColumns,
                                                                const unsigned int &ShipSize);

// Overwrites anyBoard with the ship name at the CurrentShipPositions_ints positions
void Place_Ship(std::vector<std::vector<std::string>> &anyBoard,
                const std::vector<unsigned int> &ShipPositionRows,
                const std::vector<unsigned int> &ShipPositionColumns,
                const std::string ShipName);

// Gets the computer to give ships positions for each ship, error checks, and then places ship on the board
void Get_Computer_Ship_Positions(std::vector<std::vector<std::string>> &ComputerBoard);

// Prompts computer to generate ship positions
void Generate_Computer_Ship_Positions(std::vector<unsigned int> &ShipPositionRows,
                                      std::vector<unsigned int> &ShipPositionColumns,
                                      const unsigned int &ShipSize);

// Checking whether the computer generated ship postions have ships occupying them
bool Error_Checking_On_Computer_Ship_Positions(const std::vector<std::vector<std::string>> &ComputerBoard,
                                               const std::vector<unsigned int> &ShipPositionRows,
                                               const std::vector<unsigned int> &ShipPositionColumns);

// If there are no ship letters left on either board, then true
bool Winning_Conditions_Met(const std::vector<std::vector<std::string>> &PlayerOneBoard,
                            const std::vector<std::vector<std::string>> &PlayerTwoBoard);

// Asks the user for the grid position to attack
int Ask_User_For_Next_Command(const std::vector<std::vector<std::string>> &PlayerOneBoard,
                              const std::vector<std::vector<std::string>> &PlayerTwoBoard,
                              const unsigned int &NumberOfPlayers,
                              const std::string &AIDifficulty,
                              const std::map<std::string, unsigned int> &PlayerOneShipsRemaining,
                              const std::map<std::string, unsigned int> &PlayerTwoShipsRemaining);

// Asks the computer for the grid position to attack
int Ask_Computer_For_Next_Command(const std::vector<std::vector<std::string>> &PlayerOneBoard,
                                  const std::vector<std::vector<std::string>> &PlayerTwoBoard,
                                  std::vector<unsigned int> &PlayerOneValidMovesRemaining,
                                  std::vector<unsigned int> &PlayerTwoValidMovesRemaining,
                                  const unsigned int &NumberOfPlayers,
                                  const std::string &CurrentPlayer,
                                  const std::string &AIDifficulty,
                                  const std::map<std::string, unsigned int> &PlayerOneShipsRemaining,
                                  const std::map<std::string, unsigned int> &PlayerTwoShipsRemaining);

// Carry out the attack and update the corresponding boards
void Execute_Next_Turn(std::vector<std::vector<std::string>> &PlayerOneBoard,
                       std::vector<std::vector<std::string>> &PlayerTwoBoard,
                       std::map<std::string, unsigned int> &PlayerOneShipsRemaining,
                       std::map<std::string, unsigned int> &PlayerTwoShipsRemaining,
                       const std::string &CurrentPlayer,
                       const unsigned int &Command);

// Displays the winning player and how many turns it took
void Display_Game_Over_Message(const std::string &CurrentPlayer,
                               const unsigned int &NumberOfTurns,
                               bool &GameIsRunning,
                               const std::vector<std::vector<std::string>> &PlayerOneBoard,
                               const std::vector<std::vector<std::string>> &PlayerTwoBoard,
                               const unsigned int &NumberOfPlayers,
                               const std::string &AIDifficulty,
                               const std::map<std::string, unsigned int> &PlayerOneShipsRemaining,
                               const std::map<std::string, unsigned int> &PlayerTwoShipsRemaining);

#endif
