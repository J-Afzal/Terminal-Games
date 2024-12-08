#pragma once

#include <array>
#include <random>
#include <unordered_map>

#include "Game.hpp"

class Battleships : public Game
{
public:
    /**
     * @brief Construct a new Battleships object.
     *
     * @param outputIsOnlyASCII Whether to use only ASCII characters (true)
     * or also use ANSI escapes codes (false).
     */
    explicit Battleships(const bool& outputIsOnlyASCII);

private:
    std::default_random_engine m_RandomNumberGenerator;
    std::array<std::array<char, 10>, 10> m_BoardOne, m_BoardTwo;
    std::vector<uint32_t> m_MovesRemainingOne, m_MovesRemainingTwo;
    std::unordered_map<char, uint32_t> m_ShipsRemainingOne, m_ShipsRemainingTwo;
    std::string m_NumberOfPlayers, m_AISpeedName, m_CurrentPlayer;
    uint32_t m_NumberOfTurns, m_PreviousCommand, m_AISpeed, m_AICommand;
    bool m_GameOver;

    void SetupGame() override;

    void GetPlayerCount();

    void GetAISpeed();

    void GetUserShipPositions();

    void GetAIShipPositions(std::array<std::array<char, 10>, 10>& AIBoard);

    bool IsGameOver() override;

    void ToggleCurrentPlayer() override;

    bool IsNextTurnUser() const override;

    void ExecuteCommandUser() override;

    void ExecuteCommandAI() override;

    void ExecuteCommand(
        std::array<std::array<char, 10>, 10>& OpponentBoard,
        std::unordered_map<char, uint32_t>& OpponentShipsRemaining,
        std::vector<uint32_t>& MovesRemaining,
        const uint32_t& AICommand
    );

    std::string GetGameOverMessage() const override;

    std::string GetGameDisplay() const;
};
