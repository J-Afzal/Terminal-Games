## Game List:
* TicTacToe
* Hangman
* Battleships

## TicTacToe
* Supports 0-2 players
  * 2 players represent human vs human
  * 1 player represents a human vs computer
  * 0 players represent computer vs computer
* AI Difficulty
  * Easy = random
  * Hard = minimax algorithm
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
* AI Difficulty
  * Easy = Random guessing and picks shorter words to guess from `hangman/Words.txt`
  * Hard = Probabilistic guessing and pick longer words to guess from `hangman/Words.txt`
* `hangman/Words.txt` contains some of the most common English words
* No hyphens/spaces/non-letters are allowed in the word to be guessed
* No guessing the whole word (only single letter guesses allowed)
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
