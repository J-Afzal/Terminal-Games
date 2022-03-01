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

void Play_Hangman(const HANDLE &ConsoleHandle)
{
    bool GameIsRunning = true;

    while (GameIsRunning)
    {
        unsigned int NumberOfPlayers, NumberOfErrors = 0, NumberOfTurns = 0;
        std::string WordToBeGuessed, CurrentGuessOfWord, PlayerThatIsGuessing, AIDifficulty = "N/A";
        std::vector<std::string> CorrectGuesses, IncorrectGuesses, ValidMovesRemaining;

        Setup_Game(NumberOfPlayers, PlayerThatIsGuessing, AIDifficulty, WordToBeGuessed, CurrentGuessOfWord, ValidMovesRemaining, IncorrectGuesses, ConsoleHandle);

        while (!Winning_Conditions_Met(NumberOfErrors, WordToBeGuessed, CurrentGuessOfWord))
        {
            // Display_Game() called before either user or AI are asked for an input
            if (PlayerThatIsGuessing == "HUMAN")
                Get_Next_User_Guess(NumberOfErrors, NumberOfPlayers, AIDifficulty, IncorrectGuesses, CorrectGuesses, ValidMovesRemaining, CurrentGuessOfWord, WordToBeGuessed, ConsoleHandle);
            else
                Get_Next_AI_Guess(NumberOfErrors, NumberOfPlayers, AIDifficulty, IncorrectGuesses, CorrectGuesses, ValidMovesRemaining, CurrentGuessOfWord, WordToBeGuessed);

            NumberOfTurns++;
        }

        Display_Game_Over_Message(NumberOfErrors, NumberOfPlayers, AIDifficulty, IncorrectGuesses, CurrentGuessOfWord, WordToBeGuessed, NumberOfTurns, GameIsRunning);
    }
}

void Setup_Game(unsigned int &NumberOfPlayers,
                std::string &PlayerThatIsGuessing,
                std::string &AIDifficulty,
                std::string &WordToBeGuessed,
                std::string &CurrentGuessOfWord,
                std::vector<std::string> &ValidMovesRemaining,
                const std::vector<std::string> &IncorrectGuesses,
                const HANDLE &ConsoleHandle)
{
    std::srand((unsigned int)std::time(0));

    NumberOfPlayers = Get_Number_Of_Players(IncorrectGuesses);

    switch (NumberOfPlayers)
    {
    case 0:
        PlayerThatIsGuessing = "AI";
        AIDifficulty = Get_AI_Difficulty(NumberOfPlayers, IncorrectGuesses);
        WordToBeGuessed = Get_Word_To_Be_Guessed_From_AI();
        break;

    case 1:
        PlayerThatIsGuessing = Get_User_Player_Choice(NumberOfPlayers, IncorrectGuesses);
        AIDifficulty = Get_AI_Difficulty(NumberOfPlayers, IncorrectGuesses);

        if (PlayerThatIsGuessing == "PLAYER ONE")
        {
            PlayerThatIsGuessing = "HUMAN";
            WordToBeGuessed = Get_Word_To_Be_Guessed_From_AI();
        }
        else
        {
            PlayerThatIsGuessing = "AI";
            WordToBeGuessed = Get_Word_To_Be_Guessed_From_User(IncorrectGuesses, NumberOfPlayers, AIDifficulty, ConsoleHandle);
        }
        break;

    case 2:
        PlayerThatIsGuessing = "HUMAN";
        WordToBeGuessed = Get_Word_To_Be_Guessed_From_User(IncorrectGuesses, NumberOfPlayers, AIDifficulty, ConsoleHandle);
        AIDifficulty = "N/A";
        break;
    }

    for (unsigned int i = 0; i < WordToBeGuessed.size(); i++)
        CurrentGuessOfWord.push_back('_');

    ValidMovesRemaining = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};
}

