#include <gtest/gtest.h>

#include "../include/GameState.h"

TEST(GameStateTest, addElements) {
    GameState gs;

    gs.set<int>("int", 1);
    gs.set<float>("float", 1.101);
    gs.set<bool>("bool", true);
    gs.set<std::string>("string", "string");


    EXPECT_EQ(1, gs.get<int>("int"));
    EXPECT_EQ(1.101f, gs.get<float>("float"));
    EXPECT_EQ(true, gs.get<bool>("bool"));
    EXPECT_EQ("string", gs.get<std::string>("string"));
}

TEST(GameStateTest, removeElements) {
    GameState gs;

    gs.set<int>("int", 1);
    gs.set<float>("float", 1.101);
    gs.set<bool>("bool", true);
    gs.set<std::string>("string", "string");

    gs.remove("int");
    gs.remove("float");
    gs.remove("bool");
    gs.remove("string");

    EXPECT_EQ(std::nullopt, gs.get<int>("int"));
    EXPECT_EQ(std::nullopt, gs.get<float>("float"));
    EXPECT_EQ(std::nullopt, gs.get<bool>("bool"));
    EXPECT_EQ(std::nullopt, gs.get<std::string>("string"));

    EXPECT_FALSE(gs.has("int"));
    EXPECT_FALSE(gs.has("float"));
    EXPECT_FALSE(gs.has("bool"));
    EXPECT_FALSE(gs.has("string"));
}

TEST(GameStateTest, reAssignElements) {
    GameState gs;

    gs.set<int>("a", 1);
    gs.set<float>("b", 1.101);
    gs.set<bool>("c", true);
    gs.set<std::string>("d", "string");

    gs.set<int>("d", 1);
    gs.set<float>("c", 1.101);
    gs.set<bool>("b", true);
    gs.set<std::string>("a", "string");


    EXPECT_EQ(1, gs.get<int>("d"));
    EXPECT_EQ(1.101f, gs.get<float>("c"));
    EXPECT_EQ(true, gs.get<bool>("b"));
    EXPECT_EQ("string", gs.get<std::string>("a"));
}

TEST(GameStateTest, intitElementsFromJson) {
    auto j = R"(
    {
        "int": 1,
        "float": 1.101,
        "bool": true,
        "string": "string"
    }
    )"_json;

    GameState gs;
    gs.initFromJson(j);


    EXPECT_EQ(1, gs.get<int>("int"));
    EXPECT_EQ(1.101f, gs.get<float>("float"));
    EXPECT_EQ(true, gs.get<bool>("bool"));
    EXPECT_EQ("string", gs.get<std::string>("string"));
}

TEST(GameStateTest, elementsToJson) {
    auto j = R"(
    {
        "int": 1,
        "float": 1.101,
        "bool": true,
        "string": "string"
    }
    )"_json;

    GameState gs;
    gs.initFromJson(j);

    auto jt = gs.toJson();

    EXPECT_EQ(jt["int"], 1);
    EXPECT_NEAR(jt["float"].get<float>(), 1.101, 1e-6);
    EXPECT_EQ(jt["bool"], true);
    EXPECT_EQ(jt["string"], "string");
}

TEST(GameStateTest, elementsToString) {
    GameState gs;

    gs.set<int>("int", 1);
    gs.set<float>("float", 1.101);
    gs.set<bool>("bool", true);
    gs.set<std::string>("string", "string");


    EXPECT_EQ("1", gs.getAsString<int>("int"));
    EXPECT_EQ("1.101000", gs.getAsString<float>("float"));
    EXPECT_EQ("true", gs.getAsString<bool>("bool"));
    EXPECT_EQ("string", gs.getAsString<std::string>("string"));
}

TEST(GameStateTest, elementsApplyDelta) {
    GameState gs;

    gs.set<int>("int", 1);
    gs.set<float>("float", 1.101);

    gs.applyDelta<int>("int", 10);
    gs.applyDelta<float>("float", 1.101);


    EXPECT_EQ(11, gs.get<int>("int"));
    EXPECT_EQ(2.202f, gs.get<float>("float"));
}