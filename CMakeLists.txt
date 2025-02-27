### code sample 
# set cmake minimum required version
cmake_minimum_required(VERSION 3.10.0)
project(monte_carlo_tree_search)

#standard c++ 17
set(CMAKE_CXX_STANDARD 17)

include_directories(src)
add_executable(${PROJECT_NAME} src/main.cpp src/TicTacToe.cpp src/MonteCarloTreeSearch.cpp)

 
