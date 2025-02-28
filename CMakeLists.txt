### code sample
# set cmake minimum required version
cmake_minimum_required(VERSION 3.16.0)
project(monte_carlo_tree_search)

set(CMAKE_CXX_STANDARD 20)

include_directories(src)
add_executable(${PROJECT_NAME} src/main.cpp src/TicTacToe.cpp )
