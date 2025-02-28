### code sample
# set cmake minimum required version
cmake_minimum_required(VERSION 3.16.0)
project(monte_carlo_tree_search)

set(CMAKE_CXX_STANDARD 20)

include_directories(src)
add_executable(tic_tac_toe src/main_tic_tac_toe.cpp src/TicTacToe.cpp )
