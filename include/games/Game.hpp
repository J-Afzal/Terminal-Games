/**
 * @file Game.hpp
 * @author Junaid Afzal
 * @brief The base class for all game object with it's sole purpose being to allow for
 * runtime polymorphism in the MainMenu::Run() function using the pure virtual Play() function
 * @version 1.0
 * @date 08-03-2022
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once
#include "pch.hpp"
#include "helpers/Exceptions.hpp"
#include "helpers/Terminal.hpp"

class Game
{
public:
    virtual ~Game() = default;

    virtual void Play() final
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

            Terminal::Output_To_Terminal(Get_Game_Over_Message());
            if (Terminal::Get_Key_Pressed() == 'q')
                throw Exceptions::Quit();
        }
    }

private:
    virtual void Setup_Game() = 0;

    virtual bool Game_Over() = 0;

    virtual void Toggle_Current_Player() = 0;

    virtual bool Next_Turn_Is_User() = 0;

    virtual void Execute_Next_User_Command() = 0;

    virtual void Execute_Next_AI_Command() = 0;

    virtual std::string Get_Game_Over_Message() = 0;
};
