/**
 * @file game.hpp
 * @author Junaid Afzal
 * @brief Templated play function
 * @version 1.0
 * @date 08-03-2022
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once
#include <random>

/**
 * @brief Abstract game object in which all sub objects
 * contain same play function and must override the
 * pure virtual functions
 *
 */
class Game
{
public:
    virtual bool Setup_Game() = 0;

    virtual bool Game_Over() = 0;

    virtual void Toggle_Current_Player() = 0;

    virtual bool Next_Turn_Is_User() = 0;

    virtual bool Execute_Next_User_Command() = 0;

    virtual void Execute_Next_AI_Command() = 0;

    virtual bool Display_Game_Over_Message() = 0;

    /**
     * @brief Basic game loop for all games
     *
     */
    void Play()
    {
        while (true)
        {
            if (Setup_Game()) // if true, quit to main menu
                return;

            while (!Game_Over())
            {
                Toggle_Current_Player();

                if (Next_Turn_Is_User())
                {
                    if (Execute_Next_User_Command()) // if true, quit to main menu
                        return;
                }
                else
                    Execute_Next_AI_Command();
            }

            if (Display_Game_Over_Message()) // if true, quit to main menu
                return;
        }
    }

    std::default_random_engine m_RandomNumberGenerator;
};
