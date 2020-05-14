//
//  Chess.cpp
//  Chess
//
//  Created by Main on 07/01/2020.
//  Copyright © 2020 Junaid Afzal. All rights reserved.
//

#include "Chess.hpp"
#include <time.h>
#include <string>

void Play_Chess(void)
{
  std::vector< std::vector<std::string> > Board;
  unsigned int NumberOfPlayers;
  std::string HumanPlayer, CurrentPlayer;

  Setup_Game(Board, NumberOfPlayers, HumanPlayer, CurrentPlayer);

  while (!Game_Over())
  {
      Toggle_Player(CurrentPlayer);

      Display_Game(Board);

      std::string NextMove;

      switch (NumberOfPlayers)
      {
          case 0:
              NextMove = Ask_AI_For_Next_Move();
              break;

          case 1:
          {
              if (CurrentPlayer == HumanPlayer)
                  NextMove = Ask_User_For_Next_Move();

              else
                  NextMove = Ask_AI_For_Next_Move();

              break;
          }

          case 2:
              NextMove = Ask_User_For_Next_Move();
              break;

          default:
              std::cout << "Error in number of players switch statement" << '\n';
              break;
      }

      Execute_Next_Move();
  }

  Display_Game(Board);

  Display_Winning_Message();
}

void Test_Chess(void)
{

}

void Setup_Game(std::vector< std::vector<std::string> >& Board, unsigned int& NumberOfPlayers, std::string& HumanPlayer, std::string& CurrentPlayer)
{
    for (unsigned int i = 0; i < 8; i++)
    {
        std::vector<std::string> Rows;
        Board.push_back(Rows);

        for (unsigned int j = 0; j < 8; j++)
        {
            Board[i].push_back(".");

            if (i == 0)
                switch (j)
                {
                    case 0:
                        Board[i][j] = "BLACKROOK1";
                        break;

                    case 1:
                        Board[i][j] = "BLACKKNIGHT1";
                        break;

                    case 2:
                        Board[i][j] = "BLACKBISHOP1";
                        break;

                    case 3:
                        Board[i][j] = "BLACKQUEEN";
                        break;

                    case 4:
                        Board[i][j] = "BLACKKING";
                        break;

                    case 5:
                        Board[i][j] = "BLACKBISHOP2";
                        break;

                    case 6:
                        Board[i][j] = "BLACKKNIGHT2";
                        break;

                    case 7:
                        Board[i][j] = "BLACKROOK2";
                        break;

                    default:
                        std::cout << "Error in black pieces setup in Setup_Game()" << '\n';
                        break;
                }

            else if (i == 1)
                switch (j)
                {
                    case 0:
                        Board[i][j] = "BLACKPAWN1";
                        break;

                    case 1:
                        Board[i][j] = "BLACKPAWN2";
                        break;

                    case 2:
                        Board[i][j] = "BLACKPAWN3";
                        break;

                    case 3:
                        Board[i][j] = "BLACKPAWN4";
                        break;

                    case 4:
                        Board[i][j] = "BLACKPAWN5";
                        break;

                    case 5:
                        Board[i][j] = "BLACKPAWN6";
                        break;

                    case 6:
                        Board[i][j] = "BLACKPAWN7";
                        break;

                    case 7:
                        Board[i][j] = "BLACKPAWN8";
                        break;

                    default:
                        std::cout << "Error in black pawn setup in Setup_Game()" << '\n';
                        break;
                }

            else if (i == 6)
                switch (j)
                {
                    case 0:
                        Board[i][j] = "WHITEPAWN1";
                        break;

                    case 1:
                        Board[i][j] = "WHITEPAWN2";
                        break;

                    case 2:
                        Board[i][j] = "WHITEPAWN3";
                        break;

                    case 3:
                        Board[i][j] = "WHITEPAWN4";
                        break;

                    case 4:
                        Board[i][j] = "WHITEPAWN5";
                        break;

                    case 5:
                        Board[i][j] = "WHITEPAWN6";
                        break;

                    case 6:
                        Board[i][j] = "WHITEPAWN7";
                        break;

                    case 7:
                        Board[i][j] = "WHITEPAWN8";
                        break;

                    default:
                        std::cout << "Error in white pawn setup in Setup_Game()" << '\n';
                        break;
                }

            else if (i == 7)
                switch (j)
                {
                    case 0:
                        Board[i][j] = "WHITEROOK1";
                        break;

                    case 1:
                        Board[i][j] = "WHITEKNIGHT1";
                        break;

                    case 2:
                        Board[i][j] = "WHITEBISHOP1";
                        break;

                    case 3:
                        Board[i][j] = "WHITEQUEEN";
                        break;

                    case 4:
                        Board[i][j] = "WHITEKING";
                        break;

                    case 5:
                        Board[i][j] = "WHITEBISHOP2";
                        break;

                    case 6:
                        Board[i][j] = "WHITEKNIGHT2";
                        break;

                    case 7:
                        Board[i][j] = "WHITEROOK2";
                        break;

                    default:
                        std::cout << "Error in white pieces setup in Setup_Game()" << '\n';
                        break;
                }
        }
    }


    NumberOfPlayers = Ask_User_For_Number_Of_Players();

    std::srand((unsigned int)time(0));

    if (NumberOfPlayers == 1)
        HumanPlayer = "WHITE";

    if ((std::rand() % 2) == 0)
        CurrentPlayer = "WHITE";
    else
        CurrentPlayer = "BLACK";
}

