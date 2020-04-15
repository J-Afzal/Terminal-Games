//
// The file contains the implementation of the Hangman game
//

#include "Hangman.hpp"
#include <ctime>
#include <fstream>
#include <string>



void Play_Hangman(void)
{
    //Variables for the Hangman game
    // - Hangman states representing the different states the hangman drawing can be in
    std::vector<std::string> IncorrectGuesses, CorrectGuesses;
    std::string WordToBeGuessed, CurrentGuessOfWord, PlayerThatIsGuessing;
    unsigned int NumberOfPlayers, NumberOfErrors = 0, NumberOfTurns = 0;

    // Sets up the variables required by game
    Setup_Game(WordToBeGuessed, CurrentGuessOfWord, NumberOfPlayers, PlayerThatIsGuessing);

    // while the current guess of word and word to be guessed are not the same and the hangman drawing
    // has not reached its final stage continue playing game
    while (!Game_Over(NumberOfErrors) && !Winning_Conditions_Met(WordToBeGuessed, CurrentGuessOfWord))
    {
        // Displays the current hangman state, the current guess of word and all incorrect guesses
        Display_Game(NumberOfErrors, CurrentGuessOfWord, IncorrectGuesses);

        std::string Guess;

        // Prompt the human or computer user for a guess depending upon how many human players there are
        if (PlayerThatIsGuessing == "HUMAN")
            Guess = Ask_User_For_Next_Guess(IncorrectGuesses, CorrectGuesses);

        else
            Guess = Ask_Computer_For_Next_Guess(IncorrectGuesses, CorrectGuesses);

        // If the guess is incorrect then add to incorrect list and increment errors
        if (!Check_Guess_Against_Word(Guess, WordToBeGuessed, CurrentGuessOfWord))
        {
            IncorrectGuesses.push_back(Guess);
            NumberOfErrors++;
        }

        // Else add guess to correct list
        else
            CorrectGuesses.push_back(Guess);

        // Increment
        NumberOfTurns++;
    }

    // Displays the winning or losing message
    Display_Game_Over_Message(NumberOfErrors, CurrentGuessOfWord, IncorrectGuesses, NumberOfTurns, WordToBeGuessed);
}



void Test_Hangman(void)
{
    //Variables for the Hangman game
    // - Hangman states representing the different states the hangman drawing can be in
    std::vector<std::string> IncorrectGuesses, CorrectGuesses;
    std::string WordToBeGuessed, CurrentGuessOfWord, PlayerThatIsGuessing;
    unsigned int NumberOfPlayers = 0, NumberOfErrors = 0, NumberOfTurns = 0;

    // Set seed of srand to time(0) so pseudo random
    std::srand((unsigned int)std::time(0));

    // Prompt the computer for the word to be guessed
    WordToBeGuessed = Ask_Computer_For_Word_To_Be_Guessed();

    // All players are computers so no need to ask
    PlayerThatIsGuessing = "COMPUTER";

    // Create the current guess to be the same size as the word to be guessed but only containing underscores
    for (unsigned int i = 0; i < WordToBeGuessed.size(); i++)
        CurrentGuessOfWord.push_back('_');

    // while the current guess of word and word to be guessed are not the same and the hangman drawing
    // has not reached its final stage continue playing game
    while (!Game_Over(NumberOfErrors) && !Winning_Conditions_Met(WordToBeGuessed, CurrentGuessOfWord))
    {
        std::string Guess;

        // Prompt the computer user for a guess
        Guess = Ask_Computer_For_Next_Guess(IncorrectGuesses, CorrectGuesses);

        // If the guess is incorrect then add to incorrect list and increment errors
        if (!Check_Guess_Against_Word(Guess, WordToBeGuessed, CurrentGuessOfWord))
        {
            IncorrectGuesses.push_back(Guess);
            NumberOfErrors++;
        }

        // Else add guess to correct list
        else
            CorrectGuesses.push_back(Guess);

        // Increment
        NumberOfTurns++;
    }
}



