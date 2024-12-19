#include "helpers/MainMenu.hpp"

int main(int argc, char* argv[])
{

    MainMenu MainMenu(argc, argv);
    MainMenu.Run();
}

// TODO // cspell:disable
//
// YAML linting, JSON linting, powershell linting, gitattributes script checker,
//
// CI -  c++ linter, static analyser and build and doxygen generator, PowerShell unit testing
//
// Make terminal platform agnostic (i.e. fix CI) (and run in terminal using exe as test) (resize terminal to the required size) combine these two functions??? Why isn't console cursor thick?
//
// CD - build doxygen docs page, build exe with icon, and deploy to release (runs on push to master)
//
// Fix CMAKE build location and copy words.txt over and package as part of binary (read through CMAKE docs https://cmake.org/cmake/help/latest/manual/ and then https://learn.microsoft.com/en-gb/cpp/build/cmake-projects-in-visual-studio?view=msvc-170)
//
// Update README
//
// Re-org helpers into games? Add restart with same settings to game (update game over message)
//
// Clean up tictactoe (collapse to single while loop in Execute_Next_User_Command)
//
// Clean up hangman (gracefully handle words not found) (fix gif) (delete m_errorCount??) (const the numbers?) (show word to be guessed on first turn)
//
// Clean up battleships (fix gif with sped up version)
//
// Clean up getgamedisplay funcs (const and parameterise magic numbers and strings) (maybe implement grid system??)
//
// Standardise size of games
//
// Add unit test and add unit test runner to ci
//
