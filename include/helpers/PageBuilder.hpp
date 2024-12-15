#pragma once

#include <array>
#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

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
 * @brief Pages representing the pages that PageBuilder supports.
 */
enum class Pages
{
    MAINMENU,
    TICTACTOE,
    HANGMAN,
    BATTLESHIPS
};

/**
 * @brief Used by game objects to package up their current state into a format that can be used by PageBuilder.
 */
struct GameInfo {
    struct TicTacToeStruct {
        std::array<std::array<char, 3>, 3> gameGrid;
        std::string currentPlayer, playerCount, AISpeedName;
        uint32_t turnCount;
        bool hasWinner;
    } ticTacToeStruct;

    struct HangmanStruct {
        std::vector<char> incorrectGuesses;
        std::string currentGuessOfWord, wordToBeGuessed, playerCount, AISpeedName;
        uint32_t errorCount, turnCount;
    } hangmanStruct;

    struct BattleshipsStruct {
        std::array<std::array<char, 10>, 10> boardOne, boardTwo;
        std::unordered_map<char, uint32_t> shipsRemainingOne, shipsRemainingTwo;
        std::string playerCount, AISpeedName, currentPlayer;
        uint32_t turnCount;
        bool isGameOver;
    } battleshipsStruct;
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
    explicit PageBuilder() = default;

    /**
     * @brief Construct a new StringBuilder object.
     *
     * @param page Which page type to configure the PageBuilder for.
     * @param outputIsOnlyASCII Whether to use only ASCII characters (true) or to also use ANSI escapes codes (false).
     */
    explicit PageBuilder(const Pages& page, const bool& outputIsOnlyASCII);

    /**
     * @brief Set the properties of the object.
     *
     * @param page Which page type to configure the PageBuilder for.
     * @param outputIsOnlyASCII Whether to use only ASCII characters (true) or to also use ANSI escapes codes (false).
     */
    void SetProperties(const Pages& page, const bool& outputIsOnlyASCII);

    /**
     * @brief Creates pages for displaying the main menu game selection screen.
     *
     * @param gameNames The name of the games that can be selected.
     * @return std::vector<std::string> Pages where each page has a different game selected.
     */
    std::vector<std::string> GetGameSelectionMainMenuPages(const std::vector<std::string>& gameNames) const;

    /**
     * @brief Creates pages for displaying option selection screen for the number of players playing the game.
     *
     * @param gameInfo Information on the current state of the current game.
     * @return std::vector<std::string> Pages where each page has a different number of players selected.
     */
    std::vector<std::string> GetPlayerCountOptionSelectionGamePages(const GameInfo& gameInfo) const;

    /**
     * @brief Creates pages for displaying option selection screen for the user player choice for a game.
     *
     * @param gameInfo Information on the current state of the current game.
     * @return std::vector<std::string> Pages where each page has a player choice selected.
     */
    std::vector<std::string> GetUserPlayerChoiceOptionSelectionGamePages(const GameInfo& gameInfo) const;

    /**
     * @brief Creates pages for displaying option selection screen for the AI speed for a game.
     *
     * @param gameInfo Information on the current state of the current game.
     * @return std::vector<std::string> Pages where each page has a different AI speed selected.
     */
    std::vector<std::string> GetAISpeedOptionSelectionGamePages(const GameInfo& gameInfo) const;

    /**
     * @brief Creates a general game page with a custom message for use during a game.
     *
     * @param gameInfo Information on the current state of the current game.
     * @param message The custom message to display.
     * @return std::string A page with the current state of the game and a custom message.
     * @warning The message will be truncated if it is too long to be contained within a single line on the page.
     */
    std::string GetPageWithMessage(const GameInfo& gameInfo, const std::string& message) const;

    /**
     * @brief Creates the user command page which prompts the user to enter a command during a game.
     *
     * @param gameInfo Information on the current state of the current game.
     * @return std::string A page with the current state of the game and a prompt to the user to enter a command.
     */
    std::string GetUserCommandPage(const GameInfo& gameInfo) const;

    /**
     * @brief Creates the AI command page for when the AI is entering their command.
     *
     * @param gameInfo Information on the current state of the current game.
     * @return std::string A page with the current state of the game and a message that the AI is entering their command.
     */
    std::string GetAICommandPage(const GameInfo& gameInfo) const;

    /**
     * @brief Creates the game over page.
     *
     * @param gameInfo Information on the current state of the current game.
     * @return std::string A page with the final state of the game and a message on who won, how many turns took place,
     * and how to quit the game or play again.
     */
    std::string GetGameOverPage(const GameInfo& gameInfo) const;

private:
    /**
     * @brief Sets the colour of the input text using ANSI escape codes.
     *
     * @param input The input text to be coloured.
     * @param colour The colour of the input text.
     * @return std::string The input text wrapped with ANSI colour escape codes.
     */
    std::string AddColour(const std::string& input, const Colours& colour) const;

    /**
     * @brief Creates a new line on a page but with no input text.
     *
     * @return std::string A new line with no input text.
     */
    std::string GetEmptyLine() const;

    /**
     * @brief Creates a new line on a page with the input text is automatically centered. If the spacing on the sides
     * is unequal, the left side will always have the higher amount of spacing.
     *
     * @param input The text to display on the new line.
     * @param colour The colour of the input text.
     * @return std::string A new line with the input text centered.
     * @warning The message will be truncated if it is too long to be contained within a single line on the page.
     */
    std::string GetNewLineCentred(const std::string& input, const Colours& colour = Colours::WHITE, const std::string& selector = "") const;

