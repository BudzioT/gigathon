cmake_minimum_required(VERSION 3.28)
project(consoleAnimation)

set(CMAKE_CXX_STANDARD 20)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(consoleAnimation
        src/main.cpp
        src/utils.h
        src/utils.cpp
        )
target_link_libraries(consoleAnimation ${OpenCV_LIBS} )