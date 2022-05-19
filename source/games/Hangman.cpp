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

#include "games/Hangman.hpp"

Hangman::Hangman()
{
    m_StringBuilder.Set(62, "Hangman", "q = quit to main menu");
    m_RandomNumberGenerator.seed(std::chrono::system_clock::now().time_since_epoch().count());
}

void Hangman::Setup_Game()
{
    m_MovesRemaining.reserve(26);
    m_MovesRemaining = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    m_IncorrectGuesses.clear();
    m_WordToBeGuessed = "";
    m_CurrentGuessOfWord = "";
    m_AIDifficulty = "N/A ";
    m_NumberOfPlayers = "N/A";
    m_NumberOfErrors = 0;
    m_NumberOfTurns = 0;
    m_GameOver = false;

    Get_Number_Of_Players();

    if (m_NumberOfPlayers == "0  ")
    {
        m_UserIsWordGuesser = false;
        Get_AI_Difficulty();
        Get_Word_From_AI();
    }

    else if (m_NumberOfPlayers == "1  ")
    {
        Get_User_Player_Choice();
        Get_AI_Difficulty();

        if (!m_UserIsWordGuesser)
            Get_Word_From_User();
        else
            Get_Word_From_AI();
    }

    else if (m_NumberOfPlayers == "2  ")
    {
        m_UserIsWordGuesser = true;
        Get_Word_From_User();
    }

    for (unsigned int i = 0; i < m_WordToBeGuessed.size(); i++)
        m_CurrentGuessOfWord.push_back('_');
}

void Hangman::Get_Number_Of_Players()
{
    std::vector<std::string> Menus(3);
    std::string GameDisplay = Get_Game_Display() + m_StringBuilder.New_Line_Left_Justified(" Please select the number of human players:");

    Menus[0] = GameDisplay;
    Menus[0] += m_StringBuilder.New_Line_Left_Justified(" > 0", Colours::BLUE);
    Menus[0] += m_StringBuilder.New_Line_Left_Justified("   1");
    Menus[0] += m_StringBuilder.New_Line_Left_Justified("   2");
    Menus[0] += m_StringBuilder.Empty_Line() + m_StringBuilder.Bottom_Line() + m_StringBuilder.Bottom_Box();

    Menus[1] = GameDisplay;
    Menus[1] += m_StringBuilder.New_Line_Left_Justified("   0");
    Menus[1] += m_StringBuilder.New_Line_Left_Justified(" > 1", Colours::BLUE);
    Menus[1] += m_StringBuilder.New_Line_Left_Justified("   2");
    Menus[1] += m_StringBuilder.Empty_Line() + m_StringBuilder.Bottom_Line() + m_StringBuilder.Bottom_Box();

    Menus[2] = GameDisplay;
    Menus[2] += m_StringBuilder.New_Line_Left_Justified("   0");
    Menus[2] += m_StringBuilder.New_Line_Left_Justified("   1");
    Menus[2] += m_StringBuilder.New_Line_Left_Justified(" > 2", Colours::BLUE);
    Menus[2] += m_StringBuilder.Empty_Line() + m_StringBuilder.Bottom_Line() + m_StringBuilder.Bottom_Box();

    m_NumberOfPlayers = std::to_string(Terminal::Get_User_Menu_Choice(Menus)) + "  ";
}

void Hangman::Get_User_Player_Choice()
{
    std::vector<std::string> Menus(2);
    std::string GameDisplay = Get_Game_Display() + m_StringBuilder.New_Line_Left_Justified(" Please select what player you would like to be:              ");

    Menus[0] = GameDisplay;
    Menus[0] += m_StringBuilder.New_Line_Left_Justified(" > GUESSER", Colours::BLUE);
    Menus[0] += m_StringBuilder.New_Line_Left_Justified("   WORD SETTER");
    Menus[0] += m_StringBuilder.Empty_Line() + m_StringBuilder.Empty_Line() + m_StringBuilder.Bottom_Line() + m_StringBuilder.Bottom_Box();

    Menus[1] = GameDisplay;
    Menus[1] += m_StringBuilder.New_Line_Left_Justified("   GUESSER");
    Menus[1] += m_StringBuilder.New_Line_Left_Justified(" > WORD SETTER", Colours::BLUE);
    Menus[1] += m_StringBuilder.Empty_Line() + m_StringBuilder.Empty_Line() + m_StringBuilder.Bottom_Line() + m_StringBuilder.Bottom_Box();

    Terminal::Get_User_Menu_Choice(Menus) == 0 ? m_UserIsWordGuesser = true : m_UserIsWordGuesser = false;
}

