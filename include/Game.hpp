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
#include "Terminal.hpp"
#include "Quit.hpp"

class Game
{
public:
    virtual ~Game() = default;

    /**
     * @brief Basic game loop for all games. The game quits by user entering 'q', which
     * throws an exception, and is caught by MainMenu::Run() while loop
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

    template<typename T>
    static T Get_User_Option_Choice(const std::vector<std::string> &OptionMenus, const std::vector<T> &Options)
    {
        unsigned int KeyPress, CurrentSelection = 0;
        while (true)
        {
            Terminal::Output_To_Terminal(OptionMenus[CurrentSelection]);

            KeyPress = Terminal::Get_Key_Pressed();

            if (KeyPress == '\r')
                return Options[CurrentSelection];
            else if (KeyPress == 72) // up arrow key
                CurrentSelection == 0 ? CurrentSelection = (int)(OptionMenus.size() - 1) : --CurrentSelection;
            else if (KeyPress == 80) // down arrow key
                CurrentSelection == (OptionMenus.size() - 1) ? CurrentSelection = 0 : ++CurrentSelection;
            else if (KeyPress == 'q')
                throw Quit();
        }
    }

protected:
    Terminal m_Terminal;
    std::default_random_engine m_RandomNumberGenerator;
    std::string m_AIDifficulty, m_NumberOfPlayers;
    int m_NumberOfTurns;

    virtual void Setup_Game() = 0;

    virtual bool Game_Over() = 0;

    virtual void Toggle_Current_Player() = 0;

    virtual bool Next_Turn_Is_User() = 0;

    virtual void Execute_Next_User_Command() = 0;

    virtual void Execute_Next_AI_Command() = 0;

    virtual void Display_Game_Over_Message() = 0;
};