unsigned int Get_Number_Of_Players(const std::vector<std::string> &IncorrectGuesses)
{
    unsigned int CurrentSelection = 0;
    unsigned char KeyPress = 0;

    std::string CommonString = Hangman_Game_Display(0, "N/A", "N/A", IncorrectGuesses, "", "", false);
    CommonString += Hangman_New_Line(" Please select the number of human players:                   ");

    std::string CaseZero = CommonString;
    CaseZero += Hangman_New_Line(BLUE + " > 0                                                          " + WHITE);
    CaseZero += Hangman_New_Line("   1                                                          ");
    CaseZero += Hangman_New_Line("   2                                                          ");
    CaseZero += Hangman_Empty_Line();
    CaseZero += Hangman_Bottom_Line();
    CaseZero += Hangman_Bottom_Bar();

    std::string CaseOne = CommonString;
    CaseOne += Hangman_New_Line("   0                                                          ");
    CaseOne += Hangman_New_Line(BLUE + " > 1                                                          " + WHITE);
    CaseOne += Hangman_New_Line("   2                                                          ");
    CaseOne += Hangman_Empty_Line();
    CaseOne += Hangman_Bottom_Line();
    CaseOne += Hangman_Bottom_Bar();

    std::string CaseTwo = CommonString;
    CaseTwo += Hangman_New_Line("   0                                                          ");
    CaseTwo += Hangman_New_Line("   1                                                          ");
    CaseTwo += Hangman_New_Line(BLUE + " > 2                                                          " + WHITE);
    CaseTwo += Hangman_Empty_Line();
    CaseTwo += Hangman_Bottom_Line();
    CaseTwo += Hangman_Bottom_Bar();

    while (KeyPress != '\r')
    {
        switch (KeyPress)
        {
        case 72: // up arrow key
            if (CurrentSelection == 0)
                CurrentSelection = 2;
            else
                CurrentSelection--;
            break;

        case 80: // down arrow key
            if (CurrentSelection == 2)
                CurrentSelection = 0;
            else
                CurrentSelection++;
            break;

        default:
            break;
        }

        Clear_Terminal();

        switch (CurrentSelection)
        {
        case 0:
            std::cout << CaseZero;
            break;

        case 1:
            std::cout << CaseOne;
            break;

        case 2:
            std::cout << CaseTwo;
            break;
        }

        KeyPress = _getch();
    }

    return CurrentSelection;
}

std::string Get_User_Player_Choice(const unsigned int &NumberOfPlayers,
                                   const std::vector<std::string> &IncorrectGuesses)
{
    unsigned int CurrentSelection = 0;
    unsigned char KeyPress = 0;

    std::string CommonString = Hangman_Game_Display(0, std::to_string(NumberOfPlayers), "N/A", IncorrectGuesses, "", "", false);
    CommonString += Hangman_New_Line(" Please select what player you would like to be:              ");

    std::string CaseZero = CommonString;
    CaseZero += Hangman_New_Line(BLUE + " > GUESSER                                                    " + WHITE);
    CaseZero += Hangman_New_Line("   WORD SETTER                                                ");
    CaseZero += Hangman_Empty_Line();
    CaseZero += Hangman_Empty_Line();
    CaseZero += Hangman_Bottom_Line();
    CaseZero += Hangman_Bottom_Bar();

    std::string CaseOne = CommonString;
    CaseOne += Hangman_New_Line("   GUESSER                                                    ");
    CaseOne += Hangman_New_Line(BLUE + " > WORD SETTER                                                " + WHITE);
    CaseOne += Hangman_Empty_Line();
    CaseOne += Hangman_Empty_Line();
    CaseOne += Hangman_Bottom_Line();
    CaseOne += Hangman_Bottom_Bar();

    while (KeyPress != '\r')
    {
        switch (KeyPress)
        {
        case 72: // up arrow key
            if (CurrentSelection == 0)
                CurrentSelection = 1;
            else
                CurrentSelection--;
            break;

        case 80: // down arrow key
            if (CurrentSelection == 1)
                CurrentSelection = 0;
            else
                CurrentSelection++;
            break;

        default:
            break;
        }

        Clear_Terminal();

        switch (CurrentSelection)
        {
        case 0:
            std::cout << CaseZero;
            break;

        case 1:
            std::cout << CaseOne;
            break;
        }

        KeyPress = _getch();
    }

    return CurrentSelection == 0 ? "PLAYER ONE" : "PLAYER TWO";
}

