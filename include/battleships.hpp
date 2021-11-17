/**
 * @file battleships.hpp
 * @author Junaid Afzal
 * @brief Battleship specific functions
 * @version 1.0
 * @date 07-11-2021
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef battleships_hpp
#define battleships_hpp

#include <vector>
#include <string>
#include <map>
#include <Windows.h>

/**
 * @brief Game loop for Battleships
 *
 * @param ConsoleHandle
 * @param CursorInfo
 */
void Play_Battleships(const HANDLE &ConsoleHandle,
                      CONSOLE_CURSOR_INFO &CursorInfo);

/**
 * @brief The player boards, valid moves, and remaining ships for each player
 * are created. Then the number of players is retrieved - two player are not
 * allowed as impractical to hide player boards from each other while using a
 * single terminal. Then the AI difficulty is retrieved, ship positions are
 * retrieved and the current player is randomly chosen.
 *
 * @param PlayerOneBoard
 * @param PlayerTwoBoard
 * @param PlayerOneValidMovesRemaining
 * @param PlayerTwoValidMovesRemaining
 * @param PlayerOneShipsRemaining
 * @param PlayerTwoShipsRemaining
 * @param NumberOfPlayers
 * @param AIDifficulty
 * @param CurrentPlayer
 * @param ConsoleHandle
 */
void Setup_Game(std::vector<std::vector<std::string>> &PlayerOneBoard,
                std::vector<std::vector<std::string>> &PlayerTwoBoard,
                std::vector<unsigned int> &PlayerOneValidMovesRemaining,
                std::vector<unsigned int> &PlayerTwoValidMovesRemaining,
                std::map<std::string, unsigned int> &PlayerOneShipsRemaining,
                std::map<std::string, unsigned int> &PlayerTwoShipsRemaining,
                unsigned int &NumberOfPlayers,
                std::string &AIDifficulty,
                std::string &CurrentPlayer,
                const HANDLE &ConsoleHandle);

/**
 * @brief Does what what you think
 *
 * @param PlayerOneBoard
 * @param PlayerTwoBoard
 * @param PlayerOneShipsRemaining
 * @param PlayerTwoShipsRemaining
 * @return unsigned int
 */
unsigned int Get_Number_Of_Players(const std::vector<std::vector<std::string>> &PlayerOneBoard,
                                   const std::vector<std::vector<std::string>> &PlayerTwoBoard,
                                   const std::map<std::string, unsigned int> &PlayerOneShipsRemaining,
                                   const std::map<std::string, unsigned int> &PlayerTwoShipsRemaining);

/**
 * @brief Does what what you think
 *
 * @param PlayerOneBoard
 * @param PlayerTwoBoard
 * @param PlayerOneShipsRemaining
 * @param PlayerTwoShipsRemaining
 * @param NumberOfPlayers
 * @return std::string
 */
std::string Get_AI_Difficulty(const std::vector<std::vector<std::string>> &PlayerOneBoard,
                              const std::vector<std::vector<std::string>> &PlayerTwoBoard,
                              const std::map<std::string, unsigned int> &PlayerOneShipsRemaining,
                              const std::map<std::string, unsigned int> &PlayerTwoShipsRemaining,
                              const unsigned int &NumberOfPlayers);

/**
 * @brief The user is prompted to enter sequentially increasing co-ordinates for
 * each ship, and repeatedly if needed, until a valid set of co-ordinates is given.
 * After passing the error checks, each set of co-ordinates is used to place a ship
 * on player one's board (Human player is always player one).
 *
 * @param PlayerOneBoard
 * @param PlayerTwoBoard
 * @param PlayerOneShipsRemaining
 * @param PlayerTwoShipsRemaining
 * @param NumberOfPlayers
 * @param AIDifficulty
 * @param ConsoleHandle
 */
void Get_User_Ship_Positions(std::vector<std::vector<std::string>> &PlayerOneBoard,
                             const std::vector<std::vector<std::string>> &PlayerTwoBoard,
                             const std::map<std::string, unsigned int> &PlayerOneShipsRemaining,
                             const std::map<std::string, unsigned int> &PlayerTwoShipsRemaining,
                             const unsigned int &NumberOfPlayers,
                             const std::string &AIDifficulty,
                             const HANDLE &ConsoleHandle);

