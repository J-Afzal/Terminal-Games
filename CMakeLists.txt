cmake_minimum_required( VERSION 3.20.4 )

PROJECT( Terminal-Games )

include_directories( include )

add_executable(Terminal-Games
        source/main.cpp
        include/pch.hpp
        include/Terminal.hpp
        source/Terminal.cpp
        include/MainMenu.hpp
        source/MainMenu.cpp
        include/Game.hpp
        include/QuitToMainMenu.hpp
        include/TicTacToe.hpp
        source/TicTacToe.cpp
        include/Hangman.hpp
        source/Hangman.cpp
        include/Battleships.hpp
        source/Battleships.cpp)