void Setup_Game(std::string& WordToBeGuessed,
                std::string& CurrentGuessOfWord,
                unsigned int& NumberOfPlayers,
                std::string& PlayerThatIsGuessing)
{
    std::cout << "--------------------Hangman--------------------" << '\n';

    // Prompt the user for the number of players if one the computer will guess and if two then human user will guess
    NumberOfPlayers = Ask_User_For_Number_Of_Players();

    if (NumberOfPlayers == 2)
    {
        // Prompt the user for the word to be guessed
        WordToBeGuessed = Ask_User_For_Word_To_Be_Guessed();

        // All players are humans so no need to ask
        PlayerThatIsGuessing = "HUMAN";
    }

    else if (NumberOfPlayers == 1)
    {
        // Set seed of srand to time(0) so pseudo random
        std::srand((unsigned int)std::time(0));

        // Prompts the user for who is guessing the word (human or computer)
        PlayerThatIsGuessing = Ask_User_For_Who_Is_Guessing();

        if (PlayerThatIsGuessing == "HUMAN")
            // Prompt the computer for the word to be guessed
            WordToBeGuessed = Ask_Computer_For_Word_To_Be_Guessed();

        else
            WordToBeGuessed = Ask_User_For_Word_To_Be_Guessed();
    }

    else if (NumberOfPlayers == 0)
    {
        // Set seed of srand to time(0) so pseudo random
        std::srand((unsigned int)std::time(0));

        // Prompt the computer for the word to be guessed
        WordToBeGuessed = Ask_Computer_For_Word_To_Be_Guessed();

        // All players are computers so no need to ask
        PlayerThatIsGuessing = "COMPUTER";
    }

    // Create the current guess to be the same size as the word to be guessed but only containing underscores
    for (unsigned int i = 0; i < WordToBeGuessed.size(); i++)
        CurrentGuessOfWord.push_back('_');
}



