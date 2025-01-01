#include <array>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

#include "Constants.hpp"
#include "Exceptions.hpp"
#include "helpers/PageBuilder.hpp"

namespace TerminalGames
{
    PageBuilder::PageBuilder() :
        m_displayWidth(0),
        m_displayHeight(0),
        m_onlyUseASCII(false),
        m_currentPage(Pages::DEFAULT) {}

    PageBuilder::PageBuilder(const Pages& p_page, const bool& p_onlyUseAscii) :
        m_displayWidth(0),
        m_displayHeight(0),
        m_onlyUseASCII(false),
        m_currentPage(Pages::DEFAULT)
    {
        this->SetProperties(p_page, p_onlyUseAscii);
    }

    void PageBuilder::SetProperties(const Pages& p_page, const bool& p_onlyUseAscii)
    {
        m_currentPage = p_page;
        m_onlyUseASCII = p_onlyUseAscii;

        switch (m_currentPage)
        {
        case Pages::MAINMENU:
            m_topTitle = "Terminal-Games";
            m_displayWidth = G_MAIN_MENU_DISPLAY_WIDTH;
            m_displayHeight = G_MAIN_MENU_DISPLAY_HEIGHT;
            break;

        case Pages::TICTACTOE:
            m_topTitle = "Tic Tac Toe";
            m_displayWidth = G_TICTACTOE_DISPLAY_WIDTH;
            m_displayHeight = G_TICTACTOE_DISPLAY_HEIGHT;
            break;

        case Pages::HANGMAN:
            m_topTitle = "Hangman";
            m_displayWidth = G_HANGMAN_DISPLAY_WIDTH;
            m_displayHeight = G_HANGMAN_DISPLAY_HEIGHT;
            break;

        case Pages::BATTLESHIPS:
            m_topTitle = "Battleships";
            m_displayWidth = G_BATTLESHIPS_DISPLAY_WIDTH;
            m_displayHeight = G_BATTLESHIPS_DISPLAY_HEIGHT;
            break;

        default:
            throw Exceptions::NotImplementedError();
        }
    }

    Pages PageBuilder::GetCurrentPageType() const
    {
        return m_currentPage;
    }

    std::vector<std::string> PageBuilder::GetGameSelectionMainMenuPages(const std::vector<std::string>& p_gameNames) const
    {
        const std::string COMMON_TOP_STRING = GetTopBox() + GetTopLine();
        const std::string COMMON_BOTTOM_STRING = GetBottomLine() + GetBottomBox();

        std::vector<std::string> output(p_gameNames.size());

        // Construct a page for each game selected.
        for (uint32_t i = 0; i < p_gameNames.size(); i++)
        {
            std::string currentTopString = COMMON_TOP_STRING;

            for (uint32_t j = 0; j < p_gameNames.size(); j++)
            {
                if (i == j)
                    currentTopString += GetNewLineCentred(AddColour(G_SELECTOR + p_gameNames[j], Colours::BLUE));

                else
                    currentTopString += GetNewLineCentred(p_gameNames[j]);

                if (j != p_gameNames.size() - 1) // Don't add extra line on the last game option.
                    currentTopString += GetEmptyLine();
            }

            output[i] = currentTopString;
            output[i] += GetRemainingEmptyLines(currentTopString, COMMON_BOTTOM_STRING) + COMMON_BOTTOM_STRING;
        }

        return output;
    }

    std::vector<std::string> PageBuilder::GetPlayerCountOptionSelectionGamePages(const GameInfo& p_gameInfo) const
    {
        switch (m_currentPage)
        {
        case Pages::TICTACTOE:
        case Pages::HANGMAN:
            return GetOptionSelectionPages(p_gameInfo, "Please select the number of players:", {"0", "1", "2"});

        case Pages::BATTLESHIPS:
            return GetOptionSelectionPages(p_gameInfo, "Please select the number of players:", {"0", "1"});

        default:
            return {"The 'GetPlayerCountOptionSelectionGameDisplays' function does not support the current page type."};
        }
    }

