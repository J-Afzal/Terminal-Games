CMAKE_MINIMUM_REQUIRED(VERSION 3.20)

PROJECT(Terminal-Games)

SET(CMAKE_CXX_STANDARD 20)
SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Executable names used by the CI/CD workflows
IF(APPLE)
    SET(executable_name "terminal-games-macos-latest")
ENDIF()

IF(UNIX AND NOT APPLE)
    SET(executable_name "terminal-games-ubuntu-latest")
ENDIF()

IF(WIN32)
    SET(executable_name "terminal-games-windows-latest")
ENDIF()

ADD_EXECUTABLE(
    ${executable_name}
    ${CMAKE_CURRENT_SOURCE_DIR}/source/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/helpers/MainMenu.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/helpers/PageBuilder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/helpers/Terminal.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/games/TicTacToe.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/games/Hangman.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/games/Battleships.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/resources/icons/terminal-games.rc
)
