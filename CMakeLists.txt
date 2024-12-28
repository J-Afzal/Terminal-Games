cmake_minimum_required(VERSION 3.20)

project(Terminal-Games)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(terminal-games
    ${CMAKE_CURRENT_SOURCE_DIR}/source/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/helpers/MainMenu.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/helpers/PageBuilder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/helpers/Terminal.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/games/TicTacToe.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/games/Hangman.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/games/Battleships.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/resources/icons/terminal-games.rc
)