int Ask_User_For_Number_Of_Players(void)
{
    bool isValueCorrect = false; // Flag for if input value in invalid
    unsigned int NumberOfPlayers = 0;

    while (!isValueCorrect)
    {
        // Prompt user for next command that will be the next grid position to attack
        std::cout << "Enter the number of human player: ";

        std::cin >> NumberOfPlayers;

        // Check if cin failed
        if (std::cin.fail())
        {
            // Clear buffer and retry
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            isValueCorrect = false;
            continue;
        }

        // Check if value is 0, 1 or 2
        if (NumberOfPlayers != 0 && NumberOfPlayers != 1 && NumberOfPlayers != 2)
            continue;

        // If all checks passed then value is valid
        else
            isValueCorrect = true;
    }

    // This is to clear .22222 in a value 5.22222 as value would assume to be 5
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return NumberOfPlayers;
}

bool Game_Over(void)
{
    //*******************************************************
    // Check if WK/BK are in check
    // and all possible moves result in check
    //*******************************************************

    return false;
}

bool Is_King_In_Check(void)
{
  return false;
}

void Toggle_Player(std::string& CurrentPlayer)
{
    if (CurrentPlayer == "BLACK")
        CurrentPlayer = "WHITE";
    else
        CurrentPlayer = "BLACK";
}