unsigned int Ask_User_For_Number_Of_Players(void)
{
    bool IsValueCorrect = false; // Flag for if input value is valid
    unsigned int NumberOfPlayers = 0;

    while(!IsValueCorrect)
    {
        std::cout << "Enter the number of players: ";

        std::cin >> NumberOfPlayers;

        if (std::cin.fail()) // Check if cin failed
        {
            // Clear buffer and retry
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        // Only 0 1 and 2 amount of players allowed
        else if (NumberOfPlayers != 0 && NumberOfPlayers != 1 && NumberOfPlayers != 2)
        {
            // Clear buffer and retry
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        else
            IsValueCorrect = true;
    }

    return NumberOfPlayers;
}



std::string Ask_User_For_Word_To_Be_Guessed(void) //spaces or -
{
    bool IsValueCorrect = false; // Flag for if input value is valid
    std::string WordToBeGuessed;

    while(!IsValueCorrect)
    {
        // Set flag to true by default as difficult to continue to to next iteration of while loop
        // within a nested if statements within nested for loops
        IsValueCorrect = true;

        std::cout << "Enter the word to be guessed: ";

        std::cin >> WordToBeGuessed;

        if (std::cin.fail()) // Check if cin failed
        {
            // Clear buffer and retry
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            IsValueCorrect = false;
            continue;
        }

        // Only accept chars that are either captial or lowercase letters
        for (unsigned int i = 0; i < WordToBeGuessed.size(); i++)
        {
            if(WordToBeGuessed[i] < 'A')
            {
                // Clear buffer and retry
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                IsValueCorrect = false;
                break;
            }

            else if(WordToBeGuessed[i] > 'z')
            {
                // Clear buffer and retry
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                IsValueCorrect = false;
                break;
            }

            // Check for [ \ ] ^ _ ` as they occur inbetween the uppercase and lowercase letters blocks
            else if(WordToBeGuessed[i] >= 91 && WordToBeGuessed[i] <= 96)
            {
                // Clear buffer and retry
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                IsValueCorrect = false;
                break;
            }
        }
    }

    // Capitalise all letters so that only capital letter need to be dealt with
    Capitalise_Word(WordToBeGuessed);

    return WordToBeGuessed;
}



void Capitalise_Word(std::string& aWord)
{
    // Takes a string and replaces every lowercase occurrence of a letter
    // and replaces it with its corresponding uppercase letter
    for (unsigned int i = 0; i < aWord.size(); i++)
    {
        switch (aWord[i]) {
            case 'a':
                aWord[i] = 'A';
                break;

            case 'b':
                aWord[i] = 'B';
                break;

            case 'c':
                aWord[i] = 'C';
                break;

            case 'd':
                aWord[i] = 'D';
                break;

            case 'e':
                aWord[i] = 'E';
                break;

            case 'f':
                aWord[i] = 'F';
                break;

            case 'g':
                aWord[i] = 'G';
                break;

            case 'h':
                aWord[i] = 'H';
                break;

            case 'i':
                aWord[i] = 'I';
                break;

            case 'j':
                aWord[i] = 'J';
                break;

            case 'k':
                aWord[i] = 'K';
                break;

            case 'l':
                aWord[i] = 'L';
                break;

            case 'm':
                aWord[i] = 'M';
                break;

            case 'n':
                aWord[i] = 'N';
                break;

            case 'o':
                aWord[i] = 'O';
                break;

            case 'p':
                aWord[i] = 'P';
                break;

            case 'q':
                aWord[i] = 'Q';
                break;

            case 'r':
                aWord[i] = 'R';
                break;

            case 's':
                aWord[i] = 'S';
                break;

            case 't':
                aWord[i] = 'T';
                break;

            case 'u':
                aWord[i] = 'U';
                break;

            case 'v':
                aWord[i] = 'V';
                break;

            case 'w':
                aWord[i] = 'W';
                break;

            case 'x':
                aWord[i] = 'X';
                break;

            case 'y':
                aWord[i] = 'Y';
                break;

            case 'z':
                aWord[i] = 'Z';
                break;

            default:
                break;
        }
    }
}



std::string Ask_User_For_Who_Is_Guessing(void)
{
    bool IsValueCorrect = false; // Flag for if input value is valid
    std::string PlayerThatWillBeGuessing;

    while(!IsValueCorrect)
    {
        // Set flag to true by default as difficult to continue to to next iteration of while loop
        // within a nested if statements within nested for loops
        IsValueCorrect = true;

        std::cout << "Enter player that will be guessing (HUMAN or COMPUTER): ";

        std::cin >> PlayerThatWillBeGuessing;

        if (std::cin.fail()) // Check if cin failed
        {
            // Clear buffer and retry
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            IsValueCorrect = false;
            continue;
        }

        // Only accept chars that are either captial or lowercase letters
        for (unsigned int i = 0; i < PlayerThatWillBeGuessing.size(); i++)
        {
            if(PlayerThatWillBeGuessing[i] < 'A')
            {
                // Clear buffer and retry
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                IsValueCorrect = false;
                break;
            }

            else if(PlayerThatWillBeGuessing[i] > 'z')
            {
                // Clear buffer and retry
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                IsValueCorrect = false;
                break;
            }

            // Check for [ \ ] ^ _ ` as they occur inbetween the uppercase and lowercase letters blocks
            else if(PlayerThatWillBeGuessing[i] >= 91 && PlayerThatWillBeGuessing[i] <= 96)
            {
                // Clear buffer and retry
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                IsValueCorrect = false;
                break;
            }
        }

        // Capitalise all letters so that only capital letter need to be dealt with
        Capitalise_Word(PlayerThatWillBeGuessing);

        if (PlayerThatWillBeGuessing != "HUMAN" && PlayerThatWillBeGuessing != "COMPUTER")
        {
            IsValueCorrect = false;
            continue;
        }
    }

    return PlayerThatWillBeGuessing;
}



std::string Ask_Computer_For_Word_To_Be_Guessed(void)
{
    bool IsValueCorrect = false; // Flag for if input value is valid
    std::string WordToBeGuessed;

    while(!IsValueCorrect)
    {
        // Set flag to true by default as difficult to continue to to next iteration of while loop
        // within a nested if statements within nested for loops
        IsValueCorrect = true;

        std::ifstream WordList("Words.txt");

        if (WordList.is_open())
        {
            unsigned long int LineNumber = (std::rand() % 65189) + 1;
            unsigned long int CurrentLineNumber = 0;

            while (CurrentLineNumber != LineNumber)
            {
                getline(WordList, WordToBeGuessed);
                CurrentLineNumber++;
            }

            // Only accept chars that are either captial or lowercase letters
            for (unsigned int i = 0; i < WordToBeGuessed.size(); i++)
            {
                if(WordToBeGuessed[i] < 'A')
                {
                    // Clear buffer and retry
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    IsValueCorrect = false;
                    break;
                }

                else if(WordToBeGuessed[i] > 'z')
                {
                    // Clear buffer and retry
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    IsValueCorrect = false;
                    break;
                }

                // Check for [ \ ] ^ _ ` as they occur inbetween the uppercase and lowercase letters blocks
                else if(WordToBeGuessed[i] >= 91 && WordToBeGuessed[i] <= 96)
                {
                    // Clear buffer and retry
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    IsValueCorrect = false;
                    break;
                }
            }
        }

        else
        {
            std::cout << "Unable to open Words.txt, make sure it is in the same directory as the .exe" << '\n';
            exit(1);
        }
    }

    // Capitalise all letters so that only capital letter need to be dealt with
    Capitalise_Word(WordToBeGuessed);

    return WordToBeGuessed;
}



bool Game_Over(const unsigned int& NumberOfErrors)
{
    // 10 or more errors mean that the final state of the
    // hangman drawing has been reached
    if(NumberOfErrors >= 10)
        return true;

    else
        return false;
}



bool Winning_Conditions_Met(const std::string& WordToBeGuessed,
                            const std::string& CurrentGuessOfWord)
{
    // If there is any difference then winning condition not met
    for (unsigned int i = 0; i < WordToBeGuessed.size(); i++)
        if (WordToBeGuessed[i] != CurrentGuessOfWord[i])
            return false;

    return true;
}



void Display_Game(const unsigned int& NumberOfErrors,
                  const std::string& CurrentGuessOfWord,
                  const std::vector<std::string>& IncorrectGuesses)
{
    // ***Better alternative needed***
    // Clears terminal window
    system("cls");

    std::cout << "--------------------Hangman--------------------\n\n";

    // Draw the hangman drawing
    switch (NumberOfErrors)
    {
    case 0:
        std::cout << "\n\n\n\n\n\n \n\n";
        break;

    case 1:
        std::cout << "\n\n\n\n\n\n" << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << "\n\n";
        break;

    case 2:
        std::cout << "\n    " << (char)179 << "\n    " << (char)179 << "\n    " << (char)179 << "\n    " << (char)179 << "\n    " << (char)179 << '\n' << (char)196 << (char)196 << (char)196 << (char)196 << (char)193 << (char)196 << (char)196 << (char)196 << (char)196 << "\n\n";
        break;

    case 3:
        std::cout << "    " << (char)218 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << "\n    " << (char)179 << "\n    " << (char)179 << "\n    " << (char)179 << "\n    " << (char)179 << "\n    " << (char)179 << '\n' << (char)196 << (char)196 << (char)196 << (char)196 << (char)193 << (char)196 << (char)196 << (char)196 << (char)196 << "\n\n";
        break;

    case 4:
        std::cout << "    " << (char)218 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)191 << "\n    " << (char)179 << "       " << (char)179 << "\n    " << (char)179 << "\n    " << (char)179 << "\n    " << (char)179 << "\n    " << (char)179 << '\n' << (char)196 << (char)196 << (char)196 << (char)196 << (char)193 << (char)196 << (char)196 << (char)196 << (char)196 << "\n\n";
        break;

    case 5:
        std::cout << "    " << (char)218 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)191 << "\n    " << (char)179 << "       " << (char)179 << "\n    " << (char)179 << "       O\n    " << (char)179 << "\n    " << (char)179 << "\n    " << (char)179 << '\n' << (char)196 << (char)196 << (char)196 << (char)196 << (char)193 << (char)196 << (char)196 << (char)196 << (char)196 << "\n\n";
        break;

    case 6:
        std::cout << "    " << (char)218 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)191 << "\n    " << (char)179 << "       " << (char)179 << "\n    " << (char)179 << "       O\n    " << (char)179 << "       |\n    " << (char)179 << "\n    " << (char)179 << '\n' << (char)196 << (char)196 << (char)196 << (char)196 << (char)193 << (char)196 << (char)196 << (char)196 << (char)196 << "\n\n";
        break;

    case 7:
        std::cout << "    " << (char)218 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)191 << "\n    " << (char)179 << "       " << (char)179 << "\n    " << (char)179 << "       O\n    " << (char)179 << "       |\n    " << (char)179 << "      /\n    " << (char)179 << '\n' << (char)196 << (char)196 << (char)196 << (char)196 << (char)193 << (char)196 << (char)196 << (char)196 << (char)196 << "\n\n";
        break;

    case 8:
        std::cout << "    " << (char)218 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)191 << "\n    " << (char)179 << "       " << (char)179 << "\n    " << (char)179 << "       O\n    " << (char)179 << "       |\n    " << (char)179 << "      / \\\n    " << (char)179 << '\n' << (char)196 << (char)196 << (char)196 << (char)196 << (char)193 << (char)196 << (char)196 << (char)196 << (char)196 << "\n\n";
        break;

    case 9:
        std::cout << "    " << (char)218 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)191 << "\n    " << (char)179 << "       " << (char)179 << "\n    " << (char)179 << "       O\n    " << (char)179 << "      /|\n    " << (char)179 << "      / \\\n    " << (char)179 << '\n' << (char)196 << (char)196 << (char)196 << (char)196 << (char)193 << (char)196 << (char)196 << (char)196 << (char)196 << "\n\n";
        break;

    case 10:
        std::cout << "    " << (char)218 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)191 << "\n    " << (char)179 << "       " << (char)179 << "\n    " << (char)179 << "       O\n    " << (char)179 << "      /|\\\n    " << (char)179 << "      / \\\n    " << (char)179 << '\n' << (char)196 << (char)196 << (char)196 << (char)196 << (char)193 << (char)196 << (char)196 << (char)196 << (char)196 << "\n\n";
        break;

    default:
        std::cout << "Error in Display_Game() switch statment" << '\n';
        break;
    }

    // Current guess of word
    for (unsigned int i = 0; i < CurrentGuessOfWord.size(); i++)
        std::cout << CurrentGuessOfWord[i] << " ";

    //Incorrect guesses
    std::cout << "\n\nIncorrect Guesses" << '\n';
    for (unsigned int i = 0; i < IncorrectGuesses.size(); i++)
        std::cout << IncorrectGuesses[i] << "   ";

    std::cout << "\n\n";
}