std::string Get_AI_Difficulty(const unsigned int &NumberOfPlayers,
                              const std::vector<std::string> &IncorrectGuesses)
{
    unsigned int CurrentSelection = 0;
    unsigned char KeyPress = 0;

    std::string CommonString = Hangman_Game_Display(0, std::to_string(NumberOfPlayers), "N/A", IncorrectGuesses, "", "", false);
    CommonString += Hangman_New_Line(" Please select the AI difficulty:                             ");

    std::string CaseZero = CommonString;
    CaseZero += Hangman_New_Line(BLUE + " > EASY                                                       " + WHITE);
    CaseZero += Hangman_New_Line("   HARD (Coming Soon!)                                        ");
    CaseZero += Hangman_Empty_Line();
    CaseZero += Hangman_Empty_Line();
    CaseZero += Hangman_Bottom_Line();
    CaseZero += Hangman_Bottom_Bar();

    std::string CaseTwo = CommonString;
    CaseTwo += Hangman_New_Line("   EASY                                                       ");
    CaseTwo += Hangman_New_Line(BLUE + " > HARD (Coming Soon!)                                        " + WHITE);
    CaseTwo += Hangman_Empty_Line();
    CaseTwo += Hangman_Empty_Line();
    CaseTwo += Hangman_Bottom_Line();
    CaseTwo += Hangman_Bottom_Bar();

    while (!(KeyPress == '\r' && CurrentSelection == 0))
    {
        switch (KeyPress)
        {
        case 72: // up arrow key
            if (CurrentSelection == 0)
                CurrentSelection = 1;
            else
                CurrentSelection--;
            break;

        case 80: // down arrow key
            if (CurrentSelection == 1)
                CurrentSelection = 0;
            else
                CurrentSelection++;
            break;

        default:
            break;
        }

        Clear_Terminal();

        switch (CurrentSelection)
        {
        case 0:
            std::cout << CaseZero;
            break;

        case 1:
            std::cout << CaseTwo;
            break;
        }

        KeyPress = _getch();
    }

    return CurrentSelection == 0 ? "EASY" : "HARD";
}

