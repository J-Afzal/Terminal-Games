#include <array>
#include <cmath>
#include <cstdint>
#include <string>
#include <vector>

#include "helpers/Globals.hpp"
#include "helpers/PageBuilder.hpp"

namespace TerminalGames
{
    PageBuilder::PageBuilder() :
        m_displayWidth(0),
        m_displayHeight(0),
        m_maximumInputSize(0),
        m_maximumFilledLineSize(0),
        m_useAnsiEscapeCodes(false),
        m_currentPage(Pages::DEFAULT) {}

    PageBuilder::PageBuilder(const Pages& p_page, const bool& p_useAnsiEscapeCodes) :
        m_displayWidth(0),
        m_displayHeight(0),
        m_maximumInputSize(0),
        m_maximumFilledLineSize(0),
        m_useAnsiEscapeCodes(false),
        m_currentPage(Pages::DEFAULT)
    {
        SetProperties(p_page, p_useAnsiEscapeCodes);
    }

    void PageBuilder::SetProperties(const Pages& p_page, const bool& p_useAnsiEscapeCodes)
    {
        m_currentPage = p_page;
        m_useAnsiEscapeCodes = p_useAnsiEscapeCodes;

        switch (m_currentPage)
        {
        case Pages::HOMEPAGE:
            m_topTitle = Globals::G_HOMEPAGE_TOP_TITLE;
            m_bottomTitle = Globals::G_HOMEPAGE_BOTTOM_TITLE;
            m_displayWidth = Globals::G_HOMEPAGE_DISPLAY_WIDTH;
            m_displayHeight = Globals::G_HOMEPAGE_DISPLAY_HEIGHT;
            break;

        case Pages::MAINMENU:
            m_topTitle = Globals::G_MAIN_MENU_TOP_TITLE;
            m_bottomTitle = Globals::G_MAIN_MENU_BOTTOM_TITLE;
            m_displayWidth = Globals::G_MAIN_MENU_DISPLAY_WIDTH;
            m_displayHeight = Globals::G_MAIN_MENU_DISPLAY_HEIGHT;
            break;

        case Pages::TICTACTOE:
            m_topTitle = Globals::G_TICTACTOE_TOP_TITLE;
            m_bottomTitle = Globals::G_TICTACTOE_BOTTOM_TITLE;
            m_displayWidth = Globals::G_TICTACTOE_DISPLAY_WIDTH;
            m_displayHeight = Globals::G_TICTACTOE_DISPLAY_HEIGHT;
            break;

        case Pages::HANGMAN:
            m_topTitle = Globals::G_HANGMAN_TOP_TITLE;
            m_bottomTitle = Globals::G_HANGMAN_BOTTOM_TITLE;
            m_displayWidth = Globals::G_HANGMAN_DISPLAY_WIDTH;
            m_displayHeight = Globals::G_HANGMAN_DISPLAY_HEIGHT;
            break;

        case Pages::BATTLESHIPS:
            m_topTitle = Globals::G_BATTLESHIPS_TOP_TITLE;
            m_bottomTitle = Globals::G_BATTLESHIPS_BOTTOM_TITLE;
            m_displayWidth = Globals::G_BATTLESHIPS_DISPLAY_WIDTH;
            m_displayHeight = Globals::G_BATTLESHIPS_DISPLAY_HEIGHT;
            break;

        default:
            throw Globals::Exceptions::NotImplementedError();
        }

        m_maximumInputSize = m_displayWidth - Globals::G_MINIMUM_LEFT_VERTICAL_LINE_SIZE - Globals::G_MINIMUM_LEFT_PADDING_SIZE - Globals::G_MINIMUM_RIGHT_PADDING_SIZE - Globals::G_MINIMUM_RIGHT_VERTICAL_LINE_SIZE;
        m_maximumFilledLineSize = m_displayWidth - Globals::G_MINIMUM_LEFT_VERTICAL_LINE_SIZE - Globals::G_MINIMUM_RIGHT_VERTICAL_LINE_SIZE;
    }

    Pages PageBuilder::GetCurrentPageType() const
    {
        return m_currentPage;
    }

    std::vector<std::string> PageBuilder::GetOptionSelectionHomepages()
    {
        std::vector<std::string> output;

        const bool OLD_USE_ANSI_ESCAPE_CODES = m_useAnsiEscapeCodes;
        m_useAnsiEscapeCodes = true;

#ifdef _WIN32
        const std::string COMMON_TOP_STRING = GetTopBox() + GetTopLine() +
                                              GetNewLineCentred("Platform: " + AddColour("Windows", Colours::GREEN)) + GetEmptyLine() +
                                              GetNewLineCentred("Controls: " + AddColour("Enhanced", Colours::GREEN)) + GetEmptyLine() +
                                              GetNewLineCentred("Instructions: Use the arrows keys") + GetNewLineCentred("to navigate and press enter to") + GetNewLineCentred("confirm a selection.") +
                                              GetEmptyLine() + GetEmptyLine() + GetNewLineLeftJustified("Use ANSI colour escape codes?");

        const std::string COMMON_BOTTOM_STRING = GetBottomLine() + GetBottomBox();

        output.emplace_back(
            COMMON_TOP_STRING +
            GetNewLineLeftJustified("Yes", Colours::BLUE, Globals::G_SELECTOR) +
            GetNewLineLeftJustified(std::string(Globals::G_SELECTOR.size() + 1, ' ') + "No") +
            COMMON_BOTTOM_STRING);

        output.emplace_back(RemoveColour(
            COMMON_TOP_STRING +
            GetNewLineLeftJustified(std::string(Globals::G_SELECTOR.size() + 1, ' ') + "Yes") +
            GetNewLineLeftJustified("No", Colours::BLUE, Globals::G_SELECTOR) +
            COMMON_BOTTOM_STRING));
#else
        const std::string COMMON_TOP_STRING = GetTopBox() + GetTopLine() +
                                              GetNewLineCentred("Platform: " + AddColour("macOS or Linux", Colours::GREEN)) + GetEmptyLine() +
                                              GetNewLineCentred("Controls: " + AddColour("Enhanced", Colours::GREEN)) + GetEmptyLine() +
                                              GetNewLineCentred("Instructions: Enter one of the") + GetNewLineCentred("WASD keys to navigate, 'e' to") + GetNewLineCentred("to confirm a selection and 'z' to") + GetNewLineCentred("undo a selection in Battleships.") +
                                              GetEmptyLine() + GetNewLineLeftJustified("Use ANSI colour escape codes?");

        const std::string COMMON_BOTTOM_STRING = GetBottomLine() + GetBottomBox();

        output.emplace_back(
            COMMON_TOP_STRING +
            GetNewLineLeftJustified("Yes", Colours::BLUE, Globals::G_SELECTOR) +
            GetNewLineLeftJustified(std::string(Globals::G_SELECTOR.size() + 1, ' ') + "No") +
            COMMON_BOTTOM_STRING);

        output.emplace_back(RemoveColour(
            COMMON_TOP_STRING +
            GetNewLineLeftJustified(std::string(Globals::G_SELECTOR.size() + 1, ' ') + "Yes") +
            GetNewLineLeftJustified("No", Colours::BLUE, Globals::G_SELECTOR) +
            COMMON_BOTTOM_STRING));
#endif
        m_useAnsiEscapeCodes = OLD_USE_ANSI_ESCAPE_CODES;
        return output;
    }

