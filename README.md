# My Games

### GameName
###### Overview
###### Assumptions

### TicTacToe
TicTacToe game with options to define the size of the grid - which will be assumed to be square. Also options for 0, 1 and 2 player modes - where 2 player = 2 human players; 1 player = 1 human player and one AI player; and 0 player = no human players and 2 AIs. The AI are dumb and make pseudo random moves. The game can be played through one function `Play_TicTacToe()`.

##### Improvements
* (https://www.rapidtables.com/code/text/unicode-characters.html) better visuals
* Better comments above
* size of grid to three and thus simplify code 
* Smarter AI
* remove V2.0



### Hangman
Hangman game where no hyphens or spaces allowed in the word to be guessed. The programs first asks the user for a word, then for the number of players, with one meaning an AI user will guess the word and 2 meaning a human user will guess the word. The user guessing the word is prompted for a guess and can handle a word or a letter guess. Note a word guess will not replace any letters but just compare the guess with the word to be guessed and the AI is dumb and randomly chooses a letter. With each incorrect guess the hangman is drawn more until it is complete (after 10 incorrect guesses) or the word has been guessed. The game can be played through one function `Play_Hangman()`.

##### Improvements
* (https://www.rapidtables.com/code/text/unicode-characters.html) better visuals
* Better comments above
* Dictionary file which will allow for 0 players and for AI to be the one not guessing
* maybe allow spaces and hyphens
* remove V2.0



### Battleships
Battleship game where a human user can play agaisnt the computer. The human user is asked for grid positions for each ship and then for the grid position the user next wants to attack. The AI is dumb and picks random location to place and attack ships. The game can be played through one function `Play_Battleships()`.

##### Improvements
* (https://www.rapidtables.com/code/text/unicode-characters.html) better visuals
* Better comments above
* int Column = UserCommand % GameData.size(); int Row = UserCommand / GameData.size(); 
* userBoard.size replaced with 10
* Smarter AI
* remove V2.0



### Pong

##### Improvements



### Snake

##### Improvements
