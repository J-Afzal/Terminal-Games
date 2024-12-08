/**
 * @file StringBuilder.hpp
 * @author Junaid Afzal
 * @brief This class abstracts away the creation of repetitive ASCII strings
 * @version 1.0
 * @date 04-04-2022
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <string>

enum class Colours { WHITE, RED, BLUE };

class StringBuilder
{
public:
    explicit StringBuilder() = default;

    explicit StringBuilder(const std::string& topTitle, const std::string& bottomTitle, const uint32_t& gameWidth, const bool& outputIsOnlyASCII);

    void SetProperties(const std::string& topTitle, const std::string& bottomTitle, const uint32_t& gameWidth, const bool& outputIsOnlyASCII);

    std::string AddNewLine(const std::string& input, const Colours& colour = Colours::WHITE) const;

    std::string AddNewLineCentred(const std::string& input, const Colours& colour = Colours::WHITE) const;

    std::string AddNewLineLeftJustified(const std::string& input, const Colours& colour = Colours::WHITE) const;

    std::string AddEmptyLine() const;

    std::string AddTopLine() const;

    std::string AddBottomLine() const;

    std::string AddTopBox() const;

    std::string AddBottomBox() const;

    /**
     * @brief See below for a visual example of what each function abstracts away:
     *
     * ╔═════════════════════════════════════════════════════╗   <- AddTopLine()                        <-
     * ║                     Tic Tac Toe                     ║   <- AddNewLineCentred("Tic Tac Toe")    <- AddTopBox()
     * ╚═════════════════════════════════════════════════════╝   <- AddBottomLine()                     <-
     * ╔═════════════════════════════════════════════════════╗   <- AddTopLine()
     * ║  O │ O │ X                                          ║
     * ║ ───┼───┼───      # of Players = 0                   ║
     * ║  O │ X │ O                                          ║
     * ║ ───┼───┼───     AI Difficulty = EASY                ║   <- AddNewLineLeftJustified(" ───┼───┼───     AI Difficulty = EASY")
     * ║  O │ X │ X                                          ║
     * ║                                                     ║   <- AddEmptyLine()
     * ║                      GAME OVER                      ║   <- AddNewLineCentred("GAME OVER")
     * ║                                                     ║
     * ║     Player O has won! The game lasted 9 turns.      ║   <- AddNewLine("     Player O has won! The game lasted 9 turns.      ")
     * ║                                                     ║
     * ║     Press 'Q' to quit OR Enter to play again...     ║
     * ╚═════════════════════════════════════════════════════╝   <- AddBottomLine()
     * ╔═════════════════════════════════════════════════════╗   <- AddTopLine()                                  <-
     * ║                q = quit to main menu                ║   <- AddNewLineCentred("q = quit to main menu")    <- AddBottomBox()
     * ╚═════════════════════════════════════════════════════╝   <- AddBottomLine()                               <-
     *
     *  ^---------------------------------------------------^
     *                    = GameWidth = 53
     *
     * In this example:
     *      m_topTitle = "Tic Tac Toe"
     *      m_bottomTitle = "q = quit to main menu"
     *      m_gameWidth = 53
     *
     */
        
private:
    std::string m_WHITE = "\x1B[1;37m", m_RED = "\x1B[1;31m", m_BLUE = "\x1B[1;34m", m_RESET = "\x1B[0m"; // ANSI escape codes
    std::string m_topTitle, m_bottomTitle;
    uint32_t m_gameWidth;
};
