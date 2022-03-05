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

#pragma once
#include <vector>
#include <string>
#include <map>
#include <Windows.h>

namespace Battleships
{
    /**
     * @brief Game loop for Battleships
     *
     * @param ConsoleHandle
     * @param CursorInfo
     */
    void Play(const HANDLE &ConsoleHandle,
              CONSOLE_CURSOR_INFO &CursorInfo);

    /**
     * @brief The player boards, valid moves, and remaining ships for each player
     * are created. Then the number of players is retrieved - two player are not
     * allowed as impractical to hide player boards from each other while using a
     * single terminal. Then the AI difficulty and ship positions are retrieved,
     * and the current player is randomly chosen.
     *
     * @param BoardOne
     * @param BoardTwo
     * @param ShipsRemainingOne
     * @param ShipsRemainingTwo
     * @param MovesRemainingOne
     * @param MovesRemainingTwo
     * @param CurrentPlayer
     * @param AIDifficulty
     * @param NumberOfPlayers
     * @param ConsoleHandle
     * @param CursorInfo
     * @param QuitToMainMenu
     */
    void Setup_Game(std::vector<std::vector<char>> &BoardOne,
                    std::vector<std::vector<char>> &BoardTwo,
                    std::map<char, int> &ShipsRemainingOne,
                    std::map<char, int> &ShipsRemainingTwo,
                    std::vector<int> &MovesRemainingOne,
                    std::vector<int> &MovesRemainingTwo,
                    std::string &CurrentPlayer,
                    std::string &AIDifficulty,
                    int &NumberOfPlayers,
                    const HANDLE &ConsoleHandle,
                    CONSOLE_CURSOR_INFO &CursorInfo,
                    bool &QuitToMainMenu);

    /**
     * @brief
     *
     * @param BoardOne
     * @param BoardTwo
     * @param ShipsRemainingOne
     * @param ShipsRemainingTwo
     * @param QuitToMainMenu
     * @return int
     */
    int Get_Number_Of_Players(const std::vector<std::vector<char>> &BoardOne,
                              const std::vector<std::vector<char>> &BoardTwo,
                              const std::map<char, int> &ShipsRemainingOne,
                              const std::map<char, int> &ShipsRemainingTwo,
                              bool &QuitToMainMenu);

    /**
     * @brief
     *
     * @param BoardOne
     * @param BoardTwo
     * @param ShipsRemainingOne
     * @param ShipsRemainingTwo
     * @param NumberOfPlayers
     * @param QuitToMainMenu
     * @return std::string
     */
    std::string Get_AI_Difficulty(const std::vector<std::vector<char>> &BoardOne,
                                  const std::vector<std::vector<char>> &BoardTwo,
                                  const std::map<char, int> &ShipsRemainingOne,
                                  const std::map<char, int> &ShipsRemainingTwo,
                                  const int &NumberOfPlayers,
                                  bool &QuitToMainMenu);

    /**
     * @brief The user is prompted to enter sequentially increasing/decreasing co-ordinates
     * for each ship, and repeatedly if needed, until a valid set of co-ordinates are given.
     * After passing the error checks, each set of co-ordinates is used to place a ship
     * on player one's board (Human player is always player one).
     *
     * @param BoardOne
     * @param BoardTwo
     * @param ShipsRemainingOne
     * @param ShipsRemainingTwo
     * @param AIDifficulty
     * @param NumberOfPlayers
     * @param ConsoleHandle
     * @param CursorInfo
     * @param QuitToMainMenu
     */
    void Get_User_Ship_Positions(std::vector<std::vector<char>> &BoardOne,
                                 const std::vector<std::vector<char>> &BoardTwo,
                                 const std::map<char, int> &ShipsRemainingOne,
                                 const std::map<char, int> &ShipsRemainingTwo,
                                 const std::string &AIDifficulty,
                                 const int &NumberOfPlayers,
                                 const HANDLE &ConsoleHandle,
                                 CONSOLE_CURSOR_INFO &CursorInfo,
                                 bool &QuitToMainMenu);

    /**
     * @brief The AI randomly picks the ship positions, performs error
     * checking on them, and then places them on to the AIBoard
     *
     * @param AIBoard
     */
    void Get_AI_Ship_Positions(std::vector<std::vector<char>> &AIBoard);

    /**
     * @brief Both player boards are displayed, whilst the number of players, current AI difficulty,
     * and current state of all ships for both players are displayed in between. If there is only one
     * player, then only the hits and misses by player one are displayed on player two's board (as
     * human player is automatically player one).
     *
     * @param BoardOne
     * @param BoardTwo
     * @param ShipsRemainingOne
     * @param ShipsRemainingTwo
     * @param AIDifficulty
     * @param NumberOfPlayers
     * @param GameOver
     * @return std::string
     */
    std::string Get_Game_Display(const std::vector<std::vector<char>> &BoardOne,
                                 const std::vector<std::vector<char>> &BoardTwo,
                                 const std::map<char, int> &ShipsRemainingOne,
                                 const std::map<char, int> &ShipsRemainingTwo,
                                 const std::string &AIDifficulty,
                                 const std::string &NumberOfPlayers,
                                 const bool &GameOver);

