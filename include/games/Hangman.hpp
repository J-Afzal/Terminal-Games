#pragma once

#include <cstdint>
#include <random>
#include <string>
#include <vector>

#include "games/Game.hpp"
#include "helpers/PageBuilder.hpp"

namespace TerminalGames
{
    class Hangman : public Game
    {
    public:
        /**
         * @brief Construct a new Hangman object.
         *
         * @param p_onlyUseAscii Whether to use only ASCII characters (true) or to also use ANSI escapes codes (false).
         */
        explicit Hangman(const bool& p_onlyUseAscii);

    private:
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
        void ExecuteComputerCommand() override;

        /**
         * @brief See base class function for details.
         */
        void GameOver() override;

        /**
         * @brief Prompts the user to select how many players will be playing the game.
         */
        void GetPlayerCount();

        /**
         * @brief Prompts the user to select which player the will be playing the game as (only supported if playing
         * against the computer).
         */
        void GetUserPlayerChoice();

        /**
         * @brief Prompts the user to select how the speed of the computer decision making (this does not affect the difficulty
         * of the computer).
         */
        void GetComputerSpeed();

        /**
         * @brief Prompts the user to enter a 3-14 character word (whether the word is actually a word is not checked) when
         * the user is the word setter.
         *
         */
        void GetWordFromUser();

        /**
         * @brief Gets a random word, from the word list loaded during the setup, when the computer is the word setter.
         *
         */
        void GetWordFromComputer();

        /**
         * @brief Checks the single-letter guess against the word, updates the current guess of the word and the error
         * count depending upon if the guess if correct.
         *
         * @param p_guess A single-letter to check.
         */
        void ExecuteGeneralCommand(const char& p_guess);

        PageBuilder m_pageBuilder;
        GameInfo m_gameInfo;
        std::default_random_engine m_randomNumberGenerator;
        std::vector<char> m_commandsRemaining;
        std::vector<char> m_incorrectGuesses;
        std::string m_computerSpeedName;
        std::string m_currentGuessOfWord;
        std::string m_playerCount;
        std::string m_wordToBeGuessed;
        uint32_t m_computerSpeed;
        uint32_t m_errorCount;
        uint32_t m_turnCount;
        bool m_hasWinner;
        bool m_userIsGuesser;
    };
}
