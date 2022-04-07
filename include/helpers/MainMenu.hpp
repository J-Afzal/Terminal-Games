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
#include "pch.hpp"
#include "games/Game.hpp"

namespace MainMenu
{
    void Run();

    void Setup(std::vector<std::string> &Menus, std::array<std::unique_ptr<Game>, 3> &Games);
}
