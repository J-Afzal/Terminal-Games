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

#include "Constants.hpp"
#include "Exceptions.hpp"
#include "games/Hangman.hpp"
#include "helpers/PageBuilder.hpp"
#include "helpers/Terminal.hpp"

namespace TerminalGames
{
    Hangman::Hangman(const bool &onlyUseASCII) // NOLINT(cert-msc32-c,cert-msc51-cpp,cppcoreguidelines-pro-type-member-init,hicpp-member-init)
    {
        m_pageBuilder.SetProperties(Pages::HANGMAN, onlyUseASCII);
        m_randomNumberGenerator.seed(std::chrono::system_clock::now().time_since_epoch().count());
    }

    void Hangman::SetupGame()
    {
        m_commandsRemaining.reserve(g_HANGMAN_NUMBER_OF_LETTERS_IN_THE_ALPHABET);
        m_commandsRemaining = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
        m_incorrectGuesses.clear();
        m_computerSpeedName = "N/A";
        m_currentGuessOfWord = "";
        m_playerCount = "N/A";
        m_wordToBeGuessed = "";
        m_errorCount = 0;
        m_turnCount = 0;
        m_hasWinner = false;
    }

    void Hangman::UpdateGameInfo()
    {
        m_gameInfo.hangmanStruct = {
            .incorrectGuesses = m_incorrectGuesses,
            .computerSpeedName = m_computerSpeedName,
            .currentGuessOfWord = m_currentGuessOfWord,
            .playerCount = m_playerCount,
            .wordToBeGuessed = m_wordToBeGuessed,
            .errorCount = m_errorCount,
            .turnCount = m_turnCount};
    }

    void Hangman::GetUserOptions()
    {
        GetPlayerCount();

        if (m_playerCount == "0  ")
        {
            m_userIsGuesser = false;
            GetComputerSpeed();
            GetWordFromComputer();
        }

        else if (m_playerCount == "1  ")
        {
            GetUserPlayerChoice();
            GetComputerSpeed();

            if (!m_userIsGuesser)
            {
                GetWordFromUser();
            }

            else
            {
                GetWordFromComputer();
            }
        }

        else if (m_playerCount == "2  ")
        {
            m_userIsGuesser = true;
            GetWordFromUser();
        }

        for (uint32_t i = 0; i < m_wordToBeGuessed.size(); i++)
        {
            m_currentGuessOfWord.push_back('_');
        }

        UpdateGameInfo();
    }

    bool Hangman::IsGameOver()
    {
        if (m_errorCount == g_HANGMAN_MAXIMUM_ERROR_COUNT)
        {
            m_hasWinner = true;
            return m_hasWinner;
        }

        for (uint32_t i = 0; i < m_wordToBeGuessed.size(); i++)
        {
            if (m_wordToBeGuessed[i] != m_currentGuessOfWord[i])
            {
                return false;
            }
        }

        m_hasWinner = true;
        return m_hasWinner;
    }

    void Hangman::ToggleCurrentPlayer() {}

    bool Hangman::IsCurrentTurnUsers()
    {
        return m_userIsGuesser;
    }

    void Hangman::ExecuteUserCommand()
    {
        Terminal::PrintOutput(m_pageBuilder.GetUserCommandPage(m_gameInfo));

        uint32_t keyPress = 0;
        uint32_t currentSelection = 0;

        while (true)
        {
            Terminal::SetCursorPosition(41, 13); // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

            std::cout << std::string("\x1B[1;34m") + m_commandsRemaining[currentSelection] + "\x1B[1;37m"; // Make it blue

            keyPress = Terminal::GetNextKeyPress();

            if (keyPress == g_QUIT_KEY)
            {
                throw Exceptions::QuitGame();
            }

            if (keyPress == g_ENTER_KEY)
            {
                ExecuteGeneralCommand(m_commandsRemaining[currentSelection]);
                return;
            }

            if (keyPress == g_UP_ARROW_KEY)
            {
                currentSelection == 0 ? currentSelection = m_commandsRemaining.size() - 1 : --currentSelection;
            }

            else if (keyPress == g_DOWN_ARROW_KEY)
            {
                currentSelection == (m_commandsRemaining.size() - 1) ? currentSelection = 0 : ++currentSelection;
            }

            else
            {
                auto commandFindLocation = ImplementStdRangesFind(m_commandsRemaining.begin(), m_commandsRemaining.end(), keyPress - 32); // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

                if (commandFindLocation != m_commandsRemaining.end())
                {
                    currentSelection = static_cast<uint32_t>(std::distance(m_commandsRemaining.begin(), commandFindLocation));
                }
            }
        }
    }

