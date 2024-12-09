/**
 * @file Hangman.cpp
 * @author Junaid Afzal
 * @brief Implementation of Hangman.hpp
 * @version 1.0
 * @date 07-11-2021
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <iostream>
#include <fstream>
#include <regex>

#include "games/Hangman.hpp"

Hangman::Hangman(const bool& outputIsOnlyASCII)
{
    m_stringBuilder.SetProperties("Hangman", "q = quit to main menu", 62, outputIsOnlyASCII);
    m_randomNumberGenerator.seed(std::chrono::system_clock::now().time_since_epoch().count());
}

void Hangman::SetupGame()
{
    m_movesRemaining.reserve(26);
    m_movesRemaining = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    m_incorrectGuesses.clear();
    m_wordToBeGuessed = "";
    m_currentGuessOfWord = "";
    m_PlayerCount = "N/A";
    m_speedNameAI = "N/A";
    m_errorCount = 0;
    m_turnCount = 0;
    m_hasWinner = false;
    LoadWords();

    GetPlayerCount();

    if (m_PlayerCount == "0  ")
    {
        m_userIsGuesser = false;
        GetAISpeed();
        GetWordFromAI();
    }

    else if (m_PlayerCount == "1  ")
    {
        GetPlayerChoiceFromUser();
        GetAISpeed();

        if (!m_userIsGuesser)
            GetWordFromUser();
        else
            GetWordFromAI();
    }

    else if (m_PlayerCount == "2  ")
    {
        m_userIsGuesser = true;
        GetWordFromUser();
    }

    for (uint32_t i = 0; i < m_wordToBeGuessed.size(); i++)
        m_currentGuessOfWord.push_back('_');
}

void Hangman::LoadWords()
{
    // Words.txt contains a list of the ~1,000 most used word in English from:
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

void Hangman::GetPlayerCount()
{
    std::vector<std::string> Menus(3);
    std::string GameDisplay = GetGameDisplay() + m_stringBuilder.AddNewLineLeftJustified(" Please select the number of players:");

    Menus[0] = GameDisplay;
    Menus[0] += m_stringBuilder.AddNewLineLeftJustified(" > 0", Colours::BLUE);
    Menus[0] += m_stringBuilder.AddNewLineLeftJustified("   1");
    Menus[0] += m_stringBuilder.AddNewLineLeftJustified("   2");
    Menus[0] += m_stringBuilder.AddEmptyLine() + m_stringBuilder.AddBottomLine() + m_stringBuilder.AddBottomBox();

    Menus[1] = GameDisplay;
    Menus[1] += m_stringBuilder.AddNewLineLeftJustified("   0");
    Menus[1] += m_stringBuilder.AddNewLineLeftJustified(" > 1", Colours::BLUE);
    Menus[1] += m_stringBuilder.AddNewLineLeftJustified("   2");
    Menus[1] += m_stringBuilder.AddEmptyLine() + m_stringBuilder.AddBottomLine() + m_stringBuilder.AddBottomBox();

    Menus[2] = GameDisplay;
    Menus[2] += m_stringBuilder.AddNewLineLeftJustified("   0");
    Menus[2] += m_stringBuilder.AddNewLineLeftJustified("   1");
    Menus[2] += m_stringBuilder.AddNewLineLeftJustified(" > 2", Colours::BLUE);
    Menus[2] += m_stringBuilder.AddEmptyLine() + m_stringBuilder.AddBottomLine() + m_stringBuilder.AddBottomBox();

    m_PlayerCount = std::to_string(Terminal::GetUserChoiceFromGameMenus(Menus)) + "  ";
}

void Hangman::GetPlayerChoiceFromUser()
{
    std::vector<std::string> Menus(2);
    std::string GameDisplay = GetGameDisplay() + m_stringBuilder.AddNewLineLeftJustified(" Please select what player you would like to be:");

    Menus[0] = GameDisplay;
    Menus[0] += m_stringBuilder.AddNewLineLeftJustified(" > GUESSER", Colours::BLUE);
    Menus[0] += m_stringBuilder.AddNewLineLeftJustified("   WORD SETTER");
    Menus[0] += m_stringBuilder.AddEmptyLine() + m_stringBuilder.AddEmptyLine() + m_stringBuilder.AddBottomLine() + m_stringBuilder.AddBottomBox();

    Menus[1] = GameDisplay;
    Menus[1] += m_stringBuilder.AddNewLineLeftJustified("   GUESSER");
    Menus[1] += m_stringBuilder.AddNewLineLeftJustified(" > WORD SETTER", Colours::BLUE);
    Menus[1] += m_stringBuilder.AddEmptyLine() + m_stringBuilder.AddEmptyLine() + m_stringBuilder.AddBottomLine() + m_stringBuilder.AddBottomBox();

    Terminal::GetUserChoiceFromGameMenus(Menus) == 0 ? m_userIsGuesser = true : m_userIsGuesser = false;
}

void Hangman::GetAISpeed()
{
    std::vector<std::string> Menus(3);
    std::string GameDisplay = GetGameDisplay() + m_stringBuilder.AddNewLineLeftJustified(" Please select the AI speed:");

    Menus[0] = GameDisplay;
    Menus[0] += m_stringBuilder.AddNewLineLeftJustified(" > INSTANT", Colours::BLUE);
    Menus[0] += m_stringBuilder.AddNewLineLeftJustified("   FAST");
    Menus[0] += m_stringBuilder.AddNewLineLeftJustified("   SLOW");
    Menus[0] += m_stringBuilder.AddEmptyLine() + m_stringBuilder.AddBottomLine() + m_stringBuilder.AddBottomBox();

    Menus[1] = GameDisplay;
    Menus[1] += m_stringBuilder.AddNewLineLeftJustified("   INSTANT");
    Menus[1] += m_stringBuilder.AddNewLineLeftJustified(" > FAST", Colours::BLUE);
    Menus[1] += m_stringBuilder.AddNewLineLeftJustified("   SLOW");
    Menus[1] += m_stringBuilder.AddEmptyLine() + m_stringBuilder.AddBottomLine() + m_stringBuilder.AddBottomBox();

    Menus[2] = GameDisplay;
    Menus[2] += m_stringBuilder.AddNewLineLeftJustified("   INSTANT");
    Menus[2] += m_stringBuilder.AddNewLineLeftJustified("   FAST");
    Menus[2] += m_stringBuilder.AddNewLineLeftJustified(" > SLOW", Colours::BLUE);
    Menus[2] += m_stringBuilder.AddEmptyLine() + m_stringBuilder.AddBottomLine() + m_stringBuilder.AddBottomBox();

    m_speedAI = Terminal::GetUserChoiceFromGameMenus(Menus);

    if (m_speedAI == 0)
        m_speedNameAI = "INSTANT";
    else if (m_speedAI == 1)
        m_speedNameAI = "FAST";
    else // == 2
        m_speedNameAI = "SLOW";
}

void Hangman::GetWordFromUser()
{
    std::string Output = GetGameDisplay();
    Output += m_stringBuilder.AddNewLineLeftJustified(" Please enter the word to be guessed:");
    Output += m_stringBuilder.AddEmptyLine() + m_stringBuilder.AddEmptyLine() + m_stringBuilder.AddEmptyLine() + m_stringBuilder.AddEmptyLine() + m_stringBuilder.AddBottomLine();
    Output += m_stringBuilder.AddBottomBox();

    std::string Input;
    while (true)
    {
        Terminal::PrintOutput(Output + "\x1B[1;37m");

        Terminal::SetCursorPosition(39, 13);

        std::getline(std::cin, Input);

        if (Input == "q")
            throw Exceptions::QuitGame();

        if (Input.size() < 3 || Input.size() > 14)
            continue;

        // Capitalise word
        std::transform(Input.begin(), Input.end(), Input.begin(), ::toupper);

        if (std::regex_match(Input, std::regex("^[A-Za-z]+$")))
        {
            m_wordToBeGuessed = Input;
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

bool Hangman::IsNextTurnUsers()
{
    return m_userIsGuesser;
}

void Hangman::ExecuteUserCommand()
{
    std::string Output = GetGameDisplay(), CurrentLetter;
    Output += m_stringBuilder.AddNewLineLeftJustified(" Guesser, please enter your next guess:");
    Output += m_stringBuilder.AddEmptyLine() + m_stringBuilder.AddEmptyLine() + m_stringBuilder.AddEmptyLine() + m_stringBuilder.AddEmptyLine() + m_stringBuilder.AddBottomLine();
    Output += m_stringBuilder.AddBottomBox();

    uint32_t KeyPress, CurrentSelection = 0;
    while (true)
    {
        Terminal::PrintOutput(Output);

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
    if (m_speedAI != 0)
    {
        std::string Output = GetGameDisplay();
        Output += m_stringBuilder.AddNewLineLeftJustified(" The AI is executing their next move!") + m_stringBuilder.AddEmptyLine() + m_stringBuilder.AddEmptyLine() + m_stringBuilder.AddEmptyLine() + m_stringBuilder.AddEmptyLine() + m_stringBuilder.AddBottomLine() + m_stringBuilder.AddBottomBox();
        Terminal::PrintOutput(Output);
        std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(m_speedAI));
    }

    m_commandAI = m_movesRemaining[m_randomNumberGenerator() % m_movesRemaining.size()];

    CheckGuessAndUpdateCurrentGuess(m_commandAI);
}

void Hangman::CheckGuessAndUpdateCurrentGuess(const char& Guess)
{
    bool IsGuessCorrect = false;
    for (uint32_t i = 0; i < m_wordToBeGuessed.size(); i++)
        if (m_wordToBeGuessed[i] == Guess)
        {
            IsGuessCorrect = true;
            m_currentGuessOfWord[i] = Guess;
        }

    if (!IsGuessCorrect)
    {
        m_incorrectGuesses.push_back(Guess);
        m_errorCount++;
    }

    m_movesRemaining.erase(std::find(m_movesRemaining.begin(), m_movesRemaining.end(), Guess));
    m_turnCount++;
}

void Hangman::GameOver()
{
    ToggleCurrentPlayer(); // To set player who ended the game as m_currentPlayer.

    std::string Output = GetGameDisplay() + m_stringBuilder.AddNewLineCentred("GAME OVER") + m_stringBuilder.AddEmptyLine();

    if (m_errorCount == 10)
        Output += m_stringBuilder.AddNewLineCentred(
                "The word setter has won! The game lasted " + std::to_string(m_turnCount) + " turns!");
    else
        Output += m_stringBuilder.AddNewLineCentred(
                "The guesser has won! The game lasted " + std::to_string(m_turnCount) + " turns.");

    Output += m_stringBuilder.AddEmptyLine() +
            m_stringBuilder.AddNewLineCentred("Press 'Q' to quit OR Enter to play again...") + m_stringBuilder.AddBottomLine() + m_stringBuilder.AddBottomBox();

    Terminal::PrintOutput(Output);

    if (Terminal::GetNextKeyPress() == 'q')
        throw Exceptions::QuitGame();
}

std::string Hangman::GetGameDisplay() const
{
    // Top bar
    std::string Output = m_stringBuilder.AddTopBox();

    Output += m_stringBuilder.AddTopLine();

    // Hangman State
    if (m_errorCount == 0)
        Output += m_stringBuilder.AddEmptyLine() + m_stringBuilder.AddEmptyLine() + m_stringBuilder.AddNewLineLeftJustified("                   # of Players = " + m_PlayerCount) + m_stringBuilder.AddEmptyLine() + m_stringBuilder.AddNewLineLeftJustified("                   AI Speed = " + m_speedNameAI) + m_stringBuilder.AddEmptyLine() + m_stringBuilder.AddEmptyLine();
    else if (m_errorCount == 1)
        Output += m_stringBuilder.AddEmptyLine() + m_stringBuilder.AddNewLineLeftJustified("                                          Incorrect Guesses") + m_stringBuilder.AddNewLineLeftJustified("                   # of Players = " + m_PlayerCount) + m_stringBuilder.AddNewLineLeftJustified(std::string("                                          ") + m_incorrectGuesses[0]) + m_stringBuilder.AddNewLineLeftJustified("                   AI Speed = " + m_speedNameAI) + m_stringBuilder.AddEmptyLine() + m_stringBuilder.AddNewLineLeftJustified(std::string(" ") + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196);
    else if (m_errorCount == 2)
        Output += m_stringBuilder.AddEmptyLine() + m_stringBuilder.AddNewLineLeftJustified(std::string("     ") + (char)179 + "                                    Incorrect Guesses") + m_stringBuilder.AddNewLineLeftJustified(std::string("     ") + (char)179 + "             # of Players = " + m_PlayerCount) + m_stringBuilder.AddNewLineLeftJustified(std::string("     ") + (char)179 + "                                    " + m_incorrectGuesses[0] + "   " + m_incorrectGuesses[1]) + m_stringBuilder.AddNewLineLeftJustified(std::string("     ") + (char)179 + "             AI Speed = " + m_speedNameAI) + m_stringBuilder.AddNewLineLeftJustified(std::string("     ") + (char)179) + m_stringBuilder.AddNewLineLeftJustified(std::string(" ") + (char)196 + (char)196 + (char)196 + (char)196 + (char)193 + (char)196 + (char)196 + (char)196 + (char)196);
    else if (m_errorCount == 3)
        Output += m_stringBuilder.AddNewLineLeftJustified(std::string("     ") + (char)218 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196) + m_stringBuilder.AddNewLineLeftJustified(std::string("     ") + (char)179 + "                                    Incorrect Guesses") + m_stringBuilder.AddNewLineLeftJustified(std::string("     ") + (char)179 + "             # of Players = " + m_PlayerCount) + m_stringBuilder.AddNewLineLeftJustified(std::string("     ") + (char)179 + "                                    " + m_incorrectGuesses[0] + "   " + m_incorrectGuesses[1] + "   " + m_incorrectGuesses[2]) + m_stringBuilder.AddNewLineLeftJustified(std::string("     ") + (char)179 + "             AI Speed = " + m_speedNameAI) + m_stringBuilder.AddNewLineLeftJustified(std::string("     ") + (char)179) + m_stringBuilder.AddNewLineLeftJustified(std::string(" ") + (char)196 + (char)196 + (char)196 + (char)196 + (char)193 + (char)196 + (char)196 + (char)196 + (char)196);
    else if (m_errorCount == 4)
        Output += m_stringBuilder.AddNewLineLeftJustified(std::string("     ") + (char)218 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)191) + m_stringBuilder.AddNewLineLeftJustified(std::string("     ") + (char)179 + "       " + (char)179 + "                            Incorrect Guesses") + m_stringBuilder.AddNewLineLeftJustified(std::string("     ") + (char)179 + "             # of Players = " + m_PlayerCount) + m_stringBuilder.AddNewLineLeftJustified(std::string("     ") + (char)179 + "                                    " + m_incorrectGuesses[0] + "   " + m_incorrectGuesses[1] + "   " + m_incorrectGuesses[2] + "   " + m_incorrectGuesses[3]) + m_stringBuilder.AddNewLineLeftJustified(std::string("     ") + (char)179 + "             AI Speed = " + m_speedNameAI) + m_stringBuilder.AddNewLineLeftJustified(std::string("     ") + (char)179) + m_stringBuilder.AddNewLineLeftJustified(std::string(" ") + (char)196 + (char)196 + (char)196 + (char)196 + (char)193 + (char)196 + (char)196 + (char)196 + (char)196);
    else if (m_errorCount == 5)
        Output += m_stringBuilder.AddNewLineLeftJustified(std::string("     ") + (char)218 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)191) + m_stringBuilder.AddNewLineLeftJustified(std::string("     ") + (char)179 + "       " + (char)179 + "                            Incorrect Guesses") + m_stringBuilder.AddNewLineLeftJustified(std::string("     ") + (char)179 + "       O     # of Players = " + m_PlayerCount) + m_stringBuilder.AddNewLineLeftJustified(std::string("     ") + (char)179 + "                                    " + m_incorrectGuesses[0] + "   " + m_incorrectGuesses[1] + "   " + m_incorrectGuesses[2] + "   " + m_incorrectGuesses[3] + "   " + m_incorrectGuesses[4]) + m_stringBuilder.AddNewLineLeftJustified(std::string("     ") + (char)179 + "             AI Speed = " + m_speedNameAI + "                       ") + m_stringBuilder.AddNewLineLeftJustified(std::string("     ") + (char)179) + m_stringBuilder.AddNewLineLeftJustified(std::string(" ") + (char)196 + (char)196 + (char)196 + (char)196 + (char)193 + (char)196 + (char)196 + (char)196 + (char)196);
    else if (m_errorCount == 6)
        Output += m_stringBuilder.AddNewLineLeftJustified(std::string("     ") + (char)218 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)191) + m_stringBuilder.AddNewLineLeftJustified(std::string("     ") + (char)179 + "       " + (char)179 + "                            Incorrect Guesses") + m_stringBuilder.AddNewLineLeftJustified(std::string("     ") + (char)179 + "       O     # of Players = " + m_PlayerCount) + m_stringBuilder.AddNewLineLeftJustified(std::string("     ") + (char)179 + "       " + (char)179 + "                            " + m_incorrectGuesses[0] + "   " + m_incorrectGuesses[1] + "   " + m_incorrectGuesses[2] + "   " + m_incorrectGuesses[3] + "   " + m_incorrectGuesses[4]) + m_stringBuilder.AddNewLineLeftJustified(std::string("     ") + (char)179 + "             AI Speed = " + m_speedNameAI) + m_stringBuilder.AddNewLineLeftJustified(std::string("     ") + (char)179 + "                                    " + m_incorrectGuesses[5]) + m_stringBuilder.AddNewLineLeftJustified(std::string(" ") + (char)196 + (char)196 + (char)196 + (char)196 + (char)193 + (char)196 + (char)196 + (char)196 + (char)196);
    else if (m_errorCount == 7)
        Output += m_stringBuilder.AddNewLineLeftJustified(std::string("     ") + (char)218 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)191) + m_stringBuilder.AddNewLineLeftJustified(std::string("     ") + (char)179 + "       " + (char)179 + "                            Incorrect Guesses") + m_stringBuilder.AddNewLineLeftJustified(std::string("     ") + (char)179 + "       O     # of Players = " + m_PlayerCount) + m_stringBuilder.AddNewLineLeftJustified(std::string("     ") + (char)179 + "       " + (char)179 + "                            " + m_incorrectGuesses[0] + "   " + m_incorrectGuesses[1] + "   " + m_incorrectGuesses[2] + "   " + m_incorrectGuesses[3] + "   " + m_incorrectGuesses[4]) + m_stringBuilder.AddNewLineLeftJustified(std::string("     ") + (char)179 + "      /      AI Speed = " + m_speedNameAI) + m_stringBuilder.AddNewLineLeftJustified(std::string("     ") + (char)179 + "                                    " + m_incorrectGuesses[5] + "   " + m_incorrectGuesses[6]) + m_stringBuilder.AddNewLineLeftJustified(std::string(" ") + (char)196 + (char)196 + (char)196 + (char)196 + (char)193 + (char)196 + (char)196 + (char)196 + (char)196);
    else if (m_errorCount == 8)
        Output += m_stringBuilder.AddNewLineLeftJustified(std::string("     ") + (char)218 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)191) + m_stringBuilder.AddNewLineLeftJustified(std::string("     ") + (char)179 + "       " + (char)179 + "                            Incorrect Guesses") + m_stringBuilder.AddNewLineLeftJustified(std::string("     ") + (char)179 + "       O     # of Players = " + m_PlayerCount) + m_stringBuilder.AddNewLineLeftJustified(std::string("     ") + (char)179 + "       " + (char)179 + "                            " + m_incorrectGuesses[0] + "   " + m_incorrectGuesses[1] + "   " + m_incorrectGuesses[2] + "   " + m_incorrectGuesses[3] + "   " + m_incorrectGuesses[4]) + m_stringBuilder.AddNewLineLeftJustified(std::string("     ") + (char)179 + "      / \\    AI Speed = " + m_speedNameAI) + m_stringBuilder.AddNewLineLeftJustified(std::string("     ") + (char)179 + "                                    " + m_incorrectGuesses[5] + "   " + m_incorrectGuesses[6] + "   " + m_incorrectGuesses[7]) + m_stringBuilder.AddNewLineLeftJustified(std::string(" ") + (char)196 + (char)196 + (char)196 + (char)196 + (char)193 + (char)196 + (char)196 + (char)196 + (char)196);
    else if (m_errorCount == 9)
        Output += m_stringBuilder.AddNewLineLeftJustified(std::string("     ") + (char)218 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)191) + m_stringBuilder.AddNewLineLeftJustified(std::string("     ") + (char)179 + "       " + (char)179 + "                            Incorrect Guesses") + m_stringBuilder.AddNewLineLeftJustified(std::string("     ") + (char)179 + "       O     # of Players = " + m_PlayerCount) + m_stringBuilder.AddNewLineLeftJustified(std::string("     ") + (char)179 + "      /" + (char)179 + "                            " + m_incorrectGuesses[0] + "   " + m_incorrectGuesses[1] + "   " + m_incorrectGuesses[2] + "   " + m_incorrectGuesses[3] + "   " + m_incorrectGuesses[4]) + m_stringBuilder.AddNewLineLeftJustified(std::string("     ") + (char)179 + "      / \\    AI Speed = " + m_speedNameAI) + m_stringBuilder.AddNewLineLeftJustified(std::string("     ") + (char)179 + "                                    " + m_incorrectGuesses[5] + "   " + m_incorrectGuesses[6] + "   " + m_incorrectGuesses[7] + "   " + m_incorrectGuesses[8]) + m_stringBuilder.AddNewLineLeftJustified(std::string(" ") + (char)196 + (char)196 + (char)196 + (char)196 + (char)193 + (char)196 + (char)196 + (char)196 + (char)196);
    else if (m_errorCount == 10)
        Output += m_stringBuilder.AddNewLineLeftJustified(std::string("     ") + (char)218 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)191) + m_stringBuilder.AddNewLineLeftJustified(std::string("     ") + (char)179 + "       " + (char)179 + "                            Incorrect Guesses") + m_stringBuilder.AddNewLineLeftJustified(std::string("     ") + (char)179 + "       O     # of Players = " + m_PlayerCount) + m_stringBuilder.AddNewLineLeftJustified(std::string("     ") + (char)179 + "      /" + (char)179 + "\\                           " + m_incorrectGuesses[0] + "   " + m_incorrectGuesses[1] + "   " + m_incorrectGuesses[2] + "   " + m_incorrectGuesses[3] + "   " + m_incorrectGuesses[4]) + m_stringBuilder.AddNewLineLeftJustified(std::string("     ") + (char)179 + "      / \\    AI Speed = " + m_speedNameAI) + m_stringBuilder.AddNewLineLeftJustified(std::string("     ") + (char)179 + "                                    " + m_incorrectGuesses[5] + "   " + m_incorrectGuesses[6] + "   " + m_incorrectGuesses[7] + "   " + m_incorrectGuesses[8] + "   " + m_incorrectGuesses[9]) + m_stringBuilder.AddNewLineLeftJustified(std::string(" ") + (char)196 + (char)196 + (char)196 + (char)196 + (char)193 + (char)196 + (char)196 + (char)196 + (char)196);

    // Word to be guessed, and thus current guess of word, are limited to a size in between 3 and 14
    Output += (char)186;

    for (char i : m_currentGuessOfWord)
        Output += std::string(" ") + i;

    if (m_hasWinner && m_errorCount == 10) // show what the word to be guessed was
    {
        Output += "   (The word was " + m_wordToBeGuessed + ")";
        Output.insert(Output.size(), (62 - 18 - m_wordToBeGuessed.size() * 3), ' ');
    }
    else // do not show it
        Output.insert(Output.size(), (62 - m_wordToBeGuessed.size() * 2), ' ');

    Output += (char)186;

    return Output + "\n" + m_stringBuilder.AddEmptyLine();
}
