#include <algorithm>
#include <cctype>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <iterator>
#include <regex>
#include <string>
#include <thread>
#include <vector>

#include "games/Hangman.hpp"
#include "helpers/Globals.hpp"
#include "helpers/PageBuilder.hpp"
#include "helpers/Terminal.hpp"

namespace TerminalGames
{
    Hangman::Hangman(const bool &p_useAnsiEscapeCodes) : m_computerSpeed(0),
                                                         m_turnCount(0),
                                                         m_currentLetterSelected(0),
                                                         m_hasSavedGameOptions(false),
                                                         m_isGameOver(false),
                                                         m_saveGameOptions(false)
    {
        m_pageBuilder.SetProperties(Pages::HANGMAN, p_useAnsiEscapeCodes);
        m_randomNumberGenerator.seed(std::chrono::system_clock::now().time_since_epoch().count());
    }

    void Hangman::SetupGame()
    {
        m_commandsRemaining = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
        m_currentLetterSelected = 'A';
        m_incorrectGuesses.clear();
        m_currentGuessOfWord = "";
        m_wordToBeGuessed = "";
        m_turnCount = 0;
        m_isGameOver = false;
    }

    void Hangman::GetUserOptions()
    {
        if (!(m_saveGameOptions && m_hasSavedGameOptions))
        {
            m_computerSpeedName = Globals::G_GAME_UNKNOWN_OPTION;
            m_playerCount = Globals::G_GAME_UNKNOWN_OPTION;
            m_userPlayerChoice = Globals::G_GAME_UNKNOWN_OPTION;

            GetPlayerCount();

            if (m_playerCount == "0")
            {
                GetComputerSpeed();
            }

            if (m_playerCount == "1")
            {
                GetComputerSpeed();
                GetUserPlayerChoice();
            }

            m_hasSavedGameOptions = true;
        }

        if (m_userPlayerChoice == Globals::G_HANGMAN_WORD_SETTER || m_playerCount == "2")
        {
            GetWordFromUser();
        }

        else
        {
            GetWordFromComputer();
        }

        m_currentGuessOfWord.insert(0, m_wordToBeGuessed.size(), Globals::G_HANGMAN_HIDDEN_LETTER);
    }

    void Hangman::UpdateGameInfo()
    {
        m_gameInfo.m_hangmanGameInfo = {
            .m_incorrectGuesses = m_incorrectGuesses,
            .m_computerSpeedName = m_computerSpeedName,
            .m_currentGuessOfWord = m_currentGuessOfWord,
            .m_playerCount = m_playerCount,
            .m_wordToBeGuessed = m_wordToBeGuessed,
            .m_turnCount = m_turnCount,
            .m_currentLetterSelected = m_currentLetterSelected,
            .m_isGameOver = m_isGameOver,
        };
    }

    bool Hangman::IsGameOver()
    {
        if (m_incorrectGuesses.size() == Globals::G_HANGMAN_MAXIMUM_ERROR_COUNT)
        {
            m_isGameOver = true;
            return m_isGameOver;
        }

        for (uint32_t i = 0; i < m_wordToBeGuessed.size(); i++)
        {
            if (m_wordToBeGuessed[i] != m_currentGuessOfWord[i])
            {
                return false;
            }
        }

        m_isGameOver = true;
        return m_isGameOver;
    }

    void Hangman::ToggleCurrentPlayer() {}

    bool Hangman::IsCurrentTurnUsers()
    {
        return m_userPlayerChoice == Globals::G_HANGMAN_GUESSER || m_playerCount == "2";
    }

    void Hangman::ExecuteUserCommand()
    {
        uint32_t keyPress = 0;
        uint32_t currentSelection = 0;

        while (true)
        {
            m_gameInfo.m_hangmanGameInfo.m_currentLetterSelected = m_commandsRemaining[currentSelection];

            Terminal::PrintOutput(m_pageBuilder.GetUserCommandPage(m_gameInfo));

            keyPress = Terminal::GetNextKeyPress();

            switch (keyPress)
            {
            case Globals::G_TERMINAL_QUIT_KEY:
                Terminal::GetUserChoiceFromQuitMenus(m_pageBuilder.GetQuitOptionSelectionPage());
                continue;

            case Globals::G_TERMINAL_ENTER_KEY:
                ExecuteGeneralCommand(m_commandsRemaining[currentSelection]);
                return;

            case Globals::G_TERMINAL_UP_ARROW_KEY:
                currentSelection == 0 ? currentSelection = m_commandsRemaining.size() - 1 : --currentSelection;
                break;

            case Globals::G_TERMINAL_DOWN_ARROW_KEY:
                currentSelection == (m_commandsRemaining.size() - 1) ? currentSelection = 0 : ++currentSelection;
                break;

            default:
            {
                const auto COMMAND_FIND_LOCATION = Globals::ImplementStdRangesFind(m_commandsRemaining.begin(), m_commandsRemaining.end(), keyPress - Globals::G_HANGMAN_KEY_PRESS_CHAR_OFFSET);

                if (COMMAND_FIND_LOCATION != m_commandsRemaining.end())
                {
                    currentSelection = static_cast<uint32_t>(std::distance(m_commandsRemaining.begin(), COMMAND_FIND_LOCATION));
                }
            }
            }
        }
    }

