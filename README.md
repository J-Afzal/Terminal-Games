# Terminal Games

Simple games that run in the terminal.

## Getting Started

Binaries can be found in [Releases][releases] or, if preferred, CMake can be used to build the project from source either
through the PowerShell helper module:

```text
Import-Module ./modules/Build.psd1

Build-CppCodeUsingCMake -Platform windows-latest -BuildType Release -BuildDirectory build -Parallel 8 -Verbose

./build/terminal-games
```

or manually:

```text
git clone --recurse-submodules https://github.com/J-Afzal/Terminal-Games.git
cd Terminal-Games
cmake -S . -B ./build -D "CMAKE_BUILD_TYPE=Release"
cmake --build ./build --config Release

./build/terminal-games OR ./build/terminal-games.exe
```

> [!WARNING]
> If on Windows make sure to run the above within a Visual Studio Developer Command Prompt otherwise you may see errors around
> `cl.exe` not being found. Also, if on Windows make sure to add -G "NMake Makefiles" otherwise the required dlls may not be in
> the expected locations for the above instructions.

Here are the full list of options for Terminal Games:

```text
Usage: terminal-games [options]

OPTIONS:

Generic Options:

  -h --help         Display available options.

Optional Options:

  --a --ascii-only  Only use extended ASCII characters (this removes all colour).
```

## Documentation

Checkout the [documentation page][docs] built using Doxygen and hosted using Github pages.

![Documentation Homepage](./resources/screenshots/DocumentationHomepage.png)

## General Information

There is extensive use of ANSI colour escape codes which can be toggled off on the homepage if your terminal does not support
them. All major platforms (macOS, Linux and Windows) are supported however due to the use of `Windows.h` the user experience is
much better on Windows.

### Homepage

**Feature:** Can select whether to use ANSI colour escape codes.

![Homepage With ANSI Colour Escape Codes](./resources/screenshots/HomepageANSI.png "Homepage With ANSI Colour Escape Codes")

![Homepage Without ANSI Colour Escape Codes](./resources/screenshots/HomepageASCII.png "Homepage Without ANSI Colour Escape Codes")

### Main Menu

![Main Menu](./resources/screenshots/MainMenu.png "Main Menu")

### Quit Menu

**Feature:** Pressing the `q` key on any game screen will show the quit menu.

![Quit Menu](./resources/screenshots/QuitMenu.png "Quit Menu")

### Tic Tac Toe

**Supports:** 2 players (user vs user), 1 player (user vs computer) and 0 players (computer vs computer).

**Features:** The arrow keys on Windows or the `WASD` keys on other platforms can be used to navigate the board.

**Note:** The computer's choices are random.

![Tic Tac Toe](./resources/screenshots/TicTacToe.png "Tic Tac Toe")

### Hangman

**Supports:** 2 players (user vs user), 1 player (user vs computer) and 0 players (computer vs computer).

**Constraints:** The word to be guessed must be 3-16 characters long and can only contain letters. Only a single letter can be
guessed at a time.

**Features:** When guessing, you can use the up/down arrow keys on Windows or the `W`/`S` keys on other platforms to scroll
through the available letters, or press a letter key to select it (please note that pressing q here will show the quit menu).

**Note:** The computer's choices are random both when guessing letters and when selecting a word to be guessed from the
`G_HANGMAN_COMPUTER_WORDS` variable in `Globals.hpp`.

![Hangman](./resources/screenshots/Hangman.png "Hangman")

### Battleships

**Supports:** 1 player (user vs computer) and 0 players (computer vs computer).

**Features:** The arrow keys on Windows or the `WASD` on other platforms can be used to navigate the board. Selecting ship
positions can be done in either an incrementing or decrementing order with respect to the co-ordinates. Backspace on Windows or
the `Z` key on other platforms can be used to undo a ship co-ordinate selection for a ship that has not been completely placed
on the board.

**Note:** The computer's choices are random for both selecting where to place ships and where to attack.

![Battleships](./resources/screenshots/Battleships.png "Battleships")

## CI / CD

[![Continuous Integration][ci-badge]][ci-page] [![Continuous Deployment][cd-badge]][cd-page]

The continuous integration workflow runs against all commits on pull requests, builds the code, runs unit tests and performs
linting checks.

The continuous deployment workflow runs against all commits to main, builds the code and deploys the executables as a release.

## Development Setup

For development a few extra tools are needed to check for linting issues locally which include the [Linters][linters-repo]
submodule:

```text
git clone --recurse-submodules https://github.com/J-Afzal/Terminal-Games.git
```

The development dependencies are:

- Git
- PowerShell version >= 5
- npm dependencies via `npm install`
- clang-tidy >= 19 and clang-format >= 19
- CMake >= 3.20
- Ninja >= 1.12.1

All linting helper functions can be found in the [Linters][linters-repo] submodule.

Any generator can be used to build the project but to prior to running `clang-tidy`/`clang-format` CMake must be configured
using a generator that creates a `compile_commands.json` file in the build directory (e.g. `-G "Ninja"`, `-G "NMake Makefiles"`,
etc)

On windows, clang-tidy and clang-format can be installed using the `LLVM-x.x.x-win64.exe` binary from the
[LLVM release page][llvm-release-page] or from [chocolatey][llvm-chocolatey] using `choco install llvm -y`.

### IDE

On Windows, Visual Studio 2022 can be used by opening the folder as a CMake project and Visual Studio Code can be used by
opening the folder through the `Developer PowerShell for VS` (otherwise you may see errors around cl.exe not being found).

<!-- Link References -->

[releases]: https://github.com/J-Afzal/Terminal-Games/releases
[docs]: https://J-Afzal.github.io/Terminal-Games
[ci-badge]: https://github.com/J-Afzal/Terminal-Games/actions/workflows/ContinuousIntegration.yml/badge.svg
[ci-page]: https://github.com/J-Afzal/Terminal-Games/actions/workflows/ContinuousIntegration.yml
[cd-badge]: https://github.com/J-Afzal/Terminal-Games/actions/workflows/ContinuousDeployment.yml/badge.svg
[cd-page]: https://github.com/J-Afzal/Terminal-Games/actions/workflows/ContinuousDeployment.yml
[linters-repo]: https://github.com/J-Afzal/Linters
[llvm-release-page]: https://github.com/llvm/llvm-project/releases/tag/llvmorg-19.1.6
[llvm-chocolatey]: https://community.chocolatey.org/packages/llvm
