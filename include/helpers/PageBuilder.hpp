#pragma once

#include <array>
#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

#include "helpers/Constants.hpp"

namespace TerminalGames
{
    /**
     * @brief Pages representing the pages that PageBuilder supports.
     */
    enum class Pages : std::uint8_t
    {
        DEFAULT,
        HOMEPAGE,
        MAINMENU,
        TICTACTOE,
        HANGMAN,
        BATTLESHIPS,
    };

    /**
     * @brief Colours representing ANSI escape codes.
     */
    enum class Colours : std::uint8_t
    {
        WHITE,
        RED,
        BLUE,
        GREEN,
        YELLOW,
    };

    /**
     * @brief Used by game objects to package up their current state into a format that can be used by PageBuilder.
     */
    struct GameInfo
    {
        struct TicTacToeGameInfo
        {
            std::array<std::array<std::string, G_TICTACTOE_BOARD_WIDTH>, G_TICTACTOE_BOARD_HEIGHT> m_gameGrid;
            std::string m_computerSpeedName;
            std::string m_currentPlayer;
            std::string m_playerCount;
            uint32_t m_turnCount;
            bool m_hasWinner;
        } m_ticTacToeGameInfo;

        struct HangmanGameInfo
        {
            std::vector<char> m_incorrectGuesses;
            std::string m_computerSpeedName;
            std::string m_currentGuessOfWord;
            std::string m_playerCount;
            std::string m_wordToBeGuessed;
            uint32_t m_errorCount;
            uint32_t m_turnCount;
            char m_currentGuess;
        } m_hangmanGameInfo;

        struct BattleshipsGameInfo
        {
            std::array<std::array<std::string, G_BATTLESHIPS_BOARD_WIDTH>, G_BATTLESHIPS_BOARD_HEIGHT> m_boardOne;
            std::array<std::array<std::string, G_BATTLESHIPS_BOARD_WIDTH>, G_BATTLESHIPS_BOARD_HEIGHT> m_boardTwo;
            std::unordered_map<std::string, uint32_t> m_shipsRemainingOne;
            std::unordered_map<std::string, uint32_t> m_shipsRemainingTwo;
            std::string m_computerSpeedName;
            std::string m_currentPlayer;
            std::string m_playerCount;
            uint32_t m_turnCount;
            bool m_isGameOver;
        } m_battleshipsGameInfo;
    };

    /**
     * @brief Builds pages (i.e. strings) to be printed to the terminal.
     */
    class PageBuilder
    {
    public:
        /**
         * @brief Construct a new StringBuilder object.
         */
        explicit PageBuilder();

        /**
         * @brief Construct a new StringBuilder object.
         *
         * @param p_page Which page type to configure the PageBuilder for.
         * @param p_useAnsiEscapeCodes Whether to use use ANSI escapes codes (true) or only ASCII characters (false).
         */
        explicit PageBuilder(const Pages& p_page, const bool& p_useAnsiEscapeCodes);

        /**
         * @brief Set the properties of the object.
         *
         * @param p_page Which page type to configure the PageBuilder for.
         * @param p_useAnsiEscapeCodes Whether to use use ANSI escapes codes (true) or only ASCII characters (false).
         */
        void SetProperties(const Pages& p_page, const bool& p_useAnsiEscapeCodes);

        /**
         * @brief Get the current page type.
         *
         * @return Pages The current page type.
         */
        Pages GetCurrentPageType() const;

        /**
         * @brief Creates the pages for displaying the option selection home page screen.
         *
         * @return std::vector<std::string> Pages where each page has a different option selection.
         */
        std::vector<std::string> GetOptionSelectionHomepages();

        /**
         * @brief Creates pages for displaying the main menu game selection screen.
         *
         * @param p_gameNames The name of the games that can be selected.
         * @return std::vector<std::string> Pages where each page has a different game selected.
         */
        std::vector<std::string> GetGameSelectionMainMenuPages(const std::vector<std::string>& p_gameNames) const;

        /**
         * @brief Creates pages for displaying option selection screen for the number of players playing the game.
         *
         * @param p_gameInfo Information on the current state of the current game.
         * @return std::vector<std::string> Pages where each page has a different number of players selected.
         */
        std::vector<std::string> GetPlayerCountOptionSelectionGamePages(const GameInfo& p_gameInfo) const;

        /**
         * @brief Creates pages for displaying option selection screen for the user player choice for a game.
         *
         * @param p_gameInfo Information on the current state of the current game.
         * @return std::vector<std::string> Pages where each page has a player choice selected.
         */
        std::vector<std::string> GetUserPlayerChoiceOptionSelectionGamePages(const GameInfo& p_gameInfo) const;

        /**
         * @brief Creates pages for displaying option selection screen for the computer speed for a game.
         *
         * @param p_gameInfo Information on the current state of the current game.
         * @return std::vector<std::string> Pages where each page has a different computer speed selected.
         */
        std::vector<std::string> GetComputerSpeedOptionSelectionGamePages(const GameInfo& p_gameInfo) const;

