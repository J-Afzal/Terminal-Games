#pragma once

#include <cstdint>
#include <random>
#include <string>
#include <vector>

#include "games/Game.hpp"
#include "helpers/PageBuilder.hpp"

/**
 * @namespace TerminalGames
 * @brief Contains all Terminal-Games objects.
 */
namespace TerminalGames
{
    /**
     * @class Hangman
     * @brief Implementation of the %Hangman game: https://en.wikipedia.org/wiki/Hangman_(game)
     */
    class Hangman : public Game
    {
    public:
        /**
         * @brief Constructs a new Hangman object.
         *
         * @param p_useAnsiEscapeCodes Whether to use use ANSI escapes codes (true) or only extended ASCII characters (false).
         */
        explicit Hangman(const bool& p_useAnsiEscapeCodes);

    private:
        /**
         * @brief See base class function for details.
         */
        ///@{
        void SetupGame() override;

        void GetUserOptions() override;

        void UpdateGameInfo() override;

        bool IsGameOver() override;

        void ToggleCurrentPlayer() override;

        bool IsCurrentTurnUsers() override;

        /**
         * @brief See base class function for details.
         * @warning This function does not catch any exceptions thrown by `Terminal::GetUserChoiceFromQuitMenus()`.
         */
        void ExecuteUserCommand() override;

        void ExecuteComputerCommand() override;

        /**
         * @brief See base class function for details.
         * @warning This function does not catch any exceptions thrown by `Terminal::GetUserChoiceFromGameOverMenu()`.
         */
        void GameOver() override;

        void RestartGame() override;

        void ResetGame() override;
        ///@}

        /**
         * @brief Prompts the user to select how many players will be playing the game.
         * @warning This function does not catch any exceptions thrown by `Terminal::GetUserChoiceFromGameMenus()`.
         */
        void GetPlayerCount();

        /**
         * @brief Prompts the user to select which player the will be playing the game as (only supported if playing
         * against the computer).
         * @warning This function does not catch any exceptions thrown by `Terminal::GetUserChoiceFromGameMenus()`.
         */
        void GetUserPlayerChoice();

        /**
         * @brief Prompts the user to select how the speed of the computer decision making (this does not affect the difficulty
         * of the computer).
         * @warning This function does not catch any exceptions thrown by `Terminal::GetUserChoiceFromGameMenus()`.
         */
        void GetComputerSpeed();

        /**
         * @brief Prompts the user to enter a word to be guessed (whether the word is actually a word is not checked) when the
         * user is the word setter.
         * @warning This function does not catch any exceptions thrown by `Terminal::GetUserChoiceFromQuitMenus()`.
         */
        void GetWordFromUser();

        /**
         * @brief Gets a random word, from the word list loaded during the setup, when the computer is the word setter.
         */
        void GetWordFromComputer();

        /**
         * @brief Checks the single-letter guess against the word, updates the current guess of the word and the error
         * count depending upon if the guess if correct.
         *
         * @param p_guess A single-letter to check against the word to be guessed.
         */
        void ExecuteGeneralCommand(const char& p_guess);

        /**
         * @brief Used to build pages required by the game.
         */
        PageBuilder m_pageBuilder;

        /**
         * @brief Used to package up the current state of the game so it can be used by m_pageBuilder.
         */
        GameInfo m_gameInfo;

        /**
         * @brief  Used to randomly select the word to be guessed from `Globals::G_HANGMAN_COMPUTER_WORDS` when the computer is
         * the word setter and used to randomly select a letter to guess when the computer is the guesser.
         */
        std::default_random_engine m_randomNumberGenerator;

        /**
         * @brief The letters which remain to be guessed.
         */
        std::vector<char> m_commandsRemaining;

        /**
         * @brief The letters which were guessed by the guesser and are incorrect.
         */
        std::vector<char> m_incorrectGuesses;

        /**
         * @brief The name of the user selected computer speed.
         */
        std::string m_computerSpeedName;

        /**
         * @brief The current guess state of the word to be guessed from the perspective of the guesser.
         */
        std::string m_currentGuessOfWord;

        /**
         * @brief The count of the user selected number of players.
         */
        std::string m_playerCount;

        /**
         * @brief The choice of whether the user has selected to be the guesser or word setter.
         */
        std::string m_userPlayerChoice;

        /**
         * @brief The word to be guessed by the guesser.
         */
        std::string m_wordToBeGuessed;

        /**
         * @brief The computer speed determined by the amount of seconds the computer must wait before executing it's command.
         */
        uint32_t m_computerSpeed;

        /**
         * @brief The number of turns that have occurred.
         */
        uint32_t m_turnCount;

        /**
         * @brief The letter to display to the user to represent what their current selected guess is.
         */
        char m_currentLetterSelected;

        /**
         * @brief Whether the user has selected all the game options (true) or not/partially (false). This is used to determine
         * whether to re-prompt the user to select the game options when restarting the game.
         */
        bool m_hasSavedGameOptions;

        /**
         * @brief Whether the game is over (true) or not (false).
         */
        bool m_isGameOver;

        /**
         * @brief Whether to save the user's currently selected game options (true) and restart the game or not (false) and
         * reset the game back to the initial state which will re-prompt the user for the game options.
         */
        bool m_saveGameOptions;
    };
}
