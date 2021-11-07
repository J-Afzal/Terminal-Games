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
* The use of _getch() and terminal 'refreshing' method is only supported on Windows

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
* No hyphens/spaces/non-letters are allowed in the word to be guessed
* No guessing the whole word (only single letter guesses allowed)
* The use of _getch() and terminal 'refreshing' method is only supported on Windows

<p align="center">
 <img src="screenshots/Hangman%20Playing.png" width=1000>
 <img src="screenshots/Hangman%20Game%20Over.png" width=1000>
</p>

## Battleships
* Supports 0-1 players
  * 2 players representing human vs human is NOT supported as impossible to practically hide the opponent's board when using a single terminal
  * 1 player represents a human vs computer
  * 0 players represent computer vs computer
* The computer is 'dumb' as it picks random positions to place its ships and random locations to attack ships
* The use of _getch() and terminal 'refreshing' method is only supported on Windows

<p align="center">
 <img src="screenshots/Battleships%20Playing.png" width=1000>
 <img src="screenshots/Battleships%20Game%20Over.png" width=1000>
</p>