    void Hangman::ExecuteComputerCommand()
    {
        Terminal::PrintOutput(m_pageBuilder.GetComputerCommandPage(m_gameInfo));

        std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(m_computerSpeed));

        const char COMPUTER_COMMAND = m_commandsRemaining[m_randomNumberGenerator() % m_commandsRemaining.size()];

        ExecuteGeneralCommand(COMPUTER_COMMAND);
    }

    void Hangman::GameOver()
    {
        Terminal::GetUserChoiceFromGameOverMenu(m_pageBuilder.GetGameOverPage(m_gameInfo), m_pageBuilder.GetQuitOptionSelectionPage());
    }

    void Hangman::RestartGame()
    {
        m_saveGameOptions = true;
    }

    void Hangman::ResetGame()
    {
        m_saveGameOptions = false;
        m_hasSavedGameOptions = false;
    }

    void Hangman::GetPlayerCount()
    {
        UpdateGameInfo();

        const std::vector<std::string> MENUS = m_pageBuilder.GetPlayerCountOptionSelectionGamePages(m_gameInfo);
        const std::vector<std::string> QUIT_MENUS = m_pageBuilder.GetQuitOptionSelectionPage();
        m_playerCount = Globals::G_GAME_MAX_TWO_PLAYERS_OPTIONS[Terminal::GetUserChoiceFromGameMenus(MENUS, QUIT_MENUS)];
    }

    void Hangman::GetUserPlayerChoice()
    {
        UpdateGameInfo();

        const std::vector<std::string> MENUS = m_pageBuilder.GetUserPlayerChoiceOptionSelectionGamePages(m_gameInfo);
        const std::vector<std::string> QUIT_MENUS = m_pageBuilder.GetQuitOptionSelectionPage();
        m_userPlayerChoice = Globals::G_HANGMAN_PLAYER_CHOICE_OPTIONS[Terminal::GetUserChoiceFromGameMenus(MENUS, QUIT_MENUS)];
    }

    void Hangman::GetComputerSpeed()
    {
        UpdateGameInfo();

        const std::vector<std::string> MENUS = m_pageBuilder.GetComputerSpeedOptionSelectionGamePages(m_gameInfo);
        const std::vector<std::string> QUIT_MENUS = m_pageBuilder.GetQuitOptionSelectionPage();
        m_computerSpeed = Terminal::GetUserChoiceFromGameMenus(MENUS, QUIT_MENUS);
        m_computerSpeedName = Globals::G_GAME_COMPUTER_SPEED_OPTIONS[m_computerSpeed];
    }

    void Hangman::GetWordFromUser()
    {
        UpdateGameInfo();

        std::string input;
        input.reserve(Globals::G_HANGMAN_MAXIMUM_WORD_SIZE + 1);

        while (true)
        {
            Terminal::PrintOutput(m_pageBuilder.GetPageWithMessage(m_gameInfo, "Please enter the word to be guessed:"));

            Terminal::SetCursorPosition(Globals::G_HANGMAN_GET_WORD_FROM_USER_COLUMN, Globals::G_HANGMAN_USER_INPUT_ROW);

            std::getline(std::cin, input);

            if (input[0] == Globals::G_TERMINAL_QUIT_KEY)
            {
                Terminal::GetUserChoiceFromQuitMenus(m_pageBuilder.GetQuitOptionSelectionPage());
                continue;
            }

            if (input.size() < Globals::G_HANGMAN_MINIMUM_WORD_SIZE || input.size() > Globals::G_HANGMAN_MAXIMUM_WORD_SIZE)
            {
                continue;
            }

            std::ranges::transform(input.begin(), input.end(), input.begin(), ::toupper);

            if (std::regex_match(input, std::regex("^[A-Z]+$")))
            {
                m_wordToBeGuessed = input;
                return;
            }
        }
    }

    void Hangman::GetWordFromComputer()
    {
        m_wordToBeGuessed = Globals::G_HANGMAN_COMPUTER_WORDS.at(m_randomNumberGenerator() % Globals::G_HANGMAN_COMPUTER_WORDS.size());
    }

    void Hangman::ExecuteGeneralCommand(const char &p_guess)
    {
        bool isGuessCorrect = false;

        for (uint32_t i = 0; i < m_wordToBeGuessed.size(); i++)
        {
            if (m_wordToBeGuessed[i] == p_guess)
            {
                isGuessCorrect = true;
                m_currentGuessOfWord[i] = p_guess;
            }
        }

        if (!isGuessCorrect)
        {
            m_incorrectGuesses.push_back(p_guess);
        }

        m_commandsRemaining.erase(Globals::ImplementStdRangesFind(m_commandsRemaining.begin(), m_commandsRemaining.end(), p_guess));
        m_turnCount++;
    }
}