void Display_Game(const std::vector< std::vector<std::string> >& Board)
{
    // Solution to print errors = https://www.rapidtables.com/code/text/ascii-table.html

    for (unsigned int i = 0; i < 8; i++)
    {
        if (i == 0)
            std::cout << "    A B C D E F G H" << "\n\n";

        for (unsigned int j = 0; j < 8; j++)
        {
            if (j == 0)
                std::cout << 8 - i << "   ";


            if (Board[i][j] == "BLACKROOK1")
                std::cout << "\u2656 ";

            else if (Board[i][j] == "BLACKKNIGHT1")
                std::cout << "\u2658 ";

            else if (Board[i][j] == "BLACKBISHOP1")
                std::cout << "\u2657 ";

            else if (Board[i][j] == "BLACKQUEEN")
                std::cout << "\u2655 ";

            else if (Board[i][j] == "BLACKKING")
                std::cout << "\u2654 ";

            else if (Board[i][j] == "BLACKBISHOP2")
                std::cout << "\u2657 ";

            else if (Board[i][j] == "BLACKKNIGHT2")
                std::cout << "\u2658 ";

            else if (Board[i][j] == "BLACKROOK2")
                std::cout << "\u2656 ";

            else if (Board[i][j] == "BLACKPAWN1")
                std::cout << "\u2659 ";

            else if (Board[i][j] == "BLACKPAWN2")
                std::cout << "\u2659 ";

            else if (Board[i][j] == "BLACKPAWN3")
                std::cout << "\u2659 ";

            else if (Board[i][j] == "BLACKPAWN4")
                std::cout << "\u2659 ";

            else if (Board[i][j] == "BLACKPAWN5")
                std::cout << "\u2659 ";

            else if (Board[i][j] == "BLACKPAWN6")
                std::cout << "\u2659 ";

            else if (Board[i][j] == "BLACKPAWN7")
                std::cout << "\u2659 ";

            else if (Board[i][j] == "BLACKPAWN8")
                std::cout << "\u2659 ";


            else if (Board[i][j] == "WHITEROOK1")
                std::cout << "\u265C ";

            else if (Board[i][j] == "WHITEKNIGHT1")
                std::cout << "\u265E ";

            else if (Board[i][j] == "WHITEBISHOP1")
                std::cout << "\u265D ";

            else if (Board[i][j] == "WHITEQUEEN")
                std::cout << "\u265B ";

            else if (Board[i][j] == "WHITEKING")
                std::cout << "\u265A ";

            else if (Board[i][j] == "WHITEBISHOP2")
                std::cout << "\u265D ";

            else if (Board[i][j] == "WHITEKNIGHT2")
                std::cout << "\u265E ";

            else if (Board[i][j] == "WHITEROOK2")
                std::cout << "\u265C ";

            else if (Board[i][j] == "WHITEPAWN1")
                std::cout << "\u265F ";

            else if (Board[i][j] == "WHITEPAWN2")
                std::cout << "\u265F ";

            else if (Board[i][j] == "WHITEPAWN3")
                std::cout << "\u265F ";

            else if (Board[i][j] == "WHITEPAWN4")
                std::cout << "\u265F ";

            else if (Board[i][j] == "WHITEPAWN5")
                std::cout << "\u265F ";

            else if (Board[i][j] == "WHITEPAWN6")
                std::cout << "\u265F ";

            else if (Board[i][j] == "WHITEPAWN7")
                std::cout << "\u265F ";

            else if (Board[i][j] == "WHITEPAWN8")
                std::cout << "\u265F ";


            else
                std::cout << ". ";


            if (j == 7)
                std::cout << "   " << 8 - i;
        }

        std::cout << '\n';

        if (i == 7)
            std::cout << '\n' << "    A B C D E F G H" << "\n\n";
    }
}

std::string Ask_AI_For_Next_Move(const std::vector< std::vector<std::string> >& Board, const std::string& CurrentPlayer)
{
    bool isValueCorrect = false; // Flag for if input value in invalid
    std::string NextMove;

    while (!isValueCorrect)
    {
        std::string FirstWord, SecondWord;

        ChessPieceInt = std::rand() % 15;
        switch (ChessPieceInt)
        {
          case 0:
            FirstWord = ROOK1;
          break;

          case 0:
            FirstWord = KNIGHT1;
          break;

          case 0:
            FirstWord = BISHOP1;
          break;

          case 0:
            FirstWord = QUEEN;
          break;

          case 0:
            FirstWord = KING;
          break;

          case 0:
            FirstWord = BISHOP2;
          break;

          case 0:
            FirstWord = KNIGHT2;
          break;

          case 0:
            FirstWord = ROOK2;
          break;

          case 0:
            FirstWord = PAWN1;
          break;

          case 0:
            FirstWord = PAWN2;
          break;

          case 0:
            FirstWord = PAWN3;
          break;

          case 0:
            FirstWord = PAWN4;
          break;

          case 0:
            FirstWord = PAWN5;
          break;

          case 0:
            FirstWord = PAWN6;
          break;

          case 0:
            FirstWord = PAWN7;
          break;

          case 0:
            FirstWord = PAWN8;
          break;
        }

        SecondWord[0] = (std::rand() % 8) + 97;
        SecondWord[1] = (std::rand() % 8) + 49;

        if (!Is_Next_Move_Valid(Board, CurrentPlayer, FirstWord, SecondWord))
          continue;
    }

    return NextMove;
}

