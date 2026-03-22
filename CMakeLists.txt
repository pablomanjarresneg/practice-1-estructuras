cmake_minimum_required(VERSION 3.16)
project(practice_1_estructuras)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(practice_1_estructuras
        main.cpp
        src/quicksort.cpp
        src/heapsort.cpp
        src/balancedtree.cpp)

add_executable(dataset_generator
        src/dataset_generator.cpp)
