#pragma once

#include <string>

/**
 * @brief Colours representing ANSI escape codes.
 */
enum class Colours
{
    WHITE,
    RED,
    BLUE
};

/**
 * @brief Construct output strings to print to the terminal. See below for a visual example of what each function abstracts away:
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
 *                    = displayWidth = 53
 *
 * In this example:
 *      m_topTitle = "Tic Tac Toe"
 *      m_bottomTitle = "q = quit to main menu"
 *      m_displayWidth = 53
 */
class StringBuilder
{
public:
    /**
     * @brief Construct a new StringBuilder object.
     */
    explicit StringBuilder() = default;

    /**
     * @brief Construct a new StringBuilder object.
     *
     * @param topTitle The text to display within the top box.
     * @param bottomTitle The text to display within the bottom box.
     * @param displayWidth The width of the output to display.
     * @param outputIsOnlyASCII Whether to use only ASCII characters (true)
     * or also use ANSI escapes codes (false).
     */
    explicit StringBuilder(const std::string& topTitle, const std::string& bottomTitle, const uint32_t& displayWidth, const bool& outputIsOnlyASCII);

    /**
     * @brief Set the properties of the object
     *
     * @param topTitle The text to display within the top box.
     * @param bottomTitle The text to display within the bottom box.
     * @param displayWidth The width of the output to display.
     * @param outputIsOnlyASCII Whether to use only ASCII characters (true)
     * or also use ANSI escapes codes (false).
     */
    void SetProperties(const std::string& topTitle, const std::string& bottomTitle, const uint32_t& displayWidth, const bool& outputIsOnlyASCII);

    /**
     * @brief Creates a new line on a page with input text contained within the line.
     *
     * @param input The text to display on the line.
     * @param colour The colour of the input text.
     * @return std::string A new line with the input text contained within it.
     * @warning There is no length check on input to confirm that it is not longer than the width of the page.
     */
    std::string AddNewLine(const std::string& input, const Colours& colour = Colours::WHITE) const;

    /**
     * @brief Same as AddNewLine but the input text is automatically centered. If the spacing on the 
     * sides is unequal, then the left side will always have the higher amount of spacing.
     *
     * @param input The text to display on the new line.
     * @param colour The colour of the input text.
     * @return std::string A new line with the input text centered
     * @warning There is no length check on input to confirm that it is not longer than the width of the page.
     */
    std::string AddNewLineCentred(const std::string& input, const Colours& colour = Colours::WHITE) const;

    /**
     * @brief Same as AddNewLine but the input text is automatically left justified (with one space 
     * padding on to the left page edge).
     *
     * @param input The text to display on the new line.
     * @param colour The colour of the input text.
     * @return std::string A new line with the input text left justified.
     * @warning There is no length check on input to confirm that it is not longer than the width of the page.
     */
    std::string AddNewLineLeftJustified(const std::string& input, const Colours& colour = Colours::WHITE) const;

    /**
     * @brief Same as AddNewLine but with no input text.
     *
     * @return std::string A new line with no input text.
     */
    std::string AddEmptyLine() const;

    /**
     * @brief Creates the top line of a box within a page.
     *
     * @return std::string The top line of a box.
     */
    std::string AddTopLine() const;

    /**
     * @brief Creates the bottom line of a box within a page.
     *
     * @return std::string The bottom line of a box.
     */
    std::string AddBottomLine() const;

    /**
     * @brief Creates the top box display acts as the title bar for a page.
     *
     * @return std::string The top box with the m_topTitle as the title.
     */
    std::string AddTopBox() const;

    /**
     * @brief Creates the bottom box acts as general info for a page.
     *
     * @return std::string The bottom box with the m_bottomTitle as the general info.
     */
    std::string AddBottomBox() const;

private:
    std::string m_WHITE = "\x1B[1;37m", m_RED = "\x1B[1;31m", m_BLUE = "\x1B[1;34m", m_RESET = "\x1B[0m"; // ANSI escape codes
    std::string m_topTitle, m_bottomTitle;
    uint32_t m_displayWidth;
};
