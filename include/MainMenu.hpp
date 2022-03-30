/**
 * @file MainMenu.hpp
 * @author Junaid Afzal
 * @brief Main menu functions
 * @version 1.0
 * @date 04-03-2022
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once
#include "Terminal.hpp"
#include "Game.hpp"

namespace MainMenu
{
    void Run();

    void Setup(Terminal &Terminal, std::vector<std::string> &OptionMenus, std::vector<int> &Options, std::array<std::unique_ptr<Game>, 3> &Games);
}
