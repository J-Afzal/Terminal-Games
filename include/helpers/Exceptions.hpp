#pragma once

#include <thread>

namespace Exceptions
{
    /**
     * @brief Used to quit a game and the program.
     */
    class Quit : public std::exception {};
}