std::string Ask_User_For_Next_Guess(const std::vector<std::string>& IncorrectGuesses,
                                    const std::vector<std::string>& CorrectGuesses)
{
    bool IsValueCorrect = false; // Flag for if input value is valid
    std::string Guess;

    while(!IsValueCorrect)
    {
        // Set flag to true by default as difficult to continue to to next iteration of while loop
        // within a nested if statements within nested for loops
        IsValueCorrect = true;

        std::cout << "Enter your guess: ";

        std::cin >> Guess;

        if (std::cin.fail()) // Check if cin failed
        {
            // Clear buffer and retry
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            IsValueCorrect = false;
            continue;
        }

        // Only accept chars that are either captial or lowercase letters
        for (unsigned int i = 0; i < Guess.size(); i++)
        {
            if(Guess[i] < 'A')
            {
                // Clear buffer and retry
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                IsValueCorrect = false;
                break;
            }

            else if(Guess[i] > 'z')
            {
                // Clear buffer and retry
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                IsValueCorrect = false;
                break;
            }

            // Check for [ \ ] ^ _ ` as they occur inbetween the uppercase and lowercase letters blocks
            else if(Guess[i] >= 91 && Guess[i] <= 96)
            {
                // Clear buffer and retry
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                IsValueCorrect = false;
                break;
            }
        }

        // Capitalise all letters so that only capital letter need to be dealt with
        // and the word to be guessed has already been capitalised
        Capitalise_Word(Guess);

        //Check if this string has already been guessed both correctly or incorrectly
        for (unsigned int i = 0; i < IncorrectGuesses.size(); i++)
            if(Guess == IncorrectGuesses[i])
            {
                IsValueCorrect = false;
                break;
            }

        for (unsigned int i = 0; i < CorrectGuesses.size(); i++)
            if(Guess == CorrectGuesses[i])
            {
                IsValueCorrect = false;
                break;
            }
    }

    return Guess;
}



