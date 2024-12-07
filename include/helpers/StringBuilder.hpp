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
    StringBuilder() = default;

    StringBuilder(const bool& ASCIIOnly, const uint32_t& GameWidth, const std::string& TopTitle, const std::string& BottomTitle);

    ~StringBuilder() = default;

    void Set(const bool& ASCIIOnly, const uint32_t& GameWidth, const std::string& TopTitle, const std::string& BottomTitle);

    /**
     * @brief See below for a visual example of what each function abstracts away:
     *
     * ╔═════════════════════════════════════════════════════╗   <- Top_Line()                          <-
     * ║                     Tic Tac Toe                     ║   <- New_Line_Centred("Tic Tac Toe")    <- Top_Box()
     * ╚═════════════════════════════════════════════════════╝   <- Bottom_Line()                       <-
     * ╔═════════════════════════════════════════════════════╗   <- Top_Line()
     * ║  O │ O │ X                                          ║
     * ║ ───┼───┼───      # of Players = 0                   ║
     * ║  O │ X │ O                                          ║
     * ║ ───┼───┼───     AI Difficulty = EASY                ║   <- New_Line_Left_Justified(" ───┼───┼───     AI Difficulty = EASY")
     * ║  O │ X │ X                                          ║
     * ║                                                     ║   <- Empty_Line()
     * ║                      GAME OVER                      ║   <- New_Line_Centred("GAME OVER")
     * ║                                                     ║
     * ║     Player O has won! The game lasted 9 turns.      ║   <- New_Line("     Player O has won! The game lasted 9 turns.      ")
     * ║                                                     ║
     * ║     Press 'Q' to quit OR Enter to play again...     ║
     * ╚═════════════════════════════════════════════════════╝   <- Bottom_Line()
     * ╔═════════════════════════════════════════════════════╗   <- Top_Line()                                    <-
     * ║                q = quit to main menu                ║   <- New_Line_Centred("q = quit to main menu")    <- Bottom_Box()
     * ╚═════════════════════════════════════════════════════╝   <- Bottom_Line()                                 <-
     *
     *  ^---------------------------------------------------^
     *                    = GameWidth = 53
     *
     * In this example:
     *      m_TopTitle = "Tic Tac Toe"
     *      m_BottomTitle = "q = quit to main menu"
     *      m_GameWidth = 53
     *
     */

    std::string New_Line(const std::string& Input, const Colours& Colour = Colours::WHITE) const;

    std::string New_Line_Centred(const std::string& Input, const Colours& Colour = Colours::WHITE) const;

    std::string New_Line_Left_Justified(const std::string& Input, const Colours& Colour = Colours::WHITE) const;

    std::string Empty_Line() const;

    std::string Top_Line() const;

    std::string Bottom_Line() const;

    std::string Top_Box() const;

    std::string Bottom_Box() const;

private:
    std::string m_TopTitle, m_BottomTitle;
    std::string m_WHITE = "\x1B[1;37m", m_RED = "\x1B[1;31m", m_BLUE = "\x1B[1;34m", m_RESET = "\x1B[0m"; // ANSI escape codes
    uint32_t m_GameWidth;
};
