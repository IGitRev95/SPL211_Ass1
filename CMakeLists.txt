cmake_minimum_required(VERSION 3.17)
project(SPL211_Ass1)

set(CMAKE_CXX_STANDARD 11)
include_directories(.)
add_executable(Ass1_new
        include/Agent.h
        include/Graph.h
        include/json.hpp
        src/main.cpp
        include/Session.h
        include/Tree.h
        src/Agent.cpp
        src/Graph.cpp
        src/Session.cpp
        src/Tree.cpp
        )