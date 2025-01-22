CMAKE_MINIMUM_REQUIRED(VERSION 3.20)

PROJECT(Terminal-Games)

SET(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Executable names used by the CI/CD workflows
IF(CI_CD)
    IF(APPLE)
        SET(executable_name "terminal-games-macos-latest")
    ELSEIF(UNIX AND NOT APPLE)
        SET(executable_name "terminal-games-ubuntu-latest")
    ELSEIF(WIN32)
        SET(executable_name "terminal-games-windows-latest")
    ELSE()
        SET(executable_name "terminal-games")
    ENDIF()
ELSE()
    SET(executable_name "terminal-games")
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
    ${CMAKE_CURRENT_SOURCE_DIR}/resources/icons/TerminalGames.rc
)
