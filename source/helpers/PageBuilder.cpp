#include <array>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

#include "Constants.hpp"
#include "Exceptions.hpp"
#include "helpers/PageBuilder.hpp"

namespace TerminalGames
{
    PageBuilder::PageBuilder() : m_displayWidth(0),
                                 m_displayHeight(0),
                                 m_onlyUseASCII(false),
                                 m_currentPage(Pages::DEFAULT)
    {}

    PageBuilder::PageBuilder(const Pages &page, const bool &onlyUseASCII) : m_displayWidth(0),
                                                                            m_displayHeight(0),
                                                                            m_onlyUseASCII(false),
                                                                            m_currentPage(Pages::DEFAULT)
    {
        this->SetProperties(page, onlyUseASCII);
    }

    void PageBuilder::SetProperties(const Pages &page, const bool &onlyUseASCII)
    {
        m_currentPage = page;
        m_onlyUseASCII = onlyUseASCII;

        switch (m_currentPage)
        {
        case Pages::MAINMENU:
            m_topTitle = "Terminal-Games";
            m_displayWidth = g_MAIN_MENU_DISPLAY_WIDTH;
            m_displayHeight = g_MAIN_MENU_DISPLAY_HEIGHT;
            break;

        case Pages::TICTACTOE:
            m_topTitle = "Tic Tac Toe";
            m_displayWidth = g_TICTACTOE_DISPLAY_WIDTH;
            m_displayHeight = g_TICTACTOE_DISPLAY_HEIGHT;
            break;

        case Pages::HANGMAN:
            m_topTitle = "Hangman";
            m_displayWidth = g_HANGMAN_DISPLAY_WIDTH;
            m_displayHeight = g_HANGMAN_DISPLAY_HEIGHT;
            break;

        case Pages::BATTLESHIPS:
            m_topTitle = "Battleships";
            m_displayWidth = g_BATTLESHIPS_DISPLAY_WIDTH;
            m_displayHeight = g_BATTLESHIPS_DISPLAY_HEIGHT;
            break;

        default:
            throw Exceptions::NotImplementedError();
        }
    }

    std::string PageBuilder::AddColour(const std::string &input, const Colours &colour) const
    {
        if (m_onlyUseASCII)
        {
            return input;
        }

        if (colour == Colours::RED)
        {
            return g_RED_ANSI_COLOUR_ESCAPE_CODE + input + g_WHITE_ANSI_COLOUR_ESCAPE_CODE;
        }

        if (colour == Colours::BLUE)
        {
            return g_BLUE_ANSI_COLOUR_ESCAPE_CODE + input + g_WHITE_ANSI_COLOUR_ESCAPE_CODE;
        }

        return input; // Text is already white
    }

    std::string PageBuilder::GetEmptyLine() const
    {
        std::string output;
        output += g_VERTICAL_LINE;

        output.insert(output.size(), m_displayWidth, ' ');

        return output + g_VERTICAL_LINE + "\n";
    }

    std::string PageBuilder::GetNewLineCentred(const std::string &input, const Colours &colour, const std::string &selector) const
    {
        static const double divisor = 2;

        // Pad between input and selector if the selector has been set.
        std::string selectorPadded;
        if (!selector.empty())
        {
            selectorPadded = selector + " ";
        }

        // +/- 2 = padding on either side (2) of input.
        const std::string inputTrimmed = ((input.size() + selector.size() + 2) > m_displayWidth) ? input.substr(0, m_displayWidth - selector.size() - 2) : input;

        std::string output;
        output += g_VERTICAL_LINE;

        // If selector has not been set then selectorPadded will just be a single space character.
        output.insert(output.size(), static_cast<size_t>(ceil(static_cast<double>(m_displayWidth - inputTrimmed.size()) / divisor) - static_cast<double>(selectorPadded.size())), ' ');
        output += AddColour(selectorPadded + inputTrimmed, colour);
        output.insert(output.size(), static_cast<size_t>(floor(static_cast<double>(m_displayWidth - inputTrimmed.size()) / divisor)), ' ');

        return output + g_VERTICAL_LINE + "\n";
    }

    std::string PageBuilder::GetNewLineLeftJustified(const std::string &input, const Colours &colour, const std::string &selector) const
    {
        // Pad due to left justification.
        std::string selectorPadded = " ";
        if (!selector.empty())
        {
            selectorPadded += selector + " ";
        }

        // +/- 2 = padding on either side (2) of input.
        const std::string inputTrimmed = ((input.size() + selectorPadded.size()) > m_displayWidth) ? input.substr(0, m_displayWidth - selectorPadded.size()) : input;

        std::string output;
        output += g_VERTICAL_LINE;

        output += AddColour(selectorPadded + inputTrimmed, colour);
        output.insert(output.size(), m_displayWidth - inputTrimmed.size() - selectorPadded.size(), ' ');

        return output + g_VERTICAL_LINE + "\n";
    }

    std::string PageBuilder::GetTopLine() const
    {
        std::string output;
        output += g_TOP_LEFT_CORNER;

        output.insert(output.size(), m_displayWidth, g_HORIZONTAL_LINE);

        return output + g_TOP_RIGHT_CORNER + "\n";
    }