    std::vector<std::string> PageBuilder::GetGameSelectionMainMenuPages(const std::vector<std::string>& p_gameNames) const
    {
        const std::string COMMON_TOP_STRING = GetTopBox() + GetTopLine();
        const std::string COMMON_BOTTOM_STRING = GetBottomLine() + GetBottomBox();

        return GetGeneralOptionSelectionPages(p_gameNames, COMMON_TOP_STRING, COMMON_BOTTOM_STRING, true, true);
    }

    std::vector<std::string> PageBuilder::GetPlayerCountOptionSelectionGamePages(const GameInfo& p_gameInfo) const
    {
        switch (m_currentPage)
        {
        case Pages::TICTACTOE:
        case Pages::HANGMAN:
            return GetGameOptionSelectionPages(p_gameInfo, "Please select the number of players:", {"0", "1", "2"});

        case Pages::BATTLESHIPS:
            return GetGameOptionSelectionPages(p_gameInfo, "Please select the number of players:", {"0", "1"});

        default:
            return {"The 'GetPlayerCountOptionSelectionGameDisplays' function does not support the current page type."};
        }
    }

    std::vector<std::string> PageBuilder::GetUserPlayerChoiceOptionSelectionGamePages(const GameInfo& p_gameInfo) const
    {
        switch (m_currentPage)
        {
        case Pages::TICTACTOE:
            return GetGameOptionSelectionPages(p_gameInfo, "Please select the player you would like to be:", {"PLAYER X", "PLAYER O"});

        case Pages::HANGMAN:
            return GetGameOptionSelectionPages(p_gameInfo, "Please select the player you would like to be:", {"GUESSER", "WORD SETTER"});

        default:
            return {"The 'GetUserPlayerChoiceOptionSelectionGameDisplays' function does not support the current page type."};
        }
    }

    std::vector<std::string> PageBuilder::GetComputerSpeedOptionSelectionGamePages(const GameInfo& p_gameInfo) const
    {
        switch (m_currentPage)
        {
        case Pages::TICTACTOE:
        case Pages::HANGMAN:
        case Pages::BATTLESHIPS:
            return GetGameOptionSelectionPages(p_gameInfo, "Please select the computer speed:", {"INSTANT", "FAST", "SLOW"});

        default:
            return {"The 'GetComputerSpeedOptionSelectionGameDisplays' function does not support the current page type."};
        }
    }

    std::string PageBuilder::GetPageWithMessage(const GameInfo& p_gameInfo, const std::string& p_message) const
    {
        const std::string COMMON_TOP_STRING = GetTopBox() + GetTopLine() + GetGeneralGameSubPage(p_gameInfo) + GetEmptyLine() + GetNewLineLeftJustified(p_message);
        const std::string COMMON_BOTTOM_STRING = GetBottomLine() + GetBottomBox();

        return COMMON_TOP_STRING + GetRemainingEmptyLines(COMMON_TOP_STRING, COMMON_BOTTOM_STRING) + COMMON_BOTTOM_STRING;
    }

    std::string PageBuilder::GetUserCommandPage(const GameInfo& p_gameInfo) const
    {
        switch (m_currentPage)
        {
        case Pages::TICTACTOE:
            return GetPageWithMessage(p_gameInfo, p_gameInfo.m_ticTacToeGameInfo.m_currentPlayer + ", please enter your next command!");

        case Pages::HANGMAN:
            return GetPageWithMessage(p_gameInfo, "Guesser, please enter your next guess: " + AddColour(std::string() + p_gameInfo.m_hangmanGameInfo.m_currentGuess, Colours::BLUE));

        case Pages::BATTLESHIPS:
            return GetPageWithMessage(p_gameInfo, p_gameInfo.m_battleshipsGameInfo.m_currentPlayer + ", please enter your next command!");

        default:
            return "The 'GetUserCommandGameDisplay' function does not support the current page type.";
        }
    }

    std::string PageBuilder::GetComputerCommandPage(const GameInfo& p_gameInfo) const
    {
        switch (m_currentPage)
        {
        case Pages::TICTACTOE:
        case Pages::HANGMAN:
        case Pages::BATTLESHIPS:
            return GetPageWithMessage(p_gameInfo, "The computer is executing their next move!");

        default:
            return "The 'GetComputerSpeedOptionSelectionGameDisplays' function does not support the current page type.";
        }
    }

