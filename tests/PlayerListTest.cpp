#include <gtest/gtest.h>
#include <fstream>
#include "../include/PlayerList.h"

void test_2(Player& player, CardZoneMap& cardZoneMap, GameState& gameState) {
    player.state.set<int>("test_var", 99);
    gameState.set<int>("test_var", 99);
}

TEST(PlayerListTest, checkApplyAll) {
    std::ifstream f("../example/JSON/PlayerList/PlayerList_1.json");
    json j = json::parse(f);

    PlayerList p;
    p.initFromJson(j);

    GameState gameState;
    CardZoneMap cardZoneMap;

    p.applyToAllPlayers(test_2, cardZoneMap, gameState);

    EXPECT_EQ(99, gameState.get<int>("test_var"));

    EXPECT_EQ(99, p.at(0).state.get<int>("test_var"));
    EXPECT_EQ(99, p.at(1).state.get<int>("test_var"));
    EXPECT_EQ(99, p.at(2).state.get<int>("test_var"));
}

TEST(PlayerListTest, checkApplyToPlayers) {
    std::ifstream f("../example/JSON/PlayerList/PlayerList_1.json");
    json j = json::parse(f);

    PlayerList p;
    p.initFromJson(j);

    GameState gameState;
    CardZoneMap cardZoneMap;

    p.applyToPlayers({0,2}, test_2, cardZoneMap, gameState);

    EXPECT_EQ(99, gameState.get<int>("test_var"));

    EXPECT_EQ(99, p.at(0).state.get<int>("test_var"));
    EXPECT_EQ(99, p.at(2).state.get<int>("test_var"));

    EXPECT_FALSE(p.at(1).state.has("test_var"));
}

TEST(PlayerListTest, checkApplyToPlayersExcept) {
    std::ifstream f("../example/JSON/PlayerList/PlayerList_1.json");
    json j = json::parse(f);

    PlayerList p;
    p.initFromJson(j);

    GameState gameState;
    CardZoneMap cardZoneMap;

    p.applyToAllPlayersExcept({0,2},test_2, cardZoneMap, gameState);

    EXPECT_EQ(99, gameState.get<int>("test_var"));

    EXPECT_EQ(99, p.at(1).state.get<int>("test_var"));
    EXPECT_TRUE(p.at(1).state.has("test_var"));
    EXPECT_FALSE(p.at(0).state.has("test_var"));
    EXPECT_FALSE(p.at(2).state.has("test_var"));
}

TEST(PlayerListTest, initFromJson) {
    std::ifstream f("../example/JSON/PlayerList/PlayerList_1.json");
    json j = json::parse(f);

    PlayerList p;
    p.initFromJson(j);

    EXPECT_EQ(3, p.size());
    EXPECT_EQ(0, p.at(0).getId());
    EXPECT_EQ(1, p.at(1).getId());
    EXPECT_EQ(2, p.at(2).getId());

    EXPECT_EQ("navin", p.at(0).getName());
    EXPECT_EQ("vishal", p.at(1).getName());
    EXPECT_EQ("sriram", p.at(2).getName());

    EXPECT_EQ(j[0], p.at(0).toJson());
    EXPECT_EQ(j[1], p.at(1).toJson());
    EXPECT_EQ(j[2], p.at(2).toJson());
}

TEST(PlayerListTest, toJson) {
    std::ifstream f("../example/JSON/PlayerList/PlayerList_1.json");
    json j = json::parse(f);

    PlayerList p;
    p.initFromJson(j);

    EXPECT_EQ(j, p.toJson());
}