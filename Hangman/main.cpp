//
//  main.cpp
//  Hangman
//
//  Created by Main on 11/12/2019.
//  Copyright © 2019 Junaid Afzal. All rights reserved.
//

#include "Hangman.hpp"
#include <string>
#include <vector>

int main(void) {
    
    std::string Zero =  "\n\n\n\n\n\n \n\n";
    std::string One =   "\n\n\n\n\n\n+---+---+ \n\n";
    std::string Two =   "\n    |\n    |\n    |\n    |\n    |\n+---+---+ \n\n";
    std::string Three = "    +-------+\n    |\n    |\n    |\n    |\n    |\n+---+---+ \n\n";
    std::string Four =  "    +-------+\n    |       |\n    |\n    |\n    |\n    |\n+---+---+ \n\n";
    std::string Five =  "    +-------+\n    |       |\n    |       O\n    |\n    |\n    |\n+---+---+ \n\n";
    std::string Six =   "    +-------+\n    |       |\n    |       O\n    |       |\n    |\n    |\n+---+---+ \n\n";
    std::string Seven = "    +-------+\n    |       |\n    |       O\n    |       |\n    |      /\n    |\n+---+---+ \n\n";
    std::string Eight = "    +-------+\n    |       |\n    |       O\n    |       |\n    |      / \\\n    |\n+---+---+ \n\n";
    std::string Nine =  "    +-------+\n    |       |\n    |       O\n    |      /|\n    |      / \\\n    |\n+---+---+ \n\n";
    std::string Ten =   "    +-------+\n    |       |\n    |       O\n    |      /|\\\n    |      / \\\n    |\n+---+---+ \n\n";
    
    std::vector<std::string> HangmanStates;
    HangmanStates.push_back(Zero);
    HangmanStates.push_back(One);
    HangmanStates.push_back(Two);
    HangmanStates.push_back(Three);
    HangmanStates.push_back(Four);
    HangmanStates.push_back(Five);
    HangmanStates.push_back(Six);
    HangmanStates.push_back(Seven);
    HangmanStates.push_back(Eight);
    HangmanStates.push_back(Nine);
    HangmanStates.push_back(Ten);
    
    std::string WordToBeGuessed;
    unsigned int NumberOfErrors = 0;
    
    /*
    std::cout << "Hangman V1.0 by Junaid Afzal" << std::endl;
    std::cout << "\n" << std::endl;
    
    std::cout << "    +-------+     " << std::endl;
    std::cout << "    |       |     " << std::endl;
    std::cout << "    |       O     " << std::endl;
    std::cout << "    |      /|\\   " << std::endl;
    std::cout << "    |      / \\   " << std::endl;
    std::cout << "    |             " << std::endl;
    std::cout << "+---+---+         " << std::endl;
    std::cout << "\n" << std::endl;
    
    std::cout << "_ _ _ P _ _ _ E   " << std::endl;
    std::cout << "\n" << std::endl;
    
    std::cout << "Incorrect Guesses        " << std::endl;
    std::cout << "A   F   L   K   Z   T   I   O   K   L" << std::endl;
    std::cout << "\n" << std::endl;
    */
    
    return 0;
}