    std::string PageBuilder::GetGameOverPage(const GameInfo& p_gameInfo) const
    {
        std::string topString = GetTopBox() + GetTopLine() + GetGeneralGameSubPage(p_gameInfo) + GetEmptyLine() + GetNewLineCentred("GAME OVER") + GetEmptyLine();
        const std::string BOTTOM_STRING = GetEmptyLine() + GetNewLineCentred("Press 'r' to restart game OR any key to reset game...") + GetBottomLine() + GetBottomBox();

        switch (m_currentPage)
        {
        case Pages::TICTACTOE:
            if (p_gameInfo.m_ticTacToeGameInfo.m_hasWinner) // This game can be drawn unlike the others.
                topString += GetNewLineCentred(p_gameInfo.m_ticTacToeGameInfo.m_currentPlayer + " has won! The game lasted " + std::to_string(p_gameInfo.m_ticTacToeGameInfo.m_turnCount) + " turns.");

            else
                topString += GetNewLineCentred("The game is a draw! The game lasted " + std::to_string(p_gameInfo.m_ticTacToeGameInfo.m_turnCount) + " turns.");
            break;

        case Pages::HANGMAN:
            if (p_gameInfo.m_hangmanGameInfo.m_errorCount == Globals::G_HANGMAN_MAXIMUM_ERROR_COUNT)
                topString += GetNewLineCentred("The word setter has won! The game lasted " + std::to_string(p_gameInfo.m_hangmanGameInfo.m_turnCount) + " turns!");

            else
                topString += GetNewLineCentred("The guesser has won! The game lasted " + std::to_string(p_gameInfo.m_hangmanGameInfo.m_turnCount) + " turns.");
            break;

        case Pages::BATTLESHIPS:
            topString += GetNewLineCentred(p_gameInfo.m_battleshipsGameInfo.m_currentPlayer + " has won! The game lasted " + std::to_string(p_gameInfo.m_battleshipsGameInfo.m_turnCount) + " turns.");
            break;

        default:
            return "The 'GetGameOverGameDisplay' function does not support the current page type.";
        }

        return topString + GetRemainingEmptyLines(topString, BOTTOM_STRING) + BOTTOM_STRING;
    }

    std::vector<std::string> PageBuilder::GetQuitOptionSelectionPage() const
    {
        const std::string COMMON_TOP_STRING = GetTopBox() + GetTopLine();
        const std::string COMMON_BOTTOM_STRING = GetBottomLine() + GetBottomBox();
        return GetGeneralOptionSelectionPages(Globals::G_QUIT_MENU_OPTIONS, COMMON_TOP_STRING, COMMON_BOTTOM_STRING, true, true);
    }

    std::string PageBuilder::AddColour(const std::string& p_input, const Colours& p_colour) const
    {
        if (!m_useAnsiEscapeCodes)
            return p_input;

        switch (p_colour)
        {
        case Colours::RED:
            return Globals::G_RED_ANSI_COLOUR_ESCAPE_CODE + p_input + Globals::G_WHITE_ANSI_COLOUR_ESCAPE_CODE;

        case Colours::BLUE:
            return Globals::G_BLUE_ANSI_COLOUR_ESCAPE_CODE + p_input + Globals::G_WHITE_ANSI_COLOUR_ESCAPE_CODE;

        case Colours::GREEN:
            return Globals::G_GREEN_ANSI_COLOUR_ESCAPE_CODE + p_input + Globals::G_WHITE_ANSI_COLOUR_ESCAPE_CODE;

        case Colours::YELLOW:
            return Globals::G_YELLOW_ANSI_COLOUR_ESCAPE_CODE + p_input + Globals::G_WHITE_ANSI_COLOUR_ESCAPE_CODE;

        default:
            return p_input; // Text is already white
        }
    }

    std::string PageBuilder::RemoveColour(const std::string& p_input)
    {
        std::string output = p_input;

        for (const std::string& currentAnsiColourEscapeCode : Globals::G_ALL_ANSI_COLOUR_ESCAPE_CODES)
            output = RemoveSubString(output, currentAnsiColourEscapeCode);

        return output;
    }

    std::string PageBuilder::GetEmptyLine() const
    {
        std::string output;
        output += Globals::G_VERTICAL_LINE;

        output.insert(output.size(), m_maximumFilledLineSize, ' ');

        return output + Globals::G_VERTICAL_LINE + "\n";
    }

    std::string PageBuilder::GetNewLineCentred(const std::string& p_input, const Colours& p_colour, const std::string& p_selector) const
    {
        static const double DIVISOR = 2;

        // ANSI colour escape codes when within a string take up *** characters but visually have zero width. Thus, exclude them
        // from all padding calculations.
        const std::string INPUT_WITH_SELECTOR = p_selector.empty() ? p_input : p_selector + " " + p_input;
        const uint32_t INPUT_WITH_SELECTOR_ANSI_COLOUR_ESCAPE_CODE_COUNT = Globals::ImplementStdCount(INPUT_WITH_SELECTOR.begin(), INPUT_WITH_SELECTOR.end(), Globals::G_ANSI_COLOUR_ESCAPE_CODE_START);
        const uint32_t INPUT_WITH_SELECTOR_SIZE = static_cast<uint32_t>(INPUT_WITH_SELECTOR.size()) - (INPUT_WITH_SELECTOR_ANSI_COLOUR_ESCAPE_CODE_COUNT * Globals::G_ANSI_COLOUR_ESCAPE_CODE_SIZE);

        const uint32_t SELECTOR_ANSI_COLOUR_ESCAPE_CODE_COUNT = Globals::ImplementStdCount(p_selector.begin(), p_selector.end(), Globals::G_ANSI_COLOUR_ESCAPE_CODE_START);
        const uint32_t SELECTOR_SIZE = static_cast<uint32_t>(p_selector.size()) - (SELECTOR_ANSI_COLOUR_ESCAPE_CODE_COUNT * Globals::G_ANSI_COLOUR_ESCAPE_CODE_SIZE);

        const std::string INPUT_TRIMMED = INPUT_WITH_SELECTOR_SIZE > m_maximumInputSize ? INPUT_WITH_SELECTOR.substr(0, m_maximumInputSize) : INPUT_WITH_SELECTOR;
        const uint32_t INPUT_TRIMMED_SIZE = static_cast<uint32_t>(INPUT_TRIMMED.size()) - (INPUT_WITH_SELECTOR_ANSI_COLOUR_ESCAPE_CODE_COUNT * Globals::G_ANSI_COLOUR_ESCAPE_CODE_SIZE);

        const uint32_t LEFT_PADDING_SIZE = static_cast<uint32_t>(ceil(static_cast<double>(m_maximumInputSize - (INPUT_TRIMMED_SIZE - SELECTOR_SIZE)) / DIVISOR) - SELECTOR_SIZE);
        const uint32_t RIGHT_PADDING_SIZE = static_cast<uint32_t>(floor(static_cast<double>(m_maximumInputSize - (INPUT_TRIMMED_SIZE - SELECTOR_SIZE)) / DIVISOR));

        std::string output;
        output += Globals::G_VERTICAL_LINE;
        output.insert(output.size(), Globals::G_MINIMUM_LEFT_PADDING_SIZE + LEFT_PADDING_SIZE, ' ');
        output += AddColour(INPUT_TRIMMED, p_colour);
        output.insert(output.size(), RIGHT_PADDING_SIZE + Globals::G_MINIMUM_RIGHT_PADDING_SIZE, ' ');

        return output + Globals::G_VERTICAL_LINE + "\n";
    }

