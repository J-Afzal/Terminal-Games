## Game List:
* TicTacToe
* Hangman
* Battleships

## TicTacToe
* Supports 0-2 players
  * 2 players represent human vs human
  * 1 player represents a human vs computer
  * 0 players represent computer vs computer
* The computer is 'dumb' as it picks random positions
* The terminal is 'refreshed' using a method that is only supported on Windows

<p align="center">
 <img src="tictactoe/TicTacToe%20Playing.png" width=1000>
 <img src="tictactoe/TicTacToe%20Game%20Over.png" width=1000>
</p>

## Hangman
* Supports 0-2 players
  * 2 players represent human vs human
  * 1 player represents a human vs computer, with the human player deciding who the guesser is
  * 0 players represent computer vs computer
* No hyphens/spaces/non-letters are allowed in the word to be guessed
* Guessing with a word will count as one guess and will not replace any letters
* The computer is 'dumb' by either randomly picking a word from `hangman/Words.txt` or a random letter when guessing
* The terminal is 'refreshed' using a method that is only supported on Windows

<p align="center">
 <img src="hangman/Hangman%20Playing.png" width=1000>
 <img src="hangman/Hangman%20Game%20Over.png" width=1000>
</p>

## Battleships
* Supports 0-1 players
  * 2 players representing human vs human is NOT supported as impossible to practically hide the opponent's board when using a single terminal
  * 1 player represents a human vs computer
  * 0 players represent computer vs computer
* The computer is 'dumb' as it picks random positions to place its ships and random locations to attack ships
* The terminal is 'refreshed' using a method that is only supported on Windows

<p align="center">
 <img src="battleships/Battleships%20Playing.png" width=1000>
 <img src="battleships/Battleships%20Game%20Over.png" width=1000>
</p>

## Warning
Terminal 'refreshing' is only supported on Windows Command Prompt and Windows Powershell
