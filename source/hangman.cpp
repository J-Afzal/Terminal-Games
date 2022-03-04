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

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <conio.h>
#include "functions.hpp"
#include "hangman.hpp"

void Hangman::Play(const HANDLE &ConsoleHandle)
{
    bool GameIsRunning = true;
    bool QuitToMainMenu = false;
    while (GameIsRunning)
    {
        std::vector<char> ValidMovesRemaining, IncorrectGuesses;
        std::string WordToBeGuessed, CurrentGuessOfWord, PlayerThatIsGuessing, AIDifficulty = "N/A";
        int NumberOfPlayers, NumberOfErrors = 0, NumberOfTurns = 0;

        Setup_Game(ValidMovesRemaining, IncorrectGuesses, WordToBeGuessed, CurrentGuessOfWord, PlayerThatIsGuessing, AIDifficulty, NumberOfPlayers, ConsoleHandle, QuitToMainMenu);

        if (QuitToMainMenu)
            break;

        while (!Game_Over(NumberOfTurns) && !Winning_Conditions_Met(WordToBeGuessed, CurrentGuessOfWord))
        {
            // Display_Game() called before either user or AI are asked for an input
            if (PlayerThatIsGuessing == "HUMAN")
                Get_Next_User_Guess(ValidMovesRemaining, IncorrectGuesses, WordToBeGuessed, CurrentGuessOfWord, AIDifficulty, NumberOfPlayers, NumberOfErrors, ConsoleHandle, QuitToMainMenu);
            else
                Get_Next_AI_Guess(ValidMovesRemaining, IncorrectGuesses, WordToBeGuessed, CurrentGuessOfWord, NumberOfErrors);

            if (QuitToMainMenu)
                break;

            NumberOfTurns++;
        }

        if (QuitToMainMenu)
            break;

        Display_Game_Over_Message(IncorrectGuesses, WordToBeGuessed, CurrentGuessOfWord, AIDifficulty, NumberOfPlayers, NumberOfErrors, NumberOfTurns, GameIsRunning);
    }
}

void Hangman::Setup_Game(std::vector<char> &ValidMovesRemaining,
                         const std::vector<char> &IncorrectGuesses,
                         std::string &WordToBeGuessed,
                         std::string &CurrentGuessOfWord,
                         std::string &PlayerThatIsGuessing,
                         std::string &AIDifficulty,
                         int &NumberOfPlayers,
                         const HANDLE &ConsoleHandle,
                         bool &QuitToMainMenu)
{
    std::srand(std::time(0));

    NumberOfPlayers = Get_Number_Of_Players(IncorrectGuesses, QuitToMainMenu);
    if (QuitToMainMenu)
        return;

    if (NumberOfPlayers == 0)
    {
        PlayerThatIsGuessing = "AI";
        AIDifficulty = Get_AI_Difficulty(IncorrectGuesses, NumberOfPlayers, QuitToMainMenu);
        if (QuitToMainMenu)
            return;
        WordToBeGuessed = Get_Word_To_Be_Guessed_From_AI();
    }

    else if (NumberOfPlayers == 1)
    {
        PlayerThatIsGuessing = Get_User_Player_Choice(IncorrectGuesses, NumberOfPlayers, QuitToMainMenu);
        if (QuitToMainMenu)
            return;

        AIDifficulty = Get_AI_Difficulty(IncorrectGuesses, NumberOfPlayers, QuitToMainMenu);
        if (QuitToMainMenu)
            return;

        if (PlayerThatIsGuessing == "PLAYER ONE")
        {
            PlayerThatIsGuessing = "HUMAN";
            WordToBeGuessed = Get_Word_To_Be_Guessed_From_AI();
        }
        else
        {
            PlayerThatIsGuessing = "AI";
            WordToBeGuessed = Get_Word_To_Be_Guessed_From_User(IncorrectGuesses, AIDifficulty, NumberOfPlayers, ConsoleHandle, QuitToMainMenu);
            if (QuitToMainMenu)
                return;
        }
    }

    else if (NumberOfPlayers == 2)
    {
        PlayerThatIsGuessing = "HUMAN";
        AIDifficulty = "N/A";
        WordToBeGuessed = Get_Word_To_Be_Guessed_From_User(IncorrectGuesses, AIDifficulty, NumberOfPlayers, ConsoleHandle, QuitToMainMenu);
        if (QuitToMainMenu)
            return;
    }

    for (unsigned int i = 0; i < WordToBeGuessed.size(); i++)
        CurrentGuessOfWord.push_back('_');

    ValidMovesRemaining = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
}

