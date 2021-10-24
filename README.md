## Game List:
* TicTacToe
* Hangman
* Battleships
* Chess

## TicTacToe
<p align="center">
 <img src="https://github.com/J-Afzal/Terminal_Games/blob/master/screenshots/TicTacToe%20Playing.png">
</p>
<p align="center">
 <img src="https://github.com/J-Afzal/Terminal_Games/blob/master/screenshots/TicTacToe%20Game%20Over.png">
</p>

* Supports 0-2 players
  * 2 players represent human vs human
  * 1 player represents a human vs computer
  * 0 players represent computer vs computer
* The computer is 'dumb' as it picks random positions
* The terminal is 'refreshed' by printing 100 new lines

## Hangman
<p align="center">
 <img src="https://github.com/J-Afzal/Terminal_Games/blob/master/screenshots/Hangman%20Playing.png">
</p>
<p align="center">
 <img src="https://github.com/J-Afzal/Terminal_Games/blob/master/screenshots/Hangman%20Game%20Over.png">
</p>

* Supports 0-2 players
  * 2 players represent human vs human
  * 1 player represents a human vs computer, with the human player deciding who the guesser is
  * 0 players represent computer vs computer
* No hyphens/spaces/non-letters are allowed in the word to be guessed
* Guessing with a word will count as one guess and will not replace any letters
* The computer is 'dumb' by either randomly picking a word from `hangman/Words.txt` or a random letter when guessing
* The terminal is 'refreshed' by printing 100 new lines

## Battleships
<p align="center">
 <img src="https://github.com/J-Afzal/Terminal_Games/blob/master/screenshots/Battleships%20Playing.png">
</p>
<p align="center">
 <img src="https://github.com/J-Afzal/Terminal_Games/blob/master/screenshots/Battleships%20Game%20Over.png">
</p>

* Supports 0-1 players
  * 2 players representing human vs human is NOT supported as impossible to practically hide the opponent's board when using a single terminal
  * 1 player represents a human vs computer
  * 0 players represent computer vs computer
* The computer is 'dumb' as it picks random positions to place its ships and random locations to attack ships
* The terminal is 'refreshed' by printing 100 new lines
