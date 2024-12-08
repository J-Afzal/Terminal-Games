#pragma once

#include <random>

#include "Game.hpp"

class Hangman : public Game
{
public:
    /**
     * @brief Construct a new Hangman object.
     *
     * @param outputIsOnlyASCII Whether to use only ASCII characters (true)
     * or also use ANSI escapes codes (false).
     */
    explicit Hangman(const bool& outputIsOnlyASCII);

private:
    std::default_random_engine m_randomNumberGenerator;
    std::vector<std::string> m_words;
    std::vector<char> m_movesRemaining, m_incorrectGuesses;
    std::string m_wordToBeGuessed, m_currentGuessOfWord, m_PlayerCount, m_speedNameAI;
    uint32_t m_turnCount, m_errorCount, m_speedAI;
    char m_commandAI;
    bool m_hasWinner, m_userIsGuesser;

    void SetupGame() override;

    void LoadWords();

    void GetPlayerCount();

    void GetPlayerChoiceFromUser();

    void GetAISpeed();

    void GetWordFromUser();

    void GetWordFromAI();

    bool IsGameOver() override;

    void ToggleCurrentPlayer() override;

    bool IsNextTurnUser() const override;

    void ExecuteCommandUser() override;

    void ExecuteCommandAI() override;

    void CheckGuessAndUpdateCurrentGuess(const char& Guess);

    std::string GetGameOverMessage() const override;

    std::string GetGameDisplay() const;
};