int Hangman::Get_Number_Of_Players(const std::vector<char> &IncorrectGuesses,
                                   bool &QuitToMainMenu)
{
    std::string CommonString = Get_Game_Display(IncorrectGuesses, "", "", "N/A", "N/A", 0, false);
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
        Clear_Terminal();

        if (CurrentSelection == 0)
            std::cout << CaseZero;
        else if (CurrentSelection == 1)
            std::cout << CaseOne;
        else if (CurrentSelection == 2)
            std::cout << CaseTwo;

        KeyPress = _getch();

        if (KeyPress == '\r')
            break;
        else if (KeyPress == 72) // up arrow key
            CurrentSelection == 0 ? CurrentSelection = 2 : --CurrentSelection;
        else if (KeyPress == 80) // down arrow key
            CurrentSelection == 2 ? CurrentSelection = 0 : ++CurrentSelection;
        else if (KeyPress == 'q')
        {
            QuitToMainMenu = true;
            return -1;
        }
    }

    return CurrentSelection;
}

std::string Hangman::Get_User_Player_Choice(const std::vector<char> &IncorrectGuesses,
                                            const int &NumberOfPlayers,
                                            bool &QuitToMainMenu)
{
    std::string CommonString = Get_Game_Display(IncorrectGuesses, "", "", "N/A", std::to_string(NumberOfPlayers), 0, false);
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
        Clear_Terminal();

        if (CurrentSelection == 0)
            std::cout << CaseZero;
        else if (CurrentSelection == 1)
            std::cout << CaseOne;

        KeyPress = _getch();

        if (KeyPress == '\r')
            break;
        else if (KeyPress == 72) // up arrow key
            CurrentSelection == 0 ? CurrentSelection = 1 : --CurrentSelection;
        else if (KeyPress == 80) // down arrow key
            CurrentSelection == 1 ? CurrentSelection = 0 : ++CurrentSelection;
        else if (KeyPress == 'q')
        {
            QuitToMainMenu = true;
            return "-1";
        }
    }

    return CurrentSelection == 0 ? "PLAYER ONE" : "PLAYER TWO";
}

std::string Hangman::Get_AI_Difficulty(const std::vector<char> &IncorrectGuesses,
                                       const int &NumberOfPlayers,
                                       bool &QuitToMainMenu)
{
    std::string CommonString = Get_Game_Display(IncorrectGuesses, "", "", "N/A", std::to_string(NumberOfPlayers), 0, false);
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
        Clear_Terminal();

        if (CurrentSelection == 0)
            std::cout << CaseZero;
        else if (CurrentSelection == 1)
            std::cout << CaseOne;

        KeyPress = _getch();

        if (KeyPress == '\r' && CurrentSelection == 0)
            break;
        else if (KeyPress == 72) // up arrow key
            CurrentSelection == 0 ? CurrentSelection = 1 : --CurrentSelection;
        else if (KeyPress == 80) // down arrow key
            CurrentSelection == 1 ? CurrentSelection = 0 : ++CurrentSelection;
        else if (KeyPress == 'q')
        {
            QuitToMainMenu = true;
            return "-1";
        }
    }

    return CurrentSelection == 0 ? "EASY" : "HARD";
}