    std::string PageBuilder::GetNewLineLeftJustified(const std::string& p_input, const Colours& p_colour, const std::string& p_selector) const
    {
        const std::string INPUT = p_selector.empty() ? p_input : p_selector + " " + p_input;

        // ANSI colour escape codes when within a string take up *** characters but visually have zero width. Thus, exclude them
        // from all padding calculations.
        const uint32_t ANSI_COLOUR_ESCAPE_CODE_COUNT = Globals::ImplementStdCount(INPUT.begin(), INPUT.end(), Globals::G_ANSI_COLOUR_ESCAPE_CODE_START);
        const uint32_t INPUT_SIZE = static_cast<uint32_t>(INPUT.size()) - (ANSI_COLOUR_ESCAPE_CODE_COUNT * Globals::G_ANSI_COLOUR_ESCAPE_CODE_SIZE);

        std::string output;
        output += Globals::G_VERTICAL_LINE;
        output.insert(output.size(), Globals::G_MINIMUM_LEFT_PADDING_SIZE, ' ');

        if (INPUT_SIZE > m_maximumInputSize)
        {
            output += AddColour(INPUT.substr(0, m_maximumInputSize), p_colour);
            output.insert(output.size(), Globals::G_MINIMUM_RIGHT_PADDING_SIZE, ' ');
        }

        else
        {
            output += AddColour(INPUT, p_colour);
            output.insert(output.size(), m_maximumInputSize + Globals::G_MINIMUM_RIGHT_PADDING_SIZE - INPUT_SIZE, ' ');
        }

        return output + Globals::G_VERTICAL_LINE + "\n";
    }

    std::string PageBuilder::GetTopLine() const
    {
        std::string output;
        output += Globals::G_TOP_LEFT_CORNER;

        output.insert(output.size(), m_maximumFilledLineSize, Globals::G_HORIZONTAL_LINE);

        return output + Globals::G_TOP_RIGHT_CORNER + "\n";
    }

    std::string PageBuilder::GetBottomLine() const
    {
        std::string output;
        output += Globals::G_BOTTOM_LEFT_CORNER;

        output.insert(output.size(), m_maximumFilledLineSize, Globals::G_HORIZONTAL_LINE);

        return output + Globals::G_BOTTOM_RIGHT_CORNER + "\n";
    }

    std::string PageBuilder::GetTopBox() const
    {
        return Globals::G_WHITE_ANSI_COLOUR_ESCAPE_CODE + GetTopLine() + GetNewLineCentred(m_topTitle, Colours::RED) + GetBottomLine();
    }

    std::string PageBuilder::GetBottomBox() const
    {
        // Globals::G_RESET_ANSI_COLOUR_ESCAPE_CODE used to unset any ANSI colour escape code. If the program unexpectedly crashes the
        // user's terminal will not be affected.
        return GetTopLine() + GetNewLineCentred(m_bottomTitle, Colours::RED) + GetBottomLine() + Globals::G_RESET_ANSI_COLOUR_ESCAPE_CODE;
    }

    std::string PageBuilder::GetRemainingEmptyLines(const std::string& p_commonTopString, const std::string& p_commonBottomString) const
    {
        const int32_t REMAINING_LINE_COUNT = static_cast<int32_t>(m_displayHeight) - Globals::ImplementStdCount(p_commonTopString.begin(), p_commonTopString.end(), '\n') - Globals::ImplementStdCount(p_commonBottomString.begin(), p_commonBottomString.end(), '\n');
        const uint32_t EMPTY_LINES_TO_ADD_COUNT = REMAINING_LINE_COUNT < 0 ? 0 : REMAINING_LINE_COUNT;

        std::string output;
        for (uint32_t i = 0; i < EMPTY_LINES_TO_ADD_COUNT; i++)
            output += GetEmptyLine();

        return output;
    }

    std::vector<std::string> PageBuilder::GetGameOptionSelectionPages(const GameInfo& p_gameInfo, const std::string& p_message, const std::vector<std::string>& p_options) const
    {
        const std::string COMMON_TOP_STRING = GetTopBox() + GetTopLine() + GetGeneralGameSubPage(p_gameInfo) + GetEmptyLine() + GetNewLineLeftJustified(p_message);
        const std::string COMMON_BOTTOM_STRING = GetBottomLine() + GetBottomBox();

        return GetGeneralOptionSelectionPages(p_options, COMMON_TOP_STRING, COMMON_BOTTOM_STRING, false, false);
    }