std::string Ask_Computer_For_Next_Guess(const std::vector<std::string>& IncorrectGuesses,
                                        const std::vector<std::string>& CorrectGuesses)
{
    bool IsValueCorrect = false; // Flag for if input value is valid
    std::string Guess = " ";

    while(!IsValueCorrect)
    {
        // Set flag to true by default as difficult to continue to to next iteration of while loop
        // within a nested if statements within nested for loops
        IsValueCorrect = true;

        // Computer will guess a random letter from A to Z
        Guess[0] = (std::rand() % 26) + 65;

        //Check if this string has already been guessed both correctly or incorrectly
        for (unsigned int i = 0; i < IncorrectGuesses.size(); i++)
            if(Guess == IncorrectGuesses[i])
            {
                IsValueCorrect = false;
                break;
            }

        for (unsigned int i = 0; i < CorrectGuesses.size(); i++)
            if(Guess == CorrectGuesses[i])
            {
                IsValueCorrect = false;
                break;
            }
    }

    // Output a message which is similar to human player guess
    std::cout << "Computer guessed: " << Guess << "\n\n\n\n";

    return Guess;
}



bool Check_Guess_Against_Word(const std::string& Guess,
                              const std::string& WordToBeGuessed,
                              std::string& CurrentGuessOfWord)
{
    bool IsGuessCorrect = false;

    // If below is true then guess is a letter and every occurence of this letter
    // needs to be deposited is the current guess of word
    if (Guess.size() == 1)
    {
        for (unsigned int i = 0; i < WordToBeGuessed.size(); i++) {
            if (WordToBeGuessed[i] == Guess[0])
            {
                IsGuessCorrect = true;
                CurrentGuessOfWord[i] = Guess[0];
            }
        }
    }

    // If not then guess is a word and a simple check to see if they are the
    // same and if so return true and overwrite current guess
    else if (Guess == WordToBeGuessed)
    {
        CurrentGuessOfWord = Guess;
        IsGuessCorrect = true;
    }

    return IsGuessCorrect;
}



void Display_Game_Over_Message(const unsigned int& NumberOfErrors,
                               const std::string& CurrentGuessOfWord,
                               const std::vector<std::string>& IncorrectGuesses,
                               const unsigned int& NumberOfTurns,
                               const std::string& WordToBeGuessed)
{
    Display_Game(NumberOfErrors, CurrentGuessOfWord, IncorrectGuesses);
    // If the below is true then hangman has reached its final state and thus user has lost
    if(NumberOfErrors == 10)
        std::cout << "Commisarations to the guesser, You lost!\nOnly took " << NumberOfTurns << " turns\nThe word was " << WordToBeGuessed << '\n';

    else
        std::cout << "Congratulations to the guesser, you won!\nOnly took " << NumberOfTurns << " turns" << '\n';
}
