# My Games

### TicTacToe
The classic TicTacToe game with options to pick the number of users and which player the human user would like to be (X or O)
-   2 users represents two human players and thus no need to ask user which player they would like to be
-   1 user represents a human player vs the computer and so the human player is asked which player they would like to be (X or O)
-   0 users represents no human players and thus computer vs computer
-   The AI is 'dumb' as it picks random positions
-   The game is played through the function `Play_TicTacToe()`



### Hangman
The classic Hangman game where no hyphens or spaces are allowed in the word to be guessed. Also guessing a word will not replace any letters but just compare it with the word to be guessed. With each incorrect guess the hangman is drawn more until it is complete (after 10 incorrect guesses) or when the word has been guessed.
-   2 users represents two human players, with one creating the word and the other guessing the word
-   1 user represents one human player and one computer player, the human player is then asked who is guessing the word, and so all combinations of human and computer variants are possible
-   0 users represents zero human players and two computer players
-   The AI is 'dumb' and both randomly picks a word from Words.txt and a random letter when guessing
-   The game is played through the function `Play_Hangman()`



### Battleships
The classic Battleship game where human vs human is not coded for as difficult to keep the board information for each user separate.
-   2 users represents two human players which is not coded for
-   1 users represents one human player and one computer player
-   0 users represents zero human players and two computer players
-   The AI is 'dumb' and picks random locations to place ships and random locations to attack ships
-   The game is played through the function `Play_Battleships()` 

### To Do
-   CMake and CTest
-   Doxygen
-   TravisCI
-   Installer
