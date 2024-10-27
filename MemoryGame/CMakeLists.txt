cmake_minimum_required(VERSION 3.28)
project(Testt)

set(CMAKE_CXX_STANDARD 17)

add_executable(Testt src/main.cpp
        src/headers/game.h
        src/game.cpp
        src/headers/utils.h
        src/utils.cpp)
