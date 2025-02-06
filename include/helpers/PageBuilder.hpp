#pragma once

#include <array>
#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

#include "helpers/Globals.hpp"

/**
 * @namespace TerminalGames
 * @brief Contains all Terminal-Games objects.
 */
namespace TerminalGames
{
    /**
     * @brief Represents the page types that are supported by PageBuilder.
     */
    enum class Pages : std::uint8_t
    {
        /**
         * @brief Page supported by PageBuilder.
         */
        ///@{
        DEFAULT = 0,
        HOMEPAGE,
        MAINMENU,
        TICTACTOE,
        HANGMAN,
        BATTLESHIPS,
        ///@}
    };

    /**
     * @brief Used by game objects to package themselves into a format that can be used by PageBuilder to construct a sub-page
     * for the current state of the game.
     */
    struct GameInfo
    {
        /**
         * @brief Used to package the TicTacToe current game state.
         */
        struct TicTacToeGameInfo
        {
            /**
             * @brief Refer to the member data documentation in TicTacToe.
             */
            ///@{
            std::array<std::array<std::string, Globals::G_TICTACTOE_GRID_WIDTH>, Globals::G_TICTACTOE_GRID_HEIGHT> m_gameGrid;
            std::string m_computerSpeedName;
            std::string m_currentPlayer;
            std::string m_playerCount;
            uint32_t m_turnCount;
            bool m_hasWinner;
            ///@}
        }
        /**
         * @brief Used to package the TicTacToe current game state.
         */
        m_ticTacToeGameInfo;

        /**
         * @brief Used to package the Hangman current game state.
         */
        struct HangmanGameInfo
        {
            /**
             * @brief Refer to the member data documentation in Hangman.
             */
            ///@{
            std::vector<char> m_incorrectGuesses;
            std::string m_computerSpeedName;
            std::string m_currentGuessOfWord;
            std::string m_playerCount;
            std::string m_wordToBeGuessed;
            uint32_t m_turnCount;
            char m_currentLetterSelected;
            bool m_isGameOver;
            ///@}
        }
        /**
         * @brief Used to package the Hangman current game state.
         */
        m_hangmanGameInfo;

        /**
         * @brief Used to package the Battleships current game state.
         */
        struct BattleshipsGameInfo
        {
            /**
             * @brief Refer to the member data documentation in Battleships.
             */
            ///@{
            std::array<std::array<std::string, Globals::G_BATTLESHIPS_BOARD_WIDTH>, Globals::G_BATTLESHIPS_BOARD_HEIGHT> m_boardPlayerOne;
            std::array<std::array<std::string, Globals::G_BATTLESHIPS_BOARD_WIDTH>, Globals::G_BATTLESHIPS_BOARD_HEIGHT> m_boardPlayerTwo;
            std::unordered_map<std::string, uint32_t> m_shipsRemainingPlayerOne;
            std::unordered_map<std::string, uint32_t> m_shipsRemainingPlayerTwo;
            std::string m_computerSpeedName;
            std::string m_currentPlayer;
            std::string m_playerCount;
            uint32_t m_turnCount;
            bool m_isGameOver;
            ///@}
        }
        /**
         * @brief Used to package the Battleships current game state.
         */
        m_battleshipsGameInfo;
    };

    /**
     * @class PageBuilder
     * @brief Builds pages (i.e. strings) to be printed to the terminal.
     */
    class PageBuilder
    {
    public:
        /**
         * @brief Constructs a new default %PageBuilder object.
         */
        explicit PageBuilder();

        /**
         * @brief Constructs a new custom %PageBuilder object.
         *
         * @param p_page Which page type to configure the %PageBuilder for.
         * @param p_useAnsiEscapeCodes Whether to use use ANSI escapes codes (true) or only extended ASCII characters (false).
         * @throws Globals::Exceptions::NotImplementedError When passed a Pages value that is not supported.
         */
        explicit PageBuilder(const Pages& p_page, const bool& p_useAnsiEscapeCodes);

        /**
         * @brief Set the properties of the %PageBuilder object.
         *
         * @param p_page Which page type to configure the %PageBuilder for.
         * @param p_useAnsiEscapeCodes Whether to use use ANSI escapes codes (true) or only extended ASCII characters (false).
         * @throws Globals::Exceptions::NotImplementedError When passed a Pages value that is not supported.
         */
        void SetProperties(const Pages& p_page, const bool& p_useAnsiEscapeCodes);

