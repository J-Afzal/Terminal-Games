/**
 * @file hangman.cpp
 * @author Junaid Afzal
 * @brief Implementation of hangman.hpp
 * @version 1.0
 * @date 07-11-2021
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <conio.h>
#include "terminal.hpp"
#include "hangman.hpp"

void Hangman::Play(const HANDLE &ConsoleHandle)
{
    Hangman::Game GameObject(ConsoleHandle);

    while (true)
    {
        if (GameObject.Setup_Game()) // if true, quit to main menu
            return;

        while (!GameObject.Game_Over())
        {
            if (GameObject.Next_Turn_Is_User())
            {
                if (GameObject.Execute_Next_User_Guess()) // if true, quit to main menu
                    return;
            }
            else
                GameObject.Execute_Next_AI_Guess();
        }

        if (GameObject.Display_Game_Over_Message()) // if true, quit to main menu
            return;
    }
}

Hangman::Game::Game(const HANDLE &ConsoleHandle) : m_ConsoleHandle(ConsoleHandle) {}

Hangman::Game::~Game() {}

bool Hangman::Game::Setup_Game(void)
{
    m_MovesRemaining.reserve(26);
    m_MovesRemaining = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    m_IncorrectGuesses.clear();
    m_WordToBeGuessed = "";
    m_CurrentGuessOfWord = "";
    m_AIDifficulty = "N/A";
    m_NumberOfPlayers = -1;
    m_NumberOfErrors = 0;
    m_NumberOfTurns = 0;
    m_GameOver = false;
    std::srand(std::time(0));

    if (Get_Number_Of_Players())
        return true;

    if (m_NumberOfPlayers == 0)
    {
        m_UserIsGuessing = false;
        if (Get_AI_Difficulty())
            return true;
        Get_Random_Word();
    }

    else if (m_NumberOfPlayers == 1)
    {
        if (Get_User_Player_Choice())
            return true;

        if (Get_AI_Difficulty())
            return true;

        if (m_UserIsGuessing)
            Get_Random_Word();
        else
        {
            if (Get_Word_From_User())
                return true;
        }
    }

    else if (m_NumberOfPlayers == 2)
    {
        m_UserIsGuessing = true;
        m_AIDifficulty = "N/A";
        if (Get_Word_From_User())
            return true;
    }

    for (unsigned int i = 0; i < m_WordToBeGuessed.size(); i++)
        m_CurrentGuessOfWord.push_back('_');

    return false;
}

bool Hangman::Game::Get_Number_Of_Players(void)
{
    std::string CommonString = Get_Game_Display();
    CommonString += New_Line(" Please select the number of human players:                   ");

    std::string CaseZero = CommonString;
    CaseZero += New_Line(BLUE + " > 0                                                          " + WHITE);
    CaseZero += New_Line("   1                                                          ");
    CaseZero += New_Line("   2                                                          ");
    CaseZero += Empty_Line() + Bottom_Line() + Bottom_Bar();

    std::string CaseOne = CommonString;
    CaseOne += New_Line("   0                                                          ");
    CaseOne += New_Line(BLUE + " > 1                                                          " + WHITE);
    CaseOne += New_Line("   2                                                          ");
    CaseOne += Empty_Line() + Bottom_Line() + Bottom_Bar();

    std::string CaseTwo = CommonString;
    CaseTwo += New_Line("   0                                                          ");
    CaseTwo += New_Line("   1                                                          ");
    CaseTwo += New_Line(BLUE + " > 2                                                          " + WHITE);
    CaseTwo += Empty_Line() + Bottom_Line() + Bottom_Bar();

    int KeyPress = 0, CurrentSelection = 0;
    while (true)
    {
        if (CurrentSelection == 0)
            Output_To_Terminal(CaseZero);
        else if (CurrentSelection == 1)
            Output_To_Terminal(CaseOne);
        else if (CurrentSelection == 2)
            Output_To_Terminal(CaseTwo);

        KeyPress = _getch();

        if (KeyPress == '\r')
        {
            m_NumberOfPlayers = CurrentSelection;
            return false;
        }
        else if (KeyPress == 72) // up arrow key
            CurrentSelection == 0 ? CurrentSelection = 2 : --CurrentSelection;
        else if (KeyPress == 80) // down arrow key
            CurrentSelection == 2 ? CurrentSelection = 0 : ++CurrentSelection;
        else if (KeyPress == 'q')
            return true;
    }
}

bool Hangman::Game::Get_User_Player_Choice(void)
{
    std::string CommonString = Get_Game_Display();
    CommonString += New_Line(" Please select what player you would like to be:              ");

    std::string CaseZero = CommonString;
    CaseZero += New_Line(BLUE + " > GUESSER                                                    " + WHITE);
    CaseZero += New_Line("   WORD SETTER                                                ");
    CaseZero += Empty_Line() + Empty_Line() + Bottom_Line() + Bottom_Bar();

    std::string CaseOne = CommonString;
    CaseOne += New_Line("   GUESSER                                                    ");
    CaseOne += New_Line(BLUE + " > WORD SETTER                                                " + WHITE);
    CaseOne += Empty_Line() + Empty_Line() + Bottom_Line() + Bottom_Bar();

    int KeyPress = 0, CurrentSelection = 0;
    while (true)
    {
        if (CurrentSelection == 0)
            Output_To_Terminal(CaseZero);
        else if (CurrentSelection == 1)
            Output_To_Terminal(CaseOne);

        KeyPress = _getch();

        if (KeyPress == '\r')
        {
            CurrentSelection == 0 ? m_UserIsGuessing = true : m_UserIsGuessing = false;
            return false;
        }
        else if (KeyPress == 72) // up arrow key
            CurrentSelection == 0 ? CurrentSelection = 1 : --CurrentSelection;
        else if (KeyPress == 80) // down arrow key
            CurrentSelection == 1 ? CurrentSelection = 0 : ++CurrentSelection;
        else if (KeyPress == 'q')
            return true;
    }
}

bool Hangman::Game::Get_AI_Difficulty(void)
{
    std::string CommonString = Get_Game_Display();
    CommonString += New_Line(" Please select the AI difficulty:                             ");

    std::string CaseZero = CommonString;
    CaseZero += New_Line(BLUE + " > EASY                                                       " + WHITE);
    CaseZero += New_Line("   HARD (Coming Soon!)                                        ");
    CaseZero += Empty_Line() + Empty_Line() + Bottom_Line() + Bottom_Bar();

    std::string CaseOne = CommonString;
    CaseOne += New_Line("   EASY                                                       ");
    CaseOne += New_Line(BLUE + " > HARD (Coming Soon!)                                        " + WHITE);
    CaseOne += Empty_Line() + Empty_Line() + Bottom_Line() + Bottom_Bar();

    int KeyPress = 0, CurrentSelection = 0;
    while (true)
    {
        if (CurrentSelection == 0)
            Output_To_Terminal(CaseZero);
        else if (CurrentSelection == 1)
            Output_To_Terminal(CaseOne);

        KeyPress = _getch();

        if (KeyPress == '\r' && CurrentSelection == 0)
        {
            CurrentSelection == 0 ? m_AIDifficulty = "EASY" : m_AIDifficulty = "HARD";
            return false;
        }
        else if (KeyPress == 72) // up arrow key
            CurrentSelection == 0 ? CurrentSelection = 1 : --CurrentSelection;
        else if (KeyPress == 80) // down arrow key
            CurrentSelection == 1 ? CurrentSelection = 0 : ++CurrentSelection;
        else if (KeyPress == 'q')
            return true;
    }
}

bool Hangman::Game::Get_Word_From_User(void)
{
    std::string Output = Get_Game_Display();
    Output += New_Line(" Please enter the word to be guessed:                         ");
    Output += Empty_Line() + Empty_Line() + Empty_Line() + Empty_Line() + Bottom_Line() + Bottom_Bar();

    std::string Input;
    while (true)
    {
        bool InputValid = true;

        Output_To_Terminal(Output);

        SetConsoleCursorPosition(m_ConsoleHandle, {39, 13});

        std::getline(std::cin, Input);

        if (Input == "q") // quit to main menu
            return true;

        if (Input.size() < 3 || Input.size() > 14)
            continue;

        // Capitalise word
        for (unsigned int i = 0; i < Input.size(); i++)
            if (Input[i] >= 'a' && Input[i] <= 'z')
                Input[i] -= 32;

        for (unsigned int i = 0; i < Input.size(); i++)
            if (Input[i] < 'A' || Input[i] > 'Z')
            {
                InputValid = false;
                break;
            }

        if (InputValid)
            break;
    }

    m_WordToBeGuessed = Input;

    return false;
}

void Hangman::Game::Get_Random_Word(void)
{
    std::ifstream Words("../resources/words.txt");
    if (Words.is_open())
    {
        int RandomLineNumber = std::rand() % 972;
        std::string Word;
        for (int i = 0; i < RandomLineNumber - 1; i++)
            std::getline(Words, Word);
        std::getline(Words, Word);
        m_WordToBeGuessed = Word;
    }
    else
        m_WordToBeGuessed = "ERROR";
}

bool Hangman::Game::Game_Over(void)
{
    return Winning_Conditions_Met() || No_Guesses_Left() ? true : false;
}

bool Hangman::Game::Winning_Conditions_Met(void)
{
    for (unsigned int i = 0; i < m_WordToBeGuessed.size(); i++)
        if (m_WordToBeGuessed[i] != m_CurrentGuessOfWord[i])
            return false;
    m_GameOver = true;
    return true;
}

bool Hangman::Game::No_Guesses_Left(void)
{
    m_GameOver = true;
    return m_NumberOfErrors == 10 ? true : false;
}

bool Hangman::Game::Next_Turn_Is_User(void)
{
    return m_UserIsGuessing;
}

bool Hangman::Game::Execute_Next_User_Guess(void)
{
    std::string Output = Get_Game_Display();
    Output += New_Line(" Guesser, please enter your next guess:                       ");
    Output += Empty_Line() + Empty_Line() + Empty_Line() + Empty_Line() + Bottom_Line() + Bottom_Bar();

    int KeyPress = 0, CurrentSelection = 0;
    while (true)
    {
        Output_To_Terminal(Output);

        SetConsoleCursorPosition(m_ConsoleHandle, {41, 13});

        std::cout << BLUE + m_MovesRemaining[CurrentSelection] + WHITE;

        KeyPress = _getch();

        if (KeyPress == '\r')
        {
            Check_Guess_And_Update_Current_Guess(m_MovesRemaining[CurrentSelection]);
            return false;
        }
        else if (KeyPress == 72) // up arrow key
            CurrentSelection == 0 ? CurrentSelection = m_MovesRemaining.size() - 1 : --CurrentSelection;
        else if (KeyPress == 80) // down arrow key
            CurrentSelection == int(m_MovesRemaining.size() - 1) ? CurrentSelection = 0 : ++CurrentSelection;
        else if (KeyPress == 'q')
            return true;
        else
        {
            auto Command = std::find(m_MovesRemaining.begin(), m_MovesRemaining.end(), KeyPress - 32);
            if (Command != m_MovesRemaining.end())
                CurrentSelection = std::distance(m_MovesRemaining.begin(), Command);
        }
    }
}

void Hangman::Game::Execute_Next_AI_Guess(void)
{
    Check_Guess_And_Update_Current_Guess(m_MovesRemaining[std::rand() % m_MovesRemaining.size()]);
}

bool Hangman::Game::Display_Game_Over_Message(void)
{
    std::string Output = Get_Game_Display();
    Output += New_Line("                          GAME OVER                           ") + Empty_Line();

    if (m_NumberOfErrors == 10)
        Output += New_Line("      The word setter has won! The game lasted " + std::to_string(m_NumberOfTurns) + " turns!      ");
    else
    {
        if (m_NumberOfTurns > 9)
            Output += New_Line("        The guesser has won! The game lasted " + std::to_string(m_NumberOfTurns) + " turns.        ");
        else
            Output += New_Line("        The guesser has won! The game lasted " + std::to_string(m_NumberOfTurns) + " turns.         ");
    }

    Output += Empty_Line() + New_Line("     Press 'Q' to quit OR any other key to play again...      ") + Bottom_Line() + Bottom_Bar();

    Output_To_Terminal(Output);

    return _getch() == 'q' ? true : false;
}

void Hangman::Game::Check_Guess_And_Update_Current_Guess(const char &Guess)
{
    bool IsGuessCorrect = false;
    for (unsigned int i = 0; i < m_WordToBeGuessed.size(); i++)
        if (m_WordToBeGuessed[i] == Guess)
        {
            IsGuessCorrect = true;
            m_CurrentGuessOfWord[i] = Guess;
        }

    if (!IsGuessCorrect)
    {
        m_IncorrectGuesses.push_back(Guess);
        m_NumberOfErrors++;
    }

    m_NumberOfTurns++;

    m_MovesRemaining.erase(std::find(m_MovesRemaining.begin(), m_MovesRemaining.end(), Guess));
}

std::string Hangman::Game::Get_Game_Display(void)
{
    std::string Output;

    // Top bar
    Output += WHITE + Top_Line() + New_Line(RED + "                           Hangman                            " + WHITE) + Bottom_Line();

    Output += Top_Line();

    // Line 1
    switch (m_NumberOfErrors)
    {
    case 0:
    case 1:
    case 2:
        Output += Empty_Line();
        break;

    case 3:
        Output += (char)186 + std::string("     ") + (char)218;
        Output.insert(Output.size(), 8, (char)196);
        Output += std::string("                                                ") + (char)186 + "\n";
        break;

    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
        Output += (char)186 + std::string("     ") + (char)218;
        Output.insert(Output.size(), 7, (char)196);
        Output += (char)191 + std::string("                                                ") + (char)186 + "\n";
        break;
    }

    // Line 2
    switch (m_NumberOfErrors)
    {
    case 0:
        Output += Empty_Line();
        break;

    case 1:
        Output += New_Line("                                          Incorrect Guesses   ");
        break;

    case 2:
    case 3:
        Output += New_Line(std::string("     ") + (char)179 + "                                    Incorrect Guesses   ");
        break;

    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
        Output += New_Line(std::string("     ") + (char)179 + "       " + (char)179 + "                            Incorrect Guesses   ");
        break;
    }

    // Line 3
    switch (m_NumberOfErrors)
    {
    case 0:
        if (m_NumberOfPlayers == -1)
            Output += New_Line("                   # of Players = N/A                         ");
        else
            Output += New_Line("                    # of Players = " + std::to_string(m_NumberOfPlayers) + "                          ");
        break;

    case 1:
        Output += New_Line("                    # of Players = " + std::to_string(m_NumberOfPlayers) + "                          ");
        break;

    case 2:
    case 3:
    case 4:
        Output += New_Line(std::string("     ") + (char)179 + "              # of Players = " + std::to_string(m_NumberOfPlayers) + "                          ");
        break;

    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
        Output += New_Line(std::string("     ") + (char)179 + "       O      # of Players = " + std::to_string(m_NumberOfPlayers) + "                          ");
        break;
    }

    // Line 4
    switch (m_NumberOfErrors)
    {
    case 0:
        Output += Empty_Line();
        break;

    case 1:
        Output.insert(Output.size(), New_Line(std::string("                                          ") + m_IncorrectGuesses[0] + "                   "));
        break;

    case 2:
        Output += New_Line(std::string("     ") + (char)179 + "                                    " + m_IncorrectGuesses[0] + "   " + m_IncorrectGuesses[1] + "               ");
        break;

    case 3:
        Output += New_Line(std::string("     ") + (char)179 + "                                    " + m_IncorrectGuesses[0] + "   " + m_IncorrectGuesses[1] + "   " + m_IncorrectGuesses[2] + "           ");
        break;

    case 4:
        Output += New_Line(std::string("     ") + (char)179 + "                                    " + m_IncorrectGuesses[0] + "   " + m_IncorrectGuesses[1] + "   " + m_IncorrectGuesses[2] + "   " + m_IncorrectGuesses[3] + "       ");
        break;

    case 5:
        Output += New_Line(std::string("     ") + (char)179 + "                                    " + m_IncorrectGuesses[0] + "   " + m_IncorrectGuesses[1] + "   " + m_IncorrectGuesses[2] + "   " + m_IncorrectGuesses[3] + "   " + m_IncorrectGuesses[4] + "   ");
        break;

    case 6:
    case 7:
    case 8:
        Output += New_Line(std::string("     ") + (char)179 + "       " + (char)179 + "                            " + m_IncorrectGuesses[0] + "   " + m_IncorrectGuesses[1] + "   " + m_IncorrectGuesses[2] + "   " + m_IncorrectGuesses[3] + "   " + m_IncorrectGuesses[4] + "   ");
        break;

    case 9:
        Output += New_Line(std::string("     ") + (char)179 + "      /" + (char)179 + "                            " + m_IncorrectGuesses[0] + "   " + m_IncorrectGuesses[1] + "   " + m_IncorrectGuesses[2] + "   " + m_IncorrectGuesses[3] + "   " + m_IncorrectGuesses[4] + "   ");
        break;

    case 10:
        Output += New_Line(std::string("     ") + (char)179 + "      /" + (char)179 + "\\                           " + m_IncorrectGuesses[0] + "   " + m_IncorrectGuesses[1] + "   " + m_IncorrectGuesses[2] + "   " + m_IncorrectGuesses[3] + "   " + m_IncorrectGuesses[4] + "   ");
        break;
    }

    // Line 5
    switch (m_NumberOfErrors)
    {
    case 0:
    case 1:
        if (m_AIDifficulty == "N/A")
            Output += New_Line("                   AI Difficulty = N/A                        ");
        else
            Output += New_Line("                  AI Difficulty = " + m_AIDifficulty + "                        ");
        break;

    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
        Output += (char)186 + std::string("     ") + (char)179;
        if (m_AIDifficulty == "N/A")
            Output += "             AI Difficulty = N/A                        ";
        else
            Output += "            AI Difficulty = " + m_AIDifficulty + "                        ";
        Output += (char)186;
        Output += "\n";
        break;

    case 7:
        Output += (char)186 + std::string("     ") + (char)179;
        if (m_AIDifficulty == "N/A")
            Output += "      /      AI Difficulty = N/A                        ";
        else
            Output += "      /     AI Difficulty = " + m_AIDifficulty + "                        ";
        Output += (char)186;
        Output += "\n";
        break;

    case 8:
    case 9:
    case 10:
        Output += (char)186 + std::string("     ") + (char)179;
        if (m_AIDifficulty == "N/A")
            Output += "      / \\    AI Difficulty = N/A                        ";
        else
            Output += "      / \\   AI Difficulty = " + m_AIDifficulty + "                        ";
        Output += (char)186;
        Output += "\n";
        break;
    }

    // Line 6
    switch (m_NumberOfErrors)
    {
    case 0:
    case 1:
        Output += Empty_Line();
        break;

    case 2:
    case 3:
    case 4:
    case 5:
        Output += New_Line(std::string("     ") + (char)179 + "                                                        ");
        break;

    case 6:
        Output += New_Line(std::string("     ") + (char)179 + "                                    " + m_IncorrectGuesses[5] + "                   ");
        break;

    case 7:
        Output += New_Line(std::string("     ") + (char)179 + "                                    " + m_IncorrectGuesses[5] + "   " + m_IncorrectGuesses[6] + "               ");
        break;

    case 8:
        Output += New_Line(std::string("     ") + (char)179 + "                                    " + m_IncorrectGuesses[5] + "   " + m_IncorrectGuesses[6] + "   " + m_IncorrectGuesses[7] + "           ");
        break;

    case 9:
        Output += New_Line(std::string("     ") + (char)179 + "                                    " + m_IncorrectGuesses[5] + "   " + m_IncorrectGuesses[6] + "   " + m_IncorrectGuesses[7] + "   " + m_IncorrectGuesses[8] + "       ");
        break;

    case 10:
        Output += New_Line(std::string("     ") + (char)179 + "                                    " + m_IncorrectGuesses[5] + "   " + m_IncorrectGuesses[6] + "   " + m_IncorrectGuesses[7] + "   " + m_IncorrectGuesses[8] + "   " + m_IncorrectGuesses[9] + "   ");
        break;
    }

    // Line 7
    switch (m_NumberOfErrors)
    {
    case 0:
        Output += Empty_Line();
        break;

    case 1:
        Output += (char)186 + std::string(" ");
        Output.insert(Output.size(), 9, (char)196);
        Output += std::string("                                                    ") + (char)186 + "\n";
        break;

    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
        Output += (char)186 + std::string(" ");
        Output.insert(Output.size(), 4, (char)196);
        Output += (char)193;
        Output.insert(Output.size(), 4, (char)196);
        Output += std::string("                                                    ") + (char)186 + "\n";
        break;
    }

    // Word to be guessed, and thus current guess of word, are limited to a size in between 3 and 14
    Output += (char)186;

    for (unsigned int i = 0; i < m_CurrentGuessOfWord.size(); i++)
        Output += std::string(" ") + m_CurrentGuessOfWord[i];

    if (m_GameOver && m_NumberOfErrors == 10)
    {
        Output += "   (The word was " + m_WordToBeGuessed + ")";
        Output.insert(Output.size(), (62 - 18 - m_WordToBeGuessed.size() * 3), ' ');
    }
    else
        Output.insert(Output.size(), (62 - m_WordToBeGuessed.size() * 2), ' ');

    Output += (char)186;
    Output += "\n" + Empty_Line();

    return Output;
}

std::string Hangman::Game::New_Line(const std::string &Input)
{
    return (char)186 + Input + (char)186 + "\n";
}

std::string Hangman::Game::Empty_Line(void)
{
    std::string Output;
    Output += (char)186;
    Output.insert(Output.size(), 62, ' ');
    Output += (char)186;
    return Output + "\n";
}

std::string Hangman::Game::Top_Line(void)
{
    std::string Output;
    Output += (char)201;
    Output.insert(Output.size(), 62, (char)205);
    Output += (char)187;
    return Output + "\n";
}

std::string Hangman::Game::Bottom_Line(void)
{
    std::string Output;
    Output += (char)200;
    Output.insert(Output.size(), 62, (char)205);
    Output += (char)188;
    return Output + "\n";
}

std::string Hangman::Game::Bottom_Bar(void)
{
    return Top_Line() + New_Line(RED + "                    q = quit to main menu                     " + WHITE) + Bottom_Line();
}