std::string Hangman::Get_Word_To_Be_Guessed_From_User(const std::vector<char> &IncorrectGuesses,
                                                      const std::string &AIDifficulty,
                                                      const int &NumberOfPlayers,
                                                      const HANDLE &ConsoleHandle,
                                                      bool &QuitToMainMenu)
{
    std::string Output = Get_Game_Display(IncorrectGuesses, "", "", AIDifficulty, std::to_string(NumberOfPlayers), 0, false);
    Output += New_Line(" Please enter the word to be guessed:                         ");
    Output += Empty_Line() + Empty_Line() + Empty_Line() + Empty_Line() + Bottom_Line() + Bottom_Bar();

    bool InputInvalid = true;
    std::string Input;
    while (InputInvalid)
    {
        InputInvalid = false;

        Clear_Terminal();

        std::cout << Output;

        SetConsoleCursorPosition(ConsoleHandle, {39, 13});

        std::getline(std::cin, Input);

        if (Input == "q")
        {
            QuitToMainMenu = true;
            return "-1";
        }

        if (Input.size() < 3 || Input.size() > 14)
        {
            InputInvalid = true;
            continue;
        }

        for (unsigned int i = 0; i < Input.size(); i++)
            if (Input[i] >= 'a' && Input[i] <= 'z')
                Input[i] -= 32;

        for (unsigned int i = 0; i < Input.size(); i++)
        {
            if (Input[i] < 'A' || Input[i] > 'Z')
            {
                InputInvalid = true;
                break;
            }
        }
    }

    return Input;
}

std::string Hangman::Get_Word_To_Be_Guessed_From_AI(void)
{
    return Return_Word_List()[std::rand() % Return_Word_List().size()];
}

