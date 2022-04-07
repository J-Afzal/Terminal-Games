/**
 * @file StringBuilder.hpp
 * @author Junaid Afzal
 * @brief This class allows for automated creation of repetitive ASCII
 * strings which are needed for displaying the game
 * @version 1.0
 * @date 04-04-2022
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once
#include "pch.hpp"

class StringBuilder
{
public:
    StringBuilder() = default;

    ~StringBuilder() = default;

    void Set(const int &GameWidth, const std::string &TopTitle, const std::string &BottomTitle);

    std::string New_Line(const std::string &Input, const std::string &Colour="WHITE") const;

    std::string New_Line_Centered(const std::string &Input, const std::string &Colour="WHITE") const;

    std::string New_Line_Left_Justified(const std::string &Input, const std::string &Colour="WHITE") const;

    std::string Empty_Line() const;

    std::string Top_Line() const;

    std::string Bottom_Line() const;

    std::string Top_Box() const;

    std::string Bottom_Box() const;

private:
    int m_GameWidth{};
    std::string m_TopTitle, m_BottomTitle;
    const std::string m_WHITE = "\x1B[1;37m", m_RED = "\x1B[1;31m", m_BLUE = "\x1B[1;34m", m_RESET = "\x1B[0m"; // ANSI escape codes for bold text colours

    /**
     * Example of what each function automates:
     *
     * ╔═════════════════════════════════════════════════════╗   <- Top_Line()             <-
     * ║                     Tic Tac Toe                     ║   <- New_Line_Centered()    <- Top_Box()
     * ╚═════════════════════════════════════════════════════╝   <- Bottom_Line()          <-
     * ╔═════════════════════════════════════════════════════╗   <- Top_Line()
     * ║  O │ O │ X                                          ║
     * ║ ───┼───┼───      # of Players = 0                   ║
     * ║  O │ X │ O                                          ║
     * ║ ───┼───┼───     AI Difficulty = EASY                ║   <- New_Line()
     * ║  O │ X │ X                                          ║
     * ║                                                     ║   <- Empty_Line()
     * ║                      GAME OVER                      ║   <- New_Line_Centered()
     * ║                                                     ║
     * ║     Player O has won! The game lasted 9 turns.      ║
     * ║                                                     ║
     * ║     Press 'Q' to quit OR Enter to play again...     ║
     * ╚═════════════════════════════════════════════════════╝   <- Bottom_Line()
     * ╔═════════════════════════════════════════════════════╗   <- Top_Line()             <-
     * ║                q = quit to main menu                ║   <- New_Line_Centered()    <- Bottom_Box()
     * ╚═════════════════════════════════════════════════════╝   <- Bottom_Line()          <-
     *
     * ^-----------------------------------------------------^
     *                      = Game_Width
     *
     * In this example m_TopTitle = "Tic Tac Toe" and m_BottomTitle = "q = quit to main menu"
     */
};