    std::string PageBuilder::GetBottomLine() const
    {
        std::string output;
        output += g_BOTTOM_LEFT_CORNER;

        output.insert(output.size(), m_displayWidth, g_HORIZONTAL_LINE);

        return output + g_BOTTOM_RIGHT_CORNER + "\n";
    }

    std::string PageBuilder::GetTopBox() const
    {
        return g_WHITE_ANSI_COLOUR_ESCAPE_CODE + GetTopLine() + GetNewLineCentred(m_topTitle, Colours::RED, "") + GetBottomLine();
    }

    std::string PageBuilder::GetBottomBox() const
    {
        std::string output;
        output += GetTopLine();

        switch (m_currentPage)
        {
        case Pages::MAINMENU:
            output += GetNewLineCentred(g_MENU_BOTTOM_TITLE, Colours::RED, "");
            break;

        case Pages::TICTACTOE:
        case Pages::HANGMAN:
        case Pages::BATTLESHIPS:
            output += GetNewLineCentred(g_GAME_BOTTOM_TITLE, Colours::RED, "");
            break;

        default:
            return {"The 'GetBottomBox' function does not support the current page type."};
        }

        // g_RESET_ANSI_COLOUR_ESCAPE_CODE used to unset any ANSI colour escape code. If the program unexpectedly crashes the user's terminal will
        // not be affected.
        return output + GetBottomLine() + g_RESET_ANSI_COLOUR_ESCAPE_CODE;
    }

    std::string PageBuilder::GetRemainingEmptyLines(const std::string &commonTopString, const std::string &commonBottomString) const
    {
        const int32_t remainingLineCount = static_cast<int32_t>(m_displayHeight) - TerminalGames::ImplementStdCount(commonTopString.begin(), commonTopString.end(), '\n') - TerminalGames::ImplementStdCount(commonBottomString.begin(), commonBottomString.end(), '\n');
        const uint32_t emptyLinesToAddCount = remainingLineCount < 0 ? 0 : remainingLineCount;

        std::string output;
        for (uint32_t i = 0; i < emptyLinesToAddCount; i++)
        {
            output += GetEmptyLine();
        }

        return output;
    }

    std::vector<std::string> PageBuilder::GetGameSelectionMainMenuPages(const std::vector<std::string> &gameNames) const
    {
        const std::string commonTopString = GetTopBox() + GetTopLine();
        const std::string commonBottomString = GetBottomLine() + GetBottomBox();

        std::vector<std::string> output(gameNames.size());

        // Construct a page for each game selected.
        for (uint32_t i = 0; i < output.size(); i++)
        {
            std::string currentTopString = commonTopString;

            for (uint32_t j = 0; j < gameNames.size(); j++)
            {
                if (i == j)
                {
                    currentTopString += GetNewLineCentred(gameNames[j], Colours::BLUE, g_SELECTOR);
                }

                else
                {
                    currentTopString += GetNewLineCentred(gameNames[j], Colours::WHITE, "");
                }

                if (j != gameNames.size() - 1) // Don't add extra line on the last game option.
                {
                    currentTopString += GetEmptyLine();
                }
            }

            output[i] = currentTopString;
            output[i] += GetRemainingEmptyLines(currentTopString, commonBottomString) + commonBottomString;
        }

        return output;
    }

    std::vector<std::string> PageBuilder::GetOptionSelectionPages(const GameInfo &gameInfo, const std::string &message, const std::vector<std::string> &options) const
    {
        const std::string commonTopString = GetTopBox() + GetTopLine() + GetGeneralGameSubPage(gameInfo) + GetEmptyLine() + GetNewLineLeftJustified(message, Colours::WHITE, "");
        const std::string commonBottomString = GetBottomLine() + GetBottomBox();

        std::vector<std::string> output(options.size());

        // Construct a page for each option selected.
        for (uint32_t i = 0; i < output.size(); i++)
        {
            std::string currentTopString = commonTopString;

            for (uint32_t j = 0; j < options.size(); j++)
            {
                if (i == j)
                {
                    currentTopString += GetNewLineLeftJustified(options[j], Colours::BLUE, g_SELECTOR);
                }

                else
                {
                    // + 1 to match above statement which will have an extra pad between option and selector
                    currentTopString += GetNewLineLeftJustified(std::string(g_SELECTOR.size() + 1, ' ') + options[j], Colours::WHITE, "");
                }
            }

            output[i] = currentTopString;
            output[i] += GetRemainingEmptyLines(currentTopString, commonBottomString) + commonBottomString;
        }

        return output;
    }

    std::vector<std::string> PageBuilder::GetPlayerCountOptionSelectionGamePages(const GameInfo &gameInfo) const
    {
        switch (m_currentPage)
        {
        case Pages::TICTACTOE:
        case Pages::HANGMAN:
            return GetOptionSelectionPages(gameInfo, "Please select the number of players:", {"0", "1", "2"});

        case Pages::BATTLESHIPS:
            return GetOptionSelectionPages(gameInfo, "Please select the number of players:", {"0", "1"});

        default:
            return {"The 'GetPlayerCountOptionSelectionGameDisplays' function does not support the current page type."};
        }
    }