/**
 * @brief The input is first capitalised and then separated in to the individual
 * co-ordinates, and checked if the co-ordinates are valid given the current ship,
 * the co-ordinates are then converted to the corresponding rows and columns on
 * the player board, and then checked if a ship is already occupying any of the
 * co-ordinates.
 *
 * @param PlayerOneBoard
 * @param Input
 * @param ShipPositionRows
 * @param ShipPositionColumns
 * @param ShipSize
 * @return true, if all checks passed
 * @return false, if at least one check failed
 */
bool Error_Checking_On_User_Ship_Positions(std::vector<std::vector<std::string>> &PlayerOneBoard,
                                           std::string &Input,
                                           std::vector<unsigned int> &ShipPositionRows,
                                           std::vector<unsigned int> &ShipPositionColumns,
                                           const unsigned int &ShipSize);

/**
 * @brief The AI randomly picks the ship positions, performs error
 * checking on them, and then places them on to the AIBoard
 *
 * @param AIBoard
 */
void Get_AI_Ship_Positions(std::vector<std::vector<std::string>> &AIBoard);

/**
 * @brief The AI randomly picks the ship's orientation, then from that picks one random valid
 * co-ordinate, then generates the remaining co-ordinates.
 *
 * @param ShipPositionRows
 * @param ShipPositionColumns
 * @param ShipSize
 */
void Generate_AI_Ship_Positions(std::vector<unsigned int> &ShipPositionRows,
                                std::vector<unsigned int> &ShipPositionColumns,
                                const unsigned int &ShipSize);

/**
 * @brief Checks whether the ship co-ordinates (rows and columns) have ships
 * already occupying them
 *
 * @param AIBoard
 * @param ShipPositionRows
 * @param ShipPositionColumns
 * @return true, if no ships occupying ship co-ordinates
 * @return false, ships are occupying ship co-ordinates
 */
bool Error_Checking_On_AI_Ship_Positions(const std::vector<std::vector<std::string>> &AIBoard,
                                         const std::vector<unsigned int> &ShipPositionRows,
                                         const std::vector<unsigned int> &ShipPositionColumns);

/**
 * @brief Places ShipName on to anyBoard using the array of rows and columns.
 *
 * @param anyBoard
 * @param ShipPositionRows
 * @param ShipPositionColumns
 * @param ShipName
 */
void Place_Ship(std::vector<std::vector<std::string>> &anyBoard,
                const std::vector<unsigned int> &ShipPositionRows,
                const std::vector<unsigned int> &ShipPositionColumns,
                const std::string ShipName);

/**
 * @brief Both player boards are displayed with the number of players, current AI difficulty,
 * and current state of all ships for both players displayed in between. If there is only one
 * player, then only the hits and misses by player one are displayed on player two's board (as
 * human player is automatically player one).
 *
 * @param PlayerOneBoard
 * @param PlayerTwoBoard
 * @param PlayerOneShipsRemaining
 * @param PlayerTwoShipsRemaining
 * @param NumberOfPlayers
 * @param AIDifficulty
 * @param GameOver
 * @return std::string
 */
std::string Battleships_Game_Display(const std::vector<std::vector<std::string>> &PlayerOneBoard,
                                     const std::vector<std::vector<std::string>> &PlayerTwoBoard,
                                     const std::map<std::string, unsigned int> &PlayerOneShipsRemaining,
                                     const std::map<std::string, unsigned int> &PlayerTwoShipsRemaining,
                                     const std::string &NumberOfPlayers,
                                     const std::string &AIDifficulty,
                                     const bool &GameOver);

/**
 * @brief Creates an empty new line for any of the game boxes
 *
 * @return std::string
 */
std::string Battleships_Empty_Line(void);

/**
 * @brief Creates a new line containing text for any of the game boxes
 *
 * @param Input
 * @return std::string
 */
std::string Battleships_New_Line(const std::string &Input);

/**
 * @brief Creates the top line of any of the game boxes
 *
 * @return std::string
 */
std::string Battleships_Top_Line(void);

/**
 * @brief Creates the bottom line of any of the game boxes
 *
 * @return std::string
 */
std::string Battleships_Bottom_Line(void);

/**
 * @brief Creates the bottom bar which contains the title of the game
 *
 * @return std::string
 */
std::string Battleships_Bottom_Bar(void);

/**
 * @brief Checks if there are any ship letters left on the board
 *
 * @param PlayerOneBoard
 * @param PlayerTwoBoard
 * @return true, if no ship letters left on board
 * @return false, if there are ship letters left on board
 */
