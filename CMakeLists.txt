# This CMakeList file will create the Model library and its test code and CTests
cmake_minimum_required( VERSION 3.9.2 )

# The name of the project and its current version
project( My_Games VERSION 1.0.0 )

# This project contains many header files the "include_directories" sets the path for the header files to be located
include_directories( include )

# Required for automating testing with TravisCI
include ( CTest )



# Addition of the Libraries needs to have the required headers for each class that is included to ensure that the library is built correctly
add_library( TicTacToe    include/TicTacToe.hpp     source/TicTacToe.cpp )
add_library( Hangman      include/Hangman.hpp       source/Hangman.cpp )
add_library( Battleships  include/Battleships.hpp   source/Battleships.cpp )
add_library( Chess        include/Chess.hpp         source/Chess.cpp )



# This creates the .exe file for the play code
add_executable( PlayTicTacToe     main/PlayTicTacToe.cpp )
add_executable( PlayHangman       main/PlayHangman.cpp )
add_executable( PlayBattleships   main/PlayBattleships.cpp )
add_executable( PlayChess         main/PlayChess.cpp )

# This links the libraries to the .exe files
target_link_libraries( PlayTicTacToe     TicTacToe )
target_link_libraries( PlayHangman       Hangman )
target_link_libraries( PlayBattleships   Battleships )
target_link_libraries( PlayChess         Chess )

# Copy the resource files for My_Games play files in to the build directory
ADD_CUSTOM_COMMAND(TARGET PlayHangman POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy
		               ${CMAKE_CURRENT_SOURCE_DIR}/resources/Words.txt
                   ${CMAKE_CURRENT_SOURCE_DIR}/build/Debug/Words.txt )



# This creates the .exe file for the test code
add_executable( TestTicTacToe     testcode/TestTicTacToe.cpp )
add_executable( TestHangman     	testcode/TestHangman.cpp )
add_executable( TestBattleships 	testcode/TestBattleships.cpp )

# This links the libraries to the .exe file
target_link_libraries( TestTicTacToe    TicTacToe )
target_link_libraries( TestHangman     	Hangman )
target_link_libraries( TestBattleships 	Battleships)

# This creates the CTests
add_test( TestTicTacToe			TestTicTacToe )
add_test( TestHangman  			TestHangman )
add_test( TestBattleships		TestBattleships )

# Copy the resource files for My_Games test code files in to the build directory
ADD_CUSTOM_COMMAND(TARGET PlayHangman POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy
									 ${CMAKE_CURRENT_SOURCE_DIR}/resources/Words.txt
									 ${CMAKE_CURRENT_SOURCE_DIR}/build/Words.txt )






# "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x86_amd64