    void Hangman::ExecuteComputerCommand()
    {
        Terminal::PrintOutput(m_pageBuilder.GetComputerCommandPage(m_gameInfo));

        if (m_computerSpeed != 0)
        {
            std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(m_computerSpeed));
        }

        const char computerCommand = m_commandsRemaining[m_randomNumberGenerator() % m_commandsRemaining.size()];

        ExecuteGeneralCommand(computerCommand);
    }

    void Hangman::GameOver()
    {
        Terminal::PrintOutput(m_pageBuilder.GetGameOverPage(m_gameInfo));

        if (Terminal::GetNextKeyPress() == 'q')
        {
            throw Exceptions::QuitGame();
        }
    }

    void Hangman::GetPlayerCount()
    {
        UpdateGameInfo();

        const std::vector<std::string> menus = m_pageBuilder.GetPlayerCountOptionSelectionGamePages(m_gameInfo);
        m_playerCount = std::to_string(Terminal::GetUserChoiceFromGameMenus(menus)) + "  ";
    }

    void Hangman::GetUserPlayerChoice()
    {
        UpdateGameInfo();

        const std::vector<std::string> menus = m_pageBuilder.GetUserPlayerChoiceOptionSelectionGamePages(m_gameInfo);
        Terminal::GetUserChoiceFromGameMenus(menus) == 0 ? m_userIsGuesser = true : m_userIsGuesser = false;
    }

    void Hangman::GetComputerSpeed()
    {
        UpdateGameInfo();

        const std::vector<std::string> menus = m_pageBuilder.GetComputerSpeedOptionSelectionGamePages(m_gameInfo);
        m_computerSpeed = Terminal::GetUserChoiceFromGameMenus(menus);

        if (m_computerSpeed == 0)
        {
            m_computerSpeedName = "INSTANT";
        }

        else if (m_computerSpeed == 1)
        {
            m_computerSpeedName = "FAST";
        }

        else // == 2
        {
            m_computerSpeedName = "SLOW";
        }
    }

    void Hangman::GetWordFromUser()
    {
        UpdateGameInfo();

        const std::string output = m_pageBuilder.GetPageWithMessage(m_gameInfo, "Please enter the word to be guessed:");

        std::string input;

        while (true)
        {
            Terminal::PrintOutput(output);

            Terminal::SetCursorPosition(39, 13); // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

            std::getline(std::cin, input);

            if (input == "q")
            {
                throw Exceptions::QuitGame();
            }

            if (input.size() < g_HANGMAN_MINIMUM_WORD_LENGTH || input.size() > g_HANGMAN_MAXIMUM_WORD_LENGTH)
            {
                continue;
            }

            // Capitalise word
            std::ranges::transform(input.begin(), input.end(), input.begin(), ::toupper, {});

            if (std::regex_match(input, std::regex("^[A-Za-z]+$")))
            {
                m_wordToBeGuessed = input;
                return;
            }
        }
    }

    void Hangman::GetWordFromComputer()
    {
        m_wordToBeGuessed = m_WORDS[m_randomNumberGenerator() % m_WORDS.size()]; // NOLINT(cppcoreguidelines-pro-bounds-constant-array-index)
    }

    void Hangman::ExecuteGeneralCommand(const char &guess)
    {
        bool isGuessCorrect = false;
        for (uint32_t i = 0; i < m_wordToBeGuessed.size(); i++)
        {
            if (m_wordToBeGuessed[i] == guess)
            {
                isGuessCorrect = true;
                m_currentGuessOfWord[i] = guess;
            }
        }

        if (!isGuessCorrect)
        {
            m_incorrectGuesses.push_back(guess);
            m_errorCount++;
        }

        m_commandsRemaining.erase(ImplementStdRangesFind(m_commandsRemaining.begin(), m_commandsRemaining.end(), guess));
        m_turnCount++;
    }
} // namespace TerminalGames