    std::vector<std::string> PageBuilder::GetUserPlayerChoiceOptionSelectionGamePages(const GameInfo &gameInfo) const
    {
        switch (m_currentPage)
        {
        case Pages::TICTACTOE:
            return GetOptionSelectionPages(gameInfo, "Please select the player you would like to be:", {"PLAYER X", "PLAYER O"});

        case Pages::HANGMAN:
            return GetOptionSelectionPages(gameInfo, "Please select the player you would like to be:", {"GUESSER", "WORD SETTER"});

        default:
            return {"The 'GetUserPlayerChoiceOptionSelectionGameDisplays' function does not support the current page type."};
        }
    }

    std::vector<std::string> PageBuilder::GetAISpeedOptionSelectionGamePages(const GameInfo &gameInfo) const
    {
        switch (m_currentPage)
        {
        case Pages::TICTACTOE:
        case Pages::HANGMAN:
        case Pages::BATTLESHIPS:
            return GetOptionSelectionPages(gameInfo, "Please select the AI speed:", {"INSTANT", "FAST", "SLOW"});

        default:
            return {"The 'GetAISpeedOptionSelectionGameDisplays' function does not support the current page type."};
        }
    }

    std::string PageBuilder::GetPageWithMessage(const GameInfo &gameInfo, const std::string &message) const
    {
        const std::string commonTopString = GetTopBox() + GetTopLine() + GetGeneralGameSubPage(gameInfo) + GetEmptyLine() + GetNewLineLeftJustified(message, Colours::WHITE, "");
        const std::string commonBottomString = GetBottomLine() + GetBottomBox();

        return commonTopString + GetRemainingEmptyLines(commonTopString, commonBottomString) + commonBottomString;
    }

    std::string PageBuilder::GetUserCommandPage(const GameInfo &gameInfo) const
    {
        switch (m_currentPage)
        {
        case Pages::TICTACTOE:
            return GetPageWithMessage(gameInfo, gameInfo.ticTacToeStruct.currentPlayer + ", please enter your next command!");

        case Pages::HANGMAN:
            return GetPageWithMessage(gameInfo, "Guesser, please enter your next guess:");

        case Pages::BATTLESHIPS:
            return GetPageWithMessage(gameInfo, gameInfo.battleshipsStruct.currentPlayer + ", please enter your next command!");

        default:
            return "The 'GetUserCommandGameDisplay' function does not support the current page type.";
        }
    }

    std::string PageBuilder::GetAICommandPage(const GameInfo &gameInfo) const
    {
        switch (m_currentPage)
        {
        case Pages::TICTACTOE:
        case Pages::HANGMAN:
        case Pages::BATTLESHIPS:
            return GetPageWithMessage(gameInfo, "The AI is executing their next move!");

        default:
            return "The 'GetAISpeedOptionSelectionGameDisplays' function does not support the current page type.";
        }
    }

    std::string PageBuilder::GetGameOverPage(const GameInfo &gameInfo) const
    {
        std::string topString = GetTopBox() + GetTopLine() + GetGeneralGameSubPage(gameInfo) + GetEmptyLine() + GetNewLineCentred("GAME OVER", Colours::WHITE, "") + GetEmptyLine();
        const std::string bottomString = GetEmptyLine() + GetNewLineCentred("Press 'q' to quit OR any key to play again...", Colours::WHITE, "") + GetBottomLine() + GetBottomBox();

        switch (m_currentPage)
        {
        case Pages::TICTACTOE:
            if (gameInfo.ticTacToeStruct.hasWinner) // This game can be drawn unlike the others.
            {
                topString += GetNewLineCentred(gameInfo.ticTacToeStruct.currentPlayer + " has won! The game lasted " + std::to_string(gameInfo.ticTacToeStruct.turnCount) + " turns.", Colours::WHITE, "");
            }

            else
            {
                topString += GetNewLineCentred("The game is a draw! The game lasted " + std::to_string(gameInfo.ticTacToeStruct.turnCount) + " turns.", Colours::WHITE, "");
            }

            break;

        case Pages::HANGMAN:
            if (gameInfo.hangmanStruct.errorCount == g_HANGMAN_MAXIMUM_ERROR_COUNT)
            {
                topString += GetNewLineCentred("The word setter has won! The game lasted " + std::to_string(gameInfo.hangmanStruct.turnCount) + " turns!", Colours::WHITE, "");
            }

            else
            {
                topString += GetNewLineCentred("The guesser has won! The game lasted " + std::to_string(gameInfo.hangmanStruct.turnCount) + " turns.", Colours::WHITE, "");
            }

            break;

        case Pages::BATTLESHIPS:
            topString += GetNewLineCentred(gameInfo.battleshipsStruct.currentPlayer + " has won! The game lasted " + std::to_string(gameInfo.battleshipsStruct.turnCount) + " turns.", Colours::WHITE, "");
            break;

        default:
            return "The 'GetGameOverGameDisplay' function does not support the current page type.";
        }

        return topString + GetRemainingEmptyLines(topString, bottomString) + bottomString;
    }

