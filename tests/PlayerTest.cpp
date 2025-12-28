#include <gtest/gtest.h>
#include "../include/Player.h"
#include <fstream>

TEST(PlayerTest, addIdName) {
    Player p(1, "TestPlayer");

    EXPECT_EQ(1, p.getId());
    EXPECT_EQ("TestPlayer", p.getName());
}

TEST(PlayerTest, initFromJson) {
    std::ifstream f("../example/JSON/Player/Player_1.json");
    json j = json::parse(f);

    Player p(j);

    EXPECT_EQ(j["id"], p.getId());
    EXPECT_EQ(j["name"], p.getName());
    EXPECT_EQ(j["state"], p.state.toJson());
    EXPECT_EQ(j["cardZoneMap"], p.zoneMap.toJson());
}

TEST(PlayerTest, toJson) {
    std::ifstream f("../example/JSON/Player/Player_1.json");
    json j = json::parse(f);

    Player p(j);

    EXPECT_EQ(j, p.toJson());
}