<p align="center"> <img src="screenshots/tictactoe/TicTacToe.gif" width=400> <img src="screenshots/hangman/Hangman.gif" width=400> </p>
<p align="center"> <img src="screenshots/battleships/Battleships.gif"> </p>

# About
Simple games that run in the terminal. The project is run by instantiating the `MainMenu` class and then calling its `Run()` method.
* For all games:
  * All menu and board navigation is done through the arrow keys
  * 2 players = human vs human, 1 player = human vs computer, and 0 players = computer vs computer
  * Easy AI = Random command/letter/move selection by computer (Hard AI has not been implemented yet)
* For Hangman:
  * The word to be guessed must be 3-14 characters long and contain only letters
  * Guesses can only be a single letter at a time
  * When guessing, you can use the up/down arrow keys to scroll through the available letters or press a letter key to select it (please note that pressing q here will quit the game)
* For Battleships:
  * Selecting ship positions must be done in either an incrementing or decrementing order with respect to the co-ordinates
  * Backspace can be used to undo a ship co-ordinate selection for a ship that has not been placed on the board

# Building [![CMake](https://github.com/J-Afzal/Terminal-Games/workflows/CMake/badge.svg)](https://github.com/J-Afzal/Terminal-Games/actions/workflows/cmake.yml)
Use the following CMake command in the project root directory:
```
cmake -S . -B build
```

# Warning
Due to the use of `Windows.h` and ANSI colour escape codes, this project only works on Windows using either the Visual Studio Terminal or the Visual Studio Code Integrated Powershell Terminal.