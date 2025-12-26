#include <gtest/gtest.h>
#include <fstream>
#include "../include/Engine.h"

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