bool Is_Next_Move_Valid(const std::vector< std::vector<std::string> >& Board, const std::string& CurrentPlayer, const std::string& ChessPiece, const std::string& ChessPieceNewPosition)
{
  if (ChessPiece == ROOK1 || ChessPiece == ROOK2)
  {
    //*******************************************************
    // code to check if command is legal, using playername for colour so BLACKBISHOP1
    //*******************************************************

    std::string ChessPieceCurrentPosition;

    if (Is_King_In_Check())
      return false;
  }

  else if (ChessPiece == KNIGHT1 || ChessPiece == KNIGHT2)
  {
    //*******************************************************
    // code to check if command is legal, using playername for colour so BLACKBISHOP1
    //*******************************************************


    if (Is_King_In_Check())
      return false;
  }

  else if (ChessPiece == BISHOP1 || ChessPiece == BISHOP2)
  {
    //*******************************************************
    // code to check if command is legal, using playername for colour so BLACKBISHOP1
    //*******************************************************


    if (Is_King_In_Check())
      return false;

  }

  else if (ChessPiece == QUEEN)
  {
    //*******************************************************
    // code to check if command is legal, using playername for colour so BLACKBISHOP1
    //*******************************************************


    if (Is_King_In_Check())
      return false;
  }

  else if (ChessPiece == KING)
  {
    //*******************************************************
    // code to check if command is legal, using playername for colour so BLACKBISHOP1
    //*******************************************************


    if (Is_King_In_Check())
      return false;
  }

  else if (ChessPiece == PAWN1 || ChessPiece == PAWN2 || ChessPiece == PAWN3 || ChessPiece == PAWN4 || ChessPiece == PAWN5 || ChessPiece == PAWN6 || ChessPiece == PAWN7 || ChessPiece == PAWN8)
  {
    //*******************************************************
    // code to check if command is legal, using playername for colour so BLACKBISHOP1
    //*******************************************************


    if (Is_King_In_Check())
      return false;
  }

  return true;
}

std::string Ask_User_For_Next_Move(const std::vector< std::vector<std::string> >& Board, const std::string& CurrentPlayer)
{
    bool isValueCorrect = false; // Flag for if input value in invalid
    std::string NextMove;

    while (!isValueCorrect)
    {
        // Prompt user for next command that will be the next grid position to attack
        std::cout << "Enter your next move (e.g. BISHOP1 A6): ";

        getline(std::cin, NextMove);

        // Check if cin failed
        if (std::cin.fail())
        {
            // Clear buffer and retry
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        Capitalise_Word(NextMove);

        std::string FirstWord, SecondWord;

        for (unsigned int currentPosition = 0, spaceCount = 0; currentPosition < NextMove.size(); currentPosition++) //Iterate across the line
        {
            if (NextMove[currentPosition] == ' ') //If a space is reached then whatever is in 'Placeholder' must be read in
                spaceCount++; //Increment space count

            else if (spaceCount == 0)
                FirstWord.push_back(NextMove[currentPosition]); //If current position in current line is NOT a space then read in the value

            else
                SecondWord.push_back(NextMove[currentPosition]);
        }

        if (FirstWord != "KING" && FirstWord != "QUEEN" && FirstWord != "BISHOP1" && FirstWord != "BISHOP2" && FirstWord != "KNIGHT1" && FirstWord != "KNIGHT2" && FirstWord != "ROOK1" && FirstWord != "ROOK2"
         && FirstWord != "PAWN1" && FirstWord != "PAWN2" && FirstWord != "PAWN3" && FirstWord != "PAWN4" && FirstWord != "PAWN5" && FirstWord != "PAWN6" && FirstWord != "PAWN7" && FirstWord != "PAWN8")
            continue;

        if (SecondWord.size() != 2)
            continue;

        if (SecondWord[0] >= 97 && SecondWord[0] <= 104)
            continue;

        if (SecondWord[1] >= 49 && SecondWord[1] <= 56)
            continue;

        if (!Is_Next_Move_Valid(Board, CurrentPlayer, FirstWord, SecondWord))
          continue;
    }

    return NextMove;
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

void Execute_Next_Move()
{
  // update board and pawn rule if it reaches other end, maybe have captured pieces on other side
}

void Display_Winning_Message()
{
  // maybe while loop with option to quit and restart and add to other games
}