        /**
         * @brief Creates a general game page with a custom message for use during a game.
         *
         * @param p_gameInfo Information on the current state of the current game.
         * @param p_message The custom message to display.
         * @return std::string A page with the current state of the game and a custom message.
         * @warning The message will be truncated if it is too long to be contained within a single line on the page.
         */
        std::string GetPageWithMessage(const GameInfo& p_gameInfo, const std::string& p_message) const;

        /**
         * @brief Creates the user command page which prompts the user to enter a command during a game.
         *
         * @param p_gameInfo Information on the current state of the current game.
         * @return std::string A page with the current state of the game and a prompt to the user to enter a command.
         */
        std::string GetUserCommandPage(const GameInfo& p_gameInfo) const;

        /**
         * @brief Creates the computer command page for when the computer is entering their command.
         *
         * @param p_gameInfo Information on the current state of the current game.
         * @return std::string A page with the current state of the game and a message that the computer is entering their command.
         */
        std::string GetComputerCommandPage(const GameInfo& p_gameInfo) const;

        /**
         * @brief Creates the game over page.
         *
         * @param p_gameInfo Information on the current state of the current game.
         * @return std::string A page with the final state of the game and a message on who won, how many turns took place, and
         * how to quit the game or play again.
         */
        std::string GetGameOverPage(const GameInfo& p_gameInfo) const;

        /**
         * @brief Creates the quit option selection page.
         *
         * @return std::vector<std::string> Pages where each page has a different quit option selected.
         */
        std::vector<std::string> GetQuitOptionSelectionPage() const;

    private:
        /**
         * @brief Sets the colour of the input text using ANSI escape codes.
         *
         * @param p_input The input text to be coloured.
         * @param p_colour The colour of the input text.
         * @return std::string The input text wrapped with ANSI colour escape codes.
         */
        std::string AddColour(const std::string& p_input, const Colours& p_colour) const;

        /**
         * @brief Removes colour from the input text by removing all ANSI colour escape codes.
         *
         * @param p_input The input text to be un-coloured.
         * @return std::string The input stripped of ANSI colour escape codes.
         */
        static std::string RemoveColour(const std::string& p_input);

        /**
         * @brief Creates a new line on a page but with no input text.
         *
         * @return std::string A new line with no input text.
         */
        std::string GetEmptyLine() const;

        /**
         * @brief Creates a new line on a page with the input text is automatically centred. If the spacing on the sides is
         * unequal, the left side will always have the higher amount of spacing.
         *
         * @param p_input The text to display on the new line.
         * @param p_colour The colour of the input text.
         * @param p_selector An identifier to show the line is selected.
         * @return std::string A new line with the input text centred.
         * @warning p_input will be truncated if it is too long to be contained within a single line on the page. Furthermore,
         * if p_input has colour added to it (i.e. it contins ANSI colour escape codes) then this will lead to unexpected
         * behaviour.
         */
        std::string GetNewLineCentred(const std::string& p_input, const Colours& p_colour = Colours::WHITE, const std::string& p_selector = "") const;

        /**
         * @brief Creates a new line on a page with the input text is automatically left justified (one space padding on to the
         * left page edge).
         *
         * @param p_input The text to display on the new line.
         * @param p_colour The colour of the input text.
         * @param p_selector An identifier to show the line is selected.
         * @return std::string A new line with the input text left justified.
         * @warning p_input will be truncated if it is too long to be contained within a single line on the page. Furthermore,
         * if p_input has colour added to it (i.e. it contins ANSI colour escape codes) then this will lead to unexpected
         * behaviour.
         */
        std::string GetNewLineLeftJustified(const std::string& p_input, const Colours& p_colour = Colours::WHITE, const std::string& p_selector = "") const;

        /**
         * @brief Creates the top line of a box within a page.
         *
         * @return std::string The top line of a box.
         */
        std::string GetTopLine() const;

        /**
         * @brief Creates the bottom line of a box within a page.
         *
         * @return std::string The bottom line of a box.
         */
        std::string GetBottomLine() const;

        /**
         * @brief Creates the top box display which acts as the title bar for a page.
         *
         * @return std::string The top box with the m_topTitle as the title.
         */
        std::string GetTopBox() const;

        /**
         * @brief Creates the bottom box which acts as general info for a page.
         *
         * @return std::string The bottom box with the m_bottomTitle as the general info.
         */
        std::string GetBottomBox() const;

        /**
         * @brief Used to pad a page vertically with empty lines.
         *
         * @param p_commonTopString The part of the page above where the empty lines are to be padded.
         * @param p_commonBottomString The part of the page below where the empty lines are to be padded.
         * @return std::string The empty lines that are needed in between the topString and bottomString.
         */
        std::string GetRemainingEmptyLines(const std::string& p_commonTopString, const std::string& p_commonBottomString) const;

        /**
         * @brief Creates pages for displaying option selection screens for the given options within a game screen.
         *
         * @param p_gameInfo Information on the current state of the current game.
         * @param p_message The custom message to display.
         * @param p_options The selectable options to display.
         * @return std::vector<std::string> Pages where each page has a different option selected.
         * @warning The message will be truncated if it is too long to be contained within a single line on the page.
         * @warning The page height will be allowed to extended pass the pre-defined page height to fit all the options provided.
         */
        std::vector<std::string> GetGameOptionSelectionPages(const GameInfo& p_gameInfo, const std::string& p_message, const std::vector<std::string>& p_options) const;

