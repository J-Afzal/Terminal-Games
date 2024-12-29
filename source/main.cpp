#include <string>
#include <vector>

#include "helpers/MainMenu.hpp"

int main(int argc, char *argv[])
{
    TerminalGames::MainMenu mainMenu(std::vector<std::string>(argv, argv + argc));
    mainMenu.Run();
}