    std::string PageBuilder::GetGeneralGameSubPage(const GameInfo &gameInfo) const
    {
        switch (m_currentPage)
        {
        case Pages::TICTACTOE:
            return GetTicTacToeSubPage(gameInfo);

        case Pages::HANGMAN:
            return GetHangmanSubPage(gameInfo);

        case Pages::BATTLESHIPS:
            return GetBattleshipsSubPage(gameInfo);

        default:
            return "The 'GetGeneralGameDisplay' function does not support the current page type.";
        }
    }

    // NOLINTBEGIN
    std::string PageBuilder::GetTicTacToeSubPage(const GameInfo &gameInfo) const
    {
        const std::array<std::array<char, 3>, 3> gameGrid = gameInfo.ticTacToeStruct.gameGrid;
        const std::string playerCount = gameInfo.ticTacToeStruct.playerCount, AISpeedName = gameInfo.ticTacToeStruct.AISpeedName;

        std::string Output;

        Output += GetNewLineLeftJustified(std::string("  ") + gameGrid[0][0] + " " + char(179) + " " + gameGrid[0][1] + " " + char(179) + " " + gameGrid[0][2], Colours::WHITE, "");

        Output += GetNewLineLeftJustified(std::string(" ") + (char)196 + (char)196 + (char)196 + (char)197 + (char)196 + (char)196 + (char)196 + char(197) + (char)196 + (char)196 + (char)196 + "    # of Players = " + playerCount, Colours::WHITE, "");

        Output += GetNewLineLeftJustified(std::string("  ") + gameGrid[1][0] + " " + char(179) + " " + gameGrid[1][1] + " " + char(179) + " " + gameGrid[1][2], Colours::WHITE, "");

        Output += GetNewLineLeftJustified(std::string(" ") + (char)196 + (char)196 + (char)196 + (char)197 + (char)196 + (char)196 + (char)196 + char(197) + (char)196 + (char)196 + (char)196 + "    AI Speed = " + AISpeedName, Colours::WHITE, "");

        Output += GetNewLineLeftJustified(std::string("  ") + gameGrid[2][0] + " " + char(179) + " " + gameGrid[2][1] + " " + char(179) + " " + gameGrid[2][2], Colours::WHITE, "");

        return Output;
    }

