## Warning
This program has only been tested to run in the VS Code integrated powershell terminal on Windows due to the use of _getch(), Windows.h to refresh the terminal, and ANSI colour escape codes.

## Game List:
* Tic Tac Toe
* Hangman
* Battleships

## Tic Tac Toe
* Supports 0-2 players
  * 2 players represent human vs human
  * 1 player represents a human vs computer
  * 0 players represent computer vs computer
* AI Difficulty
  * Easy = random
  * Hard = minimax algorithm

<p align="center">
 <img src="screenshots/TicTacToe%20Playing.png" width=1000>
 <img src="screenshots/TicTacToe%20Game%20Over.png" width=1000>
</p>

## Hangman
* Supports 0-2 players
  * 2 players represent human vs human
  * 1 player represents a human vs computer, with the human player deciding who the guesser is
  * 0 players represent computer vs computer
* AI Difficulty
  * Easy = Random guessing and picks shorter words to guess from internal word list
  * Hard = Probabilistic guessing and pick longer words to guess from from internal word list
* No hyphens/spaces/non-letters are allowed in the word to be guessed and must be 3-14 characters long
* No guessing the whole word (only single letter guesses allowed)

<p align="center">
 <img src="screenshots/Hangman%20Playing.png" width=1000>
 <img src="screenshots/Hangman%20Game%20Over.png" width=1000>
</p>

## Battleships
* Supports 0-1 players
  * 2 players representing human vs human is NOT supported as impossible to practically hide the opponent's board when using a single terminal
  * 1 player represents a human vs computer
  * 0 players represent computer vs computer
* AI Difficulty
  * Easy = Random placement of ships and random guessing of attack locations
  * Hard = Same as Easy but once a successful attack has been made the AI then continues to attack in the area until that ship is sunk

<p align="center">
 <img src="screenshots/Battleships%20Playing.png" width=1000>
 <img src="screenshots/Battleships%20Game%20Over.png" width=1000>
</p>