std::string Hangman::Get_Game_Display(const std::vector<char> &IncorrectGuesses,
                                      const std::string &WordToBeGuessed,
                                      const std::string &CurrentGuessOfWord,
                                      const std::string &AIDifficulty,
                                      const std::string &NumberOfPlayers,
                                      const int &NumberOfErrors,
                                      const bool &GameOver)
{
    std::string Output;

    // Top bar
    Output += WHITE + Top_Line() + New_Line(RED + "                           Hangman                            " + WHITE) + Bottom_Line();

    // Centre information
    Output += Top_Line();

    // Line 1
    switch (NumberOfErrors)
    {
    case 0:
    case 1:
    case 2:
        Output += Empty_Line();
        break;

    case 3:
        Output += (char)186 + "     " + (char)218;
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
        Output += (char)186 + "     " + (char)218;
        Output.insert(Output.size(), 7, (char)196);
        Output += std::to_string((char)191) + "                                                " + (char)186 + "\n";
        break;
    }

    // Line 2
    switch (NumberOfErrors)
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
    switch (NumberOfErrors)
    {
    case 0:
        if (NumberOfPlayers == "N/A")
            Output += New_Line("                   # of Players = " + NumberOfPlayers + "                         ");
        else
            Output += New_Line("                    # of Players = " + NumberOfPlayers + "                          ");
        break;

    case 1:
        Output += New_Line("                    # of Players = " + NumberOfPlayers + "                          ");
        break;

    case 2:
    case 3:
    case 4:
        Output += New_Line(std::string("     ") + (char)179 + "              # of Players = " + NumberOfPlayers + "                          ");
        break;

    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
        Output += New_Line(std::string("     ") + (char)179 + "       O      # of Players = " + NumberOfPlayers + "                          ");
        break;
    }

    // Line 4
    switch (NumberOfErrors)
    {
    case 0:
        Output += Empty_Line();
        break;

    case 1:
        Output.insert(Output.size(), New_Line(std::string("                                          ") + IncorrectGuesses[0] + "                   "));
        break;

    case 2:
        Output += New_Line(std::string("     ") + (char)179 + "                                    " + IncorrectGuesses[0] + "   " + IncorrectGuesses[1] + "               ");
        break;

    case 3:
        Output += New_Line(std::string("     ") + (char)179 + "                                    " + IncorrectGuesses[0] + "   " + IncorrectGuesses[1] + "   " + IncorrectGuesses[2] + "           ");
        break;

    case 4:
        Output += New_Line(std::string("     ") + (char)179 + "                                    " + IncorrectGuesses[0] + "   " + IncorrectGuesses[1] + "   " + IncorrectGuesses[2] + "   " + IncorrectGuesses[3] + "       ");
        break;

    case 5:
        Output += New_Line(std::string("     ") + (char)179 + "                                    " + IncorrectGuesses[0] + "   " + IncorrectGuesses[1] + "   " + IncorrectGuesses[2] + "   " + IncorrectGuesses[3] + "   " + IncorrectGuesses[4] + "   ");
        break;

    case 6:
    case 7:
    case 8:
        Output += New_Line(std::string("     ") + (char)179 + "       " + (char)179 + "                            " + IncorrectGuesses[0] + "   " + IncorrectGuesses[1] + "   " + IncorrectGuesses[2] + "   " + IncorrectGuesses[3] + "   " + IncorrectGuesses[4] + "   ");
        break;

    case 9:
        Output += New_Line(std::string("     ") + (char)179 + "      /" + (char)179 + "                            " + IncorrectGuesses[0] + "   " + IncorrectGuesses[1] + "   " + IncorrectGuesses[2] + "   " + IncorrectGuesses[3] + "   " + IncorrectGuesses[4] + "   ");
        break;

    case 10:
        Output += New_Line(std::string("     ") + (char)179 + "      /" + (char)179 + "\\                           " + IncorrectGuesses[0] + "   " + IncorrectGuesses[1] + "   " + IncorrectGuesses[2] + "   " + IncorrectGuesses[3] + "   " + IncorrectGuesses[4] + "   ");
        break;
    }

    // Line 5
    switch (NumberOfErrors)
    {
    case 0:
    case 1:
        if (AIDifficulty == "N/A")
            Output += New_Line("                   AI Difficulty = " + AIDifficulty + "                        ");
        else
            Output += New_Line("                  AI Difficulty = " + AIDifficulty + "                        ");
        break;

    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
        Output += (char)186 + "     " + (char)179;
        if (AIDifficulty == "N/A")
            Output += "             AI Difficulty = " + AIDifficulty + "                        ";
        else
            Output += "            AI Difficulty = " + AIDifficulty + "                        ";
        Output += (char)186 + "\n";
        break;

    case 7:
        Output += (char)186 + "     " + (char)179;
        if (AIDifficulty == "N/A")
            Output += "      /      AI Difficulty = " + AIDifficulty + "                        ";
        else
            Output += "      /     AI Difficulty = " + AIDifficulty + "                        ";
        Output += (char)186 + "\n";
        break;

    case 8:
    case 9:
    case 10:
        Output += (char)186 + "     " + (char)179;
        if (AIDifficulty == "N/A")
            Output += "      / \\    AI Difficulty = " + AIDifficulty + "                        ";
        else
            Output += "      / \\   AI Difficulty = " + AIDifficulty + "                        ";
        Output += (char)186 + "\n";
        break;
    }

    // Line 6
    switch (NumberOfErrors)
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
        Output += New_Line(std::string("     ") + (char)179 + "                                    " + IncorrectGuesses[5] + "                   ");
        break;

    case 7:
        Output += New_Line(std::string("     ") + (char)179 + "                                    " + IncorrectGuesses[5] + "   " + IncorrectGuesses[6] + "               ");
        break;

    case 8:
        Output += New_Line(std::string("     ") + (char)179 + "                                    " + IncorrectGuesses[5] + "   " + IncorrectGuesses[6] + "   " + IncorrectGuesses[7] + "           ");
        break;

    case 9:
        Output += New_Line(std::string("     ") + (char)179 + "                                    " + IncorrectGuesses[5] + "   " + IncorrectGuesses[6] + "   " + IncorrectGuesses[7] + "   " + IncorrectGuesses[8] + "       ");
        break;

    case 10:
        Output += New_Line(std::string("     ") + (char)179 + "                                    " + IncorrectGuesses[5] + "   " + IncorrectGuesses[6] + "   " + IncorrectGuesses[7] + "   " + IncorrectGuesses[8] + "   " + IncorrectGuesses[9] + "   ");
        break;
    }

    // Line 7
    switch (NumberOfErrors)
    {
    case 0:
        Output += Empty_Line();
        break;

    case 1:
        Output += (char)186 + " ";
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
        Output += (char)186 + " ";
        Output.insert(Output.size(), 4, (char)196);
        Output += (char)193;
        Output.insert(Output.size(), 4, (char)196);
        Output += std::string("                                                    ") + (char)186 + "\n";
        break;
    }

    // Word to be guessed, and thus current guess of word, are limited to a size in between 3 and 14
    Output += (char)186;

    for (unsigned int i = 0; i < CurrentGuessOfWord.size(); i++)
        Output += " " + CurrentGuessOfWord[i];

    if (GameOver && NumberOfErrors == 10)
    {
        Output += "   (The word was " + WordToBeGuessed + ")";
        Output.insert(Output.size(), (62 - 18 - WordToBeGuessed.size() * 3), ' ');
    }
    else
        Output.insert(Output.size(), (62 - WordToBeGuessed.size() * 3), ' ');

    Output += (char)186 + "\n" + Empty_Line();

    return Output;
}