    std::string PageBuilder::GetHangmanSubPage(const GameInfo &gameInfo) const
    {
        const std::vector<char> incorrectGuesses = gameInfo.hangmanStruct.incorrectGuesses;
        const std::string currentGuessOfWord = gameInfo.hangmanStruct.currentGuessOfWord, wordToBeGuessed = gameInfo.hangmanStruct.wordToBeGuessed, playerCount = gameInfo.hangmanStruct.playerCount, AISpeedName = gameInfo.hangmanStruct.AISpeedName;
        const uint32_t errorCount = gameInfo.hangmanStruct.errorCount;

        std::string output;

        // Hangman State
        if (errorCount == 0)
            output += GetEmptyLine() + GetEmptyLine() + GetNewLineLeftJustified("                   # of Players = " + playerCount, Colours::WHITE, "") + GetEmptyLine() + GetNewLineLeftJustified("                   AI Speed = " + AISpeedName, Colours::WHITE, "") + GetEmptyLine() + GetEmptyLine();
        else if (errorCount == 1)
            output += GetEmptyLine() + GetNewLineLeftJustified("                                          Incorrect Guesses", Colours::WHITE, "") + GetNewLineLeftJustified("                   # of Players = " + playerCount, Colours::WHITE, "") + GetNewLineLeftJustified(std::string("                                          ") + incorrectGuesses[0], Colours::WHITE, "") + GetNewLineLeftJustified("                   AI Speed = " + AISpeedName, Colours::WHITE, "") + GetEmptyLine() + GetNewLineLeftJustified(std::string(" ") + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196, Colours::WHITE, "");
        else if (errorCount == 2)
            output += GetEmptyLine() + GetNewLineLeftJustified(std::string("     ") + (char)179 + "                                    Incorrect Guesses", Colours::WHITE, "") + GetNewLineLeftJustified(std::string("     ") + (char)179 + "             # of Players = " + playerCount, Colours::WHITE, "") + GetNewLineLeftJustified(std::string("     ") + (char)179 + "                                    " + incorrectGuesses[0] + "   " + incorrectGuesses[1], Colours::WHITE, "") + GetNewLineLeftJustified(std::string("     ") + (char)179 + "             AI Speed = " + AISpeedName, Colours::WHITE, "") + GetNewLineLeftJustified(std::string("     ") + (char)179, Colours::WHITE, "") + GetNewLineLeftJustified(std::string(" ") + (char)196 + (char)196 + (char)196 + (char)196 + (char)193 + (char)196 + (char)196 + (char)196 + (char)196, Colours::WHITE, "");
        else if (errorCount == 3)
            output += GetNewLineLeftJustified(std::string("     ") + (char)218 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196, Colours::WHITE, "") + GetNewLineLeftJustified(std::string("     ") + (char)179 + "                                    Incorrect Guesses", Colours::WHITE, "") + GetNewLineLeftJustified(std::string("     ") + (char)179 + "             # of Players = " + playerCount, Colours::WHITE, "") + GetNewLineLeftJustified(std::string("     ") + (char)179 + "                                    " + incorrectGuesses[0] + "   " + incorrectGuesses[1] + "   " + incorrectGuesses[2], Colours::WHITE, "") + GetNewLineLeftJustified(std::string("     ") + (char)179 + "             AI Speed = " + AISpeedName, Colours::WHITE, "") + GetNewLineLeftJustified(std::string("     ") + (char)179, Colours::WHITE, "") + GetNewLineLeftJustified(std::string(" ") + (char)196 + (char)196 + (char)196 + (char)196 + (char)193 + (char)196 + (char)196 + (char)196 + (char)196, Colours::WHITE, "");
        else if (errorCount == 4)
            output += GetNewLineLeftJustified(std::string("     ") + (char)218 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)191, Colours::WHITE, "") + GetNewLineLeftJustified(std::string("     ") + (char)179 + "       " + (char)179 + "                            Incorrect Guesses", Colours::WHITE, "") + GetNewLineLeftJustified(std::string("     ") + (char)179 + "             # of Players = " + playerCount, Colours::WHITE, "") + GetNewLineLeftJustified(std::string("     ") + (char)179 + "                                    " + incorrectGuesses[0] + "   " + incorrectGuesses[1] + "   " + incorrectGuesses[2] + "   " + incorrectGuesses[3], Colours::WHITE, "") + GetNewLineLeftJustified(std::string("     ") + (char)179 + "             AI Speed = " + AISpeedName, Colours::WHITE, "") + GetNewLineLeftJustified(std::string("     ") + (char)179, Colours::WHITE, "") + GetNewLineLeftJustified(std::string(" ") + (char)196 + (char)196 + (char)196 + (char)196 + (char)193 + (char)196 + (char)196 + (char)196 + (char)196, Colours::WHITE, "");
        else if (errorCount == 5)
            output += GetNewLineLeftJustified(std::string("     ") + (char)218 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)191, Colours::WHITE, "") + GetNewLineLeftJustified(std::string("     ") + (char)179 + "       " + (char)179 + "                            Incorrect Guesses", Colours::WHITE, "") + GetNewLineLeftJustified(std::string("     ") + (char)179 + "       O     # of Players = " + playerCount, Colours::WHITE, "") + GetNewLineLeftJustified(std::string("     ") + (char)179 + "                                    " + incorrectGuesses[0] + "   " + incorrectGuesses[1] + "   " + incorrectGuesses[2] + "   " + incorrectGuesses[3] + "   " + incorrectGuesses[4], Colours::WHITE, "") + GetNewLineLeftJustified(std::string("     ") + (char)179 + "             AI Speed = " + AISpeedName + "                       ", Colours::WHITE, "") + GetNewLineLeftJustified(std::string("     ") + (char)179, Colours::WHITE, "") + GetNewLineLeftJustified(std::string(" ") + (char)196 + (char)196 + (char)196 + (char)196 + (char)193 + (char)196 + (char)196 + (char)196 + (char)196, Colours::WHITE, "");
        else if (errorCount == 6)
            output += GetNewLineLeftJustified(std::string("     ") + (char)218 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)191, Colours::WHITE, "") + GetNewLineLeftJustified(std::string("     ") + (char)179 + "       " + (char)179 + "                            Incorrect Guesses", Colours::WHITE, "") + GetNewLineLeftJustified(std::string("     ") + (char)179 + "       O     # of Players = " + playerCount, Colours::WHITE, "") + GetNewLineLeftJustified(std::string("     ") + (char)179 + "       " + (char)179 + "                            " + incorrectGuesses[0] + "   " + incorrectGuesses[1] + "   " + incorrectGuesses[2] + "   " + incorrectGuesses[3] + "   " + incorrectGuesses[4], Colours::WHITE, "") + GetNewLineLeftJustified(std::string("     ") + (char)179 + "             AI Speed = " + AISpeedName, Colours::WHITE, "") + GetNewLineLeftJustified(std::string("     ") + (char)179 + "                                    " + incorrectGuesses[5], Colours::WHITE, "") + GetNewLineLeftJustified(std::string(" ") + (char)196 + (char)196 + (char)196 + (char)196 + (char)193 + (char)196 + (char)196 + (char)196 + (char)196, Colours::WHITE, "");
        else if (errorCount == 7)
            output += GetNewLineLeftJustified(std::string("     ") + (char)218 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)191, Colours::WHITE, "") + GetNewLineLeftJustified(std::string("     ") + (char)179 + "       " + (char)179 + "                            Incorrect Guesses", Colours::WHITE, "") + GetNewLineLeftJustified(std::string("     ") + (char)179 + "       O     # of Players = " + playerCount, Colours::WHITE, "") + GetNewLineLeftJustified(std::string("     ") + (char)179 + "       " + (char)179 + "                            " + incorrectGuesses[0] + "   " + incorrectGuesses[1] + "   " + incorrectGuesses[2] + "   " + incorrectGuesses[3] + "   " + incorrectGuesses[4], Colours::WHITE, "") + GetNewLineLeftJustified(std::string("     ") + (char)179 + "      /      AI Speed = " + AISpeedName, Colours::WHITE, "") + GetNewLineLeftJustified(std::string("     ") + (char)179 + "                                    " + incorrectGuesses[5] + "   " + incorrectGuesses[6], Colours::WHITE, "") + GetNewLineLeftJustified(std::string(" ") + (char)196 + (char)196 + (char)196 + (char)196 + (char)193 + (char)196 + (char)196 + (char)196 + (char)196, Colours::WHITE, "");
        else if (errorCount == 8)
            output += GetNewLineLeftJustified(std::string("     ") + (char)218 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)191, Colours::WHITE, "") + GetNewLineLeftJustified(std::string("     ") + (char)179 + "       " + (char)179 + "                            Incorrect Guesses", Colours::WHITE, "") + GetNewLineLeftJustified(std::string("     ") + (char)179 + "       O     # of Players = " + playerCount, Colours::WHITE, "") + GetNewLineLeftJustified(std::string("     ") + (char)179 + "       " + (char)179 + "                            " + incorrectGuesses[0] + "   " + incorrectGuesses[1] + "   " + incorrectGuesses[2] + "   " + incorrectGuesses[3] + "   " + incorrectGuesses[4], Colours::WHITE, "") + GetNewLineLeftJustified(std::string("     ") + (char)179 + "      / \\    AI Speed = " + AISpeedName, Colours::WHITE, "") + GetNewLineLeftJustified(std::string("     ") + (char)179 + "                                    " + incorrectGuesses[5] + "   " + incorrectGuesses[6] + "   " + incorrectGuesses[7], Colours::WHITE, "") + GetNewLineLeftJustified(std::string(" ") + (char)196 + (char)196 + (char)196 + (char)196 + (char)193 + (char)196 + (char)196 + (char)196 + (char)196, Colours::WHITE, "");
        else if (errorCount == 9)
            output += GetNewLineLeftJustified(std::string("     ") + (char)218 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)191, Colours::WHITE, "") + GetNewLineLeftJustified(std::string("     ") + (char)179 + "       " + (char)179 + "                            Incorrect Guesses", Colours::WHITE, "") + GetNewLineLeftJustified(std::string("     ") + (char)179 + "       O     # of Players = " + playerCount, Colours::WHITE, "") + GetNewLineLeftJustified(std::string("     ") + (char)179 + "      /" + (char)179 + "                            " + incorrectGuesses[0] + "   " + incorrectGuesses[1] + "   " + incorrectGuesses[2] + "   " + incorrectGuesses[3] + "   " + incorrectGuesses[4], Colours::WHITE, "") + GetNewLineLeftJustified(std::string("     ") + (char)179 + "      / \\    AI Speed = " + AISpeedName, Colours::WHITE, "") + GetNewLineLeftJustified(std::string("     ") + (char)179 + "                                    " + incorrectGuesses[5] + "   " + incorrectGuesses[6] + "   " + incorrectGuesses[7] + "   " + incorrectGuesses[8], Colours::WHITE, "") + GetNewLineLeftJustified(std::string(" ") + (char)196 + (char)196 + (char)196 + (char)196 + (char)193 + (char)196 + (char)196 + (char)196 + (char)196, Colours::WHITE, "");
        else if (errorCount == 10)
            output += GetNewLineLeftJustified(std::string("     ") + (char)218 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)191, Colours::WHITE, "") + GetNewLineLeftJustified(std::string("     ") + (char)179 + "       " + (char)179 + "                            Incorrect Guesses", Colours::WHITE, "") + GetNewLineLeftJustified(std::string("     ") + (char)179 + "       O     # of Players = " + playerCount, Colours::WHITE, "") + GetNewLineLeftJustified(std::string("     ") + (char)179 + "      /" + (char)179 + "\\                           " + incorrectGuesses[0] + "   " + incorrectGuesses[1] + "   " + incorrectGuesses[2] + "   " + incorrectGuesses[3] + "   " + incorrectGuesses[4], Colours::WHITE, "") + GetNewLineLeftJustified(std::string("     ") + (char)179 + "      / \\    AI Speed = " + AISpeedName, Colours::WHITE, "") + GetNewLineLeftJustified(std::string("     ") + (char)179 + "                                    " + incorrectGuesses[5] + "   " + incorrectGuesses[6] + "   " + incorrectGuesses[7] + "   " + incorrectGuesses[8] + "   " + incorrectGuesses[9], Colours::WHITE, "") + GetNewLineLeftJustified(std::string(" ") + (char)196 + (char)196 + (char)196 + (char)196 + (char)193 + (char)196 + (char)196 + (char)196 + (char)196, Colours::WHITE, "");

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

    std::string PageBuilder::GetBattleshipsSubPage(const GameInfo &gameInfo) const
    {
        const std::array<std::array<std::string, 10>, 10> boardOne = gameInfo.battleshipsStruct.boardOne, boardTwo = gameInfo.battleshipsStruct.boardTwo;
        const std::unordered_map<std::string, uint32_t> shipsRemainingOne = gameInfo.battleshipsStruct.shipsRemainingOne, shipsRemainingTwo = gameInfo.battleshipsStruct.shipsRemainingTwo;
        const std::string playerCount = gameInfo.battleshipsStruct.playerCount, AISpeedName = gameInfo.battleshipsStruct.AISpeedName;
        const bool isGameOver = gameInfo.battleshipsStruct.isGameOver;

        std::string Output;

        // Top row and letter co-ordinates of both boards
        Output += GetNewLineLeftJustified("                    Player One                                                                                       Player Two", Colours::WHITE, "");

        Output += (char)186 + std::string("   ");
        for (uint32_t i = 0; i < 2; i++)
        {
            Output += (char)218;
            Output.insert(Output.size(), 3, (char)196);
            for (uint32_t j = 0; j < 10; j++)
            {
                Output += (char)194;
                Output.insert(Output.size(), 3, (char)196);
            }
            Output += (char)191;

            if (i == 0)
                Output.insert(Output.size(), "                                                   ");
        }
        Output += std::string("   ") + (char)186 + "\n";

        Output += (char)186 + std::string("   ");
        for (uint32_t i = 0; i < 2; i++)
        {
            Output += (char)179 + std::string("   ") + (char)179 + " A " + (char)179 + " B " + (char)179 + " C " + (char)179 + " D " + (char)179 + " E " + (char)179 + " F " + (char)179 + " G " + (char)179 + " H " + (char)179 + " I " + (char)179 + " J " + (char)179;

            if (i == 0)
                Output += "                                                   ";
        }
        Output += std::string("   ") + (char)186 + "\n";

        // Main parts of both boards and centre information
        for (uint32_t i = 0; i < 10; i++)
        {
            // First Line
            // Left outer box edge
            Output += (char)186 + std::string("   ");

            // Player One Board horizontal dividers
            Output += (char)195;
            Output.insert(Output.size(), 3, (char)196);
            for (uint32_t j = 0; j < 10; j++)
            {
                Output += (char)197;
                Output.insert(Output.size(), 3, (char)196);
            }
            Output += (char)180;

            // Centre information
            if (i == 3)
                Output += "   Carrier                               Carrier   ";
            else if (i == 5) // Battleship
            {
                Output += "   ";
                for (uint32_t j = 0; j < 4; j++, Output += " ")
                {
                    if (j < shipsRemainingOne.at(g_BATTLESHIPS_BATTLESHIP_NAME))
                        Output.insert(Output.size(), 3, (char)178);
                    else
                        Output.insert(Output.size(), 3, (char)176);
                }
                Output += "              ";
                for (uint32_t j = 0; j < 4; j++, Output += " ")
                {
                    if (j < (4 - shipsRemainingTwo.at(g_BATTLESHIPS_BATTLESHIP_NAME)))
                        Output.insert(Output.size(), 3, (char)176);
                    else
                        Output.insert(Output.size(), 3, (char)178);
                }
                Output += "  ";
            }
            else if (i == 6)
                Output += "   Destroyer                           Destroyer   ";
            else if (i == 8) // Submarine
            {
                Output += "   ";
                for (uint32_t j = 0; j < 3; j++, Output += " ")
                {
                    if (j < shipsRemainingOne.at(g_BATTLESHIPS_SUBMARINE_NAME))
                        Output.insert(Output.size(), 3, (char)178);
                    else
                        Output.insert(Output.size(), 3, (char)176);
                }
                Output += "                      ";
                for (uint32_t j = 0; j < 3; j++, Output += " ")
                {
                    if (j < (3 - shipsRemainingTwo.at(g_BATTLESHIPS_SUBMARINE_NAME)))
                        Output.insert(Output.size(), 3, (char)176);
                    else
                        Output.insert(Output.size(), 3, (char)178);
                }
                Output += "  ";
            }
            else if (i == 9)
                Output += "   Patrol Boat                       Patrol Boat   ";
            else
                Output += "                                                   ";

            // Player Two Board horizontal dividers
            Output += (char)195;
            Output.insert(Output.size(), 3, (char)196);
            for (uint32_t j = 0; j < 10; j++)
            {
                Output += (char)197;
                Output.insert(Output.size(), 3, (char)196);
            }
            Output += (char)180 + std::string("   ") + (char)186 + "\n";

            // Second Line
            // Player one left outer box edge and number co-ord
            Output += (char)186 + std::string("   ") + (char)179 + " " + std::to_string(i) + " " + (char)179;

            // Player One board ships
            for (uint32_t j = 0; j < 10; j++)
            {
                if (boardOne[i][j] == g_BATTLESHIPS_CARRIER_NAME || boardOne[i][j] == g_BATTLESHIPS_BATTLESHIP_NAME || boardOne[i][j] == g_BATTLESHIPS_DESTROYER_NAME || boardOne[i][j] == g_BATTLESHIPS_SUBMARINE_NAME || boardOne[i][j] == g_BATTLESHIPS_PATROL_BOAT_NAME)
                    Output.insert(Output.size(), 3, (char)178);
                else if (boardOne[i][j] == "X")
                    Output.insert(Output.size(), 3, (char)176);
                else if (boardOne[i][j] == ".")
                    Output += std::string(" ") + (char)250 + " ";
                else
                    Output += "   ";
                Output += (char)179;
            }

            // Centre Information
            if (i == 0)
                Output += "                 # of Players = " + playerCount + "                ";
            else if (i == 1)
                Output += "                 AI Speed = " + AISpeedName + "                ";
            else if (i == 3) // Carrier
            {
                Output += "   ";
                for (uint32_t j = 0; j < 5; j++, Output += " ")
                {
                    if (j < shipsRemainingOne.at(g_BATTLESHIPS_CARRIER_NAME))
                        Output.insert(Output.size(), 3, (char)178);
                    else
                        Output.insert(Output.size(), 3, (char)176);
                }
                Output += "      ";
                for (uint32_t j = 0; j < 5; j++, Output += " ")
                {
                    if (j < (5 - shipsRemainingTwo.at(g_BATTLESHIPS_CARRIER_NAME)))
                        Output.insert(Output.size(), 3, (char)176);
                    else
                        Output.insert(Output.size(), 3, (char)178);
                }
                Output += "  ";
            }
            else if (i == 4)
                Output += "   Battleship                         Battleship   ";
            else if (i == 6) // Destroyer
            {
                Output += "   ";
                for (uint32_t j = 0; j < 3; j++, Output += " ")
                {
                    if (j < shipsRemainingOne.at(g_BATTLESHIPS_DESTROYER_NAME))
                        Output.insert(Output.size(), 3, (char)178);
                    else
                        Output.insert(Output.size(), 3, (char)176);
                }
                Output += "                      ";
                for (uint32_t j = 0; j < 3; j++, Output += " ")
                {
                    if (j < (3 - shipsRemainingTwo.at(g_BATTLESHIPS_DESTROYER_NAME)))
                        Output.insert(Output.size(), 3, (char)176);
                    else
                        Output.insert(Output.size(), 3, (char)178);
                }
                Output += "  ";
            }
            else if (i == 7)
                Output += "   Submarine                           Submarine   ";
            else if (i == 9) // Patrol Boat
            {
                Output += "   ";
                for (uint32_t j = 0; j < 2; j++, Output += " ")
                {
                    if (j < shipsRemainingOne.at(g_BATTLESHIPS_PATROL_BOAT_NAME))
                        Output.insert(Output.size(), 3, (char)178);
                    else
                        Output.insert(Output.size(), 3, (char)176);
                }
                Output += "                              ";
                for (uint32_t j = 0; j < 2; j++, Output += " ")
                {
                    if (j < (2 - shipsRemainingTwo.at(g_BATTLESHIPS_PATROL_BOAT_NAME)))
                        Output.insert(Output.size(), 3, (char)176);
                    else
                        Output.insert(Output.size(), 3, (char)178);
                }
                Output += "  ";
            }
            else
                Output += "                                                   ";

            // Player Two left outer box edge and number co-ord
            Output += (char)179 + std::string(" ") + std::to_string(i) + " " + (char)179;

            // Player Two board ships
            for (uint32_t j = 0; j < 10; j++)
            {
                if ((isGameOver || playerCount == "0  ") && (boardTwo[i][j] == g_BATTLESHIPS_CARRIER_NAME || boardTwo[i][j] == g_BATTLESHIPS_BATTLESHIP_NAME || boardTwo[i][j] == g_BATTLESHIPS_DESTROYER_NAME || boardTwo[i][j] == g_BATTLESHIPS_SUBMARINE_NAME || boardTwo[i][j] == g_BATTLESHIPS_PATROL_BOAT_NAME))
                    Output.insert(Output.size(), 3, (char)178);
                else if (boardTwo[i][j] == "X")
                    Output.insert(Output.size(), 3, (char)176);
                else if (boardTwo[i][j] == ".")
                    Output += std::string(" ") + (char)250 + " ";
                else
                    Output += "   ";
                Output += (char)179;
            }
            Output += std::string("   ") + (char)186 + "\n";
        }

        // Bottom row of both boards
        Output += (char)186 + std::string("   ");
        for (uint32_t i = 0; i < 2; i++)
        {
            Output += (char)192;
            Output.insert(Output.size(), 3, (char)196);
            for (uint32_t j = 0; j < 10; j++)
            {
                Output += (char)193;
                Output.insert(Output.size(), 3, (char)196);
            }
            Output += (char)217;

            if (i == 0)
                Output += "                                                   ";
        }

        Output += std::string("   ") + (char)186 + "\n";

        return Output;
    }

    // NOLINTEND
} // namespace TerminalGames