    /**
     * @brief Creates a new line on a page with the input text is automatically left justified (one space padding on
     * to the left page edge).
     *
     * @param input The text to display on the new line.
     * @param colour The colour of the input text.
     * @return std::string A new line with the input text left justified.
     * @warning The message will be truncated if it is too long to be contained within a single line on the page.
     */
    std::string GetNewLineLeftJustified(const std::string& input, const Colours& colour = Colours::WHITE, const std::string& selector = "") const;

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
     * @param topString The part of the page above where the empty lines are to be padded.
     * @param bottomString The part of the page below where the empty lines are to be padded.
     * @return std::string The empty lines that are needed in between the topString and bottomString.
     */
    std::string GetRemainingEmptyLines(const std::string& topString, const std::string& bottomString) const;

    /**
     * @brief Creates pages for displaying option selection screens for the given options.
     *
     * @param gameInfo Information on the current state of the current game.
     * @param message The custom message to display.
     * @param options The selectable options to display.
     * @return std::vector<std::string> Pages where each page has a different option selected.
     * @warning The message will be truncated if it is too long to be contained within a single line on the page.
     * @warning The page height will be allowed to extended pass the pre-defined page height to fit all the options provided.
     */
    std::vector<std::string> GetOptionSelectionPages(const GameInfo &gameInfo, const std::string &message, const std::vector<std::string> &options) const;

    /**
     * @brief Wrapper function around the game specific sub-page functions.
     *
     * @param gameInfo Information on the current state of the current game.
     * @return std::string The subpage containing the current state of the current game.
     */
    std::string GetGeneralGameSubPage(const GameInfo& gameInfo) const;

    /**
     * @brief Creates the subpage containing the current state of the TicTacToe game.
     *
     * @param gameInfo Information on the current state of the current game.
     * @return std::string The subpage containing the current state of the TicTacToe game.
     */
    std::string GetTicTacToeSubPage(const GameInfo& gameInfo) const;

    /**
     * @brief Creates the subpage containing the current state of the Hangman game.
     *
     * @param gameInfo Information on the current state of the current game.
     * @return std::string The subpage containing the current state of the Hangman game.
     */
    std::string GetHangmanSubPage(const GameInfo& gameInfo) const;

    /**
     * @brief Creates the subpage containing the current state of the Battleships game.
     *
     * @param gameInfo Information on the current state of the current game.
     * @return std::string The subpage containing the current state of the Battleships game.
     */
    std::string GetBattleshipsSubPage(const GameInfo& gameInfo) const;

    // Member variables
    std::string m_topTitle;
    uint32_t m_displayWidth, m_displayHeight;
    bool m_outputIsOnlyASCII;
    Pages m_currentPage;

    // Member constants:
    // - Page dimensions
    const uint32_t m_MAIN_MENU_DISPLAY_WIDTH = 30, m_MAIN_MENU_DISPLAY_HEIGHT = 13;
    const uint32_t m_TICTACTOE_DISPLAY_WIDTH = 53, m_TICTACTOE_DISPLAY_HEIGHT = 19;
    const uint32_t m_HANGMAN_DISPLAY_WIDTH = 62, m_HANGMAN_DISPLAY_HEIGHT = 22;
    const uint32_t m_BATTLESHIPS_DISPLAY_WIDTH = 147, m_BATTLESHIPS_DISPLAY_HEIGHT = 38;
    // - Bottom box titles
    const std::string m_MENU_BOTTOM_TITLE = "q = quit", m_GAME_BOTTOM_TITLE = "q = quit to main menu";
    // - Selector
    const std::string m_SELECTOR = ">";
    // - Extended ASCII characters
    const char m_HORIZONTAL_LINE = 205, m_VERTICAL_LINE = 186, m_TOP_RIGHT_CORNER = 187, m_BOTTOM_RIGHT_CORNER = 188, m_BOTTOM_LEFT_CORNER = 200, m_TOP_LEFT_CORNER = 201;
    // - ANSI colour escape codes
    const std::string m_WHITE = "\x1B[1;37m", m_RED = "\x1B[1;31m", m_BLUE = "\x1B[1;34m", m_RESET = "\x1B[0m";

    /**
     * A visual example of what some of the lower level function do:
     *
     * The whole page would be returned by GetGameOverPage()
     *
     * ╔═════════════════════════════════════════════════════╗   <- AddTopLine()                         <-
     * ║                     Tic Tac Toe                     ║   <- AddNewLineCentred("Tic Tac Toe")     <- AddTopBox()
     * ╚═════════════════════════════════════════════════════╝   <- AddBottomLine()                      <-
     * ╔═════════════════════════════════════════════════════╗   <- AddTopLine()
     * ║  O │ O │ X                                          ║                                                                          <-
     * ║ ───┼───┼───      # of Players = 0                   ║                                                                          <-
     * ║  O │ X │ O                                          ║                                                                          <- GetTicTacToeSubPage() and GetGeneralGameSubPage()
     * ║ ───┼───┼───     AI Difficulty = EASY                ║   <- AddNewLineLeftJustified("───┼───┼───     AI Difficulty = EASY")     <-
     * ║  O │ X │ X                                          ║                                                                          <-
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
