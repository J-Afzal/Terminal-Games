#pragma once

#include "helpers/Globals.hpp"

/**
 * @namespace TerminalGames
 * @brief Contains all Terminal-Games objects.
 */
namespace TerminalGames
{
    /**
     * @class Game
     * @brief Base class for all games.
     */
    class Game
    {
    public:
        /**
         * @brief Constructs a new Game object.
         */
        Game() = default;

        /**
         * @brief Destructs the Game object.
         */
        virtual ~Game() = default;

        /**
         * @brief Disable constructing a new Game object using copy constructor.
         *
         * @param p_game The game to copy.
         */
        Game(const Game& p_game) = delete;

        /**
         * @brief Disable constructing a new Game object using move constructor.
         *
         * @param p_game The game to copy.
         */
        Game(const Game&& p_game) = delete;

        /**
         * @brief Disable constructing a new Game object using copy assignment operator.
         *
         * @param p_game The game to copy.
         */
        Game& operator=(const Game& p_game) = delete;

        /**
         * @brief Disable constructing a new Game object using move assignment operator.
         *
         * @param p_game The game to copy.
         */
        Game& operator=(const Game&& p_game) = delete;

        /**
         * @brief The main orchestration loop for all games.
         */
        virtual void Play() final
        {
            ResetGame();

            while (true)
            {
                try
                {
                    SetupGame();

                    GetUserOptions();

                    UpdateGameInfo();

                    while (!IsGameOver())
                    {
                        if (IsCurrentTurnUsers())
                        {
                            ExecuteUserCommand();
                        }

                        else
                        {
                            ExecuteComputerCommand();
                        }

                        ToggleCurrentPlayer();

                        UpdateGameInfo();
                    }

                    ToggleCurrentPlayer();

                    UpdateGameInfo();

                    GameOver();
                }

                catch (Globals::Exceptions::RestartGame& e)
                {
                    RestartGame();
                }

                catch (Globals::Exceptions::ResetGame& e)
                {
                    ResetGame();
                }
            }
        }

    private:
        /**
         * @brief Clears and sets all member variables to their game start default.
         */
        virtual void SetupGame() = 0;

        /**
         * @brief Prompt the user for their choice on various game-related options.
         */
        virtual void GetUserOptions() = 0;

        /**
         * @brief Updates GameInfo to match the current state of the game.
         */
        virtual void UpdateGameInfo() = 0;

        /**
         * @brief Check whether the game is over.
         */
        virtual bool IsGameOver() = 0;

        /**
         * @brief Change the current player to the other player.
         */
        virtual void ToggleCurrentPlayer() = 0;

        /**
         * @brief Check whether the current turn should be executed by the user.
         */
        virtual bool IsCurrentTurnUsers() = 0;

        /**
         * @brief Prompt the user to enter their command for the current turn.
         */
        virtual void ExecuteUserCommand() = 0;

        /**
         * @brief Get a random command from the computer.
         */
        virtual void ExecuteComputerCommand() = 0;

        /**
         * @brief Display the game over message and prompt the user whether they would like to play again or quit the game.
         */
        virtual void GameOver() = 0;

        /**
         * @brief Update variables to allow for the game to be restarted with the same user options.
         */
        virtual void RestartGame() = 0;

        /**
         * @brief Update variables to allow for the game to be reset and so the user will be asked for new options.
         */
        virtual void ResetGame() = 0;
    };
}
