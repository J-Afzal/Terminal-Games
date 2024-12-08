#pragma once

#include <array>
#include <random>

#include "Game.hpp"

class TicTacToe : public Game
{
public:
    /**
     * @brief Construct a new Tic Tac Toe object.
     *
     * @param outputIsOnlyASCII Whether to use only ASCII characters (true)
     * or also use ANSI escapes codes (false).
     */
    explicit TicTacToe(const bool& outputIsOnlyASCII);

private:
    std::default_random_engine m_randomNumberGenerator;
    std::array<std::array<char, 3>, 3> m_gameGrid;
    std::vector<uint32_t> m_movesRemaining;
    std::string m_playerCount, m_speedNameAI;
    uint32_t m_turnCount, m_speedAI, m_commandAI;
    char m_currentPlayer, m_playerChoiceUser;
    bool m_hasWinner;

    void SetupGame() override;

    void GetPlayerCount();

    void GetPlayerChoiceFromUser();

    void GetAISpeed();

    bool IsGameOver() override;

    void ToggleCurrentPlayer() override;

    bool IsNextTurnUser() const override;

    void ExecuteCommandUser() override;

    void ExecuteCommandAI() override;

    std::string GetGameOverMessage() const override;

    std::string GetGameDisplay() const;
};