    /**
     * @brief Creates a new line containing text for Battleships
     *
     * @param Input
     * @return std::string
     */
    std::string New_Line(const std::string &Input);

    /**
     * @brief Creates an empty new line for Battleships
     *
     * @return std::string
     */
    std::string Empty_Line(void);

    /**
     * @brief Creates the top line for Battleships
     *
     * @return std::string
     */
    std::string Top_Line(void);

    /**
     * @brief Creates the bottom line for Battleships
     *
     * @return std::string
     */
    std::string Bottom_Line(void);

    /**
     * @brief Creates the bottom bar for Battleships
     *
     * @return std::string
     */
    std::string Bottom_Bar(void);

    /**
     * @brief Checks if there are any ship letters left on the board
     *
     * @param BoardOne
     * @param BoardTwo
     * @return true, if no ship letters left on board
     * @return false, if there are ship letters left on board
     */
    bool Winning_Conditions_Met(const std::vector<std::vector<char>> &BoardOne,
                                const std::vector<std::vector<char>> &BoardTwo);

    /**
     * @brief The user is prompted for their next command and, if necessary,
     * repeated until a valid command is given
     *
     * @param BoardOne
     * @param BoardTwo
     * @param ShipsRemainingOne
     * @param ShipsRemainingTwo
     * @param MovesRemainingOne
     * @param CurrentPlayer
     * @param AIDifficulty
     * @param NumberOfPlayers
     * @param previousCommand
     * @param ConsoleHandle
     * @param CursorInfo
     * @param QuitToMainMenu
     */
    void Get_Next_User_Command(std::vector<std::vector<char>> &BoardOne,
                               std::vector<std::vector<char>> &BoardTwo,
                               std::map<char, int> &ShipsRemainingOne,
                               std::map<char, int> &ShipsRemainingTwo,
                               std::vector<int> &MovesRemainingOne,
                               const std::string &CurrentPlayer,
                               const std::string &AIDifficulty,
                               const int &NumberOfPlayers,
                               int &previousCommand,
                               const HANDLE &ConsoleHandle,
                               CONSOLE_CURSOR_INFO &CursorInfo,
                               bool &QuitToMainMenu);

    /**
     * @brief If AIDifficulty is set to easy, then a random valid command is chosen.
     *
     * @param BoardOne
     * @param BoardTwo
     * @param ShipsRemainingOne
     * @param ShipsRemainingTwo
     * @param MovesRemainingOne
     * @param MovesRemainingTwo
     * @param CurrentPlayer
     * @param AIDifficulty
     * @param NumberOfPlayers
     */
    void Get_Next_AI_Command(std::vector<std::vector<char>> &BoardOne,
                             std::vector<std::vector<char>> &BoardTwo,
                             std::map<char, int> &ShipsRemainingOne,
                             std::map<char, int> &ShipsRemainingTwo,
                             std::vector<int> &MovesRemainingOne,
                             std::vector<int> &MovesRemainingTwo,
                             const std::string &CurrentPlayer,
                             const std::string &AIDifficulty,
                             const int &NumberOfPlayers);

    /**
     * @brief Updates either player board with a hit or a miss as
     * well as updating how many ships remaining if it was a Hit.
     *
     * @param BoardOne
     * @param BoardTwo
     * @param ShipsRemainingOne
     * @param ShipsRemainingTwo
     * @param CurrentPlayer
     * @param Command
     */
    void Execute_Next_Turn(std::vector<std::vector<char>> &BoardOne,
                           std::vector<std::vector<char>> &BoardTwo,
                           std::map<char, int> &ShipsRemainingOne,
                           std::map<char, int> &ShipsRemainingTwo,
                           const std::string &CurrentPlayer,
                           const int &Command);

    /**
     * @brief The winner is the current player as player has not been toggled since
     * most recent turn and now. This informations is displayed to the user.
     *
     * @param BoardOne
     * @param BoardTwo
     * @param ShipsRemainingOne
     * @param ShipsRemainingTwo
     * @param CurrentPlayer
     * @param AIDifficulty
     * @param NumberOfPlayers
     * @param NumberOfTurns
     * @param GameIsRunning
     */
    void Display_Game_Over_Message(const std::vector<std::vector<char>> &BoardOne,
                                   const std::vector<std::vector<char>> &BoardTwo,
                                   const std::map<char, int> &ShipsRemainingOne,
                                   const std::map<char, int> &ShipsRemainingTwo,
                                   const std::string &CurrentPlayer,
                                   const std::string &AIDifficulty,
                                   const int &NumberOfPlayers,
                                   const int &NumberOfTurns,
                                   bool &GameIsRunning);
}
