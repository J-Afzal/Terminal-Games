cmake_minimum_required( VERSION 3.20.4 )

PROJECT( Terminal-Games )

include_directories( include )

add_executable(Terminal-Games           source/main.cpp
               include/terminal.hpp     source/terminal.cpp
               include/mainmenu.hpp     source/mainmenu.cpp
               include/tictactoe.hpp    source/tictactoe.cpp
               include/hangman.hpp      source/hangman.cpp
               include/battleships.hpp  source/battleships.cpp)
