#pragma once

#include <array>
#include <cstdint>
#include <random>
#include <string>
#include <unordered_map>
#include <vector>

#include "Game.hpp"
#include "helpers/PageBuilder.hpp"

class Battleships : public Game
{
public:
    /**
     * @brief Construct a new Battleships object.
     *
     * @param outputIsOnlyASCII Whether to use only ASCII characters (true) or to also use ANSI escapes codes (false).
     */
    explicit Battleships(const bool& outputIsOnlyASCII);

private:
    PageBuilder m_pageBuilder;
    GameInfo m_gameInfo;
    std::default_random_engine m_randomNumberGenerator;
    std::array<std::array<char, 10>, 10> m_boardOne, m_boardTwo;
    std::vector<uint32_t> m_movesRemainingOne, m_movesRemainingTwo;
    std::unordered_map<char, uint32_t> m_shipsRemainingOne, m_shipsRemainingTwo;
    std::string m_playerCount, m_AISpeedName, m_currentPlayer;
    uint32_t m_turnCount, m_previousCommand, m_AISpeed, m_AICommand;
    bool m_isGameOver;

    /**
     * @brief See base class function for details.
     */
    void SetupGame() override;

    /**
     * @brief See base class function for details.
     */
    void UpdateGameInfo() override;

    /**
     * @brief See base class function for details.
     */
    void GetUserOptions() override;

    /**
     * @brief Prompts the user to select how many players will be playing the game.
     */
    void GetPlayerCount();

    /**
     * @brief Prompts the user to select how the speed of AI decision making (this does not affect the difficulty of
     * the AI).
     */
    void GetAISpeed();

    /**
     * @brief Prompt the user to place all ships on the board.
     */
    void GetUserShipPositions();

    /**
     * @brief Randomly place all ships on the board.
     */
    void GetAIShipPositions(std::array<std::array<char, 10>, 10>& AIBoard);

    /**
     * @brief See base class function for details.
     */
    bool IsGameOver() override;

    /**
     * @brief See base class function for details.
     */
    void ToggleCurrentPlayer() override;

    /**
     * @brief See base class function for details.
     */
    bool IsCurrentTurnUsers() override;

    /**
     * @brief See base class function for details.
     */
    void ExecuteUserCommand() override;

    /**
     * @brief See base class function for details.
     */
    void ExecuteAICommand() override;

    /**
     * @brief Executes the command on the opponent's board and updates their own board.
     *
     * @param opponentBoard The board containing the opponent's ship positions.
     * @param opponentShipsRemaining The number of squares remaining for each opponent ship.
     * @param commandsRemaining List of board spaces that remain un-attacked.
     * @param command The board space that should be attacked.
     */
    void ExecuteCommand(
        std::array<std::array<char, 10>, 10>& opponentBoard,
        std::unordered_map<char, uint32_t>& opponentShipsRemaining,
        std::vector<uint32_t>& commandsRemaining,
        const uint32_t& command);

    /**
     * @brief See base class function for details.
     */
    void GameOver() override;
};
