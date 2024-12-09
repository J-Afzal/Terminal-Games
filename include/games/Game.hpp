#pragma once

#include "helpers/Exceptions.hpp"
#include "helpers/StringBuilder.hpp"
#include "helpers/Terminal.hpp"

/**
 * @brief Base class for all games.
 */
class Game
{
public:
    /**
     * @brief Contains the main game loop.
     */
    virtual void Play() final
    {
        while (true)
        {
            SetupGame();

            while (!IsGameOver())
            {
                if (IsNextTurnUsers())
                    ExecuteUserCommand();
                else
                    ExecuteAICommand();

                ToggleCurrentPlayer();
            }

            GameOver();
        }
    }

private:
    virtual void SetupGame() = 0;

    virtual bool IsGameOver() = 0;

    virtual void ToggleCurrentPlayer() = 0;

    virtual bool IsNextTurnUsers() = 0;

    virtual void ExecuteUserCommand() = 0;

    virtual void ExecuteAICommand() = 0;

    virtual void GameOver() = 0;
};