    std::vector<std::string> PageBuilder::GetGeneralOptionSelectionPages(
        const std::vector<std::string>& p_options,
        const std::string& p_commonTopString,
        const std::string& p_commonBottomString,
        const bool& p_addEmptyLineBetweenOptions,
        const bool& p_centerOptions) const
    {
        std::vector<std::string> output(p_options.size());

        // Construct a page for each option selected.
        for (uint32_t i = 0; i < p_options.size(); i++)
        {
            std::string currentTopString = p_commonTopString;

            for (uint32_t j = 0; j < p_options.size(); j++)
            {
                if (i == j)
                    if (p_centerOptions)
                        currentTopString += GetNewLineCentred(p_options[j], Colours::BLUE, Globals::G_SELECTOR);
                    else
                        currentTopString += GetNewLineLeftJustified(p_options[j], Colours::BLUE, Globals::G_SELECTOR);

                else if (p_centerOptions)
                    currentTopString += GetNewLineCentred(p_options[j]);
                else
                    currentTopString += GetNewLineLeftJustified(std::string(Globals::G_SELECTOR.size() + 1, ' ') + p_options[j]);

                if (p_addEmptyLineBetweenOptions)
                    if (j != p_options.size() - 1) // Don't add extra line on the last option.
                        currentTopString += GetEmptyLine();
            }

            output[i] = currentTopString;
            output[i] += GetRemainingEmptyLines(currentTopString, p_commonBottomString) + p_commonBottomString;
        }

        return output;
    }

    std::string PageBuilder::GetGeneralGameSubPage(const GameInfo& p_gameInfo) const
    {
        switch (m_currentPage)
        {
        case Pages::TICTACTOE:
            return GetTicTacToeSubPage(p_gameInfo);

        case Pages::HANGMAN:
            return GetHangmanSubPage(p_gameInfo);

        case Pages::BATTLESHIPS:
            return GetBattleshipsSubPage(p_gameInfo);

        default:
            return "The 'GetGeneralGameDisplay' function does not support the current page type.";
        }
    }

    // NOLINTBEGIN
    std::string PageBuilder::GetTicTacToeSubPage(const GameInfo& gameInfo) const
    {
        const std::array<std::array<std::string, Globals::G_TICTACTOE_BOARD_WIDTH>, Globals::G_TICTACTOE_BOARD_HEIGHT> gameGrid = gameInfo.m_ticTacToeGameInfo.m_gameGrid;
        const std::string playerCount = gameInfo.m_ticTacToeGameInfo.m_playerCount, computerSpeedName = gameInfo.m_ticTacToeGameInfo.m_computerSpeedName;

        std::string output;

        output += GetNewLineLeftJustified(gameGrid[0][0] + char(179) + gameGrid[0][1] + char(179) + gameGrid[0][2]);

        output += GetNewLineLeftJustified(std::string("") + (char)196 + (char)196 + (char)196 + (char)197 + (char)196 + (char)196 + (char)196 + char(197) + (char)196 + (char)196 + (char)196 + "         # of Players = " + playerCount);

        output += GetNewLineLeftJustified(gameGrid[1][0] + char(179) + gameGrid[1][1] + char(179) + gameGrid[1][2]);

        output += GetNewLineLeftJustified(std::string("") + (char)196 + (char)196 + (char)196 + (char)197 + (char)196 + (char)196 + (char)196 + char(197) + (char)196 + (char)196 + (char)196 + "        Computer Speed = " + computerSpeedName);

        output += GetNewLineLeftJustified(gameGrid[2][0] + char(179) + gameGrid[2][1] + char(179) + gameGrid[2][2]);

        return output;
    }

