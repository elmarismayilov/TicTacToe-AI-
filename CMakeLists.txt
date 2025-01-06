cmake_minimum_required(VERSION 3.29)
project(TicTacToeAI)

set(CMAKE_CXX_STANDARD 20)

add_executable(TicTacToeAI main.cpp)

find_package(SFML 2.6.1 COMPONENTS system window graphics network audio REQUIRED)
include_directories(/opt/homebrew/Cellar/sfml/2.6.1/include)
target_link_libraries(TicTacToeAI sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
