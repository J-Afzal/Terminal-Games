#pragma once

#include <cstdint>
#include <random>
#include <string>
#include <vector>

#include "Game.hpp"
#include "helpers/PageBuilder.hpp"

class Hangman : public Game
{
public:
    /**
     * @brief Construct a new Hangman object.
     *
     * @param outputIsOnlyASCII Whether to use only ASCII characters (true) or to also use ANSI escapes codes (false).
     */
    explicit Hangman(const bool& outputIsOnlyASCII);

private:
    PageBuilder m_pageBuilder;
    GameInfo m_gameInfo;
    std::default_random_engine m_randomNumberGenerator;
    std::vector<std::string> m_words;
    std::vector<char> m_movesRemaining, m_incorrectGuesses;
    std::string m_wordToBeGuessed, m_currentGuessOfWord, m_playerCount, m_AISpeedName;
    uint32_t m_turnCount, m_errorCount, m_AISpeed;
    char m_AICommand;
    bool m_hasWinner, m_userIsGuesser;

    /**
     * @brief See base class function for details.
     */
    void SetupGame() override;

    /**
     * @brief Loads in the words.txt file containing a list of the ~1,000 most used words in English (3-14 characters)
     * which will be used by the AI when selecting a word.
     */
    void LoadWords();

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
     * @brief Prompts the user to select which player the will be playing the game as (only supported if playing
     * against the AI).
     */
    void GetUserPlayerChoice();

    /**
     * @brief Prompts the user to select how the speed of AI decision making (this does not affect the difficulty of
     * the AI).
     */
    void GetAISpeed();

    /**
     * @brief Prompts the user to enter a 3-14 character word (whether the word is actually a word is not checked) when
     * the user is the word setter.
     *
     */
    void GetWordFromUser();

    /**
     * @brief Gets a random word, from the word list loaded during the setup, when the AI is the word setter.
     *
     */
    void GetWordFromAI();

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
     * @brief Checks the single-letter guess against the word and updates the current guess of the word and the error
     * count depending upon if the guess if correct.
     *
     * @param guess A single-letter to check.
     */
    void CheckGuessAndUpdateCurrentGuess(const char& guess);

    /**
     * @brief See base class function for details.
     */
    void GameOver() override;
};
