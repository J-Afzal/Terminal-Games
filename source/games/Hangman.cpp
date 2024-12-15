#include <algorithm>
#include <cctype>
#include <chrono>
#include <cstdint>
#include <fstream>
#include <iosfwd>
#include <iostream>
#include <regex>
#include <string>
#include <thread>
#include <vector>

#include "games/Hangman.hpp"
#include "helpers/Exceptions.hpp"
#include "helpers/PageBuilder.hpp"
#include "helpers/Terminal.hpp"

Hangman::Hangman(const bool& outputIsOnlyASCII)
{
    m_pageBuilder.SetProperties(Pages::HANGMAN, outputIsOnlyASCII);
    m_randomNumberGenerator.seed(std::chrono::system_clock::now().time_since_epoch().count());
}

void Hangman::SetupGame()
{
    m_movesRemaining.reserve(26);
    m_movesRemaining = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    m_incorrectGuesses.clear();
    m_wordToBeGuessed = "";
    m_currentGuessOfWord = "";
    m_playerCount = "N/A";
    m_AISpeedName = "N/A";
    m_errorCount = 0;
    m_turnCount = 0;
    m_hasWinner = false;
    LoadWords();
}

void Hangman::LoadWords()
{
    // Words.txt contains a list of the ~1,000 most used words in English from:
    // See: https://www.ef.co.uk/english-resources/english-vocabulary/top-1000-words/
    std::ifstream WordsFile("../resources/Words.txt");
    if (WordsFile.is_open())
    {
        m_words.clear();

        std::string Word;
        while(std::getline(WordsFile, Word))
            m_words.push_back(Word);

        WordsFile.close();
    }
    else
    {
        WordsFile.close();
        throw Exceptions::HangmanWordsNotFound();
    }
}

void Hangman::UpdateGameInfo()
{
    m_gameInfo.hangmanStruct = { m_incorrectGuesses, m_currentGuessOfWord, m_wordToBeGuessed, m_playerCount, m_AISpeedName, m_errorCount, m_turnCount };
}

void Hangman::GetUserOptions()
{
    GetPlayerCount();

    if (m_playerCount == "0  ")
    {
        m_userIsGuesser = false;
        GetAISpeed();
        GetWordFromAI();
    }

    else if (m_playerCount == "1  ")
    {
        GetUserPlayerChoice();
        GetAISpeed();

        if (!m_userIsGuesser)
            GetWordFromUser();
        else
            GetWordFromAI();
    }

    else if (m_playerCount == "2  ")
    {
        m_userIsGuesser = true;
        GetWordFromUser();
    }

    for (uint32_t i = 0; i < m_wordToBeGuessed.size(); i++)
        m_currentGuessOfWord.push_back('_');
}

void Hangman::GetPlayerCount()
{
    std::vector<std::string> menus = m_pageBuilder.GetPlayerCountOptionSelectionGamePages(m_gameInfo);
    m_playerCount = std::to_string(Terminal::GetUserChoiceFromGameMenus(menus)) + "  ";
}

void Hangman::GetUserPlayerChoice()
{
    std::vector<std::string> menus = m_pageBuilder.GetUserPlayerChoiceOptionSelectionGamePages(m_gameInfo);
    Terminal::GetUserChoiceFromGameMenus(menus) == 0 ? m_userIsGuesser = true : m_userIsGuesser = false;
}

void Hangman::GetAISpeed()
{
    std::vector<std::string> menus = m_pageBuilder.GetAISpeedOptionSelectionGamePages(m_gameInfo);
    m_AISpeed = Terminal::GetUserChoiceFromGameMenus(menus);

    if (m_AISpeed == 0)
        m_AISpeedName = "INSTANT";
    else if (m_AISpeed == 1)
        m_AISpeedName = "FAST";
    else // == 2
        m_AISpeedName = "SLOW";
}

void Hangman::GetWordFromUser()
{
    const std::string output = m_pageBuilder.GetPageWithMessage(m_gameInfo, "Please enter the word to be guessed:");

    std::string input;

    while (true)
    {
        Terminal::PrintOutput(output);

        Terminal::SetCursorPosition(39, 13);

        std::getline(std::cin, input);

        if (input == "q")
            throw Exceptions::QuitGame();

        if (input.size() < 3 || input.size() > 14)
            continue;

        // Capitalise word
        std::transform(input.begin(), input.end(), input.begin(), ::toupper);

        if (std::regex_match(input, std::regex("^[A-Za-z]+$")))
        {
            m_wordToBeGuessed = input;
            return;
        }
    }
}

void Hangman::GetWordFromAI()
{
    m_wordToBeGuessed = m_words[m_randomNumberGenerator() % m_words.size()];
}

bool Hangman::IsGameOver()
{
    if (m_errorCount == 10)
    {
        m_hasWinner = true;
        return m_hasWinner;
    }

    for (uint32_t i = 0; i < m_wordToBeGuessed.size(); i++)
        if (m_wordToBeGuessed[i] != m_currentGuessOfWord[i])
            return false;

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

    uint32_t KeyPress, CurrentSelection = 0;
    while (true)
    {
        Terminal::SetCursorPosition(41, 13);

        std::cout << std::string("\x1B[1;34m") + m_movesRemaining[CurrentSelection] + "\x1B[1;37m"; // Make it blue

        KeyPress = Terminal::GetNextKeyPress();

        if (KeyPress == '\r') // enter key
        {
            CheckGuessAndUpdateCurrentGuess(m_movesRemaining[CurrentSelection]);
            return;
        }
        else if (KeyPress == 72) // up arrow key
            CurrentSelection == 0 ? CurrentSelection = (uint32_t)m_movesRemaining.size() - 1 : --CurrentSelection;
        else if (KeyPress == 80) // down arrow key
            CurrentSelection == uint32_t(m_movesRemaining.size() - 1) ? CurrentSelection = 0 : ++CurrentSelection;
        else if (KeyPress == 'q')
            throw Exceptions::QuitGame();
        else
        {
            auto Command = std::find(m_movesRemaining.begin(), m_movesRemaining.end(), KeyPress - 32);
            if (Command != m_movesRemaining.end())
                CurrentSelection = (int)std::distance(m_movesRemaining.begin(), Command);
        }
    }
}

void Hangman::ExecuteAICommand()
{
    if (m_AISpeed != 0)
    {
        Terminal::PrintOutput(m_pageBuilder.GetAICommandPage(m_gameInfo));
        std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(m_AISpeed));
    }

    m_AICommand = m_movesRemaining[m_randomNumberGenerator() % m_movesRemaining.size()];

    CheckGuessAndUpdateCurrentGuess(m_AICommand);
}

void Hangman::CheckGuessAndUpdateCurrentGuess(const char& guess)
{
    bool IsGuessCorrect = false;
    for (uint32_t i = 0; i < m_wordToBeGuessed.size(); i++)
        if (m_wordToBeGuessed[i] == guess)
        {
            IsGuessCorrect = true;
            m_currentGuessOfWord[i] = guess;
        }

    if (!IsGuessCorrect)
    {
        m_incorrectGuesses.push_back(guess);
        m_errorCount++;
    }

    m_movesRemaining.erase(std::find(m_movesRemaining.begin(), m_movesRemaining.end(), guess));
    m_turnCount++;
}

void Hangman::GameOver()
{
    Terminal::PrintOutput(m_pageBuilder.GetGameOverPage(m_gameInfo));

    if (Terminal::GetNextKeyPress() == 'q')
        throw Exceptions::QuitGame();
}
