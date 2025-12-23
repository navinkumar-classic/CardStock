cmake_minimum_required(VERSION 3.29)
project(TurnCraft)

set(CMAKE_CXX_STANDARD 20)

add_executable(TurnCraft main.cpp
        src/Engine.cpp
        src/Card.cpp
        src/CardZone.cpp
        src/GameState.cpp
)
