cmake_minimum_required( VERSION 3.20.4 )

PROJECT( Terminal-Games )

include_directories( include )

add_executable(Terminal-Games
        source/main.cpp
        include/pch.hpp
        include/helpers/MainMenu.hpp
        source/helpers/MainMenu.cpp
        include/exceptions/Quit.hpp
        include/helpers/StringBuilder.hpp
        source/helpers/StringBuilder.cpp
        include/helpers/Terminal.hpp
        source/helpers/Terminal.cpp
        include/games/Game.hpp
        include/games/TicTacToe.hpp
        source/games/TicTacToe.cpp
        include/games/Hangman.hpp
        source/games/Hangman.cpp
        include/games/Battleships.hpp
        source/games/Battleships.cpp)
