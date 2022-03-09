/**
 * @file play.hpp
 * @author Junaid Afzal
 * @brief Templated play function
 * @version 1.0
 * @date 08-03-2022
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

/**
 * @brief Basic game object in which all
 * sub objects contain same play function
 *
 */
class Game
{
public:
    Game(){};

    ~Game(){};

    virtual bool Setup_Game(void) { return true; };

    virtual bool Game_Over(void) { return true; };

    virtual void Toggle_Current_Player(void){};

    virtual bool Next_Turn_Is_User(void) { return true; };

    virtual bool Execute_Next_User_Command(void) { return true; };

    virtual void Execute_Next_AI_Command(void){};

    virtual bool Display_Game_Over_Message(void) { return true; }

    /**
     * @brief Basic game loop for all games
     *
     */
    void Play(void)
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
};
