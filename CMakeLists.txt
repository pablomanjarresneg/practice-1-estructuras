cmake_minimum_required(VERSION 4.1)
project(practice_1_estructuras)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(practice_1_estructuras
        src/balancedtree.cpp
        include/balancedtree.h
        src/heapsort.cpp
        include/heapsort.h
        src/quicksort.cpp
        include/quicksort.h
        main.cpp)