std::string Get_Word_To_Be_Guessed_From_User(const std::vector<std::string> &IncorrectGuesses,
                                             const unsigned int &NumberOfPlayers,
                                             const std::string &AIDifficulty,
                                             const HANDLE &ConsoleHandle)
{
    bool InputInvalid = true;
    std::string Input;

    std::string Output = Hangman_Game_Display(0, std::to_string(NumberOfPlayers), AIDifficulty, IncorrectGuesses, "", "", false);
    Output += Hangman_New_Line(" Please enter the word to be guessed:                         ");
    Output += Hangman_Empty_Line();
    Output += Hangman_Empty_Line();
    Output += Hangman_Empty_Line();
    Output += Hangman_Empty_Line();
    Output += Hangman_Bottom_Line();
    Output += Hangman_Bottom_Bar();

    while (InputInvalid)
    {
        InputInvalid = false;

        Clear_Terminal();

        std::cout << Output;

        SetConsoleCursorPosition(ConsoleHandle, {39, 13});

        std::getline(std::cin, Input);

        if (Input.size() < 3 || Input.size() > 14)
        {
            InputInvalid = true;
            continue;
        }

        Capitalise_Word(Input);

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

std::string Get_Word_To_Be_Guessed_From_AI(void)
{
    std::vector<std::string> Words = Generate_Word_List();
    return Words[std::rand() % Words.size()];
}

std::string Hangman_Game_Display(const unsigned int &NumberOfErrors,
                                 const std::string &NumberOfPlayers,
                                 const std::string &AIDifficulty,
                                 const std::vector<std::string> &IncorrectGuesses,
                                 const std::string &CurrentGuessOfWord,
                                 const std::string &WordToBeGuessed,
                                 const bool &GameOver)
{
    Clear_Terminal();

    std::string Output;

    // Top bar
    Output.insert(Output.size(), WHITE);
    Output.insert(Output.size(), 1, (char)201);
    Output.insert(Output.size(), 62, (char)205);
    Output.insert(Output.size(), 1, (char)187);
    Output.insert(Output.size(), Hangman_New_Line(RED + "                        Terminal-Games                        " + WHITE));
    Output.insert(Output.size(), Hangman_Bottom_Line());

    // Centre information
    Output.insert(Output.size(), Hangman_Top_Line());

    // Line 1
    switch (NumberOfErrors)
    {
    case 0:
    case 1:
    case 2:
        Output.insert(Output.size(), Hangman_Empty_Line());
        break;

    case 3:
        Output.insert(Output.size(), "\n");
        Output.insert(Output.size(), 1, (char)186);
        Output.insert(Output.size(), "     ");
        Output.insert(Output.size(), 1, (char)218);
        Output.insert(Output.size(), 8, (char)196);
        Output.insert(Output.size(), "                                                ");
        Output.insert(Output.size(), 1, (char)186);
        break;

    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
        Output.insert(Output.size(), "\n");
        Output.insert(Output.size(), 1, (char)186);
        Output.insert(Output.size(), "     ");
        Output.insert(Output.size(), 1, (char)218);
        Output.insert(Output.size(), 7, (char)196);
        Output.insert(Output.size(), 1, (char)191);
        Output.insert(Output.size(), "                                                ");
        Output.insert(Output.size(), 1, (char)186);
        break;
    }

    // Line 2
    switch (NumberOfErrors)
    {
    case 0:
        Output.insert(Output.size(), Hangman_Empty_Line());
        break;

    case 1:
        Output.insert(Output.size(), Hangman_New_Line("                                          Incorrect Guesses   "));
        break;

    case 2:
    case 3:
        Output.insert(Output.size(), "\n");
        Output.insert(Output.size(), 1, (char)186);
        Output.insert(Output.size(), "     ");
        Output.insert(Output.size(), 1, (char)179);
        Output.insert(Output.size(), "                                    Incorrect Guesses   ");
        Output.insert(Output.size(), 1, (char)186);
        break;

    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
        Output.insert(Output.size(), "\n");
        Output.insert(Output.size(), 1, (char)186);
        Output.insert(Output.size(), "     ");
        Output.insert(Output.size(), 1, (char)179);
        Output.insert(Output.size(), "       ");
        Output.insert(Output.size(), 1, (char)179);
        Output.insert(Output.size(), "                            Incorrect Guesses   ");
        Output.insert(Output.size(), 1, (char)186);
        break;
    }

    // Line 3
    switch (NumberOfErrors)
    {
    case 0:
        if (NumberOfPlayers == "N/A")
            Output.insert(Output.size(), Hangman_New_Line("                   # of Players = " + NumberOfPlayers + "                         "));
        else
            Output.insert(Output.size(), Hangman_New_Line("                    # of Players = " + NumberOfPlayers + "                          "));
        break;

    case 1:
        Output.insert(Output.size(), Hangman_New_Line("                    # of Players = " + NumberOfPlayers + "                          "));
        break;

    case 2:
    case 3:
    case 4:
        Output.insert(Output.size(), "\n");
        Output.insert(Output.size(), 1, (char)186);
        Output.insert(Output.size(), "     ");
        Output.insert(Output.size(), 1, (char)179);
        Output.insert(Output.size(), "              # of Players = " + NumberOfPlayers + "                          ");
        Output.insert(Output.size(), 1, (char)186);
        break;

    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
        Output.insert(Output.size(), "\n");
        Output.insert(Output.size(), 1, (char)186);
        Output.insert(Output.size(), "     ");
        Output.insert(Output.size(), 1, (char)179);
        Output.insert(Output.size(), "       O      # of Players = " + NumberOfPlayers + "                          ");
        Output.insert(Output.size(), 1, (char)186);
        break;
    }

    // Line 4
    switch (NumberOfErrors)
    {
    case 0:
        Output.insert(Output.size(), Hangman_Empty_Line());
        break;

    case 1:
        Output.insert(Output.size(), Hangman_New_Line("                                          " + IncorrectGuesses[0] + "                   "));
        break;

    case 2:
        Output.insert(Output.size(), "\n");
        Output.insert(Output.size(), 1, (char)186);
        Output.insert(Output.size(), "     ");
        Output.insert(Output.size(), 1, (char)179);
        Output.insert(Output.size(), "                                    " + IncorrectGuesses[0] + "   " + IncorrectGuesses[1] + "               ");
        Output.insert(Output.size(), 1, (char)186);
        break;

    case 3:
        Output.insert(Output.size(), "\n");
        Output.insert(Output.size(), 1, (char)186);
        Output.insert(Output.size(), "     ");
        Output.insert(Output.size(), 1, (char)179);
        Output.insert(Output.size(), "                                    " + IncorrectGuesses[0] + "   " + IncorrectGuesses[1] + "   " + IncorrectGuesses[2] + "           ");
        Output.insert(Output.size(), 1, (char)186);
        break;

    case 4:
        Output.insert(Output.size(), "\n");
        Output.insert(Output.size(), 1, (char)186);
        Output.insert(Output.size(), "     ");
        Output.insert(Output.size(), 1, (char)179);
        Output.insert(Output.size(), "                                    " + IncorrectGuesses[0] + "   " + IncorrectGuesses[1] + "   " + IncorrectGuesses[2] + "   " + IncorrectGuesses[3] + "       ");
        Output.insert(Output.size(), 1, (char)186);
        break;

    case 5:
        Output.insert(Output.size(), "\n");
        Output.insert(Output.size(), 1, (char)186);
        Output.insert(Output.size(), "     ");
        Output.insert(Output.size(), 1, (char)179);
        Output.insert(Output.size(), "                                    " + IncorrectGuesses[0] + "   " + IncorrectGuesses[1] + "   " + IncorrectGuesses[2] + "   " + IncorrectGuesses[3] + "   " + IncorrectGuesses[4] + "   ");
        Output.insert(Output.size(), 1, (char)186);
        break;

    case 6:
    case 7:
    case 8:
        Output.insert(Output.size(), "\n");
        Output.insert(Output.size(), 1, (char)186);
        Output.insert(Output.size(), "     ");
        Output.insert(Output.size(), 1, (char)179);
        Output.insert(Output.size(), "       ");
        Output.insert(Output.size(), 1, (char)179);
        Output.insert(Output.size(), "                            " + IncorrectGuesses[0] + "   " + IncorrectGuesses[1] + "   " + IncorrectGuesses[2] + "   " + IncorrectGuesses[3] + "   " + IncorrectGuesses[4] + "   ");
        Output.insert(Output.size(), 1, (char)186);
        break;

    case 9:
        Output.insert(Output.size(), "\n");
        Output.insert(Output.size(), 1, (char)186);
        Output.insert(Output.size(), "     ");
        Output.insert(Output.size(), 1, (char)179);
        Output.insert(Output.size(), "      /");
        Output.insert(Output.size(), 1, (char)179);
        Output.insert(Output.size(), "                            " + IncorrectGuesses[0] + "   " + IncorrectGuesses[1] + "   " + IncorrectGuesses[2] + "   " + IncorrectGuesses[3] + "   " + IncorrectGuesses[4] + "   ");
        Output.insert(Output.size(), 1, (char)186);
        break;

    case 10:
        Output.insert(Output.size(), "\n");
        Output.insert(Output.size(), 1, (char)186);
        Output.insert(Output.size(), "     ");
        Output.insert(Output.size(), 1, (char)179);
        Output.insert(Output.size(), "      /");
        Output.insert(Output.size(), 1, (char)179);
        Output.insert(Output.size(), "\\                           " + IncorrectGuesses[0] + "   " + IncorrectGuesses[1] + "   " + IncorrectGuesses[2] + "   " + IncorrectGuesses[3] + "   " + IncorrectGuesses[4] + "   ");
        Output.insert(Output.size(), 1, (char)186);
        break;
    }

    // Line 5
    switch (NumberOfErrors)
    {
    case 0:
    case 1:
        if (AIDifficulty == "N/A")
            Output.insert(Output.size(), Hangman_New_Line("                   AI Difficulty = " + AIDifficulty + "                        "));
        else
            Output.insert(Output.size(), Hangman_New_Line("                  AI Difficulty = " + AIDifficulty + "                        "));
        break;

    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
        Output.insert(Output.size(), "\n");
        Output.insert(Output.size(), 1, (char)186);
        Output.insert(Output.size(), "     ");
        Output.insert(Output.size(), 1, (char)179);
        if (AIDifficulty == "N/A")
            Output.insert(Output.size(), "             AI Difficulty = " + AIDifficulty + "                        ");
        else
            Output.insert(Output.size(), "            AI Difficulty = " + AIDifficulty + "                        ");
        Output.insert(Output.size(), 1, (char)186);
        break;

    case 7:
        Output.insert(Output.size(), "\n");
        Output.insert(Output.size(), 1, (char)186);
        Output.insert(Output.size(), "     ");
        Output.insert(Output.size(), 1, (char)179);
        if (AIDifficulty == "N/A")
            Output.insert(Output.size(), "      /      AI Difficulty = " + AIDifficulty + "                        ");
        else
            Output.insert(Output.size(), "      /     AI Difficulty = " + AIDifficulty + "                        ");
        Output.insert(Output.size(), 1, (char)186);
        break;

    case 8:
    case 9:
    case 10:
        Output.insert(Output.size(), "\n");
        Output.insert(Output.size(), 1, (char)186);
        Output.insert(Output.size(), "     ");
        Output.insert(Output.size(), 1, (char)179);
        if (AIDifficulty == "N/A")
            Output.insert(Output.size(), "      / \\    AI Difficulty = " + AIDifficulty + "                        ");
        else
            Output.insert(Output.size(), "      / \\   AI Difficulty = " + AIDifficulty + "                        ");
        Output.insert(Output.size(), 1, (char)186);
        break;
    }

    // Line 6
    switch (NumberOfErrors)
    {
    case 0:
        Output.insert(Output.size(), Hangman_Empty_Line());
        break;

    case 1:
        Output.insert(Output.size(), Hangman_Empty_Line());
        break;

    case 2:
    case 3:
    case 4:
    case 5:
        Output.insert(Output.size(), "\n");
        Output.insert(Output.size(), 1, (char)186);
        Output.insert(Output.size(), "     ");
        Output.insert(Output.size(), 1, (char)179);
        Output.insert(Output.size(), "                                                        ");
        Output.insert(Output.size(), 1, (char)186);
        break;

    case 6:
        Output.insert(Output.size(), "\n");
        Output.insert(Output.size(), 1, (char)186);
        Output.insert(Output.size(), "     ");
        Output.insert(Output.size(), 1, (char)179);
        Output.insert(Output.size(), "                                    " + IncorrectGuesses[5] + "                   ");
        Output.insert(Output.size(), 1, (char)186);
        break;

    case 7:
        Output.insert(Output.size(), "\n");
        Output.insert(Output.size(), 1, (char)186);
        Output.insert(Output.size(), "     ");
        Output.insert(Output.size(), 1, (char)179);
        Output.insert(Output.size(), "                                    " + IncorrectGuesses[5] + "   " + IncorrectGuesses[6] + "               ");
        Output.insert(Output.size(), 1, (char)186);
        break;

    case 8:
        Output.insert(Output.size(), "\n");
        Output.insert(Output.size(), 1, (char)186);
        Output.insert(Output.size(), "     ");
        Output.insert(Output.size(), 1, (char)179);
        Output.insert(Output.size(), "                                    " + IncorrectGuesses[5] + "   " + IncorrectGuesses[6] + "   " + IncorrectGuesses[7] + "           ");
        Output.insert(Output.size(), 1, (char)186);
        break;

    case 9:
        Output.insert(Output.size(), "\n");
        Output.insert(Output.size(), 1, (char)186);
        Output.insert(Output.size(), "     ");
        Output.insert(Output.size(), 1, (char)179);
        Output.insert(Output.size(), "                                    " + IncorrectGuesses[5] + "   " + IncorrectGuesses[6] + "   " + IncorrectGuesses[7] + "   " + IncorrectGuesses[8] + "       ");
        Output.insert(Output.size(), 1, (char)186);
        break;

    case 10:
        Output.insert(Output.size(), "\n");
        Output.insert(Output.size(), 1, (char)186);
        Output.insert(Output.size(), "     ");
        Output.insert(Output.size(), 1, (char)179);
        Output.insert(Output.size(), "                                    " + IncorrectGuesses[5] + "   " + IncorrectGuesses[6] + "   " + IncorrectGuesses[7] + "   " + IncorrectGuesses[8] + "   " + IncorrectGuesses[9] + "   ");
        Output.insert(Output.size(), 1, (char)186);
        break;
    }

    // Line 7
    switch (NumberOfErrors)
    {
    case 0:

        Output.insert(Output.size(), Hangman_Empty_Line());
        break;

    case 1:
        Output.insert(Output.size(), "\n");
        Output.insert(Output.size(), 1, (char)186);
        Output.insert(Output.size(), " ");
        Output.insert(Output.size(), 9, (char)196);
        Output.insert(Output.size(), "                                                    ");
        Output.insert(Output.size(), 1, (char)186);
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
        Output.insert(Output.size(), "\n");
        Output.insert(Output.size(), 1, (char)186);
        Output.insert(Output.size(), " ");
        Output.insert(Output.size(), 4, (char)196);
        Output.insert(Output.size(), 1, (char)193);
        Output.insert(Output.size(), 4, (char)196);
        Output.insert(Output.size(), "                                                    ");
        Output.insert(Output.size(), 1, (char)186);
        break;
    }

    // Word to be guessed, and thus current guess of word, are limited to a size in between 3 and 14
    Output.insert(Output.size(), "\n");
    Output.insert(Output.size(), 1, (char)186);

    for (unsigned int i = 0; i < CurrentGuessOfWord.size(); i++)
    {
        Output.insert(Output.size(), " ");
        Output.insert(Output.size(), 1, CurrentGuessOfWord[i]);
    }

    if (GameOver && NumberOfErrors == 10)
    {
        Output.insert(Output.size(), "   (The word was " + WordToBeGuessed + ")");
        Output.insert(Output.size(), (62 - WordToBeGuessed.size() * 3 - 18), ' ');
    }
    else
        Output.insert(Output.size(), (62 - WordToBeGuessed.size() * 2), ' ');

    Output.insert(Output.size(), 1, (char)186);

    Output.insert(Output.size(), Hangman_Empty_Line());

    return Output;
}

std::string Hangman_Empty_Line(void)
{
    std::string Output;
    Output.insert(Output.size(), "\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.insert(Output.size(), 62, ' ');
    Output.insert(Output.size(), 1, (char)186);

    return Output;
}

std::string Hangman_New_Line(const std::string &Input)
{
    std::string Output;
    Output.insert(Output.size(), "\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.insert(Output.size(), Input);
    Output.insert(Output.size(), 1, (char)186);

    return Output;
}

std::string Hangman_Top_Line(void)
{
    std::string Output;
    Output.insert(Output.size(), "\n");
    Output.insert(Output.size(), 1, (char)201);
    Output.insert(Output.size(), 62, (char)205);
    Output.insert(Output.size(), 1, (char)187);

    return Output;
}

std::string Hangman_Bottom_Line(void)
{
    std::string Output;
    Output.insert(Output.size(), "\n");
    Output.insert(Output.size(), 1, (char)200);
    Output.insert(Output.size(), 62, (char)205);
    Output.insert(Output.size(), 1, (char)188);

    return Output;
}

std::string Hangman_Bottom_Bar(void)
{
    std::string Output;
    Output += Hangman_Top_Line();
    Output += Hangman_New_Line(RED + "                           Hangman                            " + WHITE);
    Output += Hangman_Bottom_Line();

    return Output;
}

bool Winning_Conditions_Met(const unsigned int &NumberOfErrors,
                            const std::string &WordToBeGuessed,
                            const std::string &CurrentGuessOfWord)
{
    if (NumberOfErrors == 10)
        return true;

    else
    {
        for (unsigned int i = 0; i < WordToBeGuessed.size(); i++)
            if (WordToBeGuessed[i] != CurrentGuessOfWord[i])
                return false;

        return true;
    }
}

void Get_Next_User_Guess(unsigned int &NumberOfErrors,
                         const unsigned int &NumberOfPlayers,
                         const std::string &AIDifficulty,
                         std::vector<std::string> &IncorrectGuesses,
                         std::vector<std::string> &CorrectGuesses,
                         std::vector<std::string> &ValidMovesRemaining,
                         std::string &CurrentGuessOfWord,
                         const std::string &WordToBeGuessed,
                         const HANDLE &ConsoleHandle)
{
    std::string UserGuess;
    unsigned int CurrentSelection = 0;
    unsigned char KeyPress = 0;

    std::string Output = Hangman_Game_Display(NumberOfErrors, std::to_string(NumberOfPlayers), AIDifficulty, IncorrectGuesses, CurrentGuessOfWord, WordToBeGuessed, false);
    Output += Hangman_New_Line(" Guesser, please enter your next guess:                       ");
    Output += Hangman_Empty_Line();
    Output += Hangman_Empty_Line();
    Output += Hangman_Empty_Line();
    Output += Hangman_Empty_Line();
    Output += Hangman_Bottom_Line();
    Output += Hangman_Bottom_Bar();

    while (KeyPress != '\r')
    {
        switch (KeyPress)
        {
        case 72: // up arrow key
            if (CurrentSelection == 0)
                CurrentSelection = ValidMovesRemaining.size() - 1;
            else
                CurrentSelection--;

            break;

        case 80: // down arrow key
            if (CurrentSelection == ValidMovesRemaining.size() - 1)
                CurrentSelection = 0;
            else
                CurrentSelection++;
            break;

        default:
            break;
        }

        Clear_Terminal();

        std::cout << Output;

        SetConsoleCursorPosition(ConsoleHandle, {41, 13});

        std::cout << BLUE + ValidMovesRemaining[CurrentSelection] + WHITE;

        KeyPress = _getch();
    }

    UserGuess = ValidMovesRemaining[CurrentSelection];
    auto CommandPosition = std::find(ValidMovesRemaining.begin(), ValidMovesRemaining.end(), UserGuess);
    ValidMovesRemaining.erase(CommandPosition);

    if (!Check_Guess_Against_Word_To_Be_Guessed(WordToBeGuessed, UserGuess[0], CurrentGuessOfWord))
    {
        IncorrectGuesses.push_back(UserGuess);
        NumberOfErrors++;
    }
    else
        CorrectGuesses.push_back(UserGuess);
}

void Get_Next_AI_Guess(unsigned int &NumberOfErrors,
                       const unsigned int &NumberOfPlayers,
                       const std::string &AIDifficulty,
                       std::vector<std::string> &IncorrectGuesses,
                       std::vector<std::string> &CorrectGuesses,
                       std::vector<std::string> &ValidMovesRemaining,
                       std::string &CurrentGuessOfWord,
                       const std::string &WordToBeGuessed)
{
    std::string Guess = ValidMovesRemaining[std::rand() % ValidMovesRemaining.size()];
    auto CommandPosition = std::find(ValidMovesRemaining.begin(), ValidMovesRemaining.end(), Guess);
    ValidMovesRemaining.erase(CommandPosition);

    if (!Check_Guess_Against_Word_To_Be_Guessed(WordToBeGuessed, Guess[0], CurrentGuessOfWord))
    {
        IncorrectGuesses.push_back(Guess);
        NumberOfErrors++;
    }
    else
        CorrectGuesses.push_back(Guess);
}

bool Check_Guess_Against_Word_To_Be_Guessed(const std::string &WordToBeGuessed,
                                            const unsigned char &Guess,
                                            std::string &CurrentGuessOfWord)
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

void Display_Game_Over_Message(const unsigned int &NumberOfErrors,
                               const unsigned int &NumberOfPlayers,
                               const std::string &AIDifficulty,
                               const std::vector<std::string> &IncorrectGuesses,
                               const std::string &CurrentGuessOfWord,
                               const std::string &WordToBeGuessed,
                               const unsigned int &NumberOfTurns,
                               bool &GameIsRunning)
{
    std::string Output = Hangman_Game_Display(NumberOfErrors, std::to_string(NumberOfPlayers), AIDifficulty, IncorrectGuesses, CurrentGuessOfWord, WordToBeGuessed, true);
    Output += Hangman_New_Line("                          GAME OVER                           ");
    Output += Hangman_Empty_Line();

    if (NumberOfErrors == 10)
        Output += Hangman_New_Line("      The word setter has won! The game lasted " + std::to_string(NumberOfTurns) + " turns!      ");
    else
    {
        if (NumberOfTurns < 10)
            Output += Hangman_New_Line("        The guesser has won! The game lasted " + std::to_string(NumberOfTurns) + " turns.         ");
        else
            Output += Hangman_New_Line("        The guesser has won! The game lasted " + std::to_string(NumberOfTurns) + " turns.        ");
    }

    Output += Hangman_Empty_Line();
    Output += Hangman_New_Line("     Press 'Q' to quit OR any other key to play again...      ");
    Output += Hangman_Bottom_Line();
    Output += Hangman_Bottom_Bar();

    std::cout << Output;

    if (_getch() == 'q')
    {
        GameIsRunning = false;
        Clear_Terminal();
    }
}