bool Winning_Conditions_Met(const std::vector<std::vector<std::string>> &PlayerOneBoard,
                            const std::vector<std::vector<std::string>> &PlayerTwoBoard);

/**
 * @brief The user is prompted for their next command and, if necessary,
 * repeated until a valid command is given
 *
 * @param PlayerOneBoard
 * @param PlayerTwoBoard
 * @param PlayerOneShipsRemaining
 * @param PlayerTwoShipsRemaining
 * @param ValidMovesRemaining
 * @param NumberOfPlayers
 * @param AIDifficulty
 * @param ConsoleHandle
 * @return unsigned int
 */
unsigned int Get_Next_User_Command(const std::vector<std::vector<std::string>> &PlayerOneBoard,
                                   const std::vector<std::vector<std::string>> &PlayerTwoBoard,
                                   const std::map<std::string, unsigned int> &PlayerOneShipsRemaining,
                                   const std::map<std::string, unsigned int> &PlayerTwoShipsRemaining,
                                   std::vector<unsigned int> &ValidMovesRemaining,
                                   const unsigned int &NumberOfPlayers,
                                   const std::string &AIDifficulty,
                                   const HANDLE &ConsoleHandle);

/**
 * @brief If AIDifficulty is set to easy, then a random valid command is chosen.
 *
 * @param PlayerOneBoard
 * @param PlayerTwoBoard
 * @param PlayerOneShipsRemaining
 * @param PlayerTwoShipsRemaining
 * @param PlayerOneValidMovesRemaining
 * @param PlayerTwoValidMovesRemaining
 * @param NumberOfPlayers
 * @param AIDifficulty
 * @param CurrentPlayer
 * @return unsigned int
 */
unsigned int Get_Next_AI_Command(const std::vector<std::vector<std::string>> &PlayerOneBoard,
                                 const std::vector<std::vector<std::string>> &PlayerTwoBoard,
                                 const std::map<std::string, unsigned int> &PlayerOneShipsRemaining,
                                 const std::map<std::string, unsigned int> &PlayerTwoShipsRemaining,
                                 std::vector<unsigned int> &PlayerOneValidMovesRemaining,
                                 std::vector<unsigned int> &PlayerTwoValidMovesRemaining,
                                 const unsigned int &NumberOfPlayers,
                                 const std::string &AIDifficulty,
                                 const std::string &CurrentPlayer);

/**
 * @brief Does what the function name says by updating either player board
 * with Hit or Miss as well as updating how many ships remaining if it was a Hit
 *
 * @param PlayerOneBoard
 * @param PlayerTwoBoard
 * @param PlayerOneShipsRemaining
 * @param PlayerTwoShipsRemaining
 * @param CurrentPlayer
 * @param Command
 */
void Execute_Next_Turn(std::vector<std::vector<std::string>> &PlayerOneBoard,
                       std::vector<std::vector<std::string>> &PlayerTwoBoard,
                       std::map<std::string, unsigned int> &PlayerOneShipsRemaining,
                       std::map<std::string, unsigned int> &PlayerTwoShipsRemaining,
                       const std::string &CurrentPlayer,
                       const unsigned int &Command);

/**
 * @brief First calls Display_Game() once more. The winner is the current player as Toggle_Player()
 * function has not been called since most recent turn and now. This informations is displayed to
 * the user and _getch() is used to get a key press for what the GameIsRunning should be set
 * to (true = play another game and false = quit game).
 *
 * @param PlayerOneBoard
 * @param PlayerTwoBoard
 * @param PlayerOneShipsRemaining
 * @param PlayerTwoShipsRemaining
 * @param NumberOfPlayers
 * @param AIDifficulty
 * @param CurrentPlayer
 * @param NumberOfTurns
 * @param GameIsRunning
 */
void Display_Game_Over_Message(const std::vector<std::vector<std::string>> &PlayerOneBoard,
                               const std::vector<std::vector<std::string>> &PlayerTwoBoard,
                               const std::map<std::string, unsigned int> &PlayerOneShipsRemaining,
                               const std::map<std::string, unsigned int> &PlayerTwoShipsRemaining,
                               const unsigned int &NumberOfPlayers,
                               const std::string &AIDifficulty,
                               const std::string &CurrentPlayer,
                               const unsigned int &NumberOfTurns,
                               bool &GameIsRunning);

#endif
