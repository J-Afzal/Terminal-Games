#pragma once

/**
 * @brief Base class for all games.
 */
class Game
{
public:
    /**
     * @brief The orchestration loop for all games.
     */
    virtual void Play() final
    {
        while (true)
        {
            SetupGame();

            UpdateGameInfo();

            GetUserOptions();

            while (!IsGameOver())
            {
                if (IsCurrentTurnUsers())
                    ExecuteUserCommand();
                else
                    ExecuteAICommand();

                ToggleCurrentPlayer();

                UpdateGameInfo();
            }

            ToggleCurrentPlayer();

            UpdateGameInfo();

            GameOver();
        }
    }

private:
    /**
     * @brief Clears and sets all member variables to their game start default.
     */
    virtual void SetupGame() = 0;

    /**
     * @brief Updates the gameInfo struct (used by the PageBuilder class).
     */
    virtual void UpdateGameInfo() = 0;

    /**
     * @brief Prompt the user for their choice on various game-related options.
     */
    virtual void GetUserOptions() = 0;

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
     * @brief Get a random command from the "AI".
     */
    virtual void ExecuteAICommand() = 0;

    /**
     * @brief Display the game over message and prompt the user whether they would like to play again or quit the game.
     */
    virtual void GameOver() = 0;
};