        /**
         * @brief Creates pages for displaying option selection screens for the given options.
         *
         * @param p_options The options for the option selection screen
         * @param p_commonTopString The common string between all pages found above the options.
         * @param p_commonBottomString The common string between all pages found below the options.
         * @param p_addEmptyLineBetweenOptions Whether to add an empty line between the options (true) or not (false).
         * @param p_centerOptions Whether to center the options (true) or left justify them (false).
         * @return std::vector<std::string> Pages where each page has a different option selected.
         */
        std::vector<std::string> GetGeneralOptionSelectionPages(
            const std::vector<std::string>& p_options,
            const std::string& p_commonTopString,
            const std::string& p_commonBottomString,
            const bool& p_addEmptyLineBetweenOptions,
            const bool& p_centerOptions) const;

        /**
         * @brief Wrapper function around the game specific sub-page functions.
         *
         * @param p_gameInfo Information on the current state of the current game.
         * @return std::string The subpage containing the current state of the current game.
         */
        std::string GetGeneralGameSubPage(const GameInfo& p_gameInfo) const;

        /**
         * @brief Creates the subpage containing the current state of the TicTacToe game.
         *
         * @param p_gameInfo Information on the current state of the current game.
         * @return std::string The subpage containing the current state of the TicTacToe game.
         */
        std::string GetTicTacToeSubPage(const GameInfo& p_gameInfo) const;

        /**
         * @brief Creates the subpage containing the current state of the Hangman game.
         *
         * @param p_gameInfo Information on the current state of the current game.
         * @return std::string The subpage containing the current state of the Hangman game.
         */
        std::string GetHangmanSubPage(const GameInfo& p_gameInfo) const;

        /**
         * @brief Creates the subpage containing the current state of the Battleships game.
         *
         * @param p_gameInfo Information on the current state of the current game.
         * @return std::string The subpage containing the current state of the Battleships game.
         */
        std::string GetBattleshipsSubPage(const GameInfo& p_gameInfo) const;

        /**
         * @brief Remove all instances of a substring from a string.
         *
         * @param p_string The string to be checked.
         * @param p_subString The substring to be removed.
         * @return std::string The string with the substring removed.
         */
        static std::string RemoveSubString(const std::string& p_string, const std::string& p_subString); // NOLINT(bugprone-easily-swappable-parameters)

        // Member variables
        std::string m_topTitle;
        std::string m_bottomTitle;
        uint32_t m_displayWidth;
        uint32_t m_displayHeight;
        uint32_t m_maximumInputSize;
        uint32_t m_maximumFilledLineSize;
        Pages m_currentPage;
        bool m_useAnsiEscapeCodes;

        /**
         * @brief A visual example of what some of the lower level function do:
         *
         * The whole page would be returned by GetGameOverPage()
         *
         * ╔═════════════════════════════════════════════════════╗   <- AddTopLine()                         <-
         * ║                     Tic Tac Toe                     ║   <- AddNewLineCentred("Tic Tac Toe")     <- AddTopBox()
         * ╚═════════════════════════════════════════════════════╝   <- AddBottomLine()                      <-
         * ╔═════════════════════════════════════════════════════╗   <- AddTopLine()
         * ║  O │ O │ X                                          ║                                                                            <-
         * ║ ───┼───┼───          # of Players = 0               ║                                                                            <-
         * ║  O │ X │ O                                          ║                                                                            <- GetGeneralGameSubPage() -> GetTicTacToeSubPage()
         * ║ ───┼───┼───     Computer Difficulty = EASY          ║   <- AddNewLineLeftJustified("───┼───┼───     Computer Difficulty = EASY") <-
         * ║  O │ X │ X                                          ║                                                                            <-
         * ║                                                     ║   <- AddEmptyLine()
         * ║                      GAME OVER                      ║   <- AddNewLineCentred("GAME OVER")
         * ║                                                     ║
         * ║     Player O has won! The game lasted 9 turns.      ║   <- AddNewLineCentred("Player O has won! The game lasted 9 turns.")
         * ║                                                     ║
         * ║     Press 'Q' to quit OR Enter to play again...     ║   <- AddNewLineCentred("Press 'Q' to quit OR Enter to play again...")
         * ╚═════════════════════════════════════════════════════╝   <- AddBottomLine()
         * ╔═════════════════════════════════════════════════════╗   <- AddTopLine()                                   <-
         * ║                q = quit to main menu                ║   <- AddNewLineCentred("q = quit to main menu")     <- AddBottomBox()
         * ╚═════════════════════════════════════════════════════╝   <- AddBottomLine()                                <-
         *
         *  ^---------------------------------------------------^
         *                    = displayWidth = 55
         *
         * In this example:
         *      m_topTitle = "Tic Tac Toe"
         *      m_bottomTitle = "q = quit to main menu"
         *      m_displayWidth = 55
         *      m_displayHeight = 19
         */
    };
}
