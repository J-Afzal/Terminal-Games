/**
 * @file Quit.hpp
 * @author Junaid Afzal
 * @brief Custom exception to return to the main menu
 * @version 1.0
 * @date 29-03-2022
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

class Quit : public std::exception
{
    const char* what() const noexcept override
    {
        return "User requested to quit to the main menu";
    }
};
