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

#include "terminal.hpp"
#include "hangman.hpp"

Hangman::Hangman(const HANDLE &ConsoleHandle) : m_ConsoleHandle(ConsoleHandle) {}

Hangman::~Hangman() = default;

bool Hangman::Setup_Game()
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
    m_RandomNumberGenerator.seed(std::chrono::system_clock::now().time_since_epoch().count());

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

bool Hangman::Game_Over()
{
    if (m_NumberOfErrors == 10)
        return m_GameOver = true;

    for (unsigned int i = 0; i < m_WordToBeGuessed.size(); i++)
        if (m_WordToBeGuessed[i] != m_CurrentGuessOfWord[i])
            return false;
    return m_GameOver = true;
}

void Hangman::Toggle_Current_Player() {}

bool Hangman::Next_Turn_Is_User()
{
    return m_UserIsGuessing;
}

bool Hangman::Execute_Next_User_Command()
{
    std::string Output = Get_Game_Display(), CurrentLetter;
    Output += New_Line(" Guesser, please enter your next guess:                       ");
    Output += Empty_Line(m_Width) + Empty_Line(m_Width) + Empty_Line(m_Width) + Empty_Line(m_Width) + Bottom_Line(m_Width);
    Output += Box(m_Width, "                    q = quit to main menu                     ");

    int KeyPress, CurrentSelection = 0;
    while (true)
    {
        Output_To_Terminal(Output);

        SetConsoleCursorPosition(m_ConsoleHandle, {41, 13});
        CurrentLetter = BLUE;
        CurrentLetter += m_MovesRemaining[CurrentSelection];
        CurrentLetter += WHITE;
        std::cout << CurrentLetter;

        KeyPress = _getch();

        if (KeyPress == '\r') // enter key
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

void Hangman::Execute_Next_AI_Command()
{
    Check_Guess_And_Update_Current_Guess(m_MovesRemaining[m_RandomNumberGenerator() % m_MovesRemaining.size()]);
}

bool Hangman::Display_Game_Over_Message()
{
    std::string Output = Get_Game_Display();
    Output += New_Line("                          GAME OVER                           ") + Empty_Line(m_Width);

    if (m_NumberOfErrors == 10)
        Output += New_Line("      The word setter has won! The game lasted " + std::to_string(m_NumberOfTurns) + " turns!      ");
    else
    {
        if (m_NumberOfTurns > 9)
            Output += New_Line("        The guesser has won! The game lasted " + std::to_string(m_NumberOfTurns) + " turns.        ");
        else
            Output += New_Line("        The guesser has won! The game lasted " + std::to_string(m_NumberOfTurns) + " turns.         ");
    }

    Output += Empty_Line(m_Width) + New_Line("     Press 'Q' to quit OR any other key to play again...      ") + Bottom_Line(m_Width);
    Output += Box(m_Width, "                    q = quit to main menu                     ");

    Output_To_Terminal(Output);

    return _getch() == 'q';
}

bool Hangman::Get_Number_Of_Players()
{
    std::array<std::string, 3> Options;
    std::string GameDisplay = Get_Game_Display();

    Options[0] = GameDisplay + New_Line(" Please select the number of human players:                   ");
    Options[0] += New_Line(BLUE + " > 0                                                          " + WHITE);
    Options[0] += New_Line("   1                                                          ");
    Options[0] += New_Line("   2                                                          ");
    Options[0] += Empty_Line(m_Width) + Bottom_Line(m_Width) + Box(m_Width, "                    q = quit to main menu                     ");

    Options[1] = GameDisplay + New_Line(" Please select the number of human players:                   ");
    Options[1] += New_Line("   0                                                          ");
    Options[1] += New_Line(BLUE + " > 1                                                          " + WHITE);
    Options[1] += New_Line("   2                                                          ");
    Options[1] += Empty_Line(m_Width) + Bottom_Line(m_Width) + Box(m_Width, "                    q = quit to main menu                     ");

    Options[2] = GameDisplay + New_Line(" Please select the number of human players:                   ");
    Options[2] += New_Line("   0                                                          ");
    Options[2] += New_Line("   1                                                          ");
    Options[2] += New_Line(BLUE + " > 2                                                          " + WHITE);
    Options[2] += Empty_Line(m_Width) + Bottom_Line(m_Width) + Box(m_Width, "                    q = quit to main menu                     ");

    int KeyPress, CurrentSelection = 0;
    while (true)
    {
        Output_To_Terminal(Options[CurrentSelection]);

        KeyPress = _getch();

        if (KeyPress == '\r') // enter key
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

bool Hangman::Get_User_Player_Choice()
{
    std::array<std::string, 3> Options;
    std::string GameDisplay = Get_Game_Display() + New_Line(" Please select what player you would like to be:              ");

    Options[0] = GameDisplay;
    Options[0] += New_Line(BLUE + " > GUESSER                                                    " + WHITE);
    Options[0] += New_Line("   WORD SETTER                                                ");
    Options[0] += Empty_Line(m_Width) + Empty_Line(m_Width) + Bottom_Line(m_Width) + Box(m_Width, "                    q = quit to main menu                     ");

    Options[1] = GameDisplay;
    Options[1] += New_Line("   GUESSER                                                    ");
    Options[1] += New_Line(BLUE + " > WORD SETTER                                                " + WHITE);
    Options[1] += Empty_Line(m_Width) + Empty_Line(m_Width) + Bottom_Line(m_Width) + Box(m_Width, "                    q = quit to main menu                     ");

    int KeyPress, CurrentSelection = 0;
    while (true)
    {
        Output_To_Terminal(Options[CurrentSelection]);

        KeyPress = _getch();

        if (KeyPress == '\r') // enter key
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

bool Hangman::Get_AI_Difficulty()
{
    std::array<std::string, 2> Options;
    std::string GameDisplay = Get_Game_Display() + New_Line(" Please select the AI difficulty:                             ");

    Options[0] = GameDisplay;
    Options[0] += New_Line(BLUE + " > EASY                                                       " + WHITE);
    Options[0] += New_Line("   HARD (Coming Soon!)                                        ");
    Options[0] += Empty_Line(m_Width) + Empty_Line(m_Width) + Bottom_Line(m_Width) + Box(m_Width, "                    q = quit to main menu                     ");

    Options[1] = GameDisplay;
    Options[1] += New_Line("   EASY                                                       ");
    Options[1] += New_Line(BLUE + " > HARD (Coming Soon!)                                        " + WHITE);
    Options[1] += Empty_Line(m_Width) + Empty_Line(m_Width) + Bottom_Line(m_Width) + Box(m_Width, "                    q = quit to main menu                     ");

    int KeyPress, CurrentSelection = 0;
    while (true)
    {
        Output_To_Terminal(Options[CurrentSelection]);

        KeyPress = _getch();

        if (KeyPress == '\r' && CurrentSelection == 0)
        {
            // CurrentSelection == 0 ? m_AIDifficulty = "EASY" : m_AIDifficulty = "HARD";
            m_AIDifficulty = "EASY";
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

bool Hangman::Get_Word_From_User()
{
    std::string Output = Get_Game_Display();
    Output += New_Line(" Please enter the word to be guessed:                         ");
    Output += Empty_Line(m_Width) + Empty_Line(m_Width) + Empty_Line(m_Width) + Empty_Line(m_Width) + Bottom_Line(m_Width);
    Output += Box(m_Width, "                    q = quit to main menu                     ");

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
        for (char & i : Input)
            if (i >= 'a' && i <= 'z')
                i -= 32;

        for (char i : Input)
            if (i < 'A' || i > 'Z')
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

void Hangman::Get_Random_Word()
{
    std::ifstream Words("../resources/words.txt");
    if (Words.is_open())
    {
        unsigned int RandomLineNumber = m_RandomNumberGenerator() % 972;
        std::string Word;
        for (unsigned int i = 0; i < RandomLineNumber - 1; i++)
            std::getline(Words, Word);
        std::getline(Words, Word);
        m_WordToBeGuessed = Word;
    }
    else
        m_WordToBeGuessed = "ERROR";

    Words.close();
}

void Hangman::Check_Guess_And_Update_Current_Guess(const char &Guess)
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

    m_MovesRemaining.erase(std::find(m_MovesRemaining.begin(), m_MovesRemaining.end(), Guess));
    m_NumberOfTurns++;
}

std::string Hangman::Get_Game_Display()
{
    // Top bar
    std::string Output = WHITE + Box(m_Width, "                           Hangman                            ");

    Output += Top_Line(m_Width);

    // Line 1
    switch (m_NumberOfErrors)
    {
    case 0:
    case 1:
    case 2:
        Output += Empty_Line(m_Width);
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
        Output += Empty_Line(m_Width);
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
        Output += Empty_Line(m_Width);
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
        Output += Empty_Line(m_Width);
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
        Output += Empty_Line(m_Width);
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

    for (char i : m_CurrentGuessOfWord)
        Output += std::string(" ") + i;

    if (m_GameOver && m_NumberOfErrors == 10)
    {
        Output += "   (The word was " + m_WordToBeGuessed + ")";
        Output.insert(Output.size(), (62 - 18 - m_WordToBeGuessed.size() * 3), ' ');
    }
    else
        Output.insert(Output.size(), (62 - m_WordToBeGuessed.size() * 2), ' ');

    Output += (char)186;

    return Output + "\n" + Empty_Line(m_Width);
}