        /**
         * @brief Get the current page type.
         *
         * @return `Pages` The current page type.
         */
        Pages GetCurrentPageType() const;

        /**
         * @brief Creates the pages for displaying the option selection home page.
         *
         * @return `std::vector<std::string>` %Pages where each page has a different option selection.
         */
        std::vector<std::string> GetOptionSelectionHomepages();

        /**
         * @brief Creates the pages for displaying the main menu game selection page.
         *
         * @param p_gameNames The name of the games that can be selected.
         * @return `std::vector<std::string>` %Pages where each page has a different game selected.
         */
        std::vector<std::string> GetGameSelectionMainMenuPages(const std::vector<std::string>& p_gameNames) const;

        /**
         * @brief Creates the pages for displaying the number of players playing the game option selection page.
         *
         * @param p_gameInfo Information on the current state of the current game.
         * @return `std::vector<std::string>` %Pages where each page has a different number of players selected.
         */
        std::vector<std::string> GetPlayerCountOptionSelectionGamePages(const GameInfo& p_gameInfo);

        /**
         * @brief Creates the pages for displaying the user player choice for a game option selection page.
         *
         * @param p_gameInfo Information on the current state of the current game.
         * @return` std::vector<std::string>` %Pages where each page has a different player choice selected.
         */
        std::vector<std::string> GetUserPlayerChoiceOptionSelectionGamePages(const GameInfo& p_gameInfo);

        /**
         * @brief Creates the pages for displaying the computer speed for a game option selection page.
         *
         * @param p_gameInfo Information on the current state of the current game.
         * @return `std::vector<std::string>` %Pages where each page has a different computer speed selected.
         */
        std::vector<std::string> GetComputerSpeedOptionSelectionGamePages(const GameInfo& p_gameInfo);

        /**
         * @brief Creates a general game page with a custom message to display on the page.
         *
         * @param p_gameInfo Information on the current state of the current game.
         * @param p_message The custom message to display.
         * @return `std::string` A page with the current state of the game and a custom message.
         * @warning The message will be truncated if it is too long to be contained within a single line on the page.
         */
        std::string GetPageWithMessage(const GameInfo& p_gameInfo, const std::string& p_message);

        /**
         * @brief Creates the game user command page which should prompt the user to enter a command.
         *
         * @param p_gameInfo Information on the current state of the current game.
         * @return `std::string` A page with the current state of the game and a prompt to the user to enter a command.
         */
        std::string GetUserCommandPage(const GameInfo& p_gameInfo);

        /**
         * @brief Creates the computer command page for when the computer is entering their command.
         *
         * @param p_gameInfo Information on the current state of the current game.
         * @return `std::string` A page with the current state of the game and a message that the computer is entering their
         * command.
         */
        std::string GetComputerCommandPage(const GameInfo& p_gameInfo);

        /**
         * @brief Creates the game over page.
         *
         * @param p_gameInfo Information on the current state of the current game.
         * @return `std::string` A page with the final state of the game, a message on who won, how many turns took place, and
         * how to quit the game or play again.
         */
        std::string GetGameOverPage(const GameInfo& p_gameInfo);

        /**
         * @brief Creates the quit option selection page.
         *
         * @return `std::vector<std::string>` %Pages where each page has a different quit option selected.
         */
        std::vector<std::string> GetQuitOptionSelectionPage() const;

    private:
        /**
         * @brief Sets the colour of `p_input` using ANSI escape codes.
         *
         * @param p_input The input text to be coloured.
         * @param p_colour The colour of the input text.
         * @return `std::string` The input text wrapped with ANSI colour escape codes.
         */
        std::string AddColour(const std::string& p_input, const Globals::Colours& p_colour) const;

        /**
         * @brief Removes colour from the input text by removing all ANSI colour escape codes.
         *
         * @param p_input The input text to be un-coloured.
         * @return `std::string` The input stripped of ANSI colour escape codes.
         */
        static std::string RemoveColour(const std::string& p_input);

        /**
         * @brief Creates a new line on a page but with no input text.
         *
         * @return `std::string` A new line with no input text.
         */
        std::string GetEmptyLine() const;

