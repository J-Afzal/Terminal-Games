/**
 * @file mainmenu.hpp
 * @author Junaid Afzal
 * @brief Main menu functions
 * @version 1.0
 * @date 04-03-2022
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once
#include <string>

namespace MainMenu
{
    /**
     * @brief Main menu loop
     *
     */
    void Run(void);

    /**
     * @brief Gets the main menu ASCII string
     *
     * @param CurrentSelection
     * @return std::string
     */
    std::string Get_Main_Menu(const int &CurrentSelection);

    /**
     * @brief Creates a new line containing text for the main menu box
     *
     * @param Input
     * @return std::string
     */
    std::string New_Line(const std::string &Input);

    /**
     * @brief Creates a new empty line for the main menu box
     *
     * @return std::string
     */
    std::string Empty_Line(void);

    /**
     * @brief Creates a top outline for the main menu box
     *
     * @return std::string
     */
    std::string Top_Line(void);

    /**
     * @brief Creates a bottom outline for the main menu box
     *
     * @return std::string
     */
    std::string Bottom_Line(void);
}
