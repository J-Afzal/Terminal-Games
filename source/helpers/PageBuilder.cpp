#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <string>
#include <vector>

#include "helpers/GameInformation.hpp"
#include "helpers/Globals.hpp"

#include "helpers/PageBuilder.hpp"

namespace TerminalGames
{
    PageBuilder::PageBuilder() :
        m_pageWidth(0),
        m_pageHeight(0),
        m_lineMaximumCharacterCount(0),
        m_minimumLeftPadding(0),
        m_minimumRightPadding(0),
        m_useAnsiEscapeCodes(false),
        m_currentPage(Pages::DEFAULT) {}

    PageBuilder::PageBuilder(const Pages& p_page, const bool& p_useAnsiEscapeCodes) :
        m_pageWidth(0),
        m_pageHeight(0),
        m_lineMaximumCharacterCount(0),
        m_minimumLeftPadding(0),
        m_minimumRightPadding(0),
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
            m_pageWidth = Globals::G_HOMEPAGE_DISPLAY_WIDTH;
            m_pageHeight = Globals::G_HOMEPAGE_DISPLAY_HEIGHT;
            break;

        case Pages::MAINMENU:
            m_topTitle = Globals::G_MAIN_MENU_TOP_TITLE;
            m_bottomTitle = Globals::G_MAIN_MENU_BOTTOM_TITLE;
            m_pageWidth = Globals::G_MAIN_MENU_DISPLAY_WIDTH;
            m_pageHeight = Globals::G_MAIN_MENU_DISPLAY_HEIGHT;
            break;

        case Pages::TICTACTOE:
            m_topTitle = Globals::G_TICTACTOE_TOP_TITLE;
            m_bottomTitle = Globals::G_TICTACTOE_BOTTOM_TITLE;
            m_pageWidth = Globals::G_TICTACTOE_DISPLAY_WIDTH;
            m_pageHeight = Globals::G_TICTACTOE_DISPLAY_HEIGHT;
            break;

        case Pages::HANGMAN:
            m_topTitle = Globals::G_HANGMAN_TOP_TITLE;
            m_bottomTitle = Globals::G_HANGMAN_BOTTOM_TITLE;
            m_pageWidth = Globals::G_HANGMAN_DISPLAY_WIDTH;
            m_pageHeight = Globals::G_HANGMAN_DISPLAY_HEIGHT;
            break;

        case Pages::BATTLESHIPS:
            m_topTitle = Globals::G_BATTLESHIPS_TOP_TITLE;
            m_bottomTitle = Globals::G_BATTLESHIPS_BOTTOM_TITLE;
            m_pageWidth = Globals::G_BATTLESHIPS_DISPLAY_WIDTH;
            m_pageHeight = Globals::G_BATTLESHIPS_DISPLAY_HEIGHT;
            break;

        default:
            throw Globals::Exceptions::NotImplementedError();
        }

        m_minimumLeftPadding = Globals::G_PAGE_MINIMUM_LEFT_PADDING_SIZE;
        m_minimumRightPadding = Globals::G_PAGE_MINIMUM_RIGHT_PADDING_SIZE;
        m_lineMaximumCharacterCount = m_pageWidth - Globals::G_PAGE_MINIMUM_LEFT_VERTICAL_LINE_SIZE - m_minimumLeftPadding - m_minimumRightPadding - Globals::G_PAGE_MINIMUM_RIGHT_VERTICAL_LINE_SIZE;
    }

    Pages PageBuilder::GetCurrentPageType() const
    {
        return m_currentPage;
    }

    std::vector<std::string> PageBuilder::GetOptionSelectionHomepages()
    {
        std::vector<std::string> output(Globals::G_GAME_TWO_OPTIONS);

        const bool OLD_USE_ANSI_ESCAPE_CODES = m_useAnsiEscapeCodes;
        m_useAnsiEscapeCodes = true;

        if (Globals::G_PLATFORM_IS_WINDOWS)
        {
            const std::string COMMON_TOP_STRING = GetTopBox() + GetTopLine() +
                                                  GetNewLineCentred("Platform: " + AddColour("Windows", Globals::Colours::GREEN)) + GetEmptyLine() +
                                                  GetNewLineCentred("Controls: " + AddColour("Enhanced", Globals::Colours::GREEN)) + GetEmptyLine() +
                                                  GetNewLineCentred("Instructions: Use the arrows keys") + GetNewLineCentred("to navigate and press enter to") + GetNewLineCentred("confirm a selection.") +
                                                  GetEmptyLine() + GetEmptyLine() + GetNewLineLeftJustified("Use ANSI colour escape codes?");

            const std::string COMMON_BOTTOM_STRING = GetBottomLine() + GetBottomBox();

            output[0] = COMMON_TOP_STRING + GetNewLineLeftJustified("Yes", Globals::Colours::BLUE, Globals::G_PAGE_OPTION_SELECTOR) + GetNewLineLeftJustified(Globals::G_PAGE_OPTION_SELECTOR_ABSENT_PADDING + "No") + COMMON_BOTTOM_STRING;

            output[1] = RemoveColour(COMMON_TOP_STRING + GetNewLineLeftJustified(Globals::G_PAGE_OPTION_SELECTOR_ABSENT_PADDING + "Yes") + GetNewLineLeftJustified("No", Globals::Colours::BLUE, Globals::G_PAGE_OPTION_SELECTOR) + COMMON_BOTTOM_STRING);
        }

        else
        {
            const std::string COMMON_TOP_STRING = GetTopBox() + GetTopLine() +
                                                  GetNewLineCentred("Platform: " + AddColour("macOS or Linux", Globals::Colours::GREEN)) + GetEmptyLine() +
                                                  GetNewLineCentred("Controls: " + AddColour("Enhanced", Globals::Colours::GREEN)) + GetEmptyLine() +
                                                  GetNewLineCentred("Instructions: Enter one of the") + GetNewLineCentred("WASD keys to navigate, 'e' to") + GetNewLineCentred("to confirm a selection and 'z' to") + GetNewLineCentred("undo a selection in Battleships.") +
                                                  GetEmptyLine() + GetNewLineLeftJustified("Use ANSI colour escape codes?");

            const std::string COMMON_BOTTOM_STRING = GetBottomLine() + GetBottomBox();

            output[0] = COMMON_TOP_STRING + GetNewLineLeftJustified("Yes", Globals::Colours::BLUE, Globals::G_PAGE_OPTION_SELECTOR) + GetNewLineLeftJustified(Globals::G_PAGE_OPTION_SELECTOR_ABSENT_PADDING + "No") + COMMON_BOTTOM_STRING;

            output[1] = RemoveColour(COMMON_TOP_STRING + GetNewLineLeftJustified(Globals::G_PAGE_OPTION_SELECTOR_ABSENT_PADDING + "Yes") + GetNewLineLeftJustified("No", Globals::Colours::BLUE, Globals::G_PAGE_OPTION_SELECTOR) + COMMON_BOTTOM_STRING);
        }

        m_useAnsiEscapeCodes = OLD_USE_ANSI_ESCAPE_CODES;

        return output;
    }

    std::vector<std::string> PageBuilder::GetGameSelectionMainMenuPages(const std::vector<std::string>& p_gameNames) const
    {
        const std::string COMMON_TOP_STRING = GetTopBox() + GetTopLine();
        const std::string COMMON_BOTTOM_STRING = GetBottomLine() + GetBottomBox();

        return GetGeneralOptionSelectionPages(p_gameNames, COMMON_TOP_STRING, COMMON_BOTTOM_STRING, true, true, true);
    }

    std::vector<std::string> PageBuilder::GetPlayerCountOptionSelectionGamePages(const GameInformation& p_gameInformation)
    {
        switch (m_currentPage)
        {
        case Pages::TICTACTOE:
        case Pages::HANGMAN:
            return GetGameOptionSelectionPages(p_gameInformation, "Please select the number of players:", Globals::G_GAME_MAX_TWO_PLAYERS_OPTIONS);

        case Pages::BATTLESHIPS:
            return GetGameOptionSelectionPages(p_gameInformation, "Please select the number of players:", Globals::G_GAME_MAX_ONE_PLAYER_OPTIONS);

        default:
            return {"The 'GetPlayerCountOptionSelectionGameDisplays' function does not support the current page type."};
        }
    }

    std::vector<std::string> PageBuilder::GetUserPlayerChoiceOptionSelectionGamePages(const GameInformation& p_gameInformation)
    {
        switch (m_currentPage)
        {
        case Pages::TICTACTOE:
            return GetGameOptionSelectionPages(p_gameInformation, "Please select the player you would like to be:", Globals::G_TICTACTOE_PLAYER_CHOICE_OPTIONS);

        case Pages::HANGMAN:
            return GetGameOptionSelectionPages(p_gameInformation, "Please select the player you would like to be:", Globals::G_HANGMAN_PLAYER_CHOICE_OPTIONS);

        default:
            return {"The 'GetUserPlayerChoiceOptionSelectionGameDisplays' function does not support the current page type."};
        }
    }

    std::vector<std::string> PageBuilder::GetComputerSpeedOptionSelectionGamePages(const GameInformation& p_gameInformation)
    {
        switch (m_currentPage)
        {
        case Pages::TICTACTOE:
        case Pages::HANGMAN:
        case Pages::BATTLESHIPS:
            return GetGameOptionSelectionPages(p_gameInformation, "Please select the computer speed:", Globals::G_GAME_COMPUTER_SPEED_OPTIONS);

        default:
            return {"The 'GetComputerSpeedOptionSelectionGameDisplays' function does not support the current page type."};
        }
    }

    std::string PageBuilder::GetPageWithMessage(const GameInformation& p_gameInformation, const std::string& p_message)
    {
        const std::string COMMON_TOP_STRING = GetTopBox() + GetTopLine() + GetGeneralGameSubPage(p_gameInformation) + GetEmptyLine() + GetNewLineLeftJustified(p_message);
        const std::string COMMON_BOTTOM_STRING = GetBottomLine() + GetBottomBox();

        return COMMON_TOP_STRING + GetRemainingEmptyLines(COMMON_TOP_STRING, COMMON_BOTTOM_STRING) + COMMON_BOTTOM_STRING;
    }

    std::string PageBuilder::GetUserCommandPage(const GameInformation& p_gameInformation)
    {
        switch (m_currentPage)
        {
        case Pages::TICTACTOE:
            return GetPageWithMessage(p_gameInformation, p_gameInformation.m_ticTacToeGameInformation.m_currentPlayer + ", please enter your next command!");

        case Pages::HANGMAN:
            return GetPageWithMessage(p_gameInformation, "Guesser, please enter your next guess: " + AddColour(std::string(1, p_gameInformation.m_hangmanGameInformation.m_currentLetterSelected), Globals::Colours::BLUE));

        case Pages::BATTLESHIPS:
            return GetPageWithMessage(p_gameInformation, p_gameInformation.m_battleshipsGameInformation.m_currentPlayer + ", please enter your next command!");

        default:
            return "The 'GetUserCommandGameDisplay' function does not support the current page type.";
        }
    }

    std::string PageBuilder::GetComputerCommandPage(const GameInformation& p_gameInformation)
    {
        switch (m_currentPage)
        {
        case Pages::TICTACTOE:
        case Pages::HANGMAN:
        case Pages::BATTLESHIPS:
            return GetPageWithMessage(p_gameInformation, "The computer is executing their next move!");

        default:
            return "The 'GetComputerSpeedOptionSelectionGameDisplays' function does not support the current page type.";
        }
    }

    std::string PageBuilder::GetGameOverPage(const GameInformation& p_gameInformation)
    {
        std::string topString = GetTopBox() + GetTopLine() + GetGeneralGameSubPage(p_gameInformation) + GetEmptyLine() + GetNewLineCentred("GAME OVER") + GetEmptyLine();
        const std::string BOTTOM_STRING = GetEmptyLine() + GetNewLineCentred("Press 'r' to restart game OR any key to reset game...") + GetBottomLine() + GetBottomBox();

        switch (m_currentPage)
        {
        case Pages::TICTACTOE:
            if (p_gameInformation.m_ticTacToeGameInformation.m_hasWinner) // This game can be drawn unlike the others.
            {
                topString += GetNewLineCentred(p_gameInformation.m_ticTacToeGameInformation.m_currentPlayer + " has won! The game lasted " + std::to_string(p_gameInformation.m_ticTacToeGameInformation.m_turnCount) + " turns.");
            }

            else
            {
                topString += GetNewLineCentred("The game is a draw! The game lasted " + std::to_string(p_gameInformation.m_ticTacToeGameInformation.m_turnCount) + " turns.");
            }
            break;

        case Pages::HANGMAN:
            if (p_gameInformation.m_hangmanGameInformation.m_incorrectGuesses.size() == Globals::G_HANGMAN_MAXIMUM_ERROR_COUNT)
            {
                topString += GetNewLineCentred("The word setter has won! The game lasted " + std::to_string(p_gameInformation.m_hangmanGameInformation.m_turnCount) + " turns!");
            }

            else
            {
                topString += GetNewLineCentred("The guesser has won! The game lasted " + std::to_string(p_gameInformation.m_hangmanGameInformation.m_turnCount) + " turns.");
            }
            break;

        case Pages::BATTLESHIPS:
            topString += GetNewLineCentred(p_gameInformation.m_battleshipsGameInformation.m_currentPlayer + " has won! The game lasted " + std::to_string(p_gameInformation.m_battleshipsGameInformation.m_turnCount) + " turns.");
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
        return GetGeneralOptionSelectionPages(Globals::G_QUIT_MENU_OPTIONS, COMMON_TOP_STRING, COMMON_BOTTOM_STRING, true, true, true);
    }

    std::string PageBuilder::AddColour(const std::string& p_input, const Globals::Colours& p_colour) const
    {
        if (!m_useAnsiEscapeCodes)
        {
            return p_input;
        }

        return Globals::G_PAGE_ANSI_ALL_COLOUR_ESCAPE_CODES.at(static_cast<uint8_t>(p_colour)) + p_input + Globals::G_PAGE_ANSI_WHITE_COLOUR_ESCAPE_CODE;
    }

    std::string PageBuilder::RemoveColour(const std::string& p_input)
    {
        std::string output = p_input;

        for (const std::string& currentAnsiColourEscapeCode : Globals::G_PAGE_ANSI_ALL_COLOUR_ESCAPE_CODES)
        {
            Globals::RemoveSubString(output, currentAnsiColourEscapeCode);
        }

        return output;
    }

    std::string PageBuilder::GetEmptyLine() const
    {
        std::string output;
        output.reserve(m_pageWidth + (2 * Globals::G_PAGE_ANSI_COLOUR_ESCAPE_CODE_SIZE));

        output += Globals::G_PAGE_VERTICAL_LINE;
        output.insert(output.size(), m_lineMaximumCharacterCount + m_minimumLeftPadding + m_minimumRightPadding, ' ');
        return output + Globals::G_PAGE_VERTICAL_LINE + '\n';
    }

    std::string PageBuilder::GetNewLineCentred(const std::string& p_input, const Globals::Colours& p_colour, const std::string& p_selector) const
    {
        static const double DIVISOR = 2;

        // ANSI colour escape codes when within a string take up *** characters but visually have zero width. Thus, exclude them
        // from all padding calculations.
        const std::string INPUT_WITH_SELECTOR = p_selector.empty() ? p_input : p_selector + ' ' + p_input;
        const uint32_t INPUT_WITH_SELECTOR_ANSI_COLOUR_ESCAPE_CODE_COUNT = Globals::ImplementStdCount(INPUT_WITH_SELECTOR.begin(), INPUT_WITH_SELECTOR.end(), Globals::G_PAGE_ANSI_COLOUR_ESCAPE_CODE_START);
        const uint32_t INPUT_WITH_SELECTOR_SIZE = static_cast<uint32_t>(INPUT_WITH_SELECTOR.size()) - (INPUT_WITH_SELECTOR_ANSI_COLOUR_ESCAPE_CODE_COUNT * Globals::G_PAGE_ANSI_COLOUR_ESCAPE_CODE_SIZE);

        const uint32_t SELECTOR_ANSI_COLOUR_ESCAPE_CODE_COUNT = Globals::ImplementStdCount(p_selector.begin(), p_selector.end(), Globals::G_PAGE_ANSI_COLOUR_ESCAPE_CODE_START);
        const uint32_t SELECTOR_SIZE = static_cast<uint32_t>(p_selector.size()) - (SELECTOR_ANSI_COLOUR_ESCAPE_CODE_COUNT * Globals::G_PAGE_ANSI_COLOUR_ESCAPE_CODE_SIZE);

        const std::string INPUT_TRIMMED = INPUT_WITH_SELECTOR_SIZE > m_lineMaximumCharacterCount ? INPUT_WITH_SELECTOR.substr(0, m_lineMaximumCharacterCount) : INPUT_WITH_SELECTOR;
        const uint32_t INPUT_TRIMMED_SIZE = static_cast<uint32_t>(INPUT_TRIMMED.size()) - (INPUT_WITH_SELECTOR_ANSI_COLOUR_ESCAPE_CODE_COUNT * Globals::G_PAGE_ANSI_COLOUR_ESCAPE_CODE_SIZE);

        const uint32_t LEFT_PADDING_SIZE = static_cast<uint32_t>(ceil(static_cast<double>(m_lineMaximumCharacterCount - (INPUT_TRIMMED_SIZE - SELECTOR_SIZE)) / DIVISOR) - SELECTOR_SIZE);
        const uint32_t RIGHT_PADDING_SIZE = static_cast<uint32_t>(floor(static_cast<double>(m_lineMaximumCharacterCount - (INPUT_TRIMMED_SIZE - SELECTOR_SIZE)) / DIVISOR));

        std::string output;
        output.reserve(m_pageWidth + (4 * Globals::G_PAGE_ANSI_COLOUR_ESCAPE_CODE_SIZE));

        output += Globals::G_PAGE_VERTICAL_LINE;
        output.insert(output.size(), m_minimumLeftPadding + LEFT_PADDING_SIZE, ' ');
        output += AddColour(INPUT_TRIMMED, p_colour);
        output.insert(output.size(), RIGHT_PADDING_SIZE + m_minimumRightPadding, ' ');
        return output + Globals::G_PAGE_VERTICAL_LINE + '\n';
    }

    std::string PageBuilder::GetNewLineCentredOptimised(const std::string& p_input) const
    {
        static const double DIVISOR = 2;

        const uint32_t LEFT_PADDING_SIZE = static_cast<uint32_t>(ceil(static_cast<double>(m_lineMaximumCharacterCount - p_input.size()) / DIVISOR));
        const uint32_t RIGHT_PADDING_SIZE = static_cast<uint32_t>(floor(static_cast<double>(m_lineMaximumCharacterCount - p_input.size()) / DIVISOR));

        std::string output;
        output.reserve(m_pageWidth + (2 * Globals::G_PAGE_ANSI_COLOUR_ESCAPE_CODE_SIZE));

        output += Globals::G_PAGE_VERTICAL_LINE;
        output.insert(output.size(), m_minimumLeftPadding + LEFT_PADDING_SIZE, ' ');
        output += p_input;
        output.insert(output.size(), RIGHT_PADDING_SIZE + m_minimumRightPadding, ' ');
        output += Globals::G_PAGE_VERTICAL_LINE;
        output += '\n';
        return output;
    }

    std::string PageBuilder::GetNewLineLeftJustified(const std::string& p_input, const Globals::Colours& p_colour, const std::string& p_selector) const
    {
        const std::string INPUT = p_selector.empty() ? p_input : p_selector + ' ' + p_input;

        // ANSI colour escape codes when within a string take up *** characters but visually have zero width. Thus, exclude them
        // from all padding calculations.
        const uint32_t ANSI_COLOUR_ESCAPE_CODE_COUNT = Globals::ImplementStdCount(INPUT.begin(), INPUT.end(), Globals::G_PAGE_ANSI_COLOUR_ESCAPE_CODE_START);
        const uint32_t INPUT_SIZE = static_cast<uint32_t>(INPUT.size()) - (ANSI_COLOUR_ESCAPE_CODE_COUNT * Globals::G_PAGE_ANSI_COLOUR_ESCAPE_CODE_SIZE);

        std::string output;
        output.reserve(m_pageWidth + (4 * Globals::G_PAGE_ANSI_COLOUR_ESCAPE_CODE_SIZE));

        output += Globals::G_PAGE_VERTICAL_LINE;
        output.insert(output.size(), m_minimumLeftPadding, ' ');

        if (INPUT_SIZE > m_lineMaximumCharacterCount)
        {
            output += AddColour(INPUT.substr(0, m_lineMaximumCharacterCount), p_colour);
            output.insert(output.size(), m_minimumRightPadding, ' ');
        }

        else
        {
            output += AddColour(INPUT, p_colour);
            output.insert(output.size(), m_lineMaximumCharacterCount + m_minimumRightPadding - INPUT_SIZE, ' ');
        }

        return output + Globals::G_PAGE_VERTICAL_LINE + '\n';
    }

    std::string PageBuilder::GetTopLine() const
    {
        std::string output;
        output.reserve(m_pageWidth);

        output += Globals::G_PAGE_TOP_LEFT_CORNER;
        output.insert(output.size(), m_lineMaximumCharacterCount + m_minimumLeftPadding + m_minimumRightPadding, Globals::G_PAGE_HORIZONTAL_LINE);
        return output + Globals::G_PAGE_TOP_RIGHT_CORNER + '\n';
    }

    std::string PageBuilder::GetBottomLine() const
    {
        std::string output;
        output.reserve(m_pageWidth);

        output += Globals::G_PAGE_BOTTOM_LEFT_CORNER;
        output.insert(output.size(), m_lineMaximumCharacterCount + m_minimumLeftPadding + m_minimumRightPadding, Globals::G_PAGE_HORIZONTAL_LINE);
        return output + Globals::G_PAGE_BOTTOM_RIGHT_CORNER + '\n';
    }

    std::string PageBuilder::GetTopBox() const
    {
        return Globals::G_PAGE_ANSI_WHITE_COLOUR_ESCAPE_CODE + GetTopLine() + GetNewLineCentred(m_topTitle, Globals::Colours::RED) + GetBottomLine();
    }

    std::string PageBuilder::GetBottomBox() const
    {
        // Globals::G_PAGE_ANSI_RESET_COLOUR_ESCAPE_CODE used to unset any ANSI colour escape code. If the program unexpectedly
        // crashes the user's terminal will not be affected.
        return GetTopLine() + GetNewLineCentred(m_bottomTitle, Globals::Colours::RED) + GetBottomLine() + Globals::G_PAGE_ANSI_RESET_COLOUR_ESCAPE_CODE;
    }

    std::string PageBuilder::GetRemainingEmptyLines(const std::string& p_commonTopString, const std::string& p_commonBottomString) const
    {
        const int32_t REMAINING_LINE_COUNT = static_cast<int32_t>(m_pageHeight) - Globals::ImplementStdCount(p_commonTopString.begin(), p_commonTopString.end(), '\n') - Globals::ImplementStdCount(p_commonBottomString.begin(), p_commonBottomString.end(), '\n');
        const uint32_t EMPTY_LINES_TO_ADD_COUNT = REMAINING_LINE_COUNT < 0 ? 0 : REMAINING_LINE_COUNT;

        std::string output;
        output.reserve(m_pageWidth * EMPTY_LINES_TO_ADD_COUNT); // NOLINT(bugprone-implicit-widening-of-multiplication-result)
        for (uint32_t emptyLineCount = 0; emptyLineCount < EMPTY_LINES_TO_ADD_COUNT; emptyLineCount++)
        {
            output += GetEmptyLine();
        }

        return output;
    }

    std::vector<std::string> PageBuilder::GetGeneralOptionSelectionPages( // NOLINT(readability-function-cognitive-complexity)
        const std::vector<std::string>& p_options,
        const std::string& p_commonTopString,
        const std::string& p_commonBottomString,
        const bool& p_addEmptyLineBetweenOptions,
        const bool& p_centerOptionsHorizontally,
        const bool& p_centerOptionsVertically) const
    {
        const double DIVISOR = 2;
        const uint32_t EMPTY_LINES_BEFORE_OPTIONS = static_cast<uint32_t>(floor(static_cast<double>(m_pageHeight - Globals::ImplementStdCount(p_commonTopString.begin(), p_commonTopString.end(), '\n') - Globals::ImplementStdCount(p_commonBottomString.begin(), p_commonBottomString.end(), '\n') - (2 * p_options.size() - 1)) / DIVISOR));
        const uint32_t EMPTY_LINES_AFTER_OPTIONS = static_cast<uint32_t>(ceil(static_cast<double>(m_pageHeight - Globals::ImplementStdCount(p_commonTopString.begin(), p_commonTopString.end(), '\n') - Globals::ImplementStdCount(p_commonBottomString.begin(), p_commonBottomString.end(), '\n') - (2 * p_options.size() - 1)) / DIVISOR));

        std::vector<std::string> output(p_options.size());

        // Construct a page for each option selected.
        for (uint32_t currentOptionSelected = 0; currentOptionSelected < p_options.size(); currentOptionSelected++)
        {
            std::string currentTopString = p_commonTopString;

            if (p_centerOptionsVertically)
            {
                for (uint32_t emptyLineCount = 0; emptyLineCount < EMPTY_LINES_BEFORE_OPTIONS; emptyLineCount++)
                {
                    currentTopString += GetEmptyLine();
                }
            }

            for (uint32_t currentOption = 0; currentOption < p_options.size(); currentOption++)
            {
                if (currentOption == currentOptionSelected)
                {
                    if (p_centerOptionsHorizontally)
                    {
                        currentTopString += GetNewLineCentred(p_options[currentOption], Globals::Colours::BLUE, Globals::G_PAGE_OPTION_SELECTOR);
                    }

                    else
                    {
                        currentTopString += GetNewLineLeftJustified(p_options[currentOption], Globals::Colours::BLUE, Globals::G_PAGE_OPTION_SELECTOR);
                    }
                }

                else if (p_centerOptionsHorizontally)
                {
                    currentTopString += GetNewLineCentred(p_options[currentOption]);
                }

                else
                {
                    currentTopString += GetNewLineLeftJustified(Globals::G_PAGE_OPTION_SELECTOR_ABSENT_PADDING + p_options[currentOption]);
                }

                if (p_addEmptyLineBetweenOptions)
                {
                    if (currentOption != p_options.size() - 1) // Don't add extra line on the last option.
                    {
                        currentTopString += GetEmptyLine();
                    }
                }
            }

            if (p_centerOptionsVertically)
            {
                output[currentOptionSelected] = currentTopString;

                for (uint32_t emptyLineCount = 0; emptyLineCount < EMPTY_LINES_AFTER_OPTIONS; emptyLineCount++)
                {
                    output[currentOptionSelected] += GetEmptyLine();
                }

                output[currentOptionSelected] += p_commonBottomString;
            }

            else
            {
                output[currentOptionSelected] = currentTopString;
                output[currentOptionSelected] += GetRemainingEmptyLines(currentTopString, p_commonBottomString);
                output[currentOptionSelected] += p_commonBottomString;
            }
        }

        return output;
    }

    std::vector<std::string> PageBuilder::GetGameOptionSelectionPages(const GameInformation& p_gameInformation, const std::string& p_message, const std::vector<std::string>& p_options)
    {
        const std::string COMMON_TOP_STRING = GetTopBox() + GetTopLine() + GetGeneralGameSubPage(p_gameInformation) + GetEmptyLine() + GetNewLineLeftJustified(p_message);
        const std::string COMMON_BOTTOM_STRING = GetBottomLine() + GetBottomBox();

        return GetGeneralOptionSelectionPages(p_options, COMMON_TOP_STRING, COMMON_BOTTOM_STRING, false, false, false);
    }

    std::string PageBuilder::GetGeneralGameSubPage(const GameInformation& p_gameInformation)
    {
        switch (m_currentPage)
        {
        case Pages::TICTACTOE:
            return GetTicTacToeSubPage(p_gameInformation);

        case Pages::HANGMAN:
            return GetHangmanSubPage(p_gameInformation);

        case Pages::BATTLESHIPS:
            return GetBattleshipsSubPage(p_gameInformation);

        default:
            return "The 'GetGeneralGameDisplay' function does not support the current page type.";
        }
    }

    std::string PageBuilder::GetTicTacToeSubPage(const GameInformation& p_gameInformation)
    {
        // leftGridLines and RIGHT_GRID_STRINGS vectors must equal GRID_HEIGHT in size.
        // Also LEFT_GRID_SIZE + RIGHT_GRID_SIZE must equal G_TICTACTOE_DISPLAY_WIDTH - (numberOfGrids * (Globals::G_PAGE_MINIMUM_LEFT_VERTICAL_LINE_SIZE - Globals::G_PAGE_MINIMUM_RIGHT_VERTICAL_LINE_SIZE))
        const uint32_t LEFT_GRID_SIZE = 11;
        const uint32_t RIGHT_GRID_SIZE = 40;
        const uint32_t GRID_HEIGHT = 5;

        // Tic Tac Toe board section
        std::vector<std::string> leftGridLines;
        for (uint32_t row = 0; row < Globals::G_TICTACTOE_GRID_HEIGHT; row++)
        {
            std::string currentRow;
            std::string currentRowDivider;
            currentRow.reserve(LEFT_GRID_SIZE);
            currentRowDivider.reserve(LEFT_GRID_SIZE);

            for (uint32_t column = 0; column < Globals::G_TICTACTOE_GRID_WIDTH; column++)
            {
                currentRow += p_gameInformation.m_ticTacToeGameInformation.m_gameGrid.at(row).at(column);
                currentRowDivider += Globals::G_TICTACTOE_GRID_ROW_VALUE_DIVIDER;

                // Skip on last value
                if (column != Globals::G_TICTACTOE_GRID_WIDTH - 1)
                {
                    currentRow += Globals::G_PAGE_GRID_VERTICAL_LINE;
                    currentRowDivider += Globals::G_PAGE_GRID_INTERSECTION;
                }
            }

            leftGridLines.emplace_back(currentRow);
            leftGridLines.emplace_back(currentRowDivider);
        }

        // Game options section
        const std::vector<std::string> RIGHT_GRID_LINES = {
            "",
            Globals::G_GAME_NUMBER_OF_PLAYERS + p_gameInformation.m_ticTacToeGameInformation.m_playerCount,
            "",
            Globals::G_GAME_COMPUTER_SPEED + p_gameInformation.m_ticTacToeGameInformation.m_computerSpeedName,
            "",
        };

        return GetGridLayout({LEFT_GRID_SIZE, RIGHT_GRID_SIZE}, {leftGridLines, RIGHT_GRID_LINES}, GRID_HEIGHT);
    }

    std::string PageBuilder::GetHangmanSubPage(const GameInformation& p_gameInformation)
    {
        // leftGridLines, MIDDLE_GRID_LINES and rightGridLines vectors must equal GRID_HEIGHT in size.
        // Also LEFT_GRID_SIZE + MIDDLE_GRID_SIZE + RIGHT_GRID_SIZE must equal G_HANGMAN_DISPLAY_WIDTH - (numberOfGrids * (Globals::G_PAGE_MINIMUM_LEFT_VERTICAL_LINE_SIZE - Globals::G_PAGE_MINIMUM_RIGHT_VERTICAL_LINE_SIZE))
        const uint32_t LEFT_GRID_SIZE = 13;
        const uint32_t MIDDLE_GRID_SIZE = 24;
        const uint32_t RIGHT_GRID_SIZE = 17;
        const uint32_t GRID_HEIGHT = 7;

        // Hangman state section
        const std::vector<std::string>& leftGridLines = Globals::G_HANGMAN_STATES[p_gameInformation.m_hangmanGameInformation.m_incorrectGuesses.size()];

        // Game options section
        const std::vector<std::string> MIDDLE_GRID_LINES = {
            "",
            "",
            Globals::G_GAME_NUMBER_OF_PLAYERS + p_gameInformation.m_hangmanGameInformation.m_playerCount,
            "",
            Globals::G_GAME_COMPUTER_SPEED + p_gameInformation.m_hangmanGameInformation.m_computerSpeedName,
            "",
            "",
        };

        // Incorrect Guesses section
        std::vector<std::string> rightGridLines;
        std::string currentLine;
        currentLine.reserve(RIGHT_GRID_SIZE);

        rightGridLines.emplace_back("");
        rightGridLines.emplace_back(Globals::G_HANGMAN_INCORRECT_GUESSES_TITLE);

        for (uint32_t letterIndex = 0; letterIndex < p_gameInformation.m_hangmanGameInformation.m_incorrectGuesses.size(); letterIndex++)
        {
            currentLine += p_gameInformation.m_hangmanGameInformation.m_incorrectGuesses.at(letterIndex);

            // Skip adding space on last value on each line
            if (letterIndex != Globals::G_HANGMAN_INCORRECT_GUESSES_FIRST_LINE_LAST_INDEX && letterIndex != Globals::G_HANGMAN_INCORRECT_GUESSES_SECOND_LINE_LAST_INDEX)
            {
                currentLine += Globals::G_HANGMAN_INCORRECT_GUESSES_PADDING;
            }

            else
            {
                rightGridLines.emplace_back(currentLine);
                rightGridLines.emplace_back("");
                currentLine.clear();
            }
        }

        if (!currentLine.empty())
        {
            rightGridLines.emplace_back(currentLine);
        }

        // Adding required number of empty lines to meet GRID_HEIGHT
        const uint32_t REMAINING_LINES_TO_ADD = GRID_HEIGHT - rightGridLines.size();
        for (uint32_t emptyLineCount = 0; emptyLineCount < REMAINING_LINES_TO_ADD; emptyLineCount++)
        {
            rightGridLines.emplace_back("");
        }

        std::string output = GetGridLayout({LEFT_GRID_SIZE, MIDDLE_GRID_SIZE, RIGHT_GRID_SIZE}, {leftGridLines, MIDDLE_GRID_LINES, rightGridLines}, GRID_HEIGHT);

        // Current guess of word and word to be guessed section
        std::string currentGuessOfWord;
        currentGuessOfWord.reserve(2 * p_gameInformation.m_hangmanGameInformation.m_currentGuessOfWord.size());
        for (const char& letter : p_gameInformation.m_hangmanGameInformation.m_currentGuessOfWord)
        {
            currentGuessOfWord += letter;
            currentGuessOfWord += ' ';
        }

        if (p_gameInformation.m_hangmanGameInformation.m_isGameOver)
        {
            output += GetNewLineLeftJustified(currentGuessOfWord + Globals::G_HANGMAN_WORD_TO_BE_GUESSED_START + p_gameInformation.m_hangmanGameInformation.m_wordToBeGuessed + Globals::G_HANGMAN_WORD_TO_BE_GUESSED_END);
        }

        else
        {
            output += GetNewLineLeftJustified(currentGuessOfWord);
        }

        return output;
    }

    std::string PageBuilder::GetBattleshipsSubPage(const GameInformation& p_gameInformation) // NOLINT(readability-function-cognitive-complexity)
    {
        // leftGridLines, middleGridLines and rightGridLines vectors must equal GRID_HEIGHT in size.
        // Also LEFT_GRID_SIZE + MIDDLE_GRID_SIZE + RIGHT_GRID_SIZE must equal G_BATTLESHIPS_DISPLAY_WIDTH - (numberOfGrids * Globals::G_PAGE_MINIMUM_LEFT_VERTICAL_LINE_SIZE - Globals::G_PAGE_MINIMUM_RIGHT_VERTICAL_LINE_SIZE))
        const uint32_t LEFT_GRID_SIZE = 45;
        const uint32_t MIDDLE_GRID_SIZE = 44;
        const uint32_t RIGHT_GRID_SIZE = 45;
        const uint32_t GRID_HEIGHT = 24;

        const std::string SINGLE_SPACE(1, ' ');

        std::string commonGridAlphabetAxis;
        commonGridAlphabetAxis.reserve(LEFT_GRID_SIZE);

        commonGridAlphabetAxis += Globals::G_PAGE_GRID_VERTICAL_LINE;
        commonGridAlphabetAxis += Globals::G_BATTLESHIPS_EMPTY_GRID_VALUE;

        for (uint32_t currentLetter = Globals::G_BATTLESHIPS_LETTER_OFFSET; (currentLetter - Globals::G_BATTLESHIPS_LETTER_OFFSET) < Globals::G_BATTLESHIPS_BOARD_WIDTH; currentLetter++)
        {
            commonGridAlphabetAxis += Globals::G_PAGE_GRID_VERTICAL_LINE;
            commonGridAlphabetAxis += SINGLE_SPACE;
            commonGridAlphabetAxis += static_cast<char>(currentLetter);
            commonGridAlphabetAxis += SINGLE_SPACE;
        }

        commonGridAlphabetAxis += Globals::G_PAGE_GRID_VERTICAL_LINE;

        std::vector<std::string> leftGridLines = {Globals::G_BATTLESHIPS_PLAYER_ONE, Globals::G_BATTLESHIPS_GRID_TOP_LINE, commonGridAlphabetAxis, Globals::G_BATTLESHIPS_GRID_MIDDLE_LINE};
        std::vector<std::string> rightGridLines = {Globals::G_BATTLESHIPS_PLAYER_TWO, Globals::G_BATTLESHIPS_GRID_TOP_LINE, commonGridAlphabetAxis, Globals::G_BATTLESHIPS_GRID_MIDDLE_LINE};

        // Assuming both board are the same size
        for (uint32_t row = 0; row < p_gameInformation.m_battleshipsGameInformation.m_boardPlayerOne.size(); row++)
        {
            std::string currentLeftGridValueLine;
            currentLeftGridValueLine.reserve(LEFT_GRID_SIZE);
            currentLeftGridValueLine += Globals::G_PAGE_GRID_VERTICAL_LINE;
            currentLeftGridValueLine += SINGLE_SPACE;
            currentLeftGridValueLine += std::to_string(row);
            currentLeftGridValueLine += SINGLE_SPACE;

            std::string currentRightGridValueLine = currentLeftGridValueLine;

            for (uint32_t column = 0; column < p_gameInformation.m_battleshipsGameInformation.m_boardPlayerOne.at(row).size(); column++)
            {
                // Don't include the ship name instead only its state
                currentLeftGridValueLine += Globals::G_PAGE_GRID_VERTICAL_LINE + p_gameInformation.m_battleshipsGameInformation.m_boardPlayerOne.at(row).at(column).substr(0, Globals::G_BATTLESHIPS_GRID_ELEMENT_WIDTH);

                // Only show player two board if game is over, or if not game over then only if zero player game, or if not game
                // over and not zero player game (i.e. one player game) then only if grid value is does not have a ship present
                // (i.e. only if grid value is empty, missed attack or successful attack).
                if (p_gameInformation.m_battleshipsGameInformation.m_isGameOver || p_gameInformation.m_battleshipsGameInformation.m_playerCount != "1" || p_gameInformation.m_battleshipsGameInformation.m_boardPlayerTwo.at(row).at(column).substr(0, Globals::G_BATTLESHIPS_GRID_ELEMENT_WIDTH) != Globals::G_BATTLESHIPS_SHIP_PRESENT)
                {
                    currentRightGridValueLine += Globals::G_PAGE_GRID_VERTICAL_LINE + p_gameInformation.m_battleshipsGameInformation.m_boardPlayerTwo.at(row).at(column).substr(0, Globals::G_BATTLESHIPS_GRID_ELEMENT_WIDTH);
                }

                else
                {
                    currentRightGridValueLine += Globals::G_PAGE_GRID_VERTICAL_LINE + Globals::G_BATTLESHIPS_EMPTY_GRID_VALUE;
                }
            }

            currentLeftGridValueLine += Globals::G_PAGE_GRID_VERTICAL_LINE;
            currentRightGridValueLine += Globals::G_PAGE_GRID_VERTICAL_LINE;

            leftGridLines.emplace_back(currentLeftGridValueLine);
            rightGridLines.emplace_back(currentRightGridValueLine);

            // Skip on last row
            if (row != p_gameInformation.m_battleshipsGameInformation.m_boardPlayerOne.size() - 1)
            {
                leftGridLines.emplace_back(Globals::G_BATTLESHIPS_GRID_MIDDLE_LINE);
                rightGridLines.emplace_back(Globals::G_BATTLESHIPS_GRID_MIDDLE_LINE);
            }

            else
            {
                leftGridLines.emplace_back(Globals::G_BATTLESHIPS_GRID_BOTTOM_LINE);
                rightGridLines.emplace_back(Globals::G_BATTLESHIPS_GRID_BOTTOM_LINE);
            }
        }

        std::vector<std::string> middleGridLines = {
            "",
            "",
            "",
            "",
            Globals::G_GAME_NUMBER_OF_PLAYERS + p_gameInformation.m_battleshipsGameInformation.m_playerCount,
            "",
            Globals::G_GAME_COMPUTER_SPEED + p_gameInformation.m_battleshipsGameInformation.m_computerSpeedName,
            "",
            "",
        };

        for (uint32_t currentShip = 0; currentShip < Globals::G_BATTLESHIPS_SHIP_NAMES.size(); currentShip++)
        {
            std::string currentShipHealthLine;
            currentShipHealthLine.reserve(MIDDLE_GRID_SIZE);

            // Player one
            for (uint32_t currentShipHealthSquare = 0; currentShipHealthSquare < Globals::G_BATTLESHIPS_SHIP_SIZES.at(currentShip); currentShipHealthSquare++)
            {
                if (currentShipHealthSquare < p_gameInformation.m_battleshipsGameInformation.m_shipsRemainingPlayerOne.at(Globals::G_BATTLESHIPS_SHIP_PLACED_NAMES.at(currentShip)))
                {
                    currentShipHealthLine += Globals::G_BATTLESHIPS_SHIP_PRESENT;
                }

                else
                {
                    currentShipHealthLine += Globals::G_BATTLESHIPS_SUCCESSFUL_ATTACK;
                }

                // Skip on last iteration
                if (currentShipHealthSquare != Globals::G_BATTLESHIPS_SHIP_SIZES.at(currentShip) - 1)
                {
                    currentShipHealthLine += SINGLE_SPACE;
                }
            }

            std::string currentShipHealthTitle;
            currentShipHealthTitle.reserve(MIDDLE_GRID_SIZE);

            if (p_gameInformation.m_battleshipsGameInformation.m_isGameOver || p_gameInformation.m_battleshipsGameInformation.m_playerCount != "1")
            {
                currentShipHealthTitle = Globals::G_BATTLESHIPS_SHIP_NAMES.at(currentShip) + std::string(MIDDLE_GRID_SIZE - (2 * Globals::G_BATTLESHIPS_SHIP_NAMES.at(currentShip).size()), ' ') + Globals::G_BATTLESHIPS_SHIP_NAMES.at(currentShip);

                currentShipHealthLine += std::string(MIDDLE_GRID_SIZE - (2 * Globals::G_BATTLESHIPS_SHIP_SIZES.at(currentShip) * Globals::G_BATTLESHIPS_GRID_ELEMENT_WIDTH) - (2 * (Globals::G_BATTLESHIPS_SHIP_SIZES.at(currentShip) - 1)), ' ');

                // Player Two
                for (uint32_t currentShipHealthSquare = 0; currentShipHealthSquare < Globals::G_BATTLESHIPS_SHIP_SIZES.at(currentShip); currentShipHealthSquare++)
                {
                    if (currentShipHealthSquare < (Globals::G_BATTLESHIPS_SHIP_SIZES.at(currentShip) - p_gameInformation.m_battleshipsGameInformation.m_shipsRemainingPlayerTwo.at(Globals::G_BATTLESHIPS_SHIP_PLACED_NAMES.at(currentShip))))
                    {
                        currentShipHealthLine += Globals::G_BATTLESHIPS_SUCCESSFUL_ATTACK;
                    }

                    else
                    {
                        currentShipHealthLine += Globals::G_BATTLESHIPS_SHIP_PRESENT;
                    }

                    // Skip on last iteration
                    if (currentShipHealthSquare != Globals::G_BATTLESHIPS_SHIP_SIZES.at(currentShip) - 1)
                    {
                        currentShipHealthLine += SINGLE_SPACE;
                    }
                }
            }

            else
            {
                currentShipHealthTitle = Globals::G_BATTLESHIPS_SHIP_NAMES.at(currentShip) + std::string(MIDDLE_GRID_SIZE - Globals::G_BATTLESHIPS_SHIP_NAMES.at(currentShip).size(), ' ');
                currentShipHealthLine += std::string(MIDDLE_GRID_SIZE - (Globals::G_BATTLESHIPS_SHIP_SIZES.at(currentShip) * Globals::G_BATTLESHIPS_GRID_ELEMENT_WIDTH) - (Globals::G_BATTLESHIPS_SHIP_SIZES.at(currentShip) - 1), ' ');
            }

            middleGridLines.emplace_back(currentShipHealthTitle);
            middleGridLines.emplace_back(currentShipHealthLine);
            middleGridLines.emplace_back("");
        }

        return GetGridLayout({LEFT_GRID_SIZE, MIDDLE_GRID_SIZE, RIGHT_GRID_SIZE}, {leftGridLines, middleGridLines, rightGridLines}, GRID_HEIGHT);
    }

    std::string PageBuilder::GetGridLayout(const std::vector<uint32_t>& p_gridColumnWidths, const std::vector<std::vector<std::string>>& p_gridColumnLines, const uint32_t& p_gridColumnHeight)
    {
        const uint32_t OLD_MAXIMUM_LINE_SIZE = m_lineMaximumCharacterCount;
        const uint32_t OLD_MINIMUM_LEFT_PADDING = m_minimumLeftPadding;
        const uint32_t OLD_MINIMUM_RIGHT_PADDING = m_minimumRightPadding;

        m_minimumLeftPadding = 0;
        m_minimumRightPadding = 0;

        std::string output;

        for (uint32_t currentLineNumber = 0; currentLineNumber < p_gridColumnHeight; currentLineNumber++)
        {
            std::string currentLine;
            currentLine.reserve(m_pageWidth);

            for (uint32_t currentGridSize = 0; currentGridSize < p_gridColumnWidths.size(); currentGridSize++)
            {
                m_lineMaximumCharacterCount = p_gridColumnWidths[currentGridSize];
                currentLine += GetNewLineCentredOptimised(p_gridColumnLines[currentGridSize][currentLineNumber]);
            }

            // Remove the vertical lines created between grids and all new lines
            std::ranges::replace(currentLine.begin(), currentLine.end(), Globals::G_PAGE_VERTICAL_LINE, ' ');
            std::erase(currentLine, '\n');

            // Re-add the vertical lines to the start/end and re-add a single newline to the end
            output += Globals::G_PAGE_VERTICAL_LINE;
            output += currentLine;
            output += Globals::G_PAGE_VERTICAL_LINE;
            output += '\n';
        }

        m_lineMaximumCharacterCount = OLD_MAXIMUM_LINE_SIZE;
        m_minimumLeftPadding = OLD_MINIMUM_LEFT_PADDING;
        m_minimumRightPadding = OLD_MINIMUM_RIGHT_PADDING;

        return output;
    }
}
