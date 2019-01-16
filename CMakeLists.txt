cmake_minimum_required(VERSION 3.12)
project(c___baum)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(c___baum
        main.cpp
        Trie.h)