std::string Hangman::New_Line(const std::string &Input)
{
    return (char)186 + Input + (char)186 + "\n";
}

std::string Hangman::Empty_Line(void)
{
    std::string Output;
    Output += (char)186;
    Output.insert(Output.size(), 62, ' ');
    Output += (char)186;
    return Output + "\n";
}

std::string Hangman::Top_Line(void)
{
    std::string Output;
    Output += (char)201;
    Output.insert(Output.size(), 62, (char)205);
    Output += (char)187;
    return Output + "\n";
}

std::string Hangman::Bottom_Line(void)
{
    std::string Output;
    Output += (char)200;
    Output.insert(Output.size(), 62, (char)205);
    Output += (char)188;
    return Output + "\n";
}

std::string Hangman::Bottom_Bar(void)
{
    return Top_Line() + New_Line(RED + "                    q = quit to main menu                     " + WHITE) + Bottom_Line();
}

bool Hangman::Game_Over(const int &NumberOfTurns)
{
    return (NumberOfTurns == 10) ? true : false;
}

bool Hangman::Winning_Conditions_Met(const std::string &WordToBeGuessed,
                                     const std::string &CurrentGuessOfWord)
{
    for (unsigned int i = 0; i < WordToBeGuessed.size(); i++)
        if (WordToBeGuessed[i] != CurrentGuessOfWord[i])
            return false;
    return true;
}