        /**
         * @brief Creates a new line on a page with `p_input` automatically centred. If the spacing on the sides is unequal, the
         * left side will always have the higher amount of spacing. With an optional parameters of `p_colour` to colour the
         * input text and `p_selector` used when creating option selection pages.
         *
         * @param p_input The text to display on the new line.
         * @param p_colour The colour of the input text.
         * @param p_selector An identifier to show the line is selected.
         * @return `std::string` A new line with the input text centred.
         * @warning `p_input` will be truncated if it is too long to be contained within a single line on the page.
         * @warning Unexpected behaviour will occur if `p_input` is coloured (i.e. it contins ANSI colour escape codes).
         */
        std::string GetNewLineCentred(const std::string& p_input, const Globals::Colours& p_colour = Globals::Colours::WHITE, const std::string& p_selector = "") const;

        /**
         * @brief Creates a new line on a page with `p_input` automatically centred. If the spacing on the sides is unequal, the
         * left side will always have the higher amount of spacing. This is a simplified more performant version of
         * GetNewLineCentred.
         *
         * @param p_input The text to display on the new line.
         * @return `std::string` A new line with the input text centred.
         * @warning Unexpected behaviour will occur if  `p_input` is too long to be contained within a single line on the page
         * or if `p_input` is coloured (i.e. it contins ANSI colour escape codes).
         */
        std::string GetNewLineCentredOptimised(const std::string& p_input) const;

        /**
         * @brief Creates a new line on a page with `p_input` automatically left justified (with one space padding on to the
         * left page edge). With an optional parameters of `p_colour` to colour the input text and `p_selector` used when
         * creating option selection pages.
         *
         * @param p_input The text to display on the new line.
         * @param p_colour The colour of the input text.
         * @param p_selector An identifier to show the line is selected.
         * @return `std::string` A new line with the input text left justified.
         * @warning `p_input` will be truncated if it is too long to be contained within a single line on the page.
         * @warning Unexpected behaviour will occur if `p_input` is coloured (i.e. it contins ANSI colour escape codes).
         */
        std::string GetNewLineLeftJustified(const std::string& p_input, const Globals::Colours& p_colour = Globals::Colours::WHITE, const std::string& p_selector = "") const;

        /**
         * @brief Creates the top line of a box within a page.
         *
         * @return `std::string` The top line of a box.
         */
        std::string GetTopLine() const;

        /**
         * @brief Creates the bottom line of a box within a page.
         *
         * @return `std::string` The bottom line of a box.
         */
        std::string GetBottomLine() const;

        /**
         * @brief Creates the top box display which acts as the title bar for a page.
         *
         * @return `std::string` The top box with the `m_topTitle` centred within it.
         */
        std::string GetTopBox() const;

        /**
         * @brief Creates the bottom box which acts as the footer for a page.
         *
         * @return `std::string` The bottom box with the `m_bottomTitle` centred within it.
         */
        std::string GetBottomBox() const;

        /**
         * @brief Used to pad a page vertically with empty lines.
         *
         * @param p_commonTopString The part of the page above where the empty lines are to be padded.
         * @param p_commonBottomString The part of the page below where the empty lines are to be padded.
         * @return `std::string` The empty lines that are needed in between the topString and bottomString.
         */
        std::string GetRemainingEmptyLines(const std::string& p_commonTopString, const std::string& p_commonBottomString) const;

        /**
         * @brief Creates the pages for displaying the option selection page for the given options.
         *
         * @param p_options The options for the option selection page
         * @param p_commonTopString The common string between all pages found above the options.
         * @param p_commonBottomString The common string between all pages found below the options.
         * @param p_addEmptyLineBetweenOptions Whether to add an empty line between the options (true) or not (false).
         * @param p_centerOptionsHorizontally Whether to center the options horizontally (true) or left justify them (false).
         * @param p_centerOptionsVertically Whether to center the options vertically (true) or left justify them (false).
         * @return `std::vector<std::string>` %Pages where each page has a different option selected.
         */
        std::vector<std::string> GetGeneralOptionSelectionPages(
            const std::vector<std::string>& p_options,
            const std::string& p_commonTopString,
            const std::string& p_commonBottomString,
            const bool& p_addEmptyLineBetweenOptions,
            const bool& p_centerOptionsHorizontally,
            const bool& p_centerOptionsVertically) const;

