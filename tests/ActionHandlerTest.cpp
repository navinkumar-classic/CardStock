#include <gtest/gtest.h>
#include "../include/ActionHandler.h"

std::pair<bool, std::vector<int>> test_cond_1(int x) {
    if (x > 10) return std::make_pair<bool, std::vector<int>>(true, {1});
    return std::make_pair<bool, std::vector<int>>(false, {-1});
}

std::pair<bool, std::vector<int>> test_cond_2(int x) {
    if (x > 5) return std::make_pair<bool, std::vector<int>>(true, {1});
    return std::make_pair<bool, std::vector<int>>(false, {-1});
}

std::pair<bool, std::vector<int>> test_cond_3(int x) {
    if (x < 10) return std::make_pair<bool, std::vector<int>>(true, {1});
    return std::make_pair<bool, std::vector<int>>(false, {-1});
}

bool test_action() {
    return true;
}

PlayerList players;
CardZoneMap cardZoneMap;
GameState gameState;

TEST(ActionHandler, addAction) {
    ActionHandler act;

    EXPECT_FALSE(act.execute("test_1", players, cardZoneMap, gameState, 0));

    EXPECT_TRUE(act.addAction("test_1", [](Player&, CardZoneMap&, GameState&){return test_cond_1(10);}, [](PlayerList&, CardZoneMap&, GameState&, int){return test_action();}));
    EXPECT_TRUE(act.execute("test_1", players, cardZoneMap, gameState, 0));
}

TEST(ActionHandler, disableReassignAction) {
    ActionHandler act;

    EXPECT_FALSE(act.execute("test_1", players, cardZoneMap, gameState, 0));

    EXPECT_TRUE(act.addAction("test_1", [](Player&, CardZoneMap&, GameState&){return test_cond_1(10);}, [](PlayerList&, CardZoneMap&, GameState&, int){return test_action();}));
    EXPECT_TRUE(act.execute("test_1", players, cardZoneMap, gameState, 0));

    EXPECT_FALSE(act.addAction("test_1", [&](Player&, CardZoneMap&, GameState&){return test_cond_2(10);}, [](PlayerList&, CardZoneMap&, GameState&, int){return test_action();}));
    EXPECT_TRUE(act.execute("test_1", players, cardZoneMap, gameState, 0));
}


TEST(ActionHandler, removeAction) {
    ActionHandler act;

    EXPECT_FALSE(act.execute("test_1", players, cardZoneMap, gameState, 0));

    EXPECT_TRUE(act.addAction("test_1", [](Player&, CardZoneMap&, GameState&){return test_cond_1(10);}, [](PlayerList&, CardZoneMap&, GameState&, int){return test_action();}));
    EXPECT_TRUE(act.execute("test_1", players, cardZoneMap, gameState, 0));

    EXPECT_TRUE(act.removeAction("test_1"));
    EXPECT_FALSE(act.execute("test_1", players, cardZoneMap, gameState, 0));
}

TEST(ActionHandler, removeNonExsistanceAction) {
    ActionHandler act;

    EXPECT_FALSE(act.removeAction("test_1"));
}


TEST(ActionHandler, checkValidAction) {

    ActionHandler act;

    const int x = 9;
    act.addAction("test_1", [&](Player&, CardZoneMap&, GameState&){return test_cond_1(x);}, [](PlayerList&, CardZoneMap&, GameState&, int){return test_action();});
    act.addAction("test_2", [&](Player&, CardZoneMap&, GameState&){return test_cond_2(x);}, [](PlayerList&, CardZoneMap&, GameState&, int){return test_action();});
    act.addAction("test_3", [&](Player&, CardZoneMap&, GameState&){return test_cond_3(x);}, [](PlayerList&, CardZoneMap&, GameState&, int){return test_action();});

    Player player(0, "navin");

    std::vector<std::pair<std::string, std::vector<int>>> res = act.getValidAction(player, cardZoneMap, gameState);

    auto hasAction = [&](const std::string& name) {
        return std::ranges::find_if(
            res,
            [&](const auto& p) { return p.first == name; }
        ) != res.end();
    };

    EXPECT_EQ(2, res.size());
    EXPECT_TRUE(hasAction("test_2"));
    EXPECT_TRUE(hasAction("test_3"));

}