cmake_minimum_required(VERSION 3.17)
project(montador)

set(CMAKE_CXX_STANDARD 11)

include_directories(src/utils)

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(tests/lib)