    std::string PageBuilder::GetHangmanSubPage(const GameInfo& gameInfo) const
    {
        const std::vector<char> incorrectGuesses = gameInfo.m_hangmanGameInfo.m_incorrectGuesses;
        const std::string currentGuessOfWord = gameInfo.m_hangmanGameInfo.m_currentGuessOfWord, wordToBeGuessed = gameInfo.m_hangmanGameInfo.m_wordToBeGuessed, playerCount = gameInfo.m_hangmanGameInfo.m_playerCount, computerSpeedName = gameInfo.m_hangmanGameInfo.m_computerSpeedName;
        const uint32_t errorCount = gameInfo.m_hangmanGameInfo.m_errorCount;

        std::string output;

        // Hangman State
        if (errorCount == 0)
            output += GetEmptyLine() + GetEmptyLine() + GetNewLineLeftJustified("                   # of Players = " + playerCount) + GetEmptyLine() + GetNewLineLeftJustified("                   Computer Speed = " + computerSpeedName) + GetEmptyLine() + GetEmptyLine();
        else if (errorCount == 1)
            output += GetEmptyLine() + GetNewLineLeftJustified("                                          Incorrect Guesses") + GetNewLineLeftJustified("                   # of Players = " + playerCount) + GetNewLineLeftJustified(std::string("                                          ") + incorrectGuesses[0]) + GetNewLineLeftJustified("                   Computer Speed = " + computerSpeedName) + GetEmptyLine() + GetNewLineLeftJustified(std::string(" ") + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196);
        else if (errorCount == 2)
            output += GetEmptyLine() + GetNewLineLeftJustified(std::string("     ") + (char)179 + "                                    Incorrect Guesses") + GetNewLineLeftJustified(std::string("     ") + (char)179 + "             # of Players = " + playerCount) + GetNewLineLeftJustified(std::string("     ") + (char)179 + "                                    " + incorrectGuesses[0] + "   " + incorrectGuesses[1]) + GetNewLineLeftJustified(std::string("     ") + (char)179 + "             Computer Speed = " + computerSpeedName) + GetNewLineLeftJustified(std::string("     ") + (char)179) + GetNewLineLeftJustified(std::string(" ") + (char)196 + (char)196 + (char)196 + (char)196 + (char)193 + (char)196 + (char)196 + (char)196 + (char)196);
        else if (errorCount == 3)
            output += GetNewLineLeftJustified(std::string("     ") + (char)218 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196) + GetNewLineLeftJustified(std::string("     ") + (char)179 + "                                    Incorrect Guesses") + GetNewLineLeftJustified(std::string("     ") + (char)179 + "             # of Players = " + playerCount) + GetNewLineLeftJustified(std::string("     ") + (char)179 + "                                    " + incorrectGuesses[0] + "   " + incorrectGuesses[1] + "   " + incorrectGuesses[2]) + GetNewLineLeftJustified(std::string("     ") + (char)179 + "             Computer Speed = " + computerSpeedName) + GetNewLineLeftJustified(std::string("     ") + (char)179) + GetNewLineLeftJustified(std::string(" ") + (char)196 + (char)196 + (char)196 + (char)196 + (char)193 + (char)196 + (char)196 + (char)196 + (char)196);
        else if (errorCount == 4)
            output += GetNewLineLeftJustified(std::string("     ") + (char)218 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)191) + GetNewLineLeftJustified(std::string("     ") + (char)179 + "       " + (char)179 + "                            Incorrect Guesses") + GetNewLineLeftJustified(std::string("     ") + (char)179 + "             # of Players = " + playerCount) + GetNewLineLeftJustified(std::string("     ") + (char)179 + "                                    " + incorrectGuesses[0] + "   " + incorrectGuesses[1] + "   " + incorrectGuesses[2] + "   " + incorrectGuesses[3]) + GetNewLineLeftJustified(std::string("     ") + (char)179 + "             Computer Speed = " + computerSpeedName) + GetNewLineLeftJustified(std::string("     ") + (char)179) + GetNewLineLeftJustified(std::string(" ") + (char)196 + (char)196 + (char)196 + (char)196 + (char)193 + (char)196 + (char)196 + (char)196 + (char)196);
        else if (errorCount == 5)
            output += GetNewLineLeftJustified(std::string("     ") + (char)218 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)191) + GetNewLineLeftJustified(std::string("     ") + (char)179 + "       " + (char)179 + "                            Incorrect Guesses") + GetNewLineLeftJustified(std::string("     ") + (char)179 + "       O     # of Players = " + playerCount) + GetNewLineLeftJustified(std::string("     ") + (char)179 + "                                    " + incorrectGuesses[0] + "   " + incorrectGuesses[1] + "   " + incorrectGuesses[2] + "   " + incorrectGuesses[3] + "   " + incorrectGuesses[4]) + GetNewLineLeftJustified(std::string("     ") + (char)179 + "             Computer Speed = " + computerSpeedName + "                       ") + GetNewLineLeftJustified(std::string("     ") + (char)179) + GetNewLineLeftJustified(std::string(" ") + (char)196 + (char)196 + (char)196 + (char)196 + (char)193 + (char)196 + (char)196 + (char)196 + (char)196);
        else if (errorCount == 6)
            output += GetNewLineLeftJustified(std::string("     ") + (char)218 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)191) + GetNewLineLeftJustified(std::string("     ") + (char)179 + "       " + (char)179 + "                            Incorrect Guesses") + GetNewLineLeftJustified(std::string("     ") + (char)179 + "       O     # of Players = " + playerCount) + GetNewLineLeftJustified(std::string("     ") + (char)179 + "       " + (char)179 + "                            " + incorrectGuesses[0] + "   " + incorrectGuesses[1] + "   " + incorrectGuesses[2] + "   " + incorrectGuesses[3] + "   " + incorrectGuesses[4]) + GetNewLineLeftJustified(std::string("     ") + (char)179 + "             Computer Speed = " + computerSpeedName) + GetNewLineLeftJustified(std::string("     ") + (char)179 + "                                    " + incorrectGuesses[5]) + GetNewLineLeftJustified(std::string(" ") + (char)196 + (char)196 + (char)196 + (char)196 + (char)193 + (char)196 + (char)196 + (char)196 + (char)196);
        else if (errorCount == 7)
            output += GetNewLineLeftJustified(std::string("     ") + (char)218 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)191) + GetNewLineLeftJustified(std::string("     ") + (char)179 + "       " + (char)179 + "                            Incorrect Guesses") + GetNewLineLeftJustified(std::string("     ") + (char)179 + "       O     # of Players = " + playerCount) + GetNewLineLeftJustified(std::string("     ") + (char)179 + "       " + (char)179 + "                            " + incorrectGuesses[0] + "   " + incorrectGuesses[1] + "   " + incorrectGuesses[2] + "   " + incorrectGuesses[3] + "   " + incorrectGuesses[4]) + GetNewLineLeftJustified(std::string("     ") + (char)179 + "      /      Computer Speed = " + computerSpeedName) + GetNewLineLeftJustified(std::string("     ") + (char)179 + "                                    " + incorrectGuesses[5] + "   " + incorrectGuesses[6]) + GetNewLineLeftJustified(std::string(" ") + (char)196 + (char)196 + (char)196 + (char)196 + (char)193 + (char)196 + (char)196 + (char)196 + (char)196);
        else if (errorCount == 8)
            output += GetNewLineLeftJustified(std::string("     ") + (char)218 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)191) + GetNewLineLeftJustified(std::string("     ") + (char)179 + "       " + (char)179 + "                            Incorrect Guesses") + GetNewLineLeftJustified(std::string("     ") + (char)179 + "       O     # of Players = " + playerCount) + GetNewLineLeftJustified(std::string("     ") + (char)179 + "       " + (char)179 + "                            " + incorrectGuesses[0] + "   " + incorrectGuesses[1] + "   " + incorrectGuesses[2] + "   " + incorrectGuesses[3] + "   " + incorrectGuesses[4]) + GetNewLineLeftJustified(std::string("     ") + (char)179 + "      / \\    Computer Speed = " + computerSpeedName) + GetNewLineLeftJustified(std::string("     ") + (char)179 + "                                    " + incorrectGuesses[5] + "   " + incorrectGuesses[6] + "   " + incorrectGuesses[7]) + GetNewLineLeftJustified(std::string(" ") + (char)196 + (char)196 + (char)196 + (char)196 + (char)193 + (char)196 + (char)196 + (char)196 + (char)196);
        else if (errorCount == 9)
            output += GetNewLineLeftJustified(std::string("     ") + (char)218 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)191) + GetNewLineLeftJustified(std::string("     ") + (char)179 + "       " + (char)179 + "                            Incorrect Guesses") + GetNewLineLeftJustified(std::string("     ") + (char)179 + "       O     # of Players = " + playerCount) + GetNewLineLeftJustified(std::string("     ") + (char)179 + "      /" + (char)179 + "                            " + incorrectGuesses[0] + "   " + incorrectGuesses[1] + "   " + incorrectGuesses[2] + "   " + incorrectGuesses[3] + "   " + incorrectGuesses[4]) + GetNewLineLeftJustified(std::string("     ") + (char)179 + "      / \\    Computer Speed = " + computerSpeedName) + GetNewLineLeftJustified(std::string("     ") + (char)179 + "                                    " + incorrectGuesses[5] + "   " + incorrectGuesses[6] + "   " + incorrectGuesses[7] + "   " + incorrectGuesses[8]) + GetNewLineLeftJustified(std::string(" ") + (char)196 + (char)196 + (char)196 + (char)196 + (char)193 + (char)196 + (char)196 + (char)196 + (char)196);
        else if (errorCount == 10)
            output += GetNewLineLeftJustified(std::string("     ") + (char)218 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)191) + GetNewLineLeftJustified(std::string("     ") + (char)179 + "       " + (char)179 + "                            Incorrect Guesses") + GetNewLineLeftJustified(std::string("     ") + (char)179 + "       O     # of Players = " + playerCount) + GetNewLineLeftJustified(std::string("     ") + (char)179 + "      /" + (char)179 + "\\                           " + incorrectGuesses[0] + "   " + incorrectGuesses[1] + "   " + incorrectGuesses[2] + "   " + incorrectGuesses[3] + "   " + incorrectGuesses[4]) + GetNewLineLeftJustified(std::string("     ") + (char)179 + "      / \\    Computer Speed = " + computerSpeedName) + GetNewLineLeftJustified(std::string("     ") + (char)179 + "                                    " + incorrectGuesses[5] + "   " + incorrectGuesses[6] + "   " + incorrectGuesses[7] + "   " + incorrectGuesses[8] + "   " + incorrectGuesses[9]) + GetNewLineLeftJustified(std::string(" ") + (char)196 + (char)196 + (char)196 + (char)196 + (char)193 + (char)196 + (char)196 + (char)196 + (char)196);

        // Word to be guessed, and thus current guess of word, are limited to a size in between 3 and 14
        output += (char)186;

        for (char i : currentGuessOfWord)
            output += std::string(" ") + i;

        if (errorCount == 10) // show what the word to be guessed was
        {
            output += "   (The word was " + wordToBeGuessed + ")";
            output.insert(output.size(), (62 - 18 - wordToBeGuessed.size() * 3), ' ');
        }

        else // do not show it
            output.insert(output.size(), (62 - wordToBeGuessed.size() * 2), ' ');

        output += (char)186;

        return output + "\n";
    }

    std::string PageBuilder::GetBattleshipsSubPage(const GameInfo& gameInfo) const
    {
        const std::array<std::array<std::string, 10>, 10> boardOne = gameInfo.m_battleshipsGameInfo.m_boardOne, boardTwo = gameInfo.m_battleshipsGameInfo.m_boardTwo;
        const std::unordered_map<std::string, uint32_t> shipsRemainingOne = gameInfo.m_battleshipsGameInfo.m_shipsRemainingOne, shipsRemainingTwo = gameInfo.m_battleshipsGameInfo.m_shipsRemainingTwo;
        const std::string playerCount = gameInfo.m_battleshipsGameInfo.m_playerCount, computerSpeedName = gameInfo.m_battleshipsGameInfo.m_computerSpeedName;
        const bool isGameOver = gameInfo.m_battleshipsGameInfo.m_isGameOver;

        std::string output;

        // Top row and letter co-ordinates of both boards
        output += GetNewLineLeftJustified("                    Player One                                                                                       Player Two");

        output += (char)186 + std::string("   ");
        for (uint32_t i = 0; i < 2; i++)
        {
            output += (char)218;
            output.insert(output.size(), 3, (char)196);
            for (uint32_t j = 0; j < 10; j++)
            {
                output += (char)194;
                output.insert(output.size(), 3, (char)196);
            }
            output += (char)191;

            if (i == 0)
                output.insert(output.size(), "                                                   ");
        }
        output += std::string("   ") + (char)186 + "\n";

        output += (char)186 + std::string("   ");
        for (uint32_t i = 0; i < 2; i++)
        {
            output += (char)179 + std::string("   ") + (char)179 + " A " + (char)179 + " B " + (char)179 + " C " + (char)179 + " D " + (char)179 + " E " + (char)179 + " F " + (char)179 + " G " + (char)179 + " H " + (char)179 + " I " + (char)179 + " J " + (char)179;

            if (i == 0)
                output += "                                                   ";
        }
        output += std::string("   ") + (char)186 + "\n";

        // Main parts of both boards and centre information
        for (uint32_t i = 0; i < 10; i++)
        {
            // First Line
            // Left outer box edge
            output += (char)186 + std::string("   ");

            // Player One Board horizontal dividers
            output += (char)195;
            output.insert(output.size(), 3, (char)196);
            for (uint32_t j = 0; j < 10; j++)
            {
                output += (char)197;
                output.insert(output.size(), 3, (char)196);
            }
            output += (char)180;

            // Centre information
            if (i == 3)
                output += "   Carrier                               Carrier   ";
            else if (i == 5) // Battleship
            {
                output += "   ";
                for (uint32_t j = 0; j < 4; j++, output += " ")
                {
                    if (j < shipsRemainingOne.at(Globals::G_BATTLESHIPS_BATTLESHIP_NAME))
                        output.insert(output.size(), 3, (char)178);
                    else
                        output.insert(output.size(), 3, (char)176);
                }
                output += "              ";
                for (uint32_t j = 0; j < 4; j++, output += " ")
                {
                    if (j < (4 - shipsRemainingTwo.at(Globals::G_BATTLESHIPS_BATTLESHIP_NAME)))
                        output.insert(output.size(), 3, (char)176);
                    else
                        output.insert(output.size(), 3, (char)178);
                }
                output += "  ";
            }
            else if (i == 6)
                output += "   Destroyer                           Destroyer   ";
            else if (i == 8) // Submarine
            {
                output += "   ";
                for (uint32_t j = 0; j < 3; j++, output += " ")
                {
                    if (j < shipsRemainingOne.at(Globals::G_BATTLESHIPS_SUBMARINE_NAME))
                        output.insert(output.size(), 3, (char)178);
                    else
                        output.insert(output.size(), 3, (char)176);
                }
                output += "                      ";
                for (uint32_t j = 0; j < 3; j++, output += " ")
                {
                    if (j < (3 - shipsRemainingTwo.at(Globals::G_BATTLESHIPS_SUBMARINE_NAME)))
                        output.insert(output.size(), 3, (char)176);
                    else
                        output.insert(output.size(), 3, (char)178);
                }
                output += "  ";
            }
            else if (i == 9)
                output += "   Patrol Boat                       Patrol Boat   ";
            else
                output += "                                                   ";

            // Player Two Board horizontal dividers
            output += (char)195;
            output.insert(output.size(), 3, (char)196);
            for (uint32_t j = 0; j < 10; j++)
            {
                output += (char)197;
                output.insert(output.size(), 3, (char)196);
            }
            output += (char)180 + std::string("   ") + (char)186 + "\n";

            // Second Line
            // Player one left outer box edge and number co-ord
            output += (char)186 + std::string("   ") + (char)179 + " " + std::to_string(i) + " " + (char)179;

            // Player One board ships (always shown)
            for (uint32_t j = 0; j < 10; j++)
            {
                output += boardOne[i][j];

                output += (char)179;
            }

            // Centre Information
            if (i == 0)
                output += "                 # of Players = " + playerCount + "                ";
            else if (i == 1)
                output += "                 Computer Speed = " + computerSpeedName + "                ";
            else if (i == 3) // Carrier
            {
                output += "   ";
                for (uint32_t j = 0; j < 5; j++, output += " ")
                {
                    if (j < shipsRemainingOne.at(Globals::G_BATTLESHIPS_CARRIER_NAME))
                        output.insert(output.size(), 3, (char)178);
                    else
                        output.insert(output.size(), 3, (char)176);
                }
                output += "      ";
                for (uint32_t j = 0; j < 5; j++, output += " ")
                {
                    if (j < (5 - shipsRemainingTwo.at(Globals::G_BATTLESHIPS_CARRIER_NAME)))
                        output.insert(output.size(), 3, (char)176);
                    else
                        output.insert(output.size(), 3, (char)178);
                }
                output += "  ";
            }
            else if (i == 4)
                output += "   Battleship                         Battleship   ";
            else if (i == 6) // Destroyer
            {
                output += "   ";
                for (uint32_t j = 0; j < 3; j++, output += " ")
                {
                    if (j < shipsRemainingOne.at(Globals::G_BATTLESHIPS_DESTROYER_NAME))
                        output.insert(output.size(), 3, (char)178);
                    else
                        output.insert(output.size(), 3, (char)176);
                }
                output += "                      ";
                for (uint32_t j = 0; j < 3; j++, output += " ")
                {
                    if (j < (3 - shipsRemainingTwo.at(Globals::G_BATTLESHIPS_DESTROYER_NAME)))
                        output.insert(output.size(), 3, (char)176);
                    else
                        output.insert(output.size(), 3, (char)178);
                }
                output += "  ";
            }
            else if (i == 7)
                output += "   Submarine                           Submarine   ";
            else if (i == 9) // Patrol Boat
            {
                output += "   ";
                for (uint32_t j = 0; j < 2; j++, output += " ")
                {
                    if (j < shipsRemainingOne.at(Globals::G_BATTLESHIPS_PATROL_BOAT_NAME))
                        output.insert(output.size(), 3, (char)178);
                    else
                        output.insert(output.size(), 3, (char)176);
                }
                output += "                              ";
                for (uint32_t j = 0; j < 2; j++, output += " ")
                {
                    if (j < (2 - shipsRemainingTwo.at(Globals::G_BATTLESHIPS_PATROL_BOAT_NAME)))
                        output.insert(output.size(), 3, (char)176);
                    else
                        output.insert(output.size(), 3, (char)178);
                }
                output += "  ";
            }
            else
                output += "                                                   ";

            // Player Two left outer box edge and number co-ord
            output += (char)179 + std::string(" ") + std::to_string(i) + " " + (char)179;

            // Player Two board ships
            for (uint32_t j = 0; j < 10; j++)
            {
                if (isGameOver || playerCount == "0  ")
                {
                    output += boardTwo[i][j];
                }

                else if (boardTwo[i][j].find(Globals::G_BATTLESHIPS_SUCCESSFUL_ATTACK) != std::string::npos)
                {
                    if (boardTwo[i][j].find('#') != std::string::npos)
                    {
                        output += '#' + boardTwo[i][j][1] + "#";
                    }

                    else
                    {
                        output.insert(output.size(), 3, (char)176);
                    }
                }

                else if (boardTwo[i][j].find(Globals::G_BATTLESHIPS_MISSED_ATTACK) != std::string::npos)
                {
                    if (boardTwo[i][j].find('#') != std::string::npos)
                    {
                    }

                    else
                    {
                        output += std::string(" ") + (char)250 + " ";
                    }
                }

                else if (boardTwo[i][j].find('#') != std::string::npos)
                    output += boardTwo[i][j];
                else
                    output += "   ";

                output += (char)179;
            }
            output += std::string("   ") + (char)186 + "\n";
        }

        // Bottom row of both boards
        output += (char)186 + std::string("   ");
        for (uint32_t i = 0; i < 2; i++)
        {
            output += (char)192;
            output.insert(output.size(), 3, (char)196);
            for (uint32_t j = 0; j < 10; j++)
            {
                output += (char)193;
                output.insert(output.size(), 3, (char)196);
            }
            output += (char)217;

            if (i == 0)
                output += "                                                   ";
        }

        output += std::string("   ") + (char)186 + "\n";

        return output;
    }

    std::string PageBuilder::RemoveSubString(const std::string& p_string, const std::string& p_subString) // NOLINT(bugprone-easily-swappable-parameters)
    {
        const uint32_t SUB_STRING_LENGTH = p_subString.length();

        std::string output = p_string;
        for (std::string::size_type i = output.find(p_subString); i != std::string::npos; i = output.find(p_subString))
            output.erase(i, SUB_STRING_LENGTH);

        return output;
    }

    // NOLINTEND
}