void Hangman::Get_Next_User_Guess(std::vector<char> &ValidMovesRemaining,
                                  std::vector<char> &IncorrectGuesses,
                                  const std::string &WordToBeGuessed,
                                  std::string &CurrentGuessOfWord,
                                  const std::string &AIDifficulty,
                                  const int &NumberOfPlayers,
                                  int &NumberOfErrors,
                                  const HANDLE &ConsoleHandle,
                                  bool &QuitToMainMenu)
{
    std::string Output = Get_Game_Display(IncorrectGuesses, WordToBeGuessed, CurrentGuessOfWord, AIDifficulty, std::to_string(NumberOfPlayers), NumberOfErrors, false);
    Output += New_Line(" Guesser, please enter your next guess:                       ");
    Output += Empty_Line() + Empty_Line() + Empty_Line() + Empty_Line() + Bottom_Line() + Bottom_Bar();

    int KeyPress = 0, CurrentSelection = 0;
    char UserGuess;
    while (true)
    {
        Clear_Terminal();

        std::cout << Output;

        SetConsoleCursorPosition(ConsoleHandle, {41, 13});

        std::cout << BLUE + ValidMovesRemaining[CurrentSelection] + WHITE;

        KeyPress = _getch();

        if (KeyPress == '\r')
            break;
        else if (KeyPress == 72) // up arrow key
            CurrentSelection == 0 ? CurrentSelection = ValidMovesRemaining.size() - 1 : --CurrentSelection;
        else if (KeyPress == 80) // down arrow key
            CurrentSelection == int(ValidMovesRemaining.size() - 1) ? CurrentSelection = 0 : ++CurrentSelection;
        else if (KeyPress == 'q')
        {
            QuitToMainMenu = true;
            return;
        }
        else
        {
            auto it = std::find(ValidMovesRemaining.begin(), ValidMovesRemaining.end(), KeyPress - 32);
            if (it != ValidMovesRemaining.end())
                CurrentSelection = std::distance(ValidMovesRemaining.begin(), it);
        }
    }

    UserGuess = ValidMovesRemaining[CurrentSelection];
    ValidMovesRemaining.erase(std::find(ValidMovesRemaining.begin(), ValidMovesRemaining.end(), UserGuess));
    if (!Check_Guess_Against_Word_To_Be_Guessed(WordToBeGuessed, CurrentGuessOfWord, UserGuess))
    {
        IncorrectGuesses.push_back(UserGuess);
        NumberOfErrors++;
    }
}

void Hangman::Get_Next_AI_Guess(std::vector<char> &ValidMovesRemaining,
                                std::vector<char> &IncorrectGuesses,
                                const std::string &WordToBeGuessed,
                                std::string &CurrentGuessOfWord,
                                int &NumberOfErrors)
{
    char Guess = ValidMovesRemaining[std::rand() % ValidMovesRemaining.size()];
    ValidMovesRemaining.erase(std::find(ValidMovesRemaining.begin(), ValidMovesRemaining.end(), Guess));
    if (!Check_Guess_Against_Word_To_Be_Guessed(WordToBeGuessed, CurrentGuessOfWord, Guess))
    {
        IncorrectGuesses.push_back(Guess);
        NumberOfErrors++;
    }
}

bool Hangman::Check_Guess_Against_Word_To_Be_Guessed(const std::string &WordToBeGuessed,
                                                     std::string &CurrentGuessOfWord,
                                                     const char &Guess)
{
    bool IsGuessCorrect = false;

    for (unsigned int i = 0; i < WordToBeGuessed.size(); i++)
        if (WordToBeGuessed[i] == Guess)
        {
            IsGuessCorrect = true;
            CurrentGuessOfWord[i] = Guess;
        }

    return IsGuessCorrect;
}

void Hangman::Display_Game_Over_Message(const std::vector<char> &IncorrectGuesses,
                                        const std::string &WordToBeGuessed,
                                        const std::string &CurrentGuessOfWord,
                                        const std::string &AIDifficulty,
                                        const int &NumberOfPlayers,
                                        const int &NumberOfErrors,
                                        const int &NumberOfTurns,
                                        bool &GameIsRunning)
{
    std::string Output = Get_Game_Display(IncorrectGuesses, WordToBeGuessed, CurrentGuessOfWord, AIDifficulty, std::to_string(NumberOfPlayers), NumberOfErrors, true);
    Output += New_Line("                          GAME OVER                           ") + Empty_Line();

    if (NumberOfErrors == 10)
        Output += New_Line("      The word setter has won! The game lasted " + std::to_string(NumberOfTurns) + " turns!      ");
    else
    {
        Output += New_Line("        The guesser has won! The game lasted " + std::to_string(NumberOfTurns) + " turns.        ");
        if (NumberOfTurns < 10)
            Output += (" ");
    }

    Output += Empty_Line() + New_Line("     Press 'Q' to quit OR any other key to play again...      ") + Bottom_Line() + Bottom_Bar();

    Clear_Terminal();

    std::cout << Output;

    if (_getch() == 'q')
        GameIsRunning = false;
}