    std::vector<std::string> PageBuilder::GetUserPlayerChoiceOptionSelectionGamePages(const GameInfo& p_gameInfo) const
    {
        switch (m_currentPage)
        {
        case Pages::TICTACTOE:
            return GetOptionSelectionPages(p_gameInfo, "Please select the player you would like to be:", {"PLAYER X", "PLAYER O"});

        case Pages::HANGMAN:
            return GetOptionSelectionPages(p_gameInfo, "Please select the player you would like to be:", {"GUESSER", "WORD SETTER"});

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
            return GetOptionSelectionPages(p_gameInfo, "Please select the computer speed:", {"INSTANT", "FAST", "SLOW"});

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
            return GetPageWithMessage(p_gameInfo, "Guesser, please enter your next guess:");

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
        const std::string BOTTOM_STRING = GetEmptyLine() + GetNewLineCentred("Press 'q' to quit OR any key to play again...") + GetBottomLine() + GetBottomBox();

        switch (m_currentPage)
        {
        case Pages::TICTACTOE:
            if (p_gameInfo.m_ticTacToeGameInfo.m_hasWinner) // This game can be drawn unlike the others.
                topString += GetNewLineCentred(p_gameInfo.m_ticTacToeGameInfo.m_currentPlayer + " has won! The game lasted " + std::to_string(p_gameInfo.m_ticTacToeGameInfo.m_turnCount) + " turns.");

            else
                topString += GetNewLineCentred("The game is a draw! The game lasted " + std::to_string(p_gameInfo.m_ticTacToeGameInfo.m_turnCount) + " turns.");
            break;

        case Pages::HANGMAN:
            if (p_gameInfo.m_hangmanGameInfo.m_errorCount == G_HANGMAN_MAXIMUM_ERROR_COUNT)
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

    std::string PageBuilder::AddColour(const std::string& p_input, const Colours& p_colour) const
    {
        if (m_onlyUseASCII)
            return p_input;

        if (p_colour == Colours::RED)
            return G_RED_ANSI_COLOUR_ESCAPE_CODE + p_input + G_WHITE_ANSI_COLOUR_ESCAPE_CODE;

        if (p_colour == Colours::BLUE)
            return G_BLUE_ANSI_COLOUR_ESCAPE_CODE + p_input + G_WHITE_ANSI_COLOUR_ESCAPE_CODE;

        return p_input; // Text is already white
    }

    std::string PageBuilder::GetEmptyLine() const
    {
        std::string output;
        output += G_VERTICAL_LINE;

        output.insert(output.size(), m_displayWidth, ' ');

        return output + G_VERTICAL_LINE + "\n";
    }

    std::string PageBuilder::GetNewLineCentred(const std::string& p_input) const
    {
        static const double DIVISOR = 2;

        // +/- 2 = padding on either side (2) of input.
        const std::string INPUT_TRIMMED = ((p_input.size() + 2) > m_displayWidth) ? p_input.substr(0, m_displayWidth - 2) : p_input;

        std::string output;
        output += G_VERTICAL_LINE;

        output.insert(output.size(), static_cast<size_t>(ceil(static_cast<double>(m_displayWidth - INPUT_TRIMMED.size()) / DIVISOR)), ' ');
        output += INPUT_TRIMMED;
        output.insert(output.size(), static_cast<size_t>(floor(static_cast<double>(m_displayWidth - INPUT_TRIMMED.size()) / DIVISOR)), ' ');

        return output + G_VERTICAL_LINE + "\n";
    }

    std::string PageBuilder::GetNewLineLeftJustified(const std::string& p_input) const
    {
        // +/- 2 = padding on either side (2) of input.
        const std::string INPUT_TRIMMED = ((p_input.size() + 2) > m_displayWidth) ? p_input.substr(0, m_displayWidth - 2) : p_input;

        std::string output;
        output += G_VERTICAL_LINE;
        output += INPUT_TRIMMED;
        output.insert(output.size(), m_displayWidth - INPUT_TRIMMED.size(), ' ');

        return output + G_VERTICAL_LINE + "\n";
    }

    std::string PageBuilder::GetTopLine() const
    {
        std::string output;
        output += G_TOP_LEFT_CORNER;

        output.insert(output.size(), m_displayWidth, G_HORIZONTAL_LINE);

        return output + G_TOP_RIGHT_CORNER + "\n";
    }

    std::string PageBuilder::GetBottomLine() const
    {
        std::string output;
        output += G_BOTTOM_LEFT_CORNER;

        output.insert(output.size(), m_displayWidth, G_HORIZONTAL_LINE);

        return output + G_BOTTOM_RIGHT_CORNER + "\n";
    }

    std::string PageBuilder::GetTopBox() const
    {
        return G_WHITE_ANSI_COLOUR_ESCAPE_CODE + GetTopLine() + GetNewLineCentred(AddColour(m_topTitle, Colours::RED)) + GetBottomLine();
    }

    std::string PageBuilder::GetBottomBox() const
    {
        std::string output;
        output += GetTopLine();

        switch (m_currentPage)
        {
        case Pages::MAINMENU:
            output += GetNewLineCentred(AddColour(G_MENU_BOTTOM_TITLE, Colours::RED));
            break;

        case Pages::TICTACTOE:
        case Pages::HANGMAN:
        case Pages::BATTLESHIPS:
            output += GetNewLineCentred(AddColour(G_GAME_BOTTOM_TITLE, Colours::RED));
            break;

        default:
            return {"The 'GetBottomBox' function does not support the current page type."};
        }

        // G_RESET_ANSI_COLOUR_ESCAPE_CODE used to unset any ANSI colour escape code. If the program unexpectedly crashes the
        // user's terminal will not be affected.
        return output + GetBottomLine() + G_RESET_ANSI_COLOUR_ESCAPE_CODE;
    }

    std::string PageBuilder::GetRemainingEmptyLines(const std::string& p_commonTopString, const std::string& p_commonBottomString) const
    {
        const int32_t REMAINING_LINE_COUNT = static_cast<int32_t>(m_displayHeight) - TerminalGames::ImplementStdCount(p_commonTopString.begin(), p_commonTopString.end(), '\n') - TerminalGames::ImplementStdCount(p_commonBottomString.begin(), p_commonBottomString.end(), '\n');
        const uint32_t EMPTY_LINES_TO_ADD_COUNT = REMAINING_LINE_COUNT < 0 ? 0 : REMAINING_LINE_COUNT;

        std::string output;
        for (uint32_t i = 0; i < EMPTY_LINES_TO_ADD_COUNT; i++)
            output += GetEmptyLine();

        return output;
    }

    std::vector<std::string> PageBuilder::GetOptionSelectionPages(const GameInfo& p_gameInfo, const std::string& p_message, const std::vector<std::string>& p_options) const
    {
        const std::string COMMON_TOP_STRING = GetTopBox() + GetTopLine() + GetGeneralGameSubPage(p_gameInfo) + GetEmptyLine() + GetNewLineLeftJustified(p_message);
        const std::string COMMON_BOTTOM_STRING = GetBottomLine() + GetBottomBox();

        std::vector<std::string> output(p_options.size());

        // Construct a page for each option selected.
        for (uint32_t i = 0; i < p_options.size(); i++)
        {
            std::string currentTopString = COMMON_TOP_STRING;

            for (uint32_t j = 0; j < p_options.size(); j++)
            {
                if (i == j)
                    currentTopString += GetNewLineLeftJustified(AddColour(G_SELECTOR + " " + p_options[j], Colours::BLUE));

                else
                    // + 1 to match above statement which will have an extra pad between option and selector
                    currentTopString += GetNewLineLeftJustified(std::string(G_SELECTOR.size() + 1, ' ') + p_options[j]);
            }

            output[i] = currentTopString;
            output[i] += GetRemainingEmptyLines(currentTopString, COMMON_BOTTOM_STRING) + COMMON_BOTTOM_STRING;
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
        const std::array<std::array<std::string, G_TICTACTOE_BOARD_WIDTH>, G_TICTACTOE_BOARD_HEIGHT> gameGrid = gameInfo.m_ticTacToeGameInfo.m_gameGrid;
        const std::string playerCount = gameInfo.m_ticTacToeGameInfo.m_playerCount, computerSpeedName = gameInfo.m_ticTacToeGameInfo.m_computerSpeedName;

        std::string output;

        output += GetNewLineLeftJustified(gameGrid[0][0] + char(179) + gameGrid[0][1] + char(179) + gameGrid[0][2]);

        output += GetNewLineLeftJustified(std::string("") + (char)196 + (char)196 + (char)196 + (char)197 + (char)196 + (char)196 + (char)196 + char(197) + (char)196 + (char)196 + (char)196 + "          # of Players = " + playerCount);

        output += GetNewLineLeftJustified(gameGrid[1][0] + char(179) + gameGrid[1][1] + char(179) + gameGrid[1][2]);

        output += GetNewLineLeftJustified(std::string("") + (char)196 + (char)196 + (char)196 + (char)197 + (char)196 + (char)196 + (char)196 + char(197) + (char)196 + (char)196 + (char)196 + "    Computer Speed = " + computerSpeedName);

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
                    if (j < shipsRemainingOne.at(G_BATTLESHIPS_BATTLESHIP_NAME))
                        output.insert(output.size(), 3, (char)178);
                    else
                        output.insert(output.size(), 3, (char)176);
                }
                output += "              ";
                for (uint32_t j = 0; j < 4; j++, output += " ")
                {
                    if (j < (4 - shipsRemainingTwo.at(G_BATTLESHIPS_BATTLESHIP_NAME)))
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
                    if (j < shipsRemainingOne.at(G_BATTLESHIPS_SUBMARINE_NAME))
                        output.insert(output.size(), 3, (char)178);
                    else
                        output.insert(output.size(), 3, (char)176);
                }
                output += "                      ";
                for (uint32_t j = 0; j < 3; j++, output += " ")
                {
                    if (j < (3 - shipsRemainingTwo.at(G_BATTLESHIPS_SUBMARINE_NAME)))
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
                    if (j < shipsRemainingOne.at(G_BATTLESHIPS_CARRIER_NAME))
                        output.insert(output.size(), 3, (char)178);
                    else
                        output.insert(output.size(), 3, (char)176);
                }
                output += "      ";
                for (uint32_t j = 0; j < 5; j++, output += " ")
                {
                    if (j < (5 - shipsRemainingTwo.at(G_BATTLESHIPS_CARRIER_NAME)))
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
                    if (j < shipsRemainingOne.at(G_BATTLESHIPS_DESTROYER_NAME))
                        output.insert(output.size(), 3, (char)178);
                    else
                        output.insert(output.size(), 3, (char)176);
                }
                output += "                      ";
                for (uint32_t j = 0; j < 3; j++, output += " ")
                {
                    if (j < (3 - shipsRemainingTwo.at(G_BATTLESHIPS_DESTROYER_NAME)))
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
                    if (j < shipsRemainingOne.at(G_BATTLESHIPS_PATROL_BOAT_NAME))
                        output.insert(output.size(), 3, (char)178);
                    else
                        output.insert(output.size(), 3, (char)176);
                }
                output += "                              ";
                for (uint32_t j = 0; j < 2; j++, output += " ")
                {
                    if (j < (2 - shipsRemainingTwo.at(G_BATTLESHIPS_PATROL_BOAT_NAME)))
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

                else if (boardTwo[i][j].find(G_BATTLESHIPS_SUCCESSFUL_ATTACK) != std::string::npos)
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

                else if (boardTwo[i][j].find(G_BATTLESHIPS_MISSED_ATTACK) != std::string::npos)
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

    // NOLINTEND
}
