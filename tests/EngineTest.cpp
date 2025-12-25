#include <gtest/gtest.h>
#include <fstream>
#include "../include/Engine.h"

TEST(EngineTest, checkPlayerConfig) {
    std::ifstream f("../example/JSON/EngineConfig/EngineConfig_1.json");
    json j = json::parse(f);

    Engine game(j);

    EXPECT_EQ(3, game.playersSize());
    EXPECT_EQ(0, game.playersAt(0).getId());
    EXPECT_EQ(1, game.playersAt(1).getId());
    EXPECT_EQ(2, game.playersAt(2).getId());

    EXPECT_EQ("navin", game.playersAt(0).getName());
    EXPECT_EQ("vishal", game.playersAt(1).getName());
    EXPECT_EQ("sriram", game.playersAt(2).getName());

}