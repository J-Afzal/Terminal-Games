/**
 * @file game.hpp
 * @author Junaid Afzal
 * @brief Templated game functions
 * @version 1.0
 * @date 08-03-2022
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once
#include <array>

/**
 * @brief Templated game loop
 *
 * @tparam T
 * @param GameObject
 */
template <class T>
void Play(T &GameObject)
{
    while (true)
    {
        if (GameObject.Setup_Game()) // if true, quit to main menu
            return;

        while (!GameObject.Game_Over())
        {
            GameObject.Toggle_Current_Player();

            if (GameObject.Next_Turn_Is_User())
            {
                if (GameObject.Execute_Next_User_Command()) // if true, quit to main menu
                    return;
            }
            else
                GameObject.Execute_Next_AI_Command();
        }

        if (GameObject.Display_Game_Over_Message()) // if true, quit to main menu
            return;
    }
}
