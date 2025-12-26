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

    EXPECT_EQ(j["players"][0], game.playersAt(0).toJson());
    EXPECT_EQ(j["players"][1], game.playersAt(1).toJson());
    EXPECT_EQ(j["players"][2], game.playersAt(2).toJson());
}

TEST(EngineTest, checkGameStateConfig) {
    std::ifstream f("../example/JSON/EngineConfig/EngineConfig_1.json");
    json j = json::parse(f);

    Engine game(j);

    EXPECT_EQ(j["gameState"], game.gameState.toJson());
}

TEST(EngineTest, checkCardZoneMap) {
    std::ifstream f("../example/JSON/EngineConfig/EngineConfig_1.json");
    json j = json::parse(f);

    Engine game(j);

    std::cout << game.cardZoneMap.toJson().dump(4) << std::endl;

    EXPECT_EQ(j["cardZoneMap"], game.cardZoneMap.toJson());
}

void test_1(Player& player, CardZoneMap& cardZoneMap, GameState& gameState) {
    player.state.set<int>("test_var", 99);
    gameState.set<int>("test_var", 99);
}

TEST(EngineTest, checkApplyAll) {
    std::ifstream f("../example/JSON/EngineConfig/EngineConfig_1.json");
    json j = json::parse(f);

    Engine game(j);

    game.applyToAllPlayers(test_1);

    EXPECT_EQ(99, game.gameState.get<int>("test_var"));

    EXPECT_EQ(99, game.playersAt(0).state.get<int>("test_var"));
    EXPECT_EQ(99, game.playersAt(1).state.get<int>("test_var"));
    EXPECT_EQ(99, game.playersAt(2).state.get<int>("test_var"));
}

TEST(EngineTest, checkApplyToPlayers) {
    std::ifstream f("../example/JSON/EngineConfig/EngineConfig_1.json");
    json j = json::parse(f);

    Engine game(j);

    game.applyToPlayers({0,2},test_1);

    EXPECT_EQ(99, game.gameState.get<int>("test_var"));

    EXPECT_EQ(99, game.playersAt(0).state.get<int>("test_var"));
    EXPECT_EQ(99, game.playersAt(2).state.get<int>("test_var"));

    EXPECT_FALSE(game.playersAt(1).state.has("test_var"));
}

TEST(EngineTest, checkApplyToPlayersExcept) {
    std::ifstream f("../example/JSON/EngineConfig/EngineConfig_1.json");
    json j = json::parse(f);

    Engine game(j);

    game.applyToAllPlayersExcept({0,2},test_1);

    EXPECT_EQ(99, game.gameState.get<int>("test_var"));

    EXPECT_EQ(99, game.playersAt(1).state.get<int>("test_var"));
    EXPECT_TRUE(game.playersAt(1).state.has("test_var"));
    EXPECT_FALSE(game.playersAt(0).state.has("test_var"));
    EXPECT_FALSE(game.playersAt(2).state.has("test_var"));
}
