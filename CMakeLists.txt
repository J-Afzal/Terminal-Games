# This CMakeList file will create the Model library and its test code and CTests
cmake_minimum_required( VERSION 3.9.2 )

# The name of the project and its current version
project( My_Games VERSION 1.0.0 )

# This project contains many header files the "include_directories" sets the path for the header files to be located
include_directories( include )

# Addition of the Libraries needs to have the required headers for each class that is included to ensure that the library is built correctly
add_library( TicTacToe    include/TicTacToe.hpp     source/TicTacToe.cpp )
add_library( Hangman      include/Hangman.hpp       source/Hangman.cpp )
add_library( Battleships  include/Battleships.hpp   source/Battleships.cpp )
add_library( Chess        include/Chess.hpp         source/Chess.cpp )

# This creates the .exe file for each test code
add_executable( PlayTicTacToe     main/PlayTicTacToe.cpp )
add_executable( PlayHangman       main/PlayHangman.cpp )
add_executable( PlayBattleships   main/PlayBattleships.cpp )
add_executable( PlayChess         main/PlayChess.cpp )

# This links the libraries to the .exe file
target_link_libraries( PlayTicTacToe     TicTacToe )
target_link_libraries( PlayHangman       Hangman )
target_link_libraries( PlayBattleships   Battleships )
target_link_libraries( PlayChess         Chess )

# Required for automating testing with TravisCI
include ( CTest )

# Create the CTests


# Copy the resource files for My_Games in to the build directory
ADD_CUSTOM_COMMAND(TARGET PlayHangman POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy
		               ${CMAKE_CURRENT_SOURCE_DIR}/resources/Words.txt
                   ${CMAKE_CURRENT_SOURCE_DIR}/build/Debug/Words.txt )