void Hangman::Get_AI_Difficulty()
{
    std::vector<std::string> Menus(2);
    std::string GameDisplay = Get_Game_Display() + m_StringBuilder.New_Line_Left_Justified(" Please select the AI difficulty:                             ");

    Menus[0] = GameDisplay;
    Menus[0] += m_StringBuilder.New_Line_Left_Justified(" > EASY", Colours::BLUE);
    Menus[0] += m_StringBuilder.New_Line_Left_Justified("   HARD (Coming Soon!)");
    Menus[0] += m_StringBuilder.Empty_Line() + m_StringBuilder.Empty_Line() + m_StringBuilder.Bottom_Line() + m_StringBuilder.Bottom_Box();

    Menus[1] = GameDisplay;
    Menus[1] += m_StringBuilder.New_Line_Left_Justified("   EASY");
    Menus[1] += m_StringBuilder.New_Line_Left_Justified(" > HARD (Coming Soon!)", Colours::BLUE);
    Menus[1] += m_StringBuilder.Empty_Line() + m_StringBuilder.Empty_Line() + m_StringBuilder.Bottom_Line() + m_StringBuilder.Bottom_Box();

    Terminal::Get_User_Menu_Choice(Menus) == 0 ? m_AIDifficulty = "EASY" : m_AIDifficulty = "HARD";
}

void Hangman::Get_Word_From_User()
{
    std::string Output = Get_Game_Display();
    Output += m_StringBuilder.New_Line_Left_Justified(" Please enter the word to be guessed:");
    Output += m_StringBuilder.Empty_Line() + m_StringBuilder.Empty_Line() + m_StringBuilder.Empty_Line() + m_StringBuilder.Empty_Line() + m_StringBuilder.Bottom_Line();
    Output += m_StringBuilder.Bottom_Box();

    std::string Input;
    while (true)
    {
        Terminal::Output_To_Terminal(Output + "\x1B[1;37m");

        m_Terminal.Set_Cursor_Position(39, 13);

        std::getline(std::cin, Input);

        if (Input == "q")
            throw Exceptions::Quit();

        if (Input.size() < 3 || Input.size() > 14)
            continue;

        // Capitalise word
        std::transform(Input.begin(), Input.end(), Input.begin(), ::toupper);

        if (std::regex_match(Input, std::regex("^[A-Za-z]+$")))
        {
            m_WordToBeGuessed = Input;
            return;
        }
    }
}

void Hangman::Get_Word_From_AI()
{
    /**
     * Words.txt contains a list of the ~1,000 most used word in English from:
     * https://www.ef.co.uk/english-resources/english-vocabulary/top-1000-words/
     */
    std::ifstream Words("../resources/Words.txt");
    if (Words.is_open())
    {
        unsigned int RandomLineNumber = m_RandomNumberGenerator() % 972;
        std::string Word;
        for (unsigned int i = 0; i < RandomLineNumber - 1; i++)
            std::getline(Words, Word);
        std::getline(Words, Word);
        m_WordToBeGuessed = Word;
        Words.close();
    }
    else
    {
        Words.close();
        std::cout << "\nERROR: Words.txt file cannot be found\n";
        throw Exceptions::Quit();
    }
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
    return m_UserIsWordGuesser;
}

