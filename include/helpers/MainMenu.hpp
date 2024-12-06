/**
 * @file MainMenu.hpp
 * @author Junaid Afzal
 * @brief This class contains the outer main menu while loop. It uses m_Terminal for terminal IO and to
 * get the m_CurrentSelection. This is then used to display the correct output string from m_Menus and to
 * select the correct game to play from m_Games. Polymorphism is used to contain all games in the m_Games
 * array and the inherited Play() function is used to being the selected game.
 * @version 1.0
 * @date 04-03-2022
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <array>
#include <vector>

#include "games/Game.hpp"

class MainMenu
{
public:
    /**
     * @brief Construct a new Main Menu object
     * @param ASCIIOnly determines whether to use ANSI escapes codes (false)
     * or just ASCII characters (true)
     */
    explicit MainMenu(const bool &ASCIIOnly = false);

    ~MainMenu() = default;

    /**
     * @brief Kick off the MainMenu orchestration while loop
     */
    void Run();

private:
    std::array<std::unique_ptr<Game>, 3> m_Games;
    std::vector<std::string> m_Menus;
    int m_CurrentSelection;
    Terminal m_Terminal;
};