        /**
         * @brief Creates the pages for displaying the option selection page for the given options *within a game page*.
         *
         * @param p_gameInfo Information on the current state of the current game.
         * @param p_message The custom message to display.
         * @param p_options The selectable options to display.
         * @return `std::vector<std::string>` %Pages where each page has a different option selected.
         * @warning The message will be truncated if it is too long to be contained within a single line on the page.
         * @warning The page height will be allowed to extended pass the pre-defined page height (i.e. `m_pageHeight`) to fit
         * all of the options provided.
         */
        std::vector<std::string> GetGameOptionSelectionPages(const GameInfo& p_gameInfo, const std::string& p_message, const std::vector<std::string>& p_options);

        /**
         * @brief Wrapper function around the game specific game sub-page functions.
         *
         * @param p_gameInfo Information on the current state of the current game.
         * @return `std::string` The sub-page containing the current state of the current game.
         */
        std::string GetGeneralGameSubPage(const GameInfo& p_gameInfo);

        /**
         * @brief Creates the sub-page containing the current state of the TicTacToe game.
         *
         * @param p_gameInfo Information on the current state of the current game.
         * @return `std::string` The sub-page containing the current state of the TicTacToe game.
         */
        std::string GetTicTacToeSubPage(const GameInfo& p_gameInfo);

        /**
         * @brief Creates the sub-page containing the current state of the Hangman game.
         *
         * @param p_gameInfo Information on the current state of the current game.
         * @return `std::string` The sub-page containing the current state of the Hangman game.
         */
        std::string GetHangmanSubPage(const GameInfo& p_gameInfo);

        /**
         * @brief Creates the sub-page containing the current state of the Battleships game.
         *
         * @param p_gameInfo Information on the current state of the current game.
         * @return `std::string` The sub-page containing the current state of the Battleships game.
         */
        std::string GetBattleshipsSubPage(const GameInfo& p_gameInfo);

        /**
         * @brief Calculates a grid layout based on the grid content in `p_gridColumnLines` and the grid sizes in
         * `p_gridColumnWidths`. Only columns can be defined and all content is centred within its grid column. This is used by
         * the game sub-page functions to simplify their code.
         *
         * @param p_gridColumnWidths The width of each grid column.
         * @param p_gridColumnLines The content of each grid column where each grid column is an element in `p_gridColumnLines`.
         * @param p_gridColumnHeight The height of the grid columns (i.e. the number of lines within each grid column). Note
         * that this must be the same for all grid columns.
         * @return `std::string` The grid layout based sub-page.
         * @warning `p_gridColumnWidths.size()` must be equal to `p_gridColumnLines.size()`.
         * @warning The length all elements in `p_gridColumnLines` (i.e. `p_gridColumnLines[i].size()`) must be equal to
         * `p_gridColumnHeight`.
         */
        std::string GetGridLayout(const std::vector<uint32_t>& p_gridColumnWidths, const std::vector<std::vector<std::string>>& p_gridColumnLines, const uint32_t& p_gridColumnHeight);

        /**
         * @brief The text to display in the top box which acts as the title bar within a page.
         */
        std::string m_topTitle;

        /**
         * @brief The text to display in the bottom box which acts as a footer of a page.
         */
        std::string m_bottomTitle;

        /**
         * @brief The page width in terms of the total number of characters (inclusive of the page edge characters) per line.
         */
        uint32_t m_pageWidth;

        /**
         * @brief The page height in terms of the total number of lines (inclusive of the page edge lines).
         */
        uint32_t m_pageHeight;

        /**
         * @brief The maximum number of characters (excluding page edge and padding characters) that can exist within a line.
         */
        uint32_t m_lineMaximumCharacterCount;

        /**
         * @brief The minimum amount of padding between the edge characters of the page and the inner content.
         */
        ///@{
        uint32_t m_minimumLeftPadding;
        uint32_t m_minimumRightPadding;
        ///@}

        /**
         * @brief The current page type to build for.
         */
        Pages m_currentPage;

        /**
         * @brief Whether to use use ANSI escapes codes (true) or only extended ASCII characters (false).
         */
        bool m_useAnsiEscapeCodes;
    };
}