void Hangman::Execute_Next_User_Command()
{
    std::string Output = Get_Game_Display(), CurrentLetter;
    Output += m_StringBuilder.New_Line_Left_Justified(" Guesser, please enter your next guess:");
    Output += m_StringBuilder.Empty_Line() + m_StringBuilder.Empty_Line() + m_StringBuilder.Empty_Line() + m_StringBuilder.Empty_Line() + m_StringBuilder.Bottom_Line();
    Output += m_StringBuilder.Bottom_Box();

    int KeyPress, CurrentSelection = 0;
    while (true)
    {
        Terminal::Output_To_Terminal(Output);

        m_Terminal.Set_Cursor_Position(41, 13);

        std::cout << std::string("\x1B[1;34m") + m_MovesRemaining[CurrentSelection] + "\x1B[1;37m"; // Make it blue

        KeyPress = Terminal::Get_Key_Pressed();

        if (KeyPress == '\r') // enter key
        {
            Check_Guess_And_Update_Current_Guess(m_MovesRemaining[CurrentSelection]);
            return;
        }
        else if (KeyPress == 72) // up arrow key
            CurrentSelection == 0 ? CurrentSelection = (int)m_MovesRemaining.size() - 1 : --CurrentSelection;
        else if (KeyPress == 80) // down arrow key
            CurrentSelection == int(m_MovesRemaining.size() - 1) ? CurrentSelection = 0 : ++CurrentSelection;
        else if (KeyPress == 'q')
            throw Exceptions::Quit();
        else
        {
            auto Command = std::find(m_MovesRemaining.begin(), m_MovesRemaining.end(), KeyPress - 32);
            if (Command != m_MovesRemaining.end())
                CurrentSelection = (int)std::distance(m_MovesRemaining.begin(), Command);
        }
    }
}

