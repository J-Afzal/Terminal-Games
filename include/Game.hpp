/**
 * @file Game.hpp
 * @author Junaid Afzal
 * @brief Templated play function
 * @version 1.0
 * @date 08-03-2022
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once
#include "pch.hpp"

/**
 * @brief Abstract game object in which all sub objects
 * contain same play function and must override the
 * pure virtual functions
 *
 */
class Game
{
public:
    virtual ~Game() = default;

    virtual void Setup_Game() = 0;

    virtual bool Game_Over() = 0;

    virtual void Toggle_Current_Player() = 0;

    virtual bool Next_Turn_Is_User() = 0;

    virtual void Execute_Next_User_Command() = 0;

    virtual void Execute_Next_AI_Command() = 0;

    virtual void Display_Game_Over_Message() = 0;

    /**
     * @brief Basic game loop for all games. The game quits by user entering 'q', which
     * throws an exception, and is caught by MainMenu::Run() while loop
     *
     */
    void Play()
    {

        while (true)
        {
            Setup_Game();

            while (!Game_Over())
            {
                Toggle_Current_Player();

                if (Next_Turn_Is_User())
                    Execute_Next_User_Command();
                else
                    Execute_Next_AI_Command();
            }

            Display_Game_Over_Message();
        }
    }
};
