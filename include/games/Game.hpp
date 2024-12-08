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
                ToggleCurrentPlayer();

                if (IsNextTurnUser())
                    ExecuteCommandUser();
                else
                    ExecuteCommandAI();
            }

            Terminal::PrintOutput(GetGameOverMessage());
            if (Terminal::GetNextKeyPress() == 'q')
                throw Exceptions::QuitGame();
        }
    }

protected:
    StringBuilder m_stringBuilder;

private:
    virtual void SetupGame() = 0;

    virtual bool IsGameOver() = 0;

    virtual void ToggleCurrentPlayer() = 0;

    virtual bool IsNextTurnUser() const = 0;

    virtual void ExecuteCommandUser() = 0;

    virtual void ExecuteCommandAI() = 0;

    virtual std::string GetGameOverMessage() const = 0;
};
