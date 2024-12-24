#include <string>
#include <vector>

#include "helpers/MainMenu.hpp"

int main(int argc, char *argv[])
{
    TerminalGames::MainMenu MainMenu(std::vector<std::string>(argv, argv + argc)); // NOLINT(fuchsia-default-arguments-calls)
    MainMenu.Run();
}
