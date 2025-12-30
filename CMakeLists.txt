cmake_minimum_required(VERSION 3.29)
project(CardStock)

set(CMAKE_CXX_STANDARD 20)

add_library(CardStockCore
        src/Engine.cpp
        src/Card.cpp
        src/CardZone.cpp
        src/GameState.cpp
        src/CardZoneMap.cpp
        src/TurnManager.cpp
        src/Player.cpp
        src/ActionHandler.cpp
        src/PlayerList.cpp
        src/EventManager.cpp
        util/Event.cpp
        util/Action.cpp
        src/EventsParser.cpp
        src/ActionsParser.cpp
        util/Effect.cpp
        util/Condition.cpp
)

add_executable(CardStock
        main.cpp
)

target_link_libraries(CardStock
        CardStockCore
)

include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(CardStockTests
        tests/GameStateTest.cpp
        tests/CardTest.cpp
        tests/CardZoneMapTest.cpp
        tests/CardZoneTest.cpp
        tests/TurnManagerTest.cpp
        tests/ActionHandlerTest.cpp
        tests/PlayerTest.cpp
        tests/EngineTest.cpp
        tests/PlayerListTest.cpp
        tests/EventManagerTest.cpp
        tests/ActionTest.cpp
        tests/EventTest.cpp
        tests/ConditionTest.cpp
        tests/EffectTest.cpp
)

target_link_libraries(CardStockTests
        CardStockCore
        gtest_main
)

include(GoogleTest)
gtest_discover_tests(CardStockTests)