void Hangman::Execute_Next_AI_Command()
{
    Check_Guess_And_Update_Current_Guess(m_MovesRemaining[m_RandomNumberGenerator() % m_MovesRemaining.size()]);
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

std::string Hangman::Get_Game_Over_Message()
{
    std::string Output = Get_Game_Display() + m_StringBuilder.New_Line_Centered("GAME OVER") + m_StringBuilder.Empty_Line();

    if (m_NumberOfErrors == 10)
        Output += m_StringBuilder.New_Line_Centered("The word setter has won! The game lasted " + std::to_string(m_NumberOfTurns) + " turns!");
    else
        Output += m_StringBuilder.New_Line_Centered("The guesser has won! The game lasted " + std::to_string(m_NumberOfTurns) + " turns.");

    Output += m_StringBuilder.Empty_Line() + m_StringBuilder.New_Line_Centered("Press 'Q' to quit OR Enter to play again...") + m_StringBuilder.Bottom_Line() + m_StringBuilder.Bottom_Box();

    return Output;
}

std::string Hangman::Get_Game_Display()
{
    // Top bar
    std::string Output = m_StringBuilder.Top_Box();

    Output += m_StringBuilder.Top_Line();

    // Hangman State
    if (m_NumberOfErrors == 0)
        Output += m_StringBuilder.Empty_Line() + m_StringBuilder.Empty_Line() + m_StringBuilder.New_Line("                    # of Players = " + m_NumberOfPlayers + "                        ") + m_StringBuilder.Empty_Line() + m_StringBuilder.New_Line("                   AI Difficulty = " + m_AIDifficulty + "                       ") + m_StringBuilder.Empty_Line() + m_StringBuilder.Empty_Line();
    else if (m_NumberOfErrors == 1)
        Output += m_StringBuilder.Empty_Line() + m_StringBuilder.New_Line("                                          Incorrect Guesses   ") + m_StringBuilder.New_Line("                    # of Players = " + m_NumberOfPlayers + "                        ") + m_StringBuilder.New_Line(std::string("                                          ") + m_IncorrectGuesses[0] + "                   ") + m_StringBuilder.New_Line("                   AI Difficulty = " + m_AIDifficulty + "                       ") + m_StringBuilder.Empty_Line() + m_StringBuilder.New_Line(std::string(" ") + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + "                                                    ");
    else if (m_NumberOfErrors == 2)
        Output += m_StringBuilder.Empty_Line() + m_StringBuilder.New_Line(std::string("     ") + (char)179 + "                                    Incorrect Guesses   ") + m_StringBuilder.New_Line(std::string("     ") + (char)179 + "              # of Players = " + m_NumberOfPlayers + "                        ") + m_StringBuilder.New_Line(std::string("     ") + (char)179 + "                                    " + m_IncorrectGuesses[0] + "   " + m_IncorrectGuesses[1] + "               ") + m_StringBuilder.New_Line(std::string("     ") + (char)179 + "             AI Difficulty = " + m_AIDifficulty + "                       ") + m_StringBuilder.New_Line(std::string("     ") + (char)179 + "                                                        ") + m_StringBuilder.New_Line(std::string(" ") + (char)196 + (char)196 + (char)196 + (char)196 + (char)193 + (char)196 + (char)196 + (char)196 + (char)196 + "                                                    ");
    else if (m_NumberOfErrors == 3)
        Output += m_StringBuilder.New_Line(std::string("     ") + (char)218 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + "                                                ") + m_StringBuilder.New_Line(std::string("     ") + (char)179 + "                                    Incorrect Guesses   ") + m_StringBuilder.New_Line(std::string("     ") + (char)179 + "              # of Players = " + m_NumberOfPlayers + "                        ") + m_StringBuilder.New_Line(std::string("     ") + (char)179 + "                                    " + m_IncorrectGuesses[0] + "   " + m_IncorrectGuesses[1] + "   " + m_IncorrectGuesses[2] + "           ") + m_StringBuilder.New_Line(std::string("     ") + (char)179 + "             AI Difficulty = " + m_AIDifficulty + "                       ") + m_StringBuilder.New_Line(std::string("     ") + (char)179 + "                                                        ") + m_StringBuilder.New_Line(std::string(" ") + (char)196 + (char)196 + (char)196 + (char)196 + (char)193 + (char)196 + (char)196 + (char)196 + (char)196 + "                                                    ");
    else if (m_NumberOfErrors == 4)
        Output += m_StringBuilder.New_Line(std::string("     ") + (char)218 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)191 + "                                                ") + m_StringBuilder.New_Line(std::string("     ") + (char)179 + "       " + (char)179 + "                            Incorrect Guesses   ") + m_StringBuilder.New_Line(std::string("     ") + (char)179 + "              # of Players = " + m_NumberOfPlayers + "                        ") + m_StringBuilder.New_Line(std::string("     ") + (char)179 + "                                    " + m_IncorrectGuesses[0] + "   " + m_IncorrectGuesses[1] + "   " + m_IncorrectGuesses[2] + "   " + m_IncorrectGuesses[3] + "       ") + m_StringBuilder.New_Line(std::string("     ") + (char)179 + "             AI Difficulty = " + m_AIDifficulty + "                       ") + m_StringBuilder.New_Line(std::string("     ") + (char)179 + "                                                        ") + m_StringBuilder.New_Line(std::string(" ") + (char)196 + (char)196 + (char)196 + (char)196 + (char)193 + (char)196 + (char)196 + (char)196 + (char)196 + "                                                    ");
    else if (m_NumberOfErrors == 5)
        Output += m_StringBuilder.New_Line(std::string("     ") + (char)218 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)191 + "                                                ") + m_StringBuilder.New_Line(std::string("     ") + (char)179 + "       " + (char)179 + "                            Incorrect Guesses   ") + m_StringBuilder.New_Line(std::string("     ") + (char)179 + "       O      # of Players = " + m_NumberOfPlayers + "                        ") + m_StringBuilder.New_Line(std::string("     ") + (char)179 + "                                    " + m_IncorrectGuesses[0] + "   " + m_IncorrectGuesses[1] + "   " + m_IncorrectGuesses[2] + "   " + m_IncorrectGuesses[3] + "   " + m_IncorrectGuesses[4] + "   ") + m_StringBuilder.New_Line(std::string("     ") + (char)179 + "             AI Difficulty = " + m_AIDifficulty + "                       ") + m_StringBuilder.New_Line(std::string("     ") + (char)179 + "                                                        ") + m_StringBuilder.New_Line(std::string(" ") + (char)196 + (char)196 + (char)196 + (char)196 + (char)193 + (char)196 + (char)196 + (char)196 + (char)196 + "                                                    ");
    else if (m_NumberOfErrors == 6)
        Output += m_StringBuilder.New_Line(std::string("     ") + (char)218 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)191 + "                                                ") + m_StringBuilder.New_Line(std::string("     ") + (char)179 + "       " + (char)179 + "                            Incorrect Guesses   ") + m_StringBuilder.New_Line(std::string("     ") + (char)179 + "       O      # of Players = " + m_NumberOfPlayers + "                        ") + m_StringBuilder.New_Line(std::string("     ") + (char)179 + "       " + (char)179 + "                            " + m_IncorrectGuesses[0] + "   " + m_IncorrectGuesses[1] + "   " + m_IncorrectGuesses[2] + "   " + m_IncorrectGuesses[3] + "   " + m_IncorrectGuesses[4] + "   ") + m_StringBuilder.New_Line(std::string("     ") + (char)179 + "             AI Difficulty = " + m_AIDifficulty + "                       ") + m_StringBuilder.New_Line(std::string("     ") + (char)179 + "                                    " + m_IncorrectGuesses[5] + "                   ") + m_StringBuilder.New_Line(std::string(" ") + (char)196 + (char)196 + (char)196 + (char)196 + (char)193 + (char)196 + (char)196 + (char)196 + (char)196 + "                                                    ");
    else if (m_NumberOfErrors == 7)
        Output += m_StringBuilder.New_Line(std::string("     ") + (char)218 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)191 + "                                                ") + m_StringBuilder.New_Line(std::string("     ") + (char)179 + "       " + (char)179 + "                            Incorrect Guesses   ") + m_StringBuilder.New_Line(std::string("     ") + (char)179 + "       O      # of Players = " + m_NumberOfPlayers + "                        ") + m_StringBuilder.New_Line(std::string("     ") + (char)179 + "       " + (char)179 + "                            " + m_IncorrectGuesses[0] + "   " + m_IncorrectGuesses[1] + "   " + m_IncorrectGuesses[2] + "   " + m_IncorrectGuesses[3] + "   " + m_IncorrectGuesses[4] + "   ") + m_StringBuilder.New_Line(std::string("     ") + (char)179 + "      /      AI Difficulty = " + m_AIDifficulty + "                       ") + m_StringBuilder.New_Line(std::string("     ") + (char)179 + "                                    " + m_IncorrectGuesses[5] + "   " + m_IncorrectGuesses[6] + "               ") + m_StringBuilder.New_Line(std::string(" ") + (char)196 + (char)196 + (char)196 + (char)196 + (char)193 + (char)196 + (char)196 + (char)196 + (char)196 + "                                                    ");
    else if (m_NumberOfErrors == 8)
        Output += m_StringBuilder.New_Line(std::string("     ") + (char)218 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)191 + "                                                ") + m_StringBuilder.New_Line(std::string("     ") + (char)179 + "       " + (char)179 + "                            Incorrect Guesses   ") + m_StringBuilder.New_Line(std::string("     ") + (char)179 + "       O      # of Players = " + m_NumberOfPlayers + "                        ") + m_StringBuilder.New_Line(std::string("     ") + (char)179 + "       " + (char)179 + "                            " + m_IncorrectGuesses[0] + "   " + m_IncorrectGuesses[1] + "   " + m_IncorrectGuesses[2] + "   " + m_IncorrectGuesses[3] + "   " + m_IncorrectGuesses[4] + "   ") + m_StringBuilder.New_Line(std::string("     ") + (char)179 + "      / \\    AI Difficulty = " + m_AIDifficulty + "                       ") + m_StringBuilder.New_Line(std::string("     ") + (char)179 + "                                    " + m_IncorrectGuesses[5] + "   " + m_IncorrectGuesses[6] + "   " + m_IncorrectGuesses[7] + "           ") + m_StringBuilder.New_Line(std::string(" ") + (char)196 + (char)196 + (char)196 + (char)196 + (char)193 + (char)196 + (char)196 + (char)196 + (char)196 + "                                                    ");
    else if (m_NumberOfErrors == 9)
        Output += m_StringBuilder.New_Line(std::string("     ") + (char)218 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)191 + "                                                ") + m_StringBuilder.New_Line(std::string("     ") + (char)179 + "       " + (char)179 + "                            Incorrect Guesses   ") + m_StringBuilder.New_Line(std::string("     ") + (char)179 + "       O      # of Players = " + m_NumberOfPlayers + "                        ") + m_StringBuilder.New_Line(std::string("     ") + (char)179 + "      /" + (char)179 + "                            " + m_IncorrectGuesses[0] + "   " + m_IncorrectGuesses[1] + "   " + m_IncorrectGuesses[2] + "   " + m_IncorrectGuesses[3] + "   " + m_IncorrectGuesses[4] + "   ") + m_StringBuilder.New_Line(std::string("     ") + (char)179 + "      / \\    AI Difficulty = " + m_AIDifficulty + "                       ") + m_StringBuilder.New_Line(std::string("     ") + (char)179 + "                                    " + m_IncorrectGuesses[5] + "   " + m_IncorrectGuesses[6] + "   " + m_IncorrectGuesses[7] + "   " + m_IncorrectGuesses[8] + "       ") + m_StringBuilder.New_Line(std::string(" ") + (char)196 + (char)196 + (char)196 + (char)196 + (char)193 + (char)196 + (char)196 + (char)196 + (char)196 + "                                                    ");
    else if (m_NumberOfErrors == 10)
        Output += m_StringBuilder.New_Line(std::string("     ") + (char)218 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)196 + (char)191 + "                                                ") + m_StringBuilder.New_Line(std::string("     ") + (char)179 + "       " + (char)179 + "                            Incorrect Guesses   ") + m_StringBuilder.New_Line(std::string("     ") + (char)179 + "       O      # of Players = " + m_NumberOfPlayers + "                        ") + m_StringBuilder.New_Line(std::string("     ") + (char)179 + "      /" + (char)179 + "\\                           " + m_IncorrectGuesses[0] + "   " + m_IncorrectGuesses[1] + "   " + m_IncorrectGuesses[2] + "   " + m_IncorrectGuesses[3] + "   " + m_IncorrectGuesses[4] + "   ") + m_StringBuilder.New_Line(std::string("     ") + (char)179 + "      / \\    AI Difficulty = " + m_AIDifficulty + "                       ") + m_StringBuilder.New_Line(std::string("     ") + (char)179 + "                                    " + m_IncorrectGuesses[5] + "   " + m_IncorrectGuesses[6] + "   " + m_IncorrectGuesses[7] + "   " + m_IncorrectGuesses[8] + "   " + m_IncorrectGuesses[9] + "   ") + m_StringBuilder.New_Line(std::string(" ") + (char)196 + (char)196 + (char)196 + (char)196 + (char)193 + (char)196 + (char)196 + (char)196 + (char)196 + "                                                    ");

    // Word to be guessed, and thus current guess of word, are limited to a size in between 3 and 14
    Output += (char)186;

    for (char i : m_CurrentGuessOfWord)
        Output += std::string(" ") + i;

    if (m_GameOver && m_NumberOfErrors == 10) // show what the word to be guessed was
    {
        Output += "   (The word was " + m_WordToBeGuessed + ")";
        Output.insert(Output.size(), (62 - 18 - m_WordToBeGuessed.size() * 3), ' ');
    }
    else // do not show it
        Output.insert(Output.size(), (62 - m_WordToBeGuessed.size() * 2), ' ');

    Output += (char)186;

    return Output + "\n" + m_StringBuilder.Empty_Line